<?php

$socket = socket_create(AF_INET, SOCK_STREAM, SOL_TCP);
socket_connect($socket, '127.0.0.1', 9090);
socket_write($socket, "XXXX");
return;
echo "wait accept</br>";
$rec = socket_read($socket, 6);
if ($rec != "ACCEPT") {
	echo "error</br>";
	exit;
} else {
	echo "got ACCEPT</br>";
}

echo "send identity</br>";
echo socket_write($socket, "TEST");

echo "receieve server-pub key</br>";