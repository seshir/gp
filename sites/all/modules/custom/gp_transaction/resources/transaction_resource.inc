<?php

/**
 * Callback for creating note transactions.
 *
 * @param object $data
 * @return object
 */
function _transaction_resource_create($data) {
    global $user;

    $payload = array();

    $values = $data->xpath("//SalesTransaction");
    $values = (array) $values[0];
    $values['body']['value'] = $values['Description'];
    if(!isset($values['Name']))
        $values['Name'] = $values['ID'];
    $values['title'] = $values['Name'];

    $fieldCollections['roles_customer'] =  $values['Roles']->Customer->CustomerParty;
    $fieldCollections['roles_vendor'] =  $values['Roles']->Vendor->VendorParty;

    // Check for valid customer party
    if(!isset($fieldCollections['roles_customer']->ID) || !($customerUid = _getpop_decode_user($fieldCollections['roles_customer']->ID)) ) {
        // Assign Author as Customer
        $fieldCollections['roles_customer']->ID =  $user->uid;
    }
    else if(is_numeric($customerUid)){

        $fieldCollections['roles_customer']->ID =  $customerUid;

    } else {
        services_error(t("Unauthorized Customer Party @p", array('@p' => $fieldCollections['roles_customer']->Name)), 403);
    }

    // Check for Valid Vendor party
    if(isset($fieldCollections['roles_vendor']->ID)) {
        // Identify the Vendor User based on vendor Id
        $query = new EntityFieldQuery();

        $query->entityCondition('entity_type', 'user')
            ->propertyCondition('status',1)
            ->fieldCondition('field_vendor_id', 'value', $fieldCollections['roles_vendor']->ID, '=');

        $result = $query->execute();

        if(isset($result['user'])) {
            $fieldCollections['roles_vendor']->ID = key($result['user']);
        } else {
            // Assign Author as vendor
            $fieldCollections['roles_vendor']->ID = $user->uid;
        }

    } else {
        // Assign Anonymous as vendor
        $fieldCollections['roles_vendor']->ID = 0;
    }


    $payload['details_creationdatetime'] = strtotime((string) $values['Details']->CreationDateTime);
    //$payload['details_creationdatetime']['value2'] = strtotime((string) $values['Details']->CreationDateTime) + 3600;
    $payload['details_remarks'] = (string) $values['Details']->Remarks;
    $payload['details_validityperiod']['value'] = strtotime((string) $values['Details']->ValidityPeriod->FromDate);
    $payload['details_validityperiod']['value2'] = strtotime((string) $values['Details']->ValidityPeriod->ToDate);

    // handle field collections
    if(!empty($values['Categories']))
        $fieldCollections['categories'] =  $values['Categories']->xpath('Category');
    if(!empty($values['Parts']))
        $fieldCollections['parts'] =  $values['Parts']->xpath('PaymentMethod');

    if(!empty($values['Involvement'])) {
        $fieldCollections['involvement_places'] =  $values['Involvement']->Places->xpath('Place');
        $fieldCollections['involvement_channels'] =  $values['Involvement']->Channels->xpath('Channel');
    }

    //$fieldCollections['roles_agent'] =  $values['Roles']->Agent;

    $fieldCollections['line_item'] =  $values['LineItems']->xpath('LineItem');
    $fieldCollections['customer_product'] =  $values['LineItems']->LineItem->CustomerProduct;
    //services_error(t("Received Entity are '@p' ", array('@p' => print_r($fieldCollections['customer_product']))), 403);

    unset($values['Description']);
    unset($values['Name']);
    unset($values['SalesTransactionAgreement']);
    unset($values['Details']);


    foreach($values as $key => $value ) {
        if(is_object($value)) {
            $field_instance = field_info_instance('node', 'field_'.strtolower($key), 'sales_transaction');
            if($field_instance['widget']['module'] == 'field_collection_table') {
                $fieldCollections[$key] = $value;
                continue;
            }
            $value = (array) $value;
            foreach($value as $sub_key => $sub_data){
                if(is_string($sub_data)) {
                    $field_instance = field_info_instance('node', 'field_'.strtolower($key.'_'.$sub_key), 'sales_transaction');
                    if($field_instance['settings']['text_processing'] == 1) {
                        $payload[strtolower($key.'_'.$sub_key)]['value'] = $sub_data;
                    } else {
                        $payload[strtolower($key.'_'.$sub_key)] = $sub_data;
                    }
                } else {
                    continue;
                }
            }
        } else {
          $field_instance = field_info_instance('node', 'field_'.strtolower($key), 'sales_transaction');
          if($field_instance['settings']['text_processing'] == 1)
            $payload[strtolower($key)]['value'] = $value;
          else
            $payload[strtolower($key)] = $value;
        }
    }
    $payload['type'] = 'sales_transaction';

    $resCtrl = new GPServicesTransactionResourceController();
    $res = $resCtrl->create('node',$payload);


    if(!is_numeric($res['nid'])) {
        services_error(t("Error Creating Transaction, Please contact administrator."), 500);
    } else {

        // Create 1st level Categories
        _create_fc_item ($res['nid'],'node',$payload['type'], 'field_categories', $fieldCollections['categories'],'category');

        // Create 1st level Parts Payment Method
        _create_fc_item ($res['nid'],'node',$payload['type'], 'field_parts_paymentmethod', $fieldCollections['parts'],'parts_paymentmethod');

        // Create 1st level Line items
        _create_fc_line_item ($res['nid'],'node',$payload['type'], 'field_line_item', $fieldCollections['line_item'], NULL);

        // Create 1st level Customer Party & Vendor Party
        _create_fc_role_customer_item ($res['nid'],'node',$payload['type'], 'field_roles_customer', $fieldCollections['roles_customer'],'roles_customer');
        _create_fc_role_customer_item ($res['nid'],'node',$payload['type'], 'field_roles_vendor', $fieldCollections['roles_vendor'],'roles_vendor');

        // Create Involvement Channels and Places
        _create_fc_involvement_item ($res['nid'],'node',$payload['type'], 'field_involvement_places', $fieldCollections['involvement_places'],'place');
        //_create_fc_item ($res['nid'],'node',$payload['type'], 'field_involvement_channels', $fieldCollections['involvement_channels'],'channel');

        return $res['nid'];
        //services_error(t("Created Transaction Successfully"),201,$res['nid']);
    }

}

