<?php

/**
 * @file additional admin components such as file form
 */

/**
 * A form with a file upload field.
 *
 * This form allows the user to upload a file to Drupal which is stored
 * physically and with a reference in the database.
 *
 *
 */
function analyzer_file_upload_form($form_state) {
  // If you are familiar with how browsers handle files, you know that
  // enctype="multipart/form-data" is required. Drupal takes care of that, so
  // you don't need to include it yourself.
  // Use the #managed_file FAPI element to upload an image file.
  $form['file'] = array(  
  '#title' => t('File Upload'),  
  '#type' => 'managed_file',  
  '#description' => t('Please uploade the text file.'),  
  '#upload_location' => 'public://textfiles/',
  '#upload_validators' => array('file_validate_extensions' => array('txt')),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
    '#submit' => array('analyzer_file_upload_submit'),
  );
 
  return $form;
}

function analyzer_file_upload_submit(&$form, $form_state){

$file = file_load($form_state['values']['file']);
$uri = $file->uri;
$url = file_create_url($uri);

$lines = file($url);
$res = array();

foreach($lines as $num => $line){
$res[$num] = htmlspecialchars($line);
}

$s = analyzer_get_sentiment($res);
}
