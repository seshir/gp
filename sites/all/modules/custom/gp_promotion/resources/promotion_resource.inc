<?php



/**
 * Callback for retrieving note resources.
 *
 * @param int $id
 * @return object
 */
function _promotion_resource_retrieve($id) {
    //services_error(t("Received Entity are '@nid' ", array('@nid' => $id)), 403);
    return entity_load('node',array($id));
}

/**
 * Callback for listing promotions.
 *
 * @param int $page
 * @param array $parameters
 * @return array
 */
function _promotion_resource_index($page, $parameters) {
    global $user;

    if(!($user->uid > 0) )
       services_error(t('Unauthorized transaction'),401);

    $promotions = array();
    if(empty($page))
        $page = 10;

    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'node')
        ->entityCondition('bundle', 'promotion')
        ->propertyCondition('status', 1)
        //->range(0,$page)
            ->propertyOrderBy('changed', 'DESC');

    $result = $query->execute();
    foreach (array_keys($result['node']) as $nid ) {
        $promoObj = entity_load('node', array($nid));
        if(strtotime($promoObj[$nid]->field_offer_valid_till[LANGUAGE_NONE][0]['value2']) >= time() && time() > strtotime($promoObj[$nid]->field_offer_valid_till[LANGUAGE_NONE][0]['value']) ) {
            $promotions[] = array(
              'nid' =>   $promoObj[$nid]->nid,
              'name' => $promoObj[$nid]->title,
              'description' => $promoObj[$nid]->body[LANGUAGE_NONE][0]['safe_value'],
              'validFrom' => $promoObj[$nid]->field_offer_valid_till[LANGUAGE_NONE][0]['value'],
              'validTill' => $promoObj[$nid]->field_offer_valid_till[LANGUAGE_NONE][0]['value2'],
              'vendorApplicableTo' => $promoObj[$nid]->field_vendor_association[LANGUAGE_NONE][0]['target_id'],
              'storeApplicableAt' => $promoObj[$nid]->field_store_location[LANGUAGE_NONE][0],
            );
        }
    }
    return $promotions;
}

/*
 * Callback for Redeem Offer on a promotion
 */
function _promotion_offer_redeem($data) {

    if(!( $customer = user_load($data['customerId']) )) {
        services_error(t('Unauthorized Transaction'),401);
    }

    if(_is_valid_redemption($data['offerCode'],$data['customerId'])) {

        $rid = db_insert('offer_redemption') // Table name no longer needs {}
            ->fields(array(
                'offercode' => $data['offerCode'],
                'uid' => $customer->uid,
                'status' => 1,
                'created' => REQUEST_TIME,
            ))
            ->execute();
            return $rid;
    } else {
        services_error(t('Invalid Transaction'),401);
    }
}

/*
 * helper function to check offer validity
 */
function _is_valid_redemption ($offerCode, $customerId) {

    // Check for valid offerCode
    if(_is_valid_offercode($offerCode)) {
        // Check if Redemption is already done for this offerCode by same user
        $rid = db_select('offer_redemption')
                ->fields('offer_redemption',array('rid'))
                ->condition('uid',$customerId,'=')
                ->condition('offercode',$offerCode,'=')
                ->execute()
                ->fetchField();
        if(!$rid)
            return true;
    } else {
        return false;
    }
}

function _is_valid_offercode ($offerCode) {
    // load promotion Content by Offer Code and validate if
    $query = new EntityFieldQuery();

    $query->entityCondition('entity_type', 'node')
        ->entityCondition('bundle', 'promotion')
        ->propertyCondition('status', NODE_PUBLISHED)
        ->fieldCondition('field_offer_code', 'value', $offerCode, '=');

    $result = $query->execute();

    if (isset($result['node']) && count($result['node'])) {
        return true;
    } else {
        return false;
    }
}