<?php

/**
 * @file
 * Create taxonomy csv import form and validate user input.
 */

/**
 * Invoke associated files.
 * taxonomy_csv.import.api.inc is invoked only when form is submitted.
 */
  $module_dir = drupal_get_path('module', 'taxonomy_csv');
  require_once("$module_dir/taxonomy_csv.api.inc");

/**
 * Generates the taxonomy CSV import form.
 *
 * Form contain six fieldsets:
 * - 1. What to import ?
 *   - 1. Content of the source
 *   - 2. Keep order of terms by adding a weight
 * - 2. Where are items to import ?
 *   - 1. Source select
 *   - 2. Source file or text area
 * - 3. How is your source formatted ?
 *   - 1. Source delimiter
 *   - 2. Source enclosure
 *   - 3. Line and utf8 checks
 * - 4. Which vocabulary to import into (destination) ?
 *   - 1. Destination type
 *   - 2. Vocabulary choice
 *   - 3. Deletion of terms
 *   - 4. Vocabulary hierarchy set or check
 * - 5. When a term exist, what to do with it ?
 *   - 1. Previous or existing terms
 *   - 2. Specific import options depending on source content
 * - 6. Advanced options
 *   - 1. How to be notified
 *
 * As what will become existing terms depends on what is imported, dynamic
 * options are used: only possible parameters are shown. All options are
 * displayed if javascript is not activated.
 *
 * @ingroup forms
 * @see taxonomy_csv_form_import_validate()
 * @see taxonomy_csv_form_import_submit()
 * @see _taxonomy_csv_form_import_default_values_validate()
 * @see _taxonomy_csv_form_import_default_values_submit()
 */
