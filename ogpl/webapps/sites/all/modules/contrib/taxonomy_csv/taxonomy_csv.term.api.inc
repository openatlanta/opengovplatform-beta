<?php

/**
 * @file
 * Find, get and set full or detail term items.
 */

/**
 * Get a full term object by its id.
 *
 * @param $tid
 *   The term id to get.
 *
 * @return
 *   Found full term object.
 */
function taxonomy_csv_term_load($tid) {
  $term = db_fetch_object(db_query('
    SELECT t.*
    FROM {term_data} t
    WHERE t.tid = %d
    ',
    $tid
  ));

  return $term ?
      taxonomy_csv_term_get_full($term) :
      FALSE;
}

/**
 * Load multiple full terms.
 *
 * This function can be used whenever to get more than one term from the
 * database is needed. Terms have their links (parents, relations and synonyms).
 *
 * @param $tids
 *   (Optional) An array of taxonomy term IDs.
 * @param $conditions
 *   An array of conditions to add to the query.
 *   Currently managed conditions: vid and ascendant order.
 *
 * @return
 *   An array of term objects eventually ordered.
 */
function taxonomy_csv_term_load_multiple($tids = array(), $conditions = array()) {
  $terms = array();

  // Flag use to determine if select query has already conditions.
  $flag = FALSE;

  // Prepare query for terms to be loaded.
  $sql = '
    SELECT t.*
    FROM {term_data} t
  ';

  $args = array();

  if ($tids) {
    if (!is_array($tids)) {
      $tids = array($tids);
    }
    if ($tids != array(0) && $tids != array('0')) {
      $sql .= ' WHERE t.tid IN (' . implode(',', $tids) . ')';
      $flag = TRUE;
    }
  }

  if (isset($conditions['vid']) && $conditions['vid']) {
    if (is_array($conditions['vid'])) {
      if ($conditions['vid'] != array(0)) {
        $sql .= $flag ? ' AND ' : ' WHERE ';
        $sql .= 'vid IN (' . implode(',', $conditions['vid']) . ') ';
        $flag = TRUE;
      }
    }
    else {
      $sql .= $flag ? ' AND ' : ' WHERE ';
      $sql .= '(t.vid = %d)';
      $args[] = $conditions['vid'];
      $flag = TRUE;
    }
  }

  if (isset($conditions['order']) && $conditions['order']) {
    $sql .= ' ORDER BY %s ASC';
    $args[] = $conditions['order'];
  }

  $result = db_query($sql, $args);
  while ($term = db_fetch_object($result)) {
    $term = taxonomy_csv_term_get_full($term);
    $terms[$term->tid] = $term;
  }

  return $terms;
}

/**
 * Return an array of all term ids of a given vocabulary.
 *
 * @param $vid
 *   The vocabulary id from where to fetch term ids.
 *
 * @return
 *   Array of term ids.
 */
function taxonomy_csv_term_get_tids_from_vocabulary($vid) {
  $tids = array();

  $sql = '
    SELECT t.tid
    FROM {term_data} t
    WHERE t.vid = %d
  ';
  $args = array(
    $vid,
  );

  $result = db_query($sql, $args);
  while ($term = db_fetch_object($result)) {
    $tids[] = $term->tid;
  }

  return $tids;
}

/**
 * Complete a base term object.
 *
 * @param $term
 *   The base term object to complete.
 *
 * @return
 *   Found full term object.
 */
function taxonomy_csv_term_get_full($term) {
  if (isset($term->tid)) {
    $term->parents   = taxonomy_csv_term_get_parents_tids($term->tid);
    $term->relations = taxonomy_csv_term_get_relations_tids($term->tid);
    $term->synonyms  = taxonomy_get_synonyms($term->tid);

    // Check vocabulary because if there are specific fields, term needs to be
    // completed with them.
    $vocabulary_formats = taxonomy_csv_format_check_vocabulary($term->vid);
    foreach ($vocabulary_formats as $format) {
      $funcname = "taxonomy_csv_term_get_full_$format";
      $term = $funcname($term);
    }

    return $term;
  }
  // Else.

  return FALSE;
}

/**
 * Find and load a term.
 *
 * @param $term
 *   The term object to find. It's not necessarily a standard term object. It's
 *   an object which needs only a name and eventually a vid or a parent id. Of
 *   course, if tid is set, the found term is the existing one.
 * @param $all_vocabularies
 *   (Optional) Boolean. Search in all vocabularies or only in $term->vid
 *   vocabulary (default), which need to be set. Used with relations import.
 * @param $parent_tid
 *   (Optional) The direct parent term id where to restrict search.
 *   Used for structure import. Default to NULL (no parent restriction).
 *
 * @return
 *   Formatted found term object, or FALSE if not found or error.
 */
function taxonomy_csv_term_find($term, $all_vocabularies = FALSE, $parent_tid = NULL) {
  if (isset($term->tid) && $term->tid) {
    return taxonomy_csv_term_load($term->tid);
  }
  elseif (isset($term->name)) {
    $name = drupal_strtolower(trim($term->name));

    if (drupal_strlen($name)) {
      $sql = "
        SELECT t.*, h.parent
        FROM {term_data} t
        INNER JOIN {term_hierarchy} h ON t.tid = h.tid
        WHERE '%s' LIKE LOWER(t.name)
      ";
      $args = array();
      $args[] = $name;

      if (isset($term->vid)
          && $term->vid
          && !$all_vocabularies) {
        $sql .= ' AND t.vid = %d';
        $args[] = $term->vid;
      }

      if ($parent_tid) {
        $sql .= ' AND h.parent = %d';
        $args[] = $parent_tid;
      }

      $sql .= ' ORDER BY t.tid ASC LIMIT 1';

      $term = db_fetch_object(db_query($sql, $args));
      if ($term) {
        return taxonomy_csv_term_get_full($term);
      }
    }
  }

  // Not found, or error (neither tid nor name).
  return FALSE;
}

