<?php

/**
 * @file
 * Prepare and manage vocabularies.
 */

/**
 * Creates vocabulary by its name and returns vocabulary object.
 *
 * @param $name
 *   (Optional) Name of vocabulary to create.
 *
 * @return
 *   Created vocabulary object.
 */
function taxonomy_csv_vocabulary_create($name = '') {
  $name = _taxonomy_csv_vocabulary_name_create($name);

  // Create an empty vocabulary. Relations and hierarchy are updated later.
  $vocabulary = array(
    'name'        => $name,
    'description' => t('Vocabulary created automatically by Taxonomy csv import/export module'),
    'help'        => '',
    'relations'   => TRUE,
    'hierarchy'   => 2,
    'multiple'    => TRUE,
    'required'    => FALSE,
    'tags'        => FALSE,
    'module'      => 'taxonomy',
    'weight'      => 0,
    'nodes'       => array(),
  );

  $result = taxonomy_save_vocabulary($vocabulary);

  return taxonomy_csv_vocabulary_load_name($vocabulary['name']);
}

/**
 * Duplicates a vocabulary object. If not exist, creates an empty vocabulary.
 *
 * @param $vocabulary_id
 *   Vocabulary id to duplicate.
 *
 * @return
 *   Duplicated vocabulary object.
 */
function taxonomy_csv_vocabulary_duplicate($vocabulary_id) {
  $original_vocabulary = taxonomy_vocabulary_load($vocabulary_id);
  if ($original_vocabulary) {
    // Creates an unused name.
    // Check if name begins with 'Copy of #name' in order to serialize name.
    $name = t('Copy of [!vocabulary_name]', array('!vocabulary_name' => $original_vocabulary->name));
    $name = _taxonomy_csv_vocabulary_name_create((strpos($original_vocabulary->name, $name) === FALSE) ? $name : $original_vocabulary->name);

    // Duplicate original vocabulary. Relations and hierarchy are updated later.
    $duplicated_vocabulary = array(
      'name'        => $name,
      'description' => $original_vocabulary->description,
      'help'        => $original_vocabulary->help,
      'relations'   => $original_vocabulary->relations,
      'hierarchy'   => $original_vocabulary->hierarchy,
      'multiple'    => $original_vocabulary->multiple,
      'required'    => $original_vocabulary->required,
      'tags'        => $original_vocabulary->tags,
      'module'      => $original_vocabulary->module,
      'weight'      => $original_vocabulary->weight,
      'nodes'       => array(),
    );

    $result = taxonomy_save_vocabulary($duplicated_vocabulary);

    $duplicated_vocabulary = taxonomy_csv_vocabulary_load_name($duplicated_vocabulary['name']);

    // Get all terms and attributes of original vocabulary and copy them in the
    // new one in two steps.
    $original_terms = taxonomy_get_tree($original_vocabulary->vid);

    // First step: copy each term except relations and parents.
    $duplicated_terms = array();
    foreach ($original_terms as $original_term) {
      $duplicated_terms[$original_term->tid] = (object) array(
        'vid'         => $duplicated_vocabulary->vid,
        'name'        => $original_term->name,
        'description' => $original_term->description,
        'weight'      => $original_term->weight,
        'synonyms'    => taxonomy_get_synonyms($original_term->tid),
      );
      // Term id is automatically memorized.
      $result = taxonomy_csv_term_save($duplicated_terms[$original_term->tid]);
    }

    // Second step: update duplicated terms with parents and relations.
    foreach ($original_terms as $original_term) {
      $duplicated_terms[$original_term->tid]->parents = array();
      foreach ($original_term->parents as $original_parent_tid) {
        if ($original_parent_tid != 0) {
          $duplicated_terms[$original_term->tid]->parents[] = $duplicated_terms[$original_parent_tid]->tid;
        }
      }
      $duplicated_terms[$original_term->tid]->relations = array();
      $original_related_terms = taxonomy_get_related($original_term->tid);
      foreach ($original_related_terms as $original_related_term) {
        $duplicated_terms[$original_term->tid]->relations[] = $duplicated_terms[$original_related_term->tid]->tid;
      }

      $result = taxonomy_csv_term_save($duplicated_terms[$original_term->tid]);
    }

    return $duplicated_vocabulary;
  }

  return taxonomy_csv_vocabulary_create();
}

