<?php

// settings
define('StoreDBHost', 'localhost');

// mysql
define('StoreDBType', 'mysql');
define('StoreDBPort', '3306');
define('StoreDBDb', 'cwreport');
define('StoreDBUsername', 'root');
define('StoreDBPassword', 'root');
define('StoreDBCharset', 'utf8');

// sqlserver
//define('StoreDBType', 'mssql');
//define('StoreDBPort', '');
//define('StoreDBUsername', 'sa');
//define('StoreDBPassword', 'root');

define('TablePrefix', '');

// Version
define('Version', '1.3.22');

// server setting
define( "defaultAccessibility", "public" );
if ( ! defined("handleQooxdooDates") )
{
  define( "handleQooxdooDates", true );
}

?>