/*
 * Create Line Item
 */
function _create_fc_line_item ($parentEntityId, $parentEntityType, $parentEntityName, $fc_name, $fc_array, $fc_sub_key = NULL ) {

    $entity = entity_load_single($parentEntityType, $parentEntityId);

    $fc_li_id = $entity->field_line_item[LANGUAGE_NONE][0]['value'];
    entity_delete('field_collection_item',$fc_li_id);

    foreach($fc_array as $item_key => $fc_item) {
        $fc_customerproduct = $fc_item->xpath('CustomerProduct');

        $fc_item = (array) $fc_item;
        unset($fc_item['CustomerProduct']);
        //unset($fc_item['Specifications']);
        $frame = entity_create('field_collection_item',array('field_name' => $fc_name));
        $frame->setHostEntity($parentEntityType, $entity);
        $frame_wrapper = entity_metadata_wrapper('field_collection_item', $frame);
        foreach($fc_item as $key => $value ) {
            if(is_string($value)) {
                $fc_key = 'field_'.strtolower($key);

                $field_instance = field_info_instance('field_collection_item', $fc_key, $fc_name);
                if($field_instance['settings']['text_processing'] == 1)
                    $frame_wrapper->$fc_key->set(array('value' => $value));
                else
                    $frame_wrapper->$fc_key->set($value);
            } else {
                $value = (array) $value;
                foreach($value as $fc_sub_key2 => $value2 ) {
                    if(isset($fc_sub_key))
                        $fc_key = 'field_'.strtolower($fc_sub_key.'_'.$key.'_'.$fc_sub_key2);
                    else
                        $fc_key = 'field_'.strtolower($key.'_'.$fc_sub_key2);

                    $field_instance = field_info_instance('field_collection_item', $fc_key, $fc_name);
                    if($field_instance['settings']['text_processing'] == 1)
                        $frame_wrapper->$fc_key->set(array('value' => $value2));
                    else
                        $frame_wrapper->$fc_key->set($value2);
                }

            }
        }
        $frame_wrapper->save();
        $rawWrapper = $frame_wrapper->raw();
        _create_fc_customerproduct($rawWrapper->item_id,'field_collection_item','field_line_item','field_customerproduct',$fc_customerproduct[0],'cp');
    }

    return entity_save($parentEntityType, $entity);
}

