<?php

$xmlrpc_defencoding = "UTF8";
$xmlrpc_internalencoding = 'UTF-8';

function iom_viewboard_query($method, $params) {
    $ret = array(
                 'col' => array('sku', 'name', 'color', 'comment'),
                 'rows' => array(
                                 array("210210", '大衣', '白色', 'test'),
				 array("210210", '大衣', '白色', 'test')
                                 )
                 );
   return $ret;
}

//$GLOBALS['xmlrpc_internalencoding']='UTF-8';

$xmlrpc_server = xmlrpc_server_create();
xmlrpc_server_register_method($xmlrpc_server, "iom.viewboard.query", "iom_viewboard_query");
$request = $HTTP_RAW_POST_DATA;

$xmlrpc_response = xmlrpc_server_call_method($xmlrpc_server, $request, null);

header("Content-Type:text/xml");
echo $xmlrpc_response;
xmlrpc_server_destroy($xmlrpc_server);

?>