function taxonomy_csv_form_import($form_state) {
  // Remember previous values to use specially when reloading form.
  // If not reloading form, use saved values if exist, else recommended ones.
  // Warning: specific values 'text', 'path' and 'url are not saved here.
  $list_recommended_values = _taxonomy_csv_values('import_default_ui');
  $list_previous_values = array();
  foreach ($list_recommended_values as $key => $value) {
    $list_previous_values[$key] = isset($form_state['values'][$key]) ?
      $form_state['values'][$key] :
      variable_get('taxonomy_csv_' . $key, $value);
  }

  $list_import_format = _taxonomy_csv_values('import_format');

  $list_external_format = taxonomy_csv_formats_get();

  $list_import_delimiter = array(
    'comma'            => t('« , » (Comma)'),
    'semicolon'        => t('« ; » (Semicolon)'),
    'tabulation'       => t('«   » (Tabulation)'),
    'pipe'             => t('« | » (Pipe)'),
    'space'            => t('«   » (Space)'),
    'currency_sign'    => t('« ¤ » (Currency sign)'),
    'soft_tab'         => t('«    » (Soft tab: two spaces or more)'),
    'custom_delimiter' => t('Custom delimiter'),
  );

  $list_import_enclosure = array(
    'none'             => t('None'),
    'quotation'        => t('« " » (Quotation mark)'),
    'quote'            => t("« ' » (Quote)"),
    'custom_enclosure' => t('Custom enclosure'),
  );

  $list_vocabularies = taxonomy_get_vocabularies();

  $list_vocabulary_target = array(
    'autocreate' => t('Autocreate a new vocabulary'),
    'duplicate'  => t('Duplicate an existing vocabulary'),
    'existing'   => t('Import in an existing vocabulary'),
  );

  $list_import_option = _taxonomy_csv_values('import_option');

  // Build form.

  // Needed to upload file.
  $form = array(
    '#attributes' => array(
      'enctype' => 'multipart/form-data',
    )
  );

  // Warn when modules incompatible with taxonomy_csv are enabled.
  // Problems can't be reproduced with a memory of 256 MB, even with big
  // taxonomies. Only pathauto slows down import process.
  // See http://drupal.org/node/495548
  // See http://drupal.org/node/447852
  // See http://drupal.org/node/540916 (Pathauto).
  $issues_modules = array(
    'taxonomynode',
    'taxonomy_vtn',
    'pathauto',
  );
  foreach ($issues_modules as $value) {
    if (module_exists($value) && empty($form_state['post'])) {
      drupal_set_message(t('<strong>Warning</strong>: An incompatible module is running.') . '<br />'
      . t('Memory or compatibility problems have been reported with these modules when under Drupal 6: !modules', array(
        '!modules' => '"' . implode('", "', $issues_modules) . '"',
      )) . '<br />'
      . t('It is advised to increase server and php memory temporary (no problem reported with 256 MB) or to disable these modules manually in !modules_section. Settings are not lost when you disable a module (and not uninstall it). After import process, you can decrease memory and reactivate modules.', array(
        '!modules_section' => l(t("modules section"), 'admin/build/modules'),
      )), 'warning');
      break;
    }
  }

  // Advertise that javascript is not enabled. Presume it is set by default.
  if (isset($_COOKIE['has_js']) && !$_COOKIE['has_js']) {
    $form['javascript'] = array(
      '#type'        => 'fieldset',
      '#title'       => t('WARNING'),
      '#collapsible' => TRUE,
      '#collapsed'   => FALSE,
    );
    $form['javascript']['info'] = array(
      '#type'        => 'item',
      '#title'       => t('Javascript is not activated!'),
      '#description' => t("As you see this notice, javascript is disabled on your browser. All fields are shown, but only those matching your choices needs to be set. Others won't be used. If you want specific examples and options, activate javascript or see <a href=\"!more_help_link\"> advanced help</a>.", array('!more_help_link' => url('admin/help/taxonomy_csv'))),
      '#required'    => TRUE,
    );
  }

  // Useless, but allows to keep closer Drupal 6 and Drupal 7 releases.
  $form['tab'] = array(
  //  '#type'        => 'vertical_tabs',
  //  '#default_tab' => 'format',
  );

  $form['tab']['format'] = array(
    '#type'        => 'fieldset',
    '#title'       => t('1. What do you want to import?'),
    '#collapsible' => TRUE,
    '#collapsed'   => FALSE,
    '#attributes'  => array('id' => 'format'),
  );

  $form['tab']['format']['import_format'] = array(
    '#type'          => 'select',
    '#title'         => '',
    '#options'       => $list_import_format,
    '#default_value' => $list_previous_values['import_format'],
  );

  if (!isset($_COOKIE['has_js']) || $_COOKIE['has_js']) {
    // Prepare descriptions.
    $line_format = '<br /><br />'
      . '<strong><em>' . t('Line format') . '</em></strong><br />'
      . '<code>';
    $example = '</code><br /><br />'
      . '<strong><em>' . t('Examples') . '</em></strong>'
      . '<ul><li><code>';
    $li = '</code></li><li><code>';
    $description_long = '</code></li></ul>';

    // Generic form for import format help.
    foreach ($list_import_format as $key => $value) {
      $form['tab']['format'][$key] = array(
        '#type'   => 'item',
        '#prefix' => '<div id="description_'. $key .'">',
        '#suffix' => '</div>',
      );

      // Complete generic form with specific help for external import formats.
      if (in_array($key, array_keys($list_external_format))) {
        $form['tab']['format'][$key]['#description'] = $list_external_format[$key]['description']
          . $line_format
            . $list_external_format[$key]['description_format']
          . $example
            . $list_external_format[$key]['description_example']
          . $description_long
            . $list_external_format[$key]['description_long'];
      }
    }

    // Complete generic form with specific help for each import format.
    $form['tab']['format'][TAXONOMY_CSV_FORMAT_ALONE_TERMS]['#description'] = t('Only the term in the first column of each line is imported. Additional columns are ignored.')
      . $line_format
        . t('term name')
      . $example
        . t('foo') . $li
        . t('bar')
      . $description_long;

    $form['tab']['format'][TAXONOMY_CSV_FORMAT_DEFINITION_LINKS]['#description'] = t('Allow to import full term definitions and links.')
      . $line_format
        . t('term name, term id, vocabulary id, term description, weight, number of synonyms, number of first level parents, number of first level children, number of related terms, list of synonyms, list of first level parents ids, list of first level children ids, list of related terms ids, list of vocabulary ids of related terms')
      . $example
        . t('foo, , , "Description of foo", 10, 1, 1, 2, 2, Synonym of foo, bar parent 1, bar child 1, bar child 2, bar related 1, bar related 2, , vocabulary of related 2') . $li
        . t('France, , Places, "A free country", 1, 1, 1, 3, 3, French Republic, Europe, Paris, Lyon, Vichy, USA, Japan, China') . $li
        . t('Japan, , Places, "An old country", 1, 1, 1, 2, 2, Land of the Rising Sun, Asia, Tokyo, Kyoto, China, France') . $li
        . t('China, , Places, "A big country", 2, 1, 1, 1, 2, Middle Kingdom, Asia, Beijing, Japan, France') . $li
        . t('Asia, , Places, "A large continent", 1, 0, 0, 2, 0, Japan, China')
      . $description_long
        . t('Only term name should be defined. Other values can be empty. Ids are not internal term ids or vocabulary ids, but a unique identifiant. Ids can be a number or a name. In most case, you can use true name. In fact, term ids need to be specific only for duplicate term names in order to identify each item. So for duplicates, you can use term name with a serial number. Main term id is only needed when term is a duplicate one.') . '<br />'
        . '<br />'
        . t('Note about vocabularies:') . '<br />'
        . t('With this import format, destination vocabulary is determined not only by the fourth group of options, but by the import source too.') . '<br />'
        . t('* If the third column is empty, null or "0", a vocabulary is autocreated, duplicated or used matching the destination vocabulary option. If the vocabulary of a related term is not defined, the vocabulary of the main term is used.') . '<br />'
        . t('* If the third column or the vocabulary of a related term is a name or a number, it has priority over destination vocabulary option:') . '<br />'
        . t("- When the matching vocabulary doesn't exist, a new vocabulary is created, regardless the destination vocabulary option.") . '<br />'
        . t("- When the matching vocabulary exists, it will be always used, regardless the destination option or the chosen vocabulary.") . '<br />'
        . '<br />'
        . t('Notes:') . '<br />'
        . t('- If a weight is defined for terms, do not use "Keep order of term" option.') . '<br />'
        . t('- If you use "Keep order of term" option, all terms, even parents, children and related, should have a line with a full definition.') . '<br />'
        . t("- It's not recommended to change the vocabulary of a term with links.") . '<br />'
        . t('- To make a relation between terms of different vocabularies is not allowed by the Drupal\'s default user interface for taxonomy, but is possible. Such a relation can be viewed with another UI, for example <a href="!link" title="Taxonomy manager module">Taxonomy manager</a>.', array(
          '!link' => url('http://drupal.org/project/taxonomy_manager'),
          ));

    $form['tab']['format'][TAXONOMY_CSV_FORMAT_FLAT]['#description'] = t('All items will be imported as terms.')
      . $line_format
        . t('term name, term 2 name, term 3 name...')
      . $example
        . t('foo, bar, name 3') . $li
        . t('France, UK, Belgium')
      . $description_long;

    $form['tab']['format'][TAXONOMY_CSV_FORMAT_TREE_STRUCTURE]['#description'] = t('Allow to create a tree structure (geography, classification...).')
      . $line_format
        . t('term name, child term name, sub-child term name...')
      . $example
        . t('foo, bar, small bar') . $li
        . t('Europe, France, Paris') . $li
        . t('Europe, France, Lyon') . $li
        . t('Europe, UK, London') . $li
        . t('America, USA, Washington') . $li
        . t(', , Hollywood')
      . $description_long
        . t('The first term is imported as a root level parent, the second as child of first term, the third as child of second term and so on. The lower child is the last term of a line. Others are hierarchical parents.') . '<br />'
        . t('To repeat previously imported items on each line is not needed: import process can manage one term by line.') . ' ' . t('If terms are repeated each line and lines are ordered, result and speed are same as with one term by line format.');

    $form['tab']['format'][TAXONOMY_CSV_FORMAT_POLYHIERARCHY]['#description'] = t('Allow to create a polyhierarchical structure (genealogy, complex nomenclatures...).')
      . $line_format
        . t('term name, child term name, sub-child term name...')
      . $example
        . t('foo, bar, small bar') . $li
        . t('Grand-Mother, Mother, Daughter') . $li
        . t('Grand-Father, Mother, Son') . $li
        . t('Grand-Mother 2, Father, Daughter') . $li
        . t('Grand-Father 2, Father, Son') . $li
        . t(', , Son 2') . $li
        . t(', Uncle') . $li
        . t('Grand-Mother 2, Uncle') . $li
        . t('Father, Son 3')
      . $description_long
        . t('The first term is imported as a root level parent, the second as child of first term, the third as child of second term and so on. The lower child is the last term of a line. Others are hierarchical parents.');

    $form['tab']['format'][TAXONOMY_CSV_FORMAT_PARENTS]['#description'] = t('Allow to create a polyhierarchical taxonomy (genealogy...).')
      . $line_format
        . t('term name, parent term name, parent term 2 name...')
      . $example
        . t('foo, bar, sibling bar') . $li
        . t('Daughter, Mother, Father') . $li
        . t('Son, Mother, Father') . $li
        . t('Son 2, Father') . $li
        . t('Son 3, Father') . $li
        . t('Mother, Grand-Mother, Grand-Father') . $li
        . t('Father, Grand-Mother 2, Grand-Father 2') . $li
        . t('Uncle, Grand-Mother 2, Grand-Father 2')
      . $description_long
        . t('First item is imported as a term and next ones as parents of first term. Unlike structure import, all parents are first level parents.');

    $form['tab']['format'][TAXONOMY_CSV_FORMAT_CHILDREN]['#description'] = t('Allow to create a polyhierarchical taxonomy (genealogy...).')
      . $line_format
        . t('term name, child term name, child term 2 name...')
      . $example
        . t('foo, bar, sibling bar') . $li
        . t('Mother, Daughter, Son') . $li
        . t('Father, Daughter, Son, Son 2, Son 3') . $li
        . t('Grand-Mother, Mother') . $li
        . t('Grand-Father, Mother') . $li
        . t('Grand-Mother 2, Father, Uncle') . $li
        . t('Grand-Father 2, Father, Uncle')
      . $description_long
        . t('First item is imported as a term and next ones as children of first term. Unlike structure import, all children are first level children.');

    $form['tab']['format'][TAXONOMY_CSV_FORMAT_RELATIONS]['#description'] = t('Allow to create relations between the term in the first column and next terms of the line.')
      . $line_format
        . t('term name, related term 1 name, related term 2 name...')
      . $example
        . t('foo, bar, bar 2') . $li
        . t('Baobab, Madagascar, Ghost')
      . $description_long;

    $form['tab']['format'][TAXONOMY_CSV_FORMAT_SYNONYMS]['#description'] = t('Allow to import synonyms of terms. Each line contains a term in the first column and next items are matching synonyms.')
      . $line_format
        . t('term name, synonym 1, synonym 2...')
      . $example
        . t('foo, bar, bar 2') . $li
        . t('"United Kingdom", "Great Britain", "England"')
      . $description_long;

    $form['tab']['format'][TAXONOMY_CSV_FORMAT_DEFINITIONS]['#description'] = t('Import a full term definition.')
      . $line_format
        . t('term name, weight, description, synonym 1, synonym 2...')
      . $example
        . t('foo, 10, description of foo, bar, bar 2') . $li
        . t('"United Kingdom", 50, "A European country", "Great Britain", "England"')
      . $description_long;

    $form['tab']['format'][TAXONOMY_CSV_FORMAT_DESCRIPTIONS]['#description'] = t('Allow to import descriptions of terms.')
      . $line_format
        . t('term name, description')
      . $example
        . t('foo, description of foo') . $li
        . t('"United Kingdom", "A European country"')
      . $description_long
        . t('The term is in the first column and the matching description is in the second column.');

    $form['tab']['format'][TAXONOMY_CSV_FORMAT_WEIGHTS]['#description'] = t('Allow to import a weight of a term.')
      . $line_format
        . t('term name, weight')
      . $example
        . t('foo, 12') . $li
        . t('"United Kingdom", 50')
      . $description_long
        . t('The term is in the first column and the matching weight is in the second column.') . '<br />'
        . t('Reminder: A weight cannot be higher than 50, unless you apply a <a href="http://drupal.org/node/612870">patch to Drupal</a>.');
  }
  $form['tab']['format']['info'] = array(
    '#type'        => 'item',
    '#description' => t('See <a href="!more_help_link">advanced help</a> for more informations about import types.', array('!more_help_link' => url('admin/help/taxonomy_csv'))),
  );

  // Specific options.
  // Specific options to Related terms.
  $form['tab']['format']['specific'][TAXONOMY_CSV_FORMAT_RELATIONS] = array(
    '#type'        => 'fieldset',
    '#title'       => t('Specific settings of "') . ' ' . t('Related terms') . '"',
    '#collapsible' => TRUE,
    '#collapsed'   => FALSE,
    '#description' => t('Set these options only if you import:') . ' ' . t('Related terms') . ' .',
    '#attributes'  => array('id' => 'edit-relations'),
  );
  $form['tab']['format']['specific'][TAXONOMY_CSV_FORMAT_RELATIONS]['relations_create_subrelations'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Import subrelations'),
    '#default_value' => $list_previous_values['relations_create_subrelations'],
    '#description'   => t('This checkbox allows to import subrelations of related terms and not only relations of first column term with others.') . '<br />'
      . t('For example, with the line < <code>"Paris", "London", "Bern", "Roma"</code> >, default import is to make a link between < <code>Paris</code> > and each of three terms. There is no link between < <code>London</code> > and < <code>Bern</code> > nor < <code>Roma</code> >. Checking this option creates not only relations with first term, but all subrelations too: < <code>London</code> > and < <code>Bern</code> >, < <code>London</code> > and < <code>Roma</code> > and finally < <code>Bern</code> > and < <code>Roma</code> >.'),
  );
  // Internal use only.
  $form['tab']['format']['specific'][TAXONOMY_CSV_FORMAT_RELATIONS]['relations_all_vocabularies'] = array(
    '#type'          => 'value',
    '#title'         => t('Make relations with existing terms of all vocabularies'),
    '#default_value' => $list_previous_values['relations_all_vocabularies'],
    '#description'   => t("This checkbox allows to create relations with existing terms in other vocabularies if they don't exist in selected vocabulary."),
    '#disabled'      => TRUE,
  );

  // External specific options.
  // @todo when needed.
  // foreach ($list_external_format as $key => $value) {
  // }

  $form['tab']['format']['keep_order'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Keep order of terms'),
    '#default_value' => $list_previous_values['keep_order'],
    '#description'   => t('If checked, a weight will be added to each term, so order of lines will be preserved. If unchecked, order will be alphabetic.') . '<br />' .
    t('Note: With polyhierarchical vocabulary (multiple parents for a term) and duplicate terms, unpredictable results may occur, because weight of a term is incremented each time it appears and a term can only have one weight, without context.') . '<br />' .
    t('Note: If you want to keep order of more than 50 terms, you need to apply a <a href="http://drupal.org/node/612870">patch to Drupal</a> to avoid a <a href="http://drupal.org/node/1248926">limitation</a>.'),
  );

  $form['tab']['import'] = array(
    '#type'        => 'fieldset',
    '#title'       => t('2. Where are items to import?'),
    '#collapsible' => TRUE,
    '#collapsed'   => FALSE,
    '#attributes'  => array('id' => 'import'),
  );

  $form['tab']['import']['source_choice'] = array(
    '#type'          => 'select',
    '#title'         => '',
    '#options'       => array(
      'text' => t('In the below text area'),
      'file' => t('In a local file'),
      'url'  => t('In a distant file'),
    ),
    '#default_value' => $list_previous_values['source_choice'],
  );

  $form['tab']['import']['text'] = array(
    '#type'          => 'textarea',
    '#title'         => t('Terms to import'),
    '#rows'          => 5,
    '#cols'          => 80,
    '#default_value' => isset($form_state['values']['text']) ?
        $form_state['values']['text'] :
        '',
    '#description'   => t('Write your csv formatted terms directly in this text area.'),
  );

  $form['tab']['import']['file'] = array(
    '#type'          => 'file',
    '#title'         => t('CSV file'),
    '#description'   => t('Browse to the file') . '<br >'
      . (($max_size = parse_size(ini_get('upload_max_filesize'))) ?
          t('Due to server restrictions, the <strong>maximum upload file size is !max_size</strong>. Files that exceed this size will be disregarded.', array('!max_size' => format_size($max_size))) . '<br >'
          . t('Use "distant file" import to go beyond, even with local file.') :
          ''),
  );

  $form['tab']['import']['url'] = array(
    '#type'          => 'textfield',
    '#title'         => t('CSV file'),
    '#description'   => t('Enter the url (http, ftp, file, path...)'),
  );

  $form['tab']['csv_format'] = array(
    '#type'        => 'fieldset',
    '#title'       => t('3. How is your source formatted?'),
    '#description' => t('Default delimiter is a comma ("<strong><code>,</code></strong>"). Default enclosure is none, but quotation mark ("<strong><code>"</code></strong>") is automatically managed.') . '<br />'
      . t('Notice') . ': ' . t('Either you import terms by a file or by a text area, the csv format is the same.') . '<br />'
      . '<strong>' . t('Warning') . '</strong>: ' . t('You should enclose any item beginning with a non-ascii letter, such as "É", "ç", "œ" or any non-latin letter.'),
    '#collapsible' => TRUE,
    '#collapsed'   => TRUE,
    '#attributes'  => array('id' => 'csv_format'),
  );

  $form['tab']['csv_format']['import_delimiter'] = array(
    '#type'          => 'select',
    '#title'         => t('CSV value delimiter'),
    '#options'       => $list_import_delimiter,
    '#default_value' => $list_previous_values['import_delimiter'],
    '#description'   => t("Choose the delimiter used in the CSV file you want to import. Tabulation can't be used with text area import."),
    '#attributes'    => array('id' => 'delimiter'),
  );

  $form['tab']['csv_format']['import_delimiter_soft_tab_width'] = array(
    '#type'          => 'select',
    '#title'         => t('Soft tab width'),
    '#options'       => array(
      2 => 2,
      3 => 3,
      4 => 4,
      5 => 5,
      6 => 6,
      7 => 7,
      8 => 8,
      9 => 9,
    ),
    '#default_value' => $list_previous_values['import_delimiter_soft_tab_width'],
    '#description'   => t("Specify number of spaces of the soft tab delimiter. These spaces will be replaced with a true tab."),
  );

  $form['tab']['csv_format']['import_delimiter_custom'] = array(
    '#type'          => 'textfield',
    '#title'         => 'Custom delimiter',
    '#default_value' => $list_previous_values['import_delimiter_custom'],
    '#size'          => 2,
    '#maxlength'     => 1,
    '#description'   => t('Specify your custom delimiter.'),
  );

  $form['tab']['csv_format']['import_enclosure'] = array(
    '#type'          => 'select',
    '#title'         => t('CSV value enclosure'),
    '#options'       => $list_import_enclosure,
    '#default_value' => $list_previous_values['import_enclosure'],
    '#description'   => t('Choose the enclosure used in the CSV file you want to import.'),
    '#attributes'    => array('id' => 'enclosure'),
  );

  $form['tab']['csv_format']['import_enclosure_custom'] = array(
    '#type'          => 'textfield',
    '#title'         => 'Custom enclosure',
    '#default_value' => $list_previous_values['import_enclosure_custom'],
    '#size'          => 2,
    '#maxlength'     => 1,
    '#description'   => t('Specify your custom enclosure.'),
  );

  $form['tab']['csv_format']['check_line'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Check lines'),
    '#default_value' => $list_previous_values['check_line'],
    '#description'   => t('Format of each line of your input (order of items, format of names, duplicate terms...) can be checked if you are not sure of your vocabulary.'),
  );

  $form['tab']['csv_format']['check_utf8'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Check UTF-8 format'),
    '#description'   => t('File needs to be UTF-8 formatted. You can disable this check if you are sure that your file is encoded correctly. Desactivation is needed with some server configurations too. This option is not used with a textarea import.') . ' '
      . t('ISO-8859-1 and ISO-8859-15 files are automatically converted.'),
  );
  if (function_exists('mb_detect_encoding')) {
    $form['tab']['csv_format']['check_utf8']['#default_value'] = $list_previous_values['check_utf8'];
  }
  else {
    $form['tab']['csv_format']['check_utf8']['#default_value'] = FALSE;
    $form['tab']['csv_format']['check_utf8']['#disabled'] = TRUE;
    $form['tab']['csv_format']['check_utf8']['#description'] .= t('This checkbox is currently disabled, because iconv, GNU recode or mbstring for PHP are not installed on your server.');
  }

  $form['tab']['csv_format']['locale_custom'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Manually set locale of the file'),
    '#default_value' => $list_previous_values['locale_custom'],
    '#size'          => 60,
    '#maxlength'     => 255,
    '#description'   => t('To set locale can resolve some import issues related to file or database. Choose the locale you use, for example "<code>en_DK.utf8</code>", and it will be automatically set before import and reset after. Let empty when no problem occurs: import will use your default locale.'),
  );

  $form['tab']['destination'] = array(
    '#type'        => 'fieldset',
    '#title'       => t('4. Which vocabulary do you want to import into?'),
    '#collapsible' => TRUE,
    '#collapsed'   => TRUE,
    '#description' => t('Terms can be imported into a new vocabulary or in an existing one. You can choose to duplicate an existing vocabulary too in order to check import. You might want to !add-new-vocab.', array(
        '!add-new-vocab' => l(t('add a new vocabulary'), 'admin/content/taxonomy/add/vocabulary', array('query' => drupal_get_destination())),
      )) . '<br />'
      . t('With some import formats as "Fields and links", vocabulary destination is defined by source content and this option is not used.'),
    '#attributes'  => array('id' => 'destination'),
  );

  if (count($list_vocabularies) == 0) {
    $form['tab']['destination']['#description'] .= '<br /><br />'
      . t("As there isn't any vocabulary, terms will be imported in a new automatically created vocabulary.");

    $form['tab']['destination']['vocabulary_target'] = array(
      '#type'  => 'value',
      '#value' => 'autocreate',
    );

    $form['tab']['destination']['vocabulary_id'] = array(
      '#type'  => 'value',
      '#value' => 0,
    );
  }
  else {
    $form['tab']['destination']['vocabulary_target'] = array(
      '#type'          => 'select',
      '#options'       => $list_vocabulary_target,
      '#default_value' => $list_previous_values['vocabulary_target'],
      '#description'   => t('Choose the vocabulary where you want to import your items.'),
    );

    $form['tab']['destination']['vocabulary_id'] = array(
      '#type'          => 'select',
      '#title'         => t('Vocabulary choice'),
      '#options'       => array(
        0 => t('[Choose an existing vocabulary]'),
      ),
      '#default_value' => $list_previous_values['vocabulary_id'],
      '#description'   => t('The vocabulary you want to import the file into.'),
    );
    foreach ($list_vocabularies as $vocabulary) {
      $form['tab']['destination']['vocabulary_id']['#options'][$vocabulary->vid] = $vocabulary->name;
    }
  }

  $form['tab']['destination']['delete_terms'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Automatically delete all terms of the selected vocabulary before import'),
    '#default_value' => $list_previous_values['delete_terms'],
    '#description'   => t("Warning: You won't be warned before deletion."),
  );

  $form['tab']['destination']['info_hierarchy'] = array(
    '#type'        => 'item',
    '#title'       => t('What is the type of vocabulary?'),
  );
  $form['tab']['destination']['check_hierarchy'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Automatically check vocabulary hierarchy'),
    '#default_value' => $list_previous_values['check_hierarchy'],
    '#description'   => t('Warning: to calculate true hierarchy of vocabulary is memory intensive. Choose to check automatically only if your vocabulary is little.'),
  );
  $form['tab']['destination']['set_hierarchy'] = array(
    '#type'          => 'radios',
    '#title'         => '',
    '#options'       => array(
      0 => t('no parent (flat)'),
      1 => t('single parent (tree)'),
      2 => t('multiple parents (polyhierarchy)'),
    ),
    '#default_value' => $list_previous_values['set_hierarchy'],
    '#prefix'        => '<div id="set_hierarchy">',
    '#suffix'        => '</div>',
  );

  $form['tab']['import_options'] = array(
    '#type'        => 'fieldset',
    '#title'       => t('5. When a term exists, what to do with it?'),
    '#collapsible' => TRUE,
    '#collapsed'   => TRUE,
    '#description' => t('What will existing term become when a term with same name will be imported?'),
    '#attributes'  => array('id' => 'import_options'),
  );

  if (!isset($_COOKIE['has_js']) || $_COOKIE['has_js']) {
    $list_import_allowed = _taxonomy_csv_values('import_allowed');
    foreach ($list_import_format as $key => $value) {
      $form['tab']['import_options']["existing_items_$key"] = array(
        '#type'          => 'radios',
        '#options'       => array_intersect_key($list_import_option, array_flip($list_import_allowed[$key])),
        '#default_value' => $list_previous_values['existing_items'],
        '#description'   => '',
        '#prefix'      => '<div id="existing_items_'. $key .'">',
        '#suffix'      => '</div>',
      );
      // Preselection if import format has only one option.
      if (count($form['tab']['import_options']["existing_items_$key"]['#options']) == 1) {
        $options = array_keys($form['tab']['import_options']["existing_items_$key"]['#options']);
        $form['tab']['import_options']["existing_items_$key"]['#default_value'] = array_pop($options);
      }
    }

    // Generic form for import format help.
    foreach ($list_import_format as $key => $value) {
      $form['tab']['import_options'][$key] = array(
        '#type'   => 'item',
        '#value'  => t('Help for import format:') . ' ' . $value,
        '#prefix' => '<div id="help_'. $key .'">',
        '#suffix' => '</div>',
      );

      // Complete generic form with specific help for external import formats.
      if (in_array($key, array_keys($list_external_format))) {
        $form['tab']['import_options'][$key]['#description'] = $list_external_format[$key]['import_options_help'];
      }
    }

    // Complete generic form with specific help for each import format.
    $form['tab']['import_options'][TAXONOMY_CSV_FORMAT_ALONE_TERMS]['#description'] = t('This option indicates whether existing terms with the same name should be updated or ignored. If ignored, duplicates may be created.');

    $form['tab']['import_options'][TAXONOMY_CSV_FORMAT_DEFINITION_LINKS]['#description'] = t('This option indicates whether and how existing terms with the same name should be updated or ignored.') . '<br />'
      . t('By nature, only one option can be chosen with this format.') . '<br />'
      . '<ul>
          <li>' . t('"<em>Update"</em>: update term and merge eventual item with new one.') . '</li>
        </ul>';

    $form['tab']['import_options'][TAXONOMY_CSV_FORMAT_FLAT]['#description'] = t('This option indicates whether existing terms with the same name should be updated or ignored. If ignored, duplicates may be created.');

    $form['tab']['import_options'][TAXONOMY_CSV_FORMAT_TREE_STRUCTURE]['#description'] = t('This option indicates whether and how existing terms with the same name should be updated or ignored.') . '<br />'
      . t('This option is used with last term of the line.') . '<br />'
      . '<ul>
          <li>' . t('<em>"Replace"</em>: each parent replaces eventual older ones.') . '</li>
          <li>' . t('<em>"Ignore"</em>: child is always created and eventually its parents if they don\'t exist.') . ' ' . t('It is recommended if you use duplicate terms.') . '</li>
        </ul>';

    $form['tab']['import_options'][TAXONOMY_CSV_FORMAT_POLYHIERARCHY]['#description'] = t('This option indicates whether and how existing terms with the same name should be updated or ignored.') . '<br />'
      . t('By nature, only one option can be chosen with this format.') . '<br />'
      . '<ul>
          <li>' . t('<em>"Update"</em>: each child and parents are merged with old ones, except if the child has the same name than parent, in which case a new term is created, because a child cannot be a parent of itself. Warning: on next lines, direct children of this term name will be attached to the first imported term.') . '</li>
        </ul>';

    $form['tab']['import_options'][TAXONOMY_CSV_FORMAT_PARENTS]['#description'] = t('This option indicates whether and how existing terms with the same name should be updated or ignored.') . '<br />'
      . '<ul>
          <li>' . t('<em>"Update"</em>: each child and parents are merged with old ones. No duplicate are created.') . '</li>
          <li>' . t('<em>"Replace"</em>: each parent replaces eventual older ones.') . '</li>
          <li>' . t('<em>"Ignore"</em>: child is always created and eventually its parents if they don\'t exist.') . '</li>
        </ul>';

    $form['tab']['import_options'][TAXONOMY_CSV_FORMAT_CHILDREN]['#description'] = t('This option indicates whether and how existing terms with the same name should be updated or ignored.') . '<br />'
      . '<ul>
          <li>' . t('<em>"Update"</em>: each child and parents are merged with old ones.') . '</li>
          <li>' . t('<em>"Replace"</em>: each parent replaces eventual older ones.') . '</li>
          <li>' . t('<em>"Ignore"</em>: child is always created and eventually its parents if they don\'t exist.') . '</li>
        </ul>';

    $form['tab']['import_options'][TAXONOMY_CSV_FORMAT_RELATIONS]['#description'] = t('This option indicates whether existing terms with the same name should be updated or ignored.
    <p>For example, if existing related terms of term < <code>foo</code> > are < <code>bar 1</code> > and < <code>bar 2</code> > and an imported line in the csv file is < <code>"foo", "bar 3", "bar 2"</code> >, then:') . '<br >'
      . '<ul>
          <li>' . t('<em>"Update"</em> choice makes related terms of < <code>foo</code> > are now < <code>bar 1</code> >, < <code>bar 2</code> > and < <code>bar 3</code> >;') . '</li>
          <li>' . t('<em>"Replace"</em> choice makes related terms of < <code>foo</code> > are now < <code>bar 3</code> > and < <code>bar 2</code> >;') . '</li>
          <li>' . t('<em>"Ignore"</em> choice makes two < <code>foo</code> > terms, one with existing related and other items and another one with the imported related terms < <code>bar 3</code> > and < <code>bar 1</code> >, which one has not been duplicated.') . '</li>
        </ul></p>';

    $form['tab']['import_options'][TAXONOMY_CSV_FORMAT_SYNONYMS]['#description'] = t('This option indicates whether and how existing terms with the same name should be updated or ignored.') . '<br />'
      . '<ul>
          <li>' . t('<em>"Update"</em>: update term or create it if not exists and merge eventual synonyms with new ones. Always remove duplicate synonyms.') . '</li>
          <li>' . t('<em>"Replace"</em>: update term or create it if not exists and replace eventual synonyms with new ones.') . '</li>
          <li>' . t('<em>"Ignore"</em>: term is always created.') . '</li>
        </ul>';

    $form['tab']['import_options'][TAXONOMY_CSV_FORMAT_DEFINITIONS]['#description'] = t('This option indicates whether existing terms with the same name should be updated or ignored. If ignored, duplicates may be created.') . '<br />'
      . '<ul>
          <li>' . t('<em>"Update"</em>: update term or create it if not exists and merge eventual description with new one.') . '</li>
          <li>' . t('<em>"Replace"</em>: update term or create it if not exists and replace eventual description with new one.') . '</li>
          <li>' . t('<em>"Ignore"</em>: term is always created.') . '</li>
        </ul>';

    $form['tab']['import_options'][TAXONOMY_CSV_FORMAT_DESCRIPTIONS]['#description'] = t('This option indicates whether and how existing terms with the same name should be updated or ignored.') . '<br />'
      . '<ul>
          <li>' . t('<em>"Update"</em>: update term or create it if not exists and merge eventual description with new one.') . '</li>
          <li>' . t('<em>"Replace"</em>: update term or create it if not exists and replace eventual description with new one.') . '</li>
          <li>' . t('<em>"Ignore"</em>: term is always created.') . '</li>
        </ul>';

    $form['tab']['import_options'][TAXONOMY_CSV_FORMAT_WEIGHTS]['#description'] = t('This option indicates whether and how existing terms with the same name should be updated or ignored.');
  }
  else {
    $form['tab']['import_options']['help_no_javascript'] = array(
      '#type'        => 'item',
      '#description' => t("As you see this notice, javascript is not activated on your browser. Only options matching your source content and vocabulary destination needs to be set. Others won't be used. If you want specific examples and options, activate javascript or see <a href=\"!more_help_link\"> advanced help</a>.", array('!more_help_link' => url('admin/help/taxonomy_csv'))),
    );
    // Use this form only if no javascript or in a second step wizard.
    $form['tab']['import_options']['existing_items'] = array(
      '#type'          => 'radios',
      '#options'       => array_intersect_key($list_import_option, array_flip(array(
        TAXONOMY_CSV_EXISTING_UPDATE,
        TAXONOMY_CSV_EXISTING_UPDATE_REPLACE,
        TAXONOMY_CSV_EXISTING_IGNORE,
        TAXONOMY_CSV_EXISTING_IGNORE_ALL,
      ))),
      '#default_value' => $list_previous_values['existing_items'],
      // '#description' below in order to use same help with javascript.
      '#description'   => t('This option allows to set what previous imported terms will become if a new line contains the same terms. Usually, it indicates an error or a unoptimized source, unless you allow duplicates.') . '<br />'
    . t('This option is used too with existing terms in the target vocabulary. Recommended value is to update and merge. If you choose to ignore previous or existing terms, the vocabulary will have duplicate terms.') . '<br />'
    . t('Some choices may be currently disabled.'),
    );
  }

  $form['tab']['advanced_options'] = array(
    '#type'        => 'fieldset',
    '#title'       => t('6. Informations on process'),
    '#collapsible' => TRUE,
    '#collapsed'   => TRUE,
    '#description' => t('All these options influe on memory and time process. The more information you want, the more power you need.') . ' '
      . t("It's recommended to reduce displayed infos when imported vocabulary is big (from 1000 or 10000 lines depending on the server)."),
    '#attributes'  => array('id' => 'advanced_options'),
  );

  $form['tab']['advanced_options']['result_choices'] = array(
    '#type'          => 'checkboxes',
    '#options'       => array(
      'result_stats' => t('Basic stats on imported terms'),
      'result_terms' => t('List of imported terms'),
    ),
    '#default_value' => array(
      $list_previous_values['result_stats'],
      $list_previous_values['result_terms'],
    ),
  );

  $form['tab']['advanced_options']['result_level'] = array(
    '#type'          => 'select',
    '#title'         => t('Log level'),
    '#options'       => array(
      'first'    => t('Only first warning or notice'),
      'warnings' => t('Warnings only'),
      'notices'  => t('Warnings and notices'),
      'infos'    => t('Warnings, notices and informations'),
    ),
    '#default_value' => $list_previous_values['result_level'],
  );

  $form['tab']['advanced_options']['result_type'] = array(
    '#type'          => 'radios',
    '#title'         => t('Group informations'),
    '#options'       => array(
      'by_message'  => t('By message (compact view)'),
      'by_line'     => t('By line (list view)'),
      // 'by_collapse' => t('By line (collapsible view)'),
    ),
    '#default_value' => $list_previous_values['result_type'],
    '#prefix'        => '<div id="result_type">',
    '#suffix'        => '</div>',
  );

  $form['tab']['advanced_options']['info'] = array(
    '#type'        => 'item',
    '#description' => t('Warning: to display warnings, notices and informations, especially by line, can help you to detect issues when submitted list of terms is not clean and when you choose to check lines, but it is memory intensive.'),
  );

  $form['import_submit'] = array(
    '#type'  => 'submit',
    '#value' => t('Import'),
  );

  $form['import_default_values'] = array(
    '#type'     => 'submit',
    '#value'    => t('Reset to defaults'),
    '#validate' => array('_taxonomy_csv_form_import_default_values_validate'),
    '#submit'   => array('_taxonomy_csv_form_import_default_values_submit'),
  );

  return $form;
}

