<?php
/**
 * @file
 * sales_transaction_content_type.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function sales_transaction_content_type_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function sales_transaction_content_type_node_info() {
  $items = array(
    'sales_transaction' => array(
      'name' => t('Sales Transaction'),
      'base' => 'node_content',
      'description' => t('Sales Transaction object to be used by MyPOP system.'),
      'has_title' => '1',
      'title_label' => t('Name'),
      'help' => '',
    ),
  );
  return $items;
}
