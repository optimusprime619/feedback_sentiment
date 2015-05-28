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
  $res = array();

  foreach($lines as $num => $line) {
    $res[$num] = htmlspecialchars($line);
  }
  // @ToDo Need to check if we need to return the sentiment analysis result and use for
  // further processing or not to assign return value
  $s = analyzer_get_sentiment($res);
}