/**
 * Handles CSV import form validation.
 *
 * @see taxonomy_csv_form_import()
 */
function taxonomy_csv_form_import_validate($form, &$form_state) {
  // Invoke taxonomy_csv.import.api.
  $module_dir = drupal_get_path('module', 'taxonomy_csv');
  require_once("$module_dir/import/taxonomy_csv.import.api.inc");

  $options = &$form_state['values'];

  // 1. Preload text or file in order to check it.
  switch ($options['source_choice']) {
    case 'text':
      $options['url'] = '';
      $options['file'] = '';
      break;
    case 'url':
      $options['text'] = '';
      $options['file'] = '';
      break;
    case 'file':
      $options['text'] = '';
      $options['url'] = '';

      // When source is path, need to preload here.
      $options['file'] = file_save_upload('file');
      break;
  }
  $messages = _taxonomy_csv_import_input_preload($options);

  // 2, Simplify values to be compatible with api checks.
  // Define true delimiter.
  $delimiter = array(
    'comma'            => ',',
    'semicolon'        => ';',
    'tabulation'       => "\t",
    'pipe'             => '|',
    'space'            => ' ',
    'currency_sign'    => '¤',
    'soft_tab'         => str_repeat(' ', $options['import_delimiter_soft_tab_width']),
    'custom_delimiter' => $options['import_delimiter_custom'],
  );
  $options['delimiter'] = $delimiter[$options['import_delimiter']];

  // Define true enclosure.
  $enclosure = array(
    'none'             => '',
    'quotation'        => '"',
    'quote'            => "'",
    'custom_enclosure' => $options['import_enclosure_custom'],
  );
  $options['enclosure'] = $enclosure[$options['import_enclosure']];

  // Define existing items choice.
  if (!isset($_COOKIE['has_js']) || $_COOKIE['has_js']) {
    $import_format = $options['import_format'];
    $options['existing_items'] = $options["existing_items_$import_format"];
  }

  // Define result preferences.
  foreach ($options['result_choices'] as $key => $value) {
    $options[$key] = $value;
  }

  // 3. Make api checks and eventually update options by reference.
  $messages = array_merge($messages, _taxonomy_csv_import_check_options($options));

  // Use form set error for api errors.
  foreach (array(
      'delimiter'   => 'import_delimiter',
      'enclosure'   => 'import_enclosure',
    ) as $key => $value) {
    if (isset($messages[$key])) {
      $messages[$value] = $messages[$key];
      unset($messages[$key]);
    }
  }

  // 4. Make non api checks.
  if (($options['import_delimiter'] == 'custom_delimiter')
      && (empty($options['import_delimiter_custom']))) {
    $messages['import_delimiter_custom'] = t('You choose to use a custom delimiter, but your delimiter is empty.');
  }

  if (($options['import_enclosure'] == 'custom_enclosure')
      && (empty($options['import_enclosure_custom']))) {
    $messages['import_enclosure_custom'] = t('You choose to use a custom enclosure, but your enclosure is empty.');
  }

  if (($options['import_delimiter'] == 'custom_delimiter')
      && (drupal_strlen($options['import_delimiter_custom']) > 1)) {
    $messages['import_delimiter_custom'] = t('Delimiter should have only one character.');
  }
  if (($options['import_enclosure'] == 'custom_enclosure')
      && (drupal_strlen($options['import_enclosure_custom']) > 1)) {
    $messages['import_enclosure_custom'] = t('Enclosure should have only zero or one character.');
  }

  // 5. Finish validatation of form.
  foreach ($messages as $item => $message) {
    form_set_error(check_plain($item), filter_xss($message));
  }
}