/*
 * Creates FC Customer product
 */
function _create_fc_customerproduct($parentEntityId,$parentEntityType,$parentEntityName, $fc_name, $fc_array, $fc_sub_key = NULL ) {
    $entity = entity_load_single($parentEntityType, $parentEntityId);
    $cp_specification = array();
    $cp_categories =  $fc_array->xpath("Categories");
    $cp_proofs =  $fc_array->xpath("Proofs");
    $cp_specification =  $fc_array->xpath("Specifications");

    $fc_item = (array) $fc_array;

    unset($fc_item['Categories']);
    unset($fc_item['Proofs']);
    unset($fc_item['Specifications']);
    $fc_cp_id = NULL;
    if($fc_cp_id = $entity->field_customerproduct[LANGUAGE_NONE][0]['value']) {
        $frame = entity_load_single('field_collection_item',$fc_cp_id);
    } else {
        $frame = entity_create('field_collection_item',array('field_name' => $fc_name));
        $frame->setHostEntity($parentEntityType, $entity);
    }
    $frame_wrapper = entity_metadata_wrapper('field_collection_item', $frame);

    foreach($fc_item as $key => $value ) {

        if(is_string($value)) {

            if(isset($fc_sub_key))
                $fc_key = 'field_'.strtolower($fc_sub_key.'_'.$key);
            else
                $fc_key = 'field_'.strtolower($key);

            $field_instance = field_info_instance('field_collection_item', $fc_key, $fc_name);
            if($field_instance['settings']['text_processing'] == 1)
                $frame_wrapper->$fc_key->set(array('value' => $value));
            else
                $frame_wrapper->$fc_key->set($value);
        } else {
            $value = (array) $value;
            if($key == 'ProductType')
                $key = 'pt';

            foreach($value as $fc_sub_key2 => $value2 ) {

                if($fc_sub_key2 == 'ProductSubType') {
                    $fc_sub_key2 = 'sub';
                }

                if(is_string($value2)) {
                    if(isset($fc_sub_key))
                        $fc_key = 'field_'.strtolower($fc_sub_key.'_'.$key.'_'.$fc_sub_key2);
                    else
                        $fc_key = 'field_'.strtolower($key.'_'.$fc_sub_key2);

                    $field_instance = field_info_instance('field_collection_item', $fc_key, $fc_name);
                    if($field_instance['settings']['text_processing'] == 1)
                        $frame_wrapper->$fc_key->set(array('value' => $value2));
                    else
                        $frame_wrapper->$fc_key->set($value2);
                } else {
                    $value2 = (array) $value2;
                    foreach($value2 as $fc_subkey3 => $value3 ) {
                        if(isset($fc_sub_key))
                            $fc_key = 'field_'.strtolower($fc_sub_key.'_'.$key.'_'.$fc_sub_key2.'_'.$fc_subkey3);
                        else
                            $fc_key = 'field_'.strtolower($key.'_'.$fc_sub_key2.'_'.$fc_subkey3);

                        $field_instance = field_info_instance('field_collection_item', $fc_key, $fc_name);
                        if($field_instance['settings']['text_processing'] == 1)
                            $frame_wrapper->$fc_key->set(array('value' => $value3));
                        else
                            $frame_wrapper->$fc_key->set($value3);

                    }
                }
            }

        }
    }

    $frame_wrapper->save();
    $cpWrapper = $frame_wrapper->raw();
    foreach($cp_specification as $cp_specif)
        _create_fc_cp_specifications ($cpWrapper->item_id,'field_collection_item','field_customerproduct', 'field_specification', $cp_specif,'sp');
    return entity_save($parentEntityType, $entity);
}


