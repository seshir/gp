<?php
/**
 * @file
 * sales_transaction_content_type.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function sales_transaction_content_type_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_anonymous_sales_transaction';
  $strongarm->value = 0;
  $export['comment_anonymous_sales_transaction'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_mode_sales_transaction';
  $strongarm->value = 1;
  $export['comment_default_mode_sales_transaction'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_per_page_sales_transaction';
  $strongarm->value = '50';
  $export['comment_default_per_page_sales_transaction'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_form_location_sales_transaction';
  $strongarm->value = 1;
  $export['comment_form_location_sales_transaction'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_preview_sales_transaction';
  $strongarm->value = '1';
  $export['comment_preview_sales_transaction'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_sales_transaction';
  $strongarm->value = '1';
  $export['comment_sales_transaction'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_subject_field_sales_transaction';
  $strongarm->value = 1;
  $export['comment_subject_field_sales_transaction'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_node__sales_transaction';
  $strongarm->value = array(
    'view_modes' => array(),
    'extra_fields' => array(
      'form' => array(
        'title' => array(
          'weight' => '0',
        ),
        'redirect' => array(
          'weight' => '17',
        ),
      ),
      'display' => array(),
    ),
  );
  $export['field_bundle_settings_node__sales_transaction'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_sales_transaction';
  $strongarm->value = array();
  $export['menu_options_sales_transaction'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_sales_transaction';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_sales_transaction'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_sales_transaction';
  $strongarm->value = array(
    0 => 'status',
  );
  $export['node_options_sales_transaction'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_sales_transaction';
  $strongarm->value = '1';
  $export['node_preview_sales_transaction'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_sales_transaction';
  $strongarm->value = 0;
  $export['node_submitted_sales_transaction'] = $strongarm;

  return $export;
}