/**
 * Helper to create an unused vocabulary name from a string.
 */
function _taxonomy_csv_vocabulary_name_create($name = '') {
  $name = preg_replace('/.csv$/', '', trim(basename(strval($name))));
  $name = (drupal_strlen($name) == 0) ?
    t('Auto created vocabulary') :
    // Limit to 250 characters.
    drupal_substr($name, 0, 250);

  // Invent a unused vocabulary name.
  if (taxonomy_csv_vocabulary_get_id($name)) {
    for ($i = 2; taxonomy_csv_vocabulary_get_id("$name $i"); $i++) {
    }
    $name = "$name $i";
  }

  return $name;
}

/**
 * Return vocabulary vid by its name or NULL if none.
 */
function taxonomy_csv_vocabulary_get_id($name) {
  if (is_string($name) && ($vocabularies = taxonomy_get_vocabularies())) {
    foreach ($vocabularies as $vocabulary) {
      if ($name == $vocabulary->name) {
        return $vocabulary->vid;
      }
    }
  }
}

/**
 * Return the vocabulary object matching a vocabulary name.
 */
function taxonomy_csv_vocabulary_load_name($name) {
  return taxonomy_vocabulary_load(taxonomy_csv_vocabulary_get_id($name));
}

/**
 * Check and update hierarchy flag of a given vocabulary.
 *
 * Drupal hierarchy check function bugs with vocabularies without hierarchy.
 *
 * @param $vocabulary
 *   The vocabulary array to check and to update.
 * @param $changed_term
 *   (Optional) Useless. Kept for compatibility with taxonomy D6 function.
 * @return
 *   Updated hierarchy level.
 */
function _taxonomy_csv_check_vocabulary_hierarchy($vocabulary, $changed_term = array('tid' => 0)) {
  $tree = taxonomy_get_tree($vocabulary['vid']);
  $hierarchy = 0;
  foreach ($tree as $term) {
    // Check this term's parent count.
    if (count($term->parents) > 1) {
      $hierarchy = 2;
      break;
    }
    // taxonomy.module l. 285 can't detect level 0 with '0 !== array_shift'.
    elseif (count($term->parents) == 1 && 0 != array_shift($term->parents)) {
      $hierarchy = 1;
    }
  }
  if ($hierarchy != $vocabulary['hierarchy']) {
    $vocabulary['hierarchy'] = $hierarchy;
    taxonomy_save_vocabulary($vocabulary);
  }

  return $hierarchy;
}

/**
 * Calculate number of terms in a vocabulary or in all vocabularies.
 *
 * @todo Regular query.
 *
 * @param $vocabulary_id
 *   (Optional) Id or array of ids of the chosen vocabularies. If not specified,
 *   count terms in all vocabularies.
 *
 * @return
 *   Number of terms in specified vocabularies or in all vocabularies.
 */
function taxonomy_csv_vocabulary_count_terms($vocabulary_id = 0) {
  $sql = "
    SELECT COUNT(*)
    FROM {term_data}
  ";

  $args = array();
  if ($vocabulary_id) {
    if (is_array($vocabulary_id)) {
      if (($vocabulary_id != array(0)) && ($vocabulary_id != array('0'))) {
        $sql .= ' WHERE vid IN (' . implode(',', $vocabulary_id) . ') ';
      }
    }
    else {
      $sql .= ' WHERE vid = %d ';
      $args[] = $vocabulary_id;
    }
  }

  return array_shift(db_fetch_array(db_query($sql, $args)));
}
