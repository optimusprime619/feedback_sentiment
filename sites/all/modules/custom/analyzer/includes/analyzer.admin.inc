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
  $form['file'] = array(
    '#type' => 'file',
    '#title' => t('Upload File'),
    '#required' => TRUE,
    '#description' => t('Upload a file, allowed extensions: txt'),
  );
  
  // Use the #managed_file FAPI element to upload an image file.
  $form['image_example_image_fid'] = array(  
  '#title' => t('File Upload'),  
  '#type' => 'managed_file',  
  '#description' => t('The uploaded text file.'),  
  '#default_value' => variable_get('text_file_fid', ''), 
  '#upload_location' => 'public://textfiles/',
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );
  
//   $form['#validate'][] = 'analyzer_file_upload_validate';

  return $form;
}

function analyzer_file_upload_validate(){

}