/**
 * Validate options of imported vocabulary or line.
 *
 * @param $options
 *   Array of options.
 *
 * @return
 *   Array of messages errors if any.
 *   By reference options are cleaned and completed.
 */
function _taxonomy_csv_import_check_options(&$options) {
  $messages = array();

  // Delimiter or enclosure greater than one character are useless with fgetcsv,
  // except with soft tab.
  if ($options['delimiter'] == ''
      || ((drupal_strlen($options['delimiter']) > 1) && (trim($options['delimiter'], ' ')) != '')
    ) {
    $messages['delimiter'] = t('Delimiter should be a one character string or a soft tab (two spaces or more).');
  }
  if (drupal_strlen($options['enclosure']) == 0) {
    // With fgetcsv, empty enclosure bugs, so use default quote enclosure.
    $options['enclosure'] = '"';
  }
  elseif (drupal_strlen($options['enclosure']) > 1) {
    $messages['enclosure'] = t('Enclosure lenght cannot be greater than one character.');
  }
  if ($options['delimiter'] == $options['enclosure']) {
    $messages['delimiter'] = t('Delimiter and enclosure cannot be same character.');
  }

  // Clean locale if any.
  $options['locale_custom'] = trim($options['locale_custom']);

  // Calculates number of lines to be imported.
  if (!isset($options['file'])
      || !is_object($options['file'])
      || count(file($options['file']->filepath)) == 0) {
    $messages['total_lines'] = t('No term to import.');
  }

  if (!in_array($options['vocabulary_target'], array(
      'autocreate',
      'duplicate',
      'existing',
    ))) {
    $messages['vocabulary_target'] = t('Destination target should be "autocreate", "duplicate" or "existing".');
  }

  if ($options['vocabulary_target'] == 'duplicate'
      || $options['vocabulary_target'] == 'existing') {
    $list_vocabularies = taxonomy_get_vocabularies();
    if (!isset($list_vocabularies[$options['vocabulary_id']])) {
      $messages['vocabulary_id'] = t("You choose to use an existing vocabulary, but you haven't choose it.");
    }
  }

  $list_import_format = _taxonomy_csv_values('import_format');
  $list_import_option = _taxonomy_csv_values('import_option');
  $list_import_allowed = _taxonomy_csv_values('import_allowed');
  if (!array_key_exists($options['import_format'], $list_import_format)) {
    $messages['import_format'] = t('Source content "!import_format" is not managed.', array(
      '!import_format' => $list_import_format[$options['import_format']]
    ));
  }
  elseif (!in_array($options['existing_items'], $list_import_allowed[$options['import_format']])) {
    $messages['existing_items'] = t('Import option "%existing_items" cannot be used with source content "!import_format".', array(
      '%existing_items' => $list_import_option[$options['existing_items']],
      '!import_format'  => $list_import_format[$options['import_format']],
    ));
  }

  if (!$options['existing_items']) {
    $messages['existing_items'] = t('Please set what will become existing terms.');
  }
  elseif (!array_key_exists($options['existing_items'], $list_import_option)) {
    $messages['existing_items'] = t('Import option "!existing_items" is not managed.', array(
      '!existing_items' => $list_import_option[$options['existing_items']]
    ));
  }

  if ($options['check_hierarchy']
      && ($options['set_hierarchy'] < 0 || $options['set_hierarchy'] > 2)) {
    $messages['set_hierarchy'] = t('You need to set hierarchy level if hierarchy check of vocabulary is disabled.');
  }

  return $messages;
}

