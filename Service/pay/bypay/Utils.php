<?php
class XmlUtils
{
    private $nodeArray; // upomp键值对集合
    private $attributeArray; //
    public function getNodeArray()
    {
        return $this->nodeArray;
    }
    public function getAttributeArray()
    {
        return $this->attributeArray;
    }
    public function readXml($xml)
    {
        $xml_parser = xml_parser_create();
        if (!xml_parse($xml_parser, $xml, true)) {
            xml_parser_free($xml_parser);
            return false;
        } else {
            // 创建xml对象
            $document = new DOMDocument("1.0", "utf-8");
            $document->loadXML($xml);
            $document->formatOutput = true;
            // 返回根节点
            $rootElement = $document->documentElement;
            // 根节点子节点集合
            $rootNodeList = $rootElement->childNodes;
            // 获取根节点 及其属性值
            for ($i = 0; $i < $rootElement->attributes->length; $i++) {
                $value = $rootElement->attributes->item($i)->value;
                $key = $rootElement->attributes->item($i)->name;
                // 存放进数组
                $this->attributeArray[$key] = $value;
            }
            for ($i = 0; $i < $rootNodeList->length; $i++) {
                $rootNode = $rootNodeList->item($i);

                if ($rootNode->nodeName == "#text") {
                    continue;
                } else {
                    // 判断子节点是否是叶节点
                    $key = $rootNode->nodeName;
                    $value = $rootNode->nodeValue;
                    // 存放进数组
                    $this->nodeArray[$key] = $value;
                }
            }
            return true;
        }
    }

    // 循环写入xml中的各个节点值(无list节点)
    public static function writeXml($attrArrays, $nodeArrays)
    {
        // 创建xml对象
        $document = new DOMDocument("1.0", "utf-8");
        $document->formatOutput = false;
        // 创建并添加根节点
        $root = $document->createElement("upomp");
        //根节点添加属性
        $id = array_keys($attrArrays);
        for ($i = 0; $i < count($id); $i++) {
            $attribute = $document->createAttribute($id[$i]);
            $attribute->appendChild($document->createTextNode($attrArrays[$id[$i]]));
            $root->appendChild($attribute);
        }
        $document->appendChild($root);
        //添加子节点
        $id = array_keys($nodeArrays);
        for ($i = 0; $i < count($id); $i++) {
            $element = $document->createElement($id[$i]);
            $element->appendChild($document->createTextNode($nodeArrays[$id[$i]]));
            $root->appendChild($element);
        }
        return $document->saveXML();
    }
}

class SecretUtils
{
    public static function sign($data, $privateKeyPath, $privateKeyPassword)
    {
        $dateMd5 = md5($data, true);
        $p12cert = array();
        $fd = fopen($privateKeyPath, 'r');
        $p12buf = fread($fd, filesize($privateKeyPath));
        fclose($fd);
        if (openssl_pkcs12_read($p12buf, $p12cert, $privateKeyPassword)) {
            $private_key = $p12cert['pkey'];
            //私钥加密
            openssl_private_encrypt($dateMd5, $crypted, $private_key);
            return base64_encode($crypted);
        } else {
            return "";
        }
    }
    public static function checkSign($data, $publicKeyPath, $cryptedStr)
    {
        $base64Sign = base64_decode($cryptedStr);
        $dateMd5 = md5($data, true);
        $fd1 = fopen($publicKeyPath, 'r');
        $p12buf1 = fread($fd1, filesize($publicKeyPath));
        fclose($fd1);
        $pem = chunk_split(base64_encode($p12buf1), 64, "\n");
        $pem = "-----BEGIN CERTIFICATE-----\n" . $pem . "-----END CERTIFICATE-----\n";
        //获取公钥
        $pem = openssl_pkey_get_public($pem);
        if (openssl_public_decrypt($base64Sign, $crypted, $pem)) {
            //验证签名信息
            if ($crypted == $dateMd5) {
                return "0000";
            } else {
                return "0001";
            }
        } else {
            return "9999";
        }
    }
    public static function getPublicKeyBase64($publicKeyPath)
    {
        $fd2 = fopen($publicKeyPath, 'r');
        $p12buf2 = fread($fd2, filesize($publicKeyPath));
        fclose($fd2);
        $pem = base64_encode($p12buf2);
        return $pem;
    }
}

class PostUtils
{
    //  function submitByPost($remote_server, $post_string)
    //    {
    //        echo "发送请求报文：".$post_string."<br>";
    //        $post_string=urlencode($post_string);
    //        $context = array('http' => array('method' => 'POST', 'header' =>
    //            'Content-type:text/plain', 'Content-length: ' . strlen($post_string)+8,
    //            'content' => $post_string));
    //        $stream_context = stream_context_create($context);
    //        $data = file_get_contents($remote_server, false, $stream_context);
    //        echo "接收响应报文：".$data."<br>";
    //        $data=urldecode($data);
    //        return $data;
    //    }
    function submitByPost($url, $post_string, $timeout = 30)
    {
        $post_string = urlencode($post_string);
        $URL_Info = parse_url($url);
        if (empty($URL_Info["port"]))
            $port = 80;
        else
            $port = $URL_Info["port"];
        if (($fsock = fsockopen($URL_Info["host"], $port, $errno, $errstr, $timeout)) <
            0)
            return "建立通讯连接失败";
        $in = "POST " . $URL_Info["path"] . " HTTP/1.0\r\n";
        $in .= "Accept: */*\r\n";
        $in .= "Host: " . $URL_Info["host"] . "\r\n";
        $in .= "Content-type: text/plain\r\n";
        $in .= "Content-Length: " . strlen($post_string) . "\r\n";
        $in .= "Connection: Close\r\n\r\n";
        $in .= $post_string . "\r\n\r\n";

        if (!@fwrite($fsock, $in, strlen($in))) {
            fclose($fsock);
            return "发送报文失败";
        }
        $out = "";
        while ($buff = fgets($fsock, 2048)) {
            $out .= $buff;
        }
        fclose($fsock);
        $pos = strpos($out, "\r\n\r\n");
        $head = substr($out, 0, $pos); //http head
        $status = substr($head, 0, strpos($head, "\r\n")); //http status line
        $status_arr = explode(" ", $status, 3);
        if ($status_arr[1] == 200) {
            $body = substr($out, $pos + 4, strlen($out) - ($pos + 4)); //page body
            $body = urldecode($body);
        } else {
            return "http " . $status_arr[1];
        }
        return $body;
    }
}
//$xmlDeal=new XmlUtils();
//$attrArray = array("application" =>"TransNotify.Rsp1" ,"version"=>"1.0.0");
//$nodeArray = array("transType" =>"1" ,"merchantId"=>"11","merchantOrderId"=>"1111","respCode"=>"111111");
//
//$result= $xmlDeal->writeXml($attrArray,$nodeArray);
//        // 返回响应XML
// $xmlDeal-> readXml ($result);
//
//  $nodeArray1= $xmlDeal->getAttributeArray();
//  echo $nodeArray1['version'];
//  echo $nodeArray1['application'];

?>