/**
 * @TODO _create_fc_cp_proofs
 */
function _create_fc_cp_proofs() {

}

/**
 * @TODO _create_fc_cp_categories
 */

/**
 * @TODO _create_fc_cp_specifications
 */
function _create_fc_cp_specifications($parentEntityId, $parentEntityType, $parentEntityName, $fc_name, $fc_array, $fc_sub_key ) {

    $entity = entity_load_single($parentEntityType, $parentEntityId);
    //services_error('Specification',500,$fc_array);
    $fc_item = array();
    foreach($fc_array as $item_key => $fc_item) {
        $fc_item = (array) $fc_item;

        $frame = entity_create('field_collection_item',array('field_name' => $fc_name));
        $frame->setHostEntity($parentEntityType, $entity);
        $frame_wrapper = entity_metadata_wrapper('field_collection_item', $frame);
        foreach($fc_item as $key => $value ) {
            if(is_string($value)) {
                if($key == 'CharecteristicValue')
                    $fc_key = 'field_charecteristic_value';
                else
                    $fc_key = 'field_'.strtolower($fc_sub_key.'_'.$key);

                if(strlen($fc_key) > 30 )
                    $fc_key = 'field_'.strtolower($fc_sub_key.'_'.'descri');

                $field_instance = field_info_instance('field_collection_item', $fc_key, $fc_name);
                if($field_instance['settings']['text_processing'] == 1)
                    $frame_wrapper->$fc_key->set(array('value' => $value));
                else
                    $frame_wrapper->$fc_key->set($value);
            } else {
                $value = (array) $value;
                foreach($value as $fc_sub_key2 => $value2 ) {
                    if($fc_sub_key == 'parts_paymentmethod')
                        $fc_key = 'field_'.strtolower($key.'_'.$fc_sub_key2);
                    else
                        $fc_key = 'field_'.strtolower($fc_sub_key.'_'.$key.'_'.$fc_sub_key2);

                    $field_instance = field_info_instance('field_collection_item', $fc_key, $fc_name);
                    if($field_instance['settings']['text_processing'] == 1)
                        $frame_wrapper->$fc_key->set(array('value' => $value2));
                    else
                        $frame_wrapper->$fc_key->set($value2);
                }

            }
        }
        $frame_wrapper->save();
    }

    return entity_save($parentEntityType, $entity);
}

/*
 * Create Roles
 */
function _create_fc_role_customer_item ($parentEntityId, $parentEntityType, $parentEntityName, $fc_name, $fc_array, $fc_sub_key ) {

    $entity = entity_load_single($parentEntityType, $parentEntityId);

    $fc_item = (array) $fc_array;

    unset($fc_item['Address']);
    //services_error(t("Received Customer wrapper'@p' ", array('@p' => print_r($fc_item))), 403);

    $frame = entity_create('field_collection_item',array('field_name' => $fc_name));
    $frame->setHostEntity($parentEntityType, $entity);
    $frame_wrapper = entity_metadata_wrapper('field_collection_item', $frame);
    foreach($fc_item as $key => $value ) {
        if(is_string($value)) {
            $fc_key = 'field_'.strtolower($fc_sub_key.'_'.$key);

            $field_instance = field_info_instance('field_collection_item', $fc_key, $fc_name);
            if($field_instance['settings']['text_processing'] == 1)
                $frame_wrapper->$fc_key->set(array('value' => $value));
            else
                $frame_wrapper->$fc_key->set($value);
        } else {
            $value = (array) $value;
            if($key == 'Categories') {
                $categories = (array) $value['Category'];
                unset($value['Category']);
            }
            foreach($value as $fc_sub_key2 => $value2 ) {

                $fc_key = 'field_'.strtolower($key.'_'.$fc_sub_key2);

                $field_instance = field_info_instance('field_collection_item', $fc_key, $fc_name);
                if($field_instance['settings']['text_processing'] == 1)
                    $frame_wrapper->$fc_key->set(array('value' => $value2));
                else
                    $frame_wrapper->$fc_key->set($value2);
            }

        }
    }
    $frame_wrapper->save();

    $rawWrapper = $frame_wrapper->raw();
    _create_fc_item ($rawWrapper->item_id,'field_collection_item','field_roles_customer', 'field_categories', $categories,'category');
    return entity_save($parentEntityType, $entity);
}

