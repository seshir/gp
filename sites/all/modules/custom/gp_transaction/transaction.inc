<?php
// transaction.inc
/**
 * Callback for creating note transactions.
 *
 * @param object $data
 * @return object
 */
function _transaction_create($data) {
    global $user;
    services_error(t("Received data '@data' ", array('@p' => print_r($data))), 403);
    unset($data->id);
    $data->uid = $user->uid;
    $data->created = time();
    $data->modified = time();
    if (!isset($data->subject)) {
        return services_error('Missing note attribute subject', 406);
    }
    if (!isset($data->note)) {
        return services_error('Missing note attribute note', 406);
    }
    transaction_write_resource($data);
    return (object)array(
        'id' => $data->id,
        'uri' => services_resource_uri(array('transaction', $data->id)),
    );
}

/**
 * Callback for updating note transactions.
 *
 * @param int $id
 * @param object $data
 * @return object
 */
function _transaction_update($id, $data) {
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
function _transaction_retrieve($id) {
    services_error(t("Received data '@data' ", array('@data' => print_r($id))), 403);
    return transaction_get_resource($id);
}
/**
 * Callback for deleting note resources.
 *
 * @param int $id
 * @return object
 */
function _transaction_delete($id) {
    transaction_delete_resource($id);
    return (object)array(
        'id' => $id,
    );
}

/**
 * Callback for listing notes.
 *
 * @param int $page
 * @param array $parameters
 * @return array
 */
function _transaction_index($page, $parameters) {
    global $user;
    services_error(t("Received data '@data' ", array('@data' => print_r('Data'))), 403);
    $transactions = array();

    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'node')
        ->entityCondition('bundle', 'transaction')
        ->propertyCondition('status', 1);
    foreach($parameters as $param => $value) {
        if(strstr('field_consumer',$param))
            $query->fieldCondition($param,'target_id',$value);
        else
            $query->propertyCondition($param, $value);
    }
    $result = $query->execute();
    $tids = array();
    if (isset($result['node'])) {
        $tids[] = array_keys($result['node']);
        $transactions = entity_load('node', $tids);
    }
    return $transactions;
}

