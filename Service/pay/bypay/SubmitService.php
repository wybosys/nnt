<?php
include_once ("Config.php");
include_once ("Utils.php");
class SubmitEntity
{
    static function getXml($merchantOrderId, $merchantOrderTime,$merchantOrderAmt,$merchantOrderDesc,$transTimeout,$backEndUrl)
    {
        
        $merchantPublicCert = SecretUtils::getPublicKeyBase64(MY_public_key);
        // echo  $merchantPublicCert;
        $merchantId = MY_id;
        $merchantName=MY_name;
        $strForSign = "merchantName=" . $merchantName . 
            "&merchantId=" . $merchantId .
            "&merchantOrderId=" . $merchantOrderId . 
            "&merchantOrderTime=" . $merchantOrderTime.
            "&merchantOrderAmt=" . $merchantOrderAmt . 
            "&merchantOrderDesc=" . $merchantOrderDesc.
            "&transTimeout=" .$transTimeout;
        //echo $strForSign;
        $sign = SecretUtils::sign($strForSign, MY_private_key, MY_prikey_password);

        $attrArray = array("application" => "SubmitOrder.Req", "version" => "1.0.0");
        $nodeArray = array("merchantName" => $merchantName,
            "merchantId" => $merchantId,
            "merchantOrderId" => $merchantOrderId, 
            "merchantOrderTime" => $merchantOrderTime,
            "merchantOrderAmt"=>$merchantOrderAmt,
            "merchantOrderDesc"=>$merchantOrderDesc,
            "transTimeout"=>$transTimeout,
            "backEndUrl"=>$backEndUrl,
            "sign" => $sign, 
            "merchantPublicCert" => $merchantPublicCert);
        $result = XmlUtils::writeXml($attrArray, $nodeArray);
        return $result;
    }
}
$merchantOrderId="123234244";
$merchantOrderTime="20111012135602";
$merchantOrderAmt="1";
$merchantOrderDesc="自动订购";
$transTimeout="20111012135802";
$backEndUrl="WWW.163.COM";
$xml = SubmitEntity::getXml($merchantOrderId, $merchantOrderTime,$merchantOrderAmt,$merchantOrderDesc,$transTimeout,$backEndUrl);
$postDeal = new PostUtils();
$recv = $postDeal->submitByPost(SUBMIT_url, $xml);
$xmlDeal = new XmlUtils();
$parse= $xmlDeal->readXml($recv);
if ($parse) {
    $nodeArray = $xmlDeal->getNodeArray();
    echo "respCode=".$nodeArray['respCode'];
} else {
    echo "失败,接收返回：".$recv;
}
?>