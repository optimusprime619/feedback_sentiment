
<?php

/**
 * @file additional admin components such as file form
 */

/**
 * A form with a file upload field.
 *
 * This form allows the user to upload a file to Drupal which is stored
 * physically and with a reference in the database (managed file).
 *
 *
 */
function analyzer_file_upload_form($form_state) {
  $form['file'] = array(
    '#title' => t('File Upload'),
    '#type' => 'managed_file',
    '#description' => t('Please uploade the text file.'),
    '#upload_location' => "public://" . variable_get('sentiment_src_dir', 'textfiles'),
    '#upload_validators' => array('file_validate_extensions' => array('txt')),
    '#required' => TRUE,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
    '#submit' => array('analyzer_file_upload_submit'),
  );
 
  return $form;
}

/**
 * Form submission handler for file upload analysis.
 */
function analyzer_file_upload_submit(&$form, $form_state) {
  $file = file_load($form_state['values']['file']);
  $uri = $file->uri;
  $url = file_create_url($uri);
  if ($url === FALSE) {
    drupal_set_message(t('Could not read file @file', array('@file' => $url)), 'error');
  }
  $lines = file($url);
  if ($lines === FALSE) {
    drupal_set_message(t('Could not read source file @file', array('@file' => $url)), 'error');
  }
  $result_values = array();
  foreach($lines as $num => $line) {
    $result_values[$num] = htmlspecialchars($line);
  }
  $src = REQUEST_TIME . '_' . basename($url, '.txt');
  $status  = analyzer_get_sentiment($result_values, $src);
  if ($status){
    drupal_set_message(t('File :: <em>@file</em> uploaded successfully and processed with sentiment analyzer. View the results ' . l('here', 'admin/config/analyzer/results'), array('@file' => $src . '.txt')), 'status');
  }
  else{
    drupal_set_message(t('Could not upload source file @file', array('@file' => $url)), 'error'); 
  }
}

/**
 * Function to display the analysis results
 */

function display_analysis_results() {
  $analysis_res = db_select('file_managed', 'fm')
                  ->fields('fm', array('filename', 'fid', 'uri'))
                  ->where("fm.filename NOT LIKE '%_result.txt%'")
                  ->orderBy('fid', 'DESC') 
                  ->execute();
  $column_data = array();
  foreach ($analysis_res as $result) {
    $result_name = basename($result->filename,'.txt');
    $dest_result = db_query("SELECT `fid`  FROM  {file_managed} WHERE filename LIKE '%" . $result_name . "%' AND `fid` > $result->fid ORDER BY fid ASC LIMIT 1")->fetchField();    
    $result_obj = file_load($dest_result);
    $column_data[] = array(l($result->filename, file_create_url($result->uri), $options = array('absolute' => TRUE)), l($result_obj->filename, file_create_url($result_obj->uri), $options = array('absolute' => TRUE)));
  }
  $headers = array('File Name', 'Result');
  $data = array($column_data);
  return theme('table', array('header' => $headers, 'rows' => $column_data)); 
}
