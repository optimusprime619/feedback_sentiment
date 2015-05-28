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
  '#default_value' => variable_get('text_file_fid', ''), 
  '#upload_location' => 'public://textfiles/',
  '#upload_validators' => array('file_validate_extensions' => array('txt')),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );
  $path = libraries_get_path('phpInsight');
  require_once DRUPAL_ROOT . '/' . $path . '/autoload.php'; 
  $strings = array(
	1 => 'Weather today is rubbish',
	2 => 'This cake looks amazing',
	3 => 'His skills are mediocre',
	4 => 'He is very talented',
	5 => 'She is seemingly very agressive',
	6 => 'Marie was enthusiastic about the upcoming trip. Her brother was also passionate about her leaving - he would finally have the house for himself.',
	7 => 'To be or not to be?',
);

  try {
    $sentiment = new \PHPInsight\Sentiment();
    dsm($sentiment);
    foreach ($strings as $string) {

	// calculations:
	$scores = $sentiment->score($string);
	$class = $sentiment->categorise($string);

	// output:
	echo "String: $string\n";
	echo "Dominant: $class, scores: ";
	print_r($scores);
	echo "\n";
}

  }
  catch (Exception $e) {
    dsm($e->getMessage());
  }
  return $form;
}
