<?php
/**
 * Created by PhpStorm.
 * User: seshireddy
 * Date: 13/10/14
 * Time: 11:34 PM
 */

function checkConnectionStatus() {
    // Your organization name
    $org = 'api';
    // API endpoint in Apigee’s cloud
    $endpoint = 'https://api.enterprise.apigee.com/v1';
    // Authenticated user for this organization.
    // This user should have the ‘orgadmin’ role on Edge.
    $user = 'seshireddy@apigee.com';
    // Password for the above user
    $pass = 'ses2hiRR';
    // An array of other connection options
    $options = array(
        'http_options' => array(
            'connection_timeout' => 4,
            'timeout' => 4
        )
    );

    $org_config = new Apigee\Util\OrgConfig($org, $endpoint, $user, $pass, $options);

    // Load Developer
    $developer = new Apigee\ManagementAPI\Developer($org_config);
    try {
        $developer->load('seshireddy@apigee.com');
        $developer->setFirstName('John');
        $developer->setLastName('D');
        $developer->save();
        print "Developer updated!\n";
    }
    catch (Apigee\Exceptions\ResponseException $e) {
        print $e->getMessage();
    }
}