/**
 * Create Involvement channels and places
 * @param $parentEntityId
 * @param $parentEntityType
 * @param $parentEntityName
 * @param $fc_name
 * @param $fc_array
 * @param $fc_sub_key
 * @return bool
 */
function _create_fc_involvement_item ($parentEntityId, $parentEntityType, $parentEntityName, $fc_name, $fc_array, $fc_sub_key ) {

    $entity = entity_load_single($parentEntityType, $parentEntityId);

    foreach($fc_array as $fc_item) {
        $fc_item = (array) $fc_item;

        $frame = entity_create('field_collection_item',array('field_name' => $fc_name));
        $frame->setHostEntity($parentEntityType, $entity);
        $frame_wrapper = entity_metadata_wrapper('field_collection_item', $frame);
        foreach($fc_item as $key => $value ) {
            if(is_string($value)) {
                $fc_key = 'field_'.strtolower($fc_sub_key.'_'.$key);

                $field_instance = field_info_instance('field_collection_item', $fc_key, $fc_name);
                if($field_instance['settings']['text_processing'] == 1)
                    $frame_wrapper->$fc_key->set(array('value' => $value));
                else
                    $frame_wrapper->$fc_key->set($value);
            } else {
                $value = (array) $value;
                if($key == 'Categories') {
                    $categories = (array) $value['Category'];
                    unset($value['Category']);
                }
                foreach($value as $fc_sub_key2 => $value2 ) {

                    $fc_key = 'field_'.strtolower($fc_sub_key.'_'.$key.'_'.$fc_sub_key2);

                    $field_instance = field_info_instance('field_collection_item', $fc_key, $fc_name);
                    if($field_instance['settings']['text_processing'] == 1)
                        $frame_wrapper->$fc_key->set(array('value' => $value2));
                    else
                        $frame_wrapper->$fc_key->set($value2);
                }

            }
        }
        $frame_wrapper->save();

        $rawWrapper = $frame_wrapper->raw();
        _create_fc_item ($rawWrapper->item_id,'field_collection_item','field_roles_customer', 'field_categories', $categories,'category');
    }
    return entity_save($parentEntityType, $entity);
}


/**
 * Callback for updating note transactions.
 *
 * @param int $id
 * @param object $data
 * @return object
 */
function _transaction_resource_update($id, $data) {
    global $user;
    $note = transaction_get_resource($id);
    unset($data->created);
    $data->id = $id;
    $data->uid = $note->uid;
    $data->modified = time();
    transaction_write_resource($data);
    return (object)array(
        'id' => $id,
        'uri' => services_resource_uri(array('transaction', $id)),
    );
}

/**
 * Callback for retrieving note resources.
 *
 * @param int $id
 * @return object
 */
function _transaction_resource_retrieve($id) {
    //services_error(t("Received Entity are '@nid' ", array('@nid' => $id)), 403);
    return transaction_get_resource($id);
}
/**
 * Callback for deleting note resources.
 *
 * @param int $id
 * @return object
 */
function _transaction_resource_delete($id) {
    transaction_delete_resource($id);
    return (object)array(
        'id' => $id,
    );
}

