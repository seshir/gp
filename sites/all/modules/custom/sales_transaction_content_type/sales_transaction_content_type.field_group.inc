<?php
/**
 * @file
 * sales_transaction_content_type.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function sales_transaction_content_type_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_details|node|sales_transaction|form';
  $field_group->group_name = 'group_details';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'sales_transaction';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Details',
    'weight' => '5',
    'children' => array(
      0 => 'field_details_creationdatetime',
      1 => 'field_details_validityperiod',
      2 => 'field_details_remarks',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-details field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_details|node|sales_transaction|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_involvement|node|sales_transaction|form';
  $field_group->group_name = 'group_involvement';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'sales_transaction';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Involvement',
    'weight' => '8',
    'children' => array(
      0 => 'field_involvement_places',
      1 => 'field_involvement_channels',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-involvement field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_involvement|node|sales_transaction|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_producttype|field_collection_item|field_customerproduct|form';
  $field_group->group_name = 'group_producttype';
  $field_group->entity_type = 'field_collection_item';
  $field_group->bundle = 'field_customerproduct';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Product Type',
    'weight' => '38',
    'children' => array(
      0 => 'field_cp_pt_description',
      1 => 'field_cp_pt_id',
      2 => 'field_cp_pt_name',
      3 => 'field_cp_pt_sub_name',
      4 => 'field_cp_pt_sub_description',
      5 => 'field_cp_pt_sub_id',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-producttype field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_producttype|field_collection_item|field_customerproduct|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_status|node|sales_transaction|form';
  $field_group->group_name = 'group_status';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'sales_transaction';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Status',
    'weight' => '4',
    'children' => array(
      0 => 'field_status_description',
      1 => 'field_status_name',
      2 => 'field_status_id',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-status field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_status|node|sales_transaction|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_type|node|sales_transaction|form';
  $field_group->group_name = 'group_type';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'sales_transaction';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Type',
    'weight' => '3',
    'children' => array(
      0 => 'field_type_name',
      1 => 'field_type_id',
      2 => 'field_type_description',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-type field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_type|node|sales_transaction|form'] = $field_group;

  return $export;
}