/**
 * Handles CSV import form submission and launch batch set.
 *
 * @see taxonomy_csv_form_import()
 */
function taxonomy_csv_form_import_submit($form, &$form_state) {
  // Remember last preferences and prepare only options to be sent to Api.
  foreach (array(
      'import_format',
      'keep_order',
      'source_choice',
      'import_delimiter',
      'import_delimiter_soft_tab_width',
      'import_delimiter_custom',
      'import_enclosure',
      'import_enclosure_custom',
      'check_line',
      'check_utf8',
      'locale_custom',
      'vocabulary_target',
      'vocabulary_id',
      'delete_terms',
      'check_hierarchy',
      'set_hierarchy',
      'existing_items',
      // Specific to relations import.
      'relations_create_subrelations',
      'relations_all_vocabularies',
      // General options.
      'result_stats',
      'result_terms',
      'result_level',
      'result_type',
    ) as $option) {
    variable_set('taxonomy_csv_' . $option, $form_state['values'][$option]);
    $options[$option] = $form_state['values'][$option];
  }
  // Finish to prepare $options. Unset useless options for api.
  if ($options['source_choice'] == 'text') {
    $options['text'] = &$form_state['values']['text'];
    unset($form_state['values']['text']);
  }
  unset($options['import_delimiter']);
  unset($options['import_delimiter_soft_tab_width']);
  unset($options['import_delimiter_custom']);
  unset($options['import_enclosure']);
  unset($options['import_enclosure_custom']);
  $options['delimiter'] = $form_state['values']['delimiter'];
  $options['enclosure'] = $form_state['values']['enclosure'];
  $options['file'] = $form_state['values']['file'];
  $options['url']  = $form_state['values']['url'];
  $options['check_options'] = FALSE; // Already done.
  $options['result_display'] = TRUE;

  // Prepares process batch (will be automatically processed when returns).
  taxonomy_csv_vocabulary_import($options);
}

/**
 * Restore recommended default values in the import form. Empty validate hook.
 */
function _taxonomy_csv_form_import_default_values_validate($form, &$form_state) {
}

/**
 * Restore recommended default values in the import form.
 */
function _taxonomy_csv_form_import_default_values_submit($form, &$form_state) {
  foreach (_taxonomy_csv_values('import_default_ui') as $option => $value) {
    variable_set("taxonomy_csv_$option", $value);
  }
  unset($form_state['values']);
  unset($form_state['storage']);

  drupal_set_message(t('Import options have been reset to default.'));
}