/**
 * Callback for listing transactions.
 *
 * @param int $page
 * @param array $parameters
 * @return array
 */
function _transaction_resource_index($page, $parameters) {
    global $user;

    if(!($user->uid > 0) )
       services_error(t('Unauthorized transaction'),401);

    $transactions = array();
    if(empty($page))
        $page = 10;

    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'node')
        ->entityCondition('bundle', 'sales_transaction')
        ->propertyCondition('status', 1)
        //->range(0,$page)
        ->propertyOrderBy('nid', 'DESC');

    $result = $query->execute();
    foreach (array_keys($result['node']) as $nid ) {
        $transObj = entity_load('node', array($nid));

        $fc_vendor_id = $transObj[$nid]->field_roles_vendor[LANGUAGE_NONE][0]['value'];
        $fc_vendor = field_collection_item_load_multiple(array($fc_vendor_id));

        $fc_customer_id = $transObj[$nid]->field_roles_customer[LANGUAGE_NONE][0]['value'];
        $fc_customer = field_collection_item_load_multiple(array($fc_customer_id));

        $lineItemIds = array();
        $revisionIds = array();
        foreach($transObj[$nid]->field_line_item[LANGUAGE_NONE] as $item) {
            $lineItemIds[] = $item['value'];
            $revisionIds[$item['value']] = $item['revision_id'];
        }

        $transactionPrice = 0;
        //$lineItems = field_collection_item_load_multiple($lineItemIds);
        foreach($lineItemIds as $lid) {
            $lineItems[$lid] = field_collection_item_revision_load($revisionIds[$lid]);
            $transactionPrice += $lineItems[$lid]->field_price_quantity[LANGUAGE_NONE][0]['value'];
            $currency = $lineItems[$lid]->field_price_unitofmeasure[LANGUAGE_NONE][0]['value'];
        }
        if($user->uid == $fc_customer[$fc_customer_id]->field_roles_customer_id[LANGUAGE_NONE][0]['target_id'] ) {
            $transactions[] = array(
              'nid' =>   $transObj[$nid]->nid,
              'name' => $transObj[$nid]->title,
              'id' => $transObj[$nid]->field_id[LANGUAGE_NONE][0]['value'],
              'vendorName' =>  $fc_vendor[$fc_vendor_id]->field_roles_vendor_name[LANGUAGE_NONE][0]['value'],
              'vendorId' =>  $fc_vendor[$fc_vendor_id]->field_roles_vendor_id[LANGUAGE_NONE][0]['target_id'],
              'customerName' => $fc_customer[$fc_customer_id]->field_roles_customer_name[LANGUAGE_NONE][0]['value'],
              'customerId' =>  $fc_customer[$fc_customer_id]->field_roles_customer_id[LANGUAGE_NONE][0]['target_id'],
              'creationDateTime' => $transObj[$nid]->field_details_creationdatetime[LANGUAGE_NONE][0]['value'],
              'transactionAmount' => $transactionPrice.' '.$currency
            );
        }
    }
    return $transactions;
}

/**
 * @param $fieldCollections
 * @param $nid
 */
function createFieldCollection($fieldCollection, $nid = NULL) {
    $transactionEntity = node_load($nid);
    foreach($fieldCollection as $key => $values ) {
        $payload = array();
        if($key == 'categories') {
            $fcItem = entity_create('field_collection_item', array('field_name' => 'field_'.strtolower($key)));
            $fcItem->setHostEntity('node', $transactionEntity);
            $fcItem_wrapper = entity_metadata_wrapper('field_collection_item', $fcItem);
            foreach($values as $sub_key => $sub_data ) {
                if(is_string($sub_data)) {
                    $fcKey = strtolower('field_'.$sub_key);
                    $fcItem_wrapper->$fcKey->set($sub_data);
                }
            }

        $wrapper[] = $fcItem_wrapper->save(TRUE);
        }
    }

    return $fcItem_wrapper;
}