/**
 * Find duplicate terms in a vocabulary or in all vocabularies.
 *
 * @param $vid
 *  (Optional) Vocabulary to check in.
 *
 * @return
 *  An array of term names, indexed by tid.
 */
function taxonomy_csv_term_find_duplicate($vid = 0) {
  $terms = array();

  $sql = '
    SELECT t1.tid, t1.name
    FROM {term_data} t1
    LEFT OUTER JOIN {term_data} t2 ON t1.tid != t2.tid AND LOWER(t1.name) = LOWER(t2.name)
    WHERE t2.tid IS NOT NULL
  ';

  $args = array();

  if ($vid) {
    $sql .= ' AND t1.vid = %d AND t2.vid = %d ';
    $args[] = $vid;
    $args[] = $vid;
  }

  $sql .= ' ORDER BY t1.tid ASC ';

  $result = db_query($sql, $args);
  while ($term = db_fetch_object($result)) {
    $terms[$term->tid] = $term->name;
  }

  return $terms;
}

/**
 * Return an array of all parents term ids of a given term id.
 */
function taxonomy_csv_term_get_parents_tids($tid) {
  return array_keys(taxonomy_get_parents($tid));
}

/**
 * Return an array of all parents term names of a given term id.
 */
function taxonomy_csv_term_get_parents_names($tid) {
  return array_keys(taxonomy_get_parents($tid, 'name'));
}

/**
 * Return an array of all children term ids of a given term id.
 */
function taxonomy_csv_term_get_children_tids($tid) {
  return array_keys(taxonomy_get_children($tid));
}

/**
 * Return an array of all children term names of a given term id.
 */
function taxonomy_csv_term_get_children_names($tid) {
  return array_keys(taxonomy_get_children($tid, 0, 'name'));
}

/**
 * Return an array of all related term ids of a given term id.
 */
function taxonomy_csv_term_get_relations_tids($tid) {
  return array_keys(taxonomy_get_related($tid));
}

/**
 * Return an array of all related term names of a given term id.
 */
function taxonomy_csv_term_get_relations_names($tid) {
  return array_keys(taxonomy_get_related($tid, 'name'));
}

/**
 * Return the first path to the root of a term.
 *
 * @param $term
 *   A term object with parents attribute, as obtained with taxonomy_get_tree().
 * @param $tree
 *   A tree array as obtained with taxonomy_get_tree().
 *
 * @return
 *   Array of term objects matching to the path of a term to its root term.
 *   If a term is a root term, return an empty array.
 */
function taxonomy_csv_term_get_first_path($term, &$tree) {
  $path = array();

  // To use a counter prevents infinite loop when the hierarchy is inconsistent.
  $i = 0;
  while ($i < 100
      // A term root has no parent.
      && isset($term->parents)
      && !empty($term->parents)
      && $term->parents[0] <> 0
    ) {
    $tid = $term->parents[0];
    if ($tid > 0) {
      // Get the full term from the tree.
      foreach ($tree as $parent) {
        if ($parent->tid == $tid) {
          break;
        }
      }
      $path[] = $term = $parent;
    }
    else {
      break;
    }
    $i++;
  }

  // The path is reversed in order to begin with root term.
  return array_reverse($path);
}

/**
 * Save by reference an internally formatted term object.
 *
 * Drupal taxonomy_save_term uses a text area format to save synonyms.
 * This helper convert a synonym array into a string before using it.
 * It converts 'parents', such in Drupal 7, to 'parent' too.
 *
 * @param $term
 *   A term object to save by reference. Term is an object containing:
 *   - 'name'        : term name string,
 *   - 'vid'         : the vocabulary id,
 *   and eventually:
 *   - 'tid'         : term id in case of an update,
 *   - 'description' : description string,
 *   - 'weight'      : weight integer,
 *   - 'parents'     : array of first level parent tids,
 *   - 'relations'   : array of related tids,
 *   - 'synonyms'    : array of synonyms terms names strings,
 *
 * @return
 *   Status value (SAVED_NEW or SAVED_UPDATED). Term is updated with its tid.
 */
function taxonomy_csv_term_save(&$term) {
  $term_to_save = (array) $term;

  if (isset($term->synonyms)) {
    $term_to_save['synonyms'] = implode("\n", $term->synonyms);
  }

  if (isset($term->parents)) {
    $term_to_save['parent'] = $term->parents;
    unset($term_to_save['parents']);
  }
  else {
    $term_to_save['parent'] = array(0);
    $term->parents = array(0);
  }

  // Term is automaticaly updated, because it's used by reference.
  // Return either SAVED_NEW or SAVED_UPDATED.
  $result = taxonomy_save_term($term_to_save);

  // Update term.
  $term->tid = $term_to_save['tid'];

  return $result;
}

/**
 * Delete multiple terms.
 *
 * @param $tids
 *   (Optional) An array of taxonomy term IDs.
 *
 * @return
 *   TRUE.
 */
function taxonomy_csv_term_delete_multiple($tids = array()) {
  foreach ($tids as $tid) {
    taxonomy_del_term($tid);
  }
  return TRUE;
}
