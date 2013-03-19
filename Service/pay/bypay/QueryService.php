<?php
include_once ("Config.php");
include_once ("Utils.php");
class QueryEntity
{
    static function getXml($transType, $merchantOrderId, $merchantOrderTime)
    {
        $merchantPublicCert = SecretUtils::getPublicKeyBase64(MY_public_key);
        // echo  $merchantPublicCert;
        $merchantId = MY_id;
        $strForSign = "transType=" . $transType . 
            "&merchantId=" . $merchantId .
            "&merchantOrderId=" . $merchantOrderId . 
            "&merchantOrderTime=" . $merchantOrderTime;
        //echo $strForSign;
        $sign = SecretUtils::sign($strForSign, MY_private_key, MY_prikey_password);

        $attrArray = array("application" => "QueryOrder.Req", "version" => "1.0.0");
        $nodeArray = array("transType" => $transType, 
            "merchantId" => $merchantId,
            "merchantOrderId" => $merchantOrderId, 
            "merchantOrderTime" => $merchantOrderTime,
            "sign" => $sign, 
            "merchantPublicCert" => $merchantPublicCert);
        $result = XmlUtils::writeXml($attrArray, $nodeArray);
        return $result;
    }
}
$transType="01";
$merchantOrderId="22201111010125560000000519";
$merchantOrderTime="20111101012556";
$xml = QueryEntity::getXml($transType, $merchantOrderId, $merchantOrderTime);
$postDeal = new PostUtils();
$recv = $postDeal->submitByPost(SUBMIT_url, $xml);
$xmlDeal = new XmlUtils();
$parse= $xmlDeal->readXml($recv);
if ($parse) {
    $nodeArray = $xmlDeal->getNodeArray();
    //验签
    $checkIdentifier = "transType=" . $nodeArray['transType'] .
        "&merchantId=" . $nodeArray['merchantId'] .
        "&merchantOrderId=" . $nodeArray['merchantOrderId'] . 
        "&merchantOrderTime=" . $nodeArray['merchantOrderTime'] .
        "&queryResult=" . $nodeArray['queryResult'] . 
        "&settleDate=" . $nodeArray['settleDate'] .
        "&setlAmt=" . $nodeArray['setlAmt'] . 
        "&setlCurrency=" . $nodeArray['setlCurrency'] .
        "&converRate=" . $nodeArray['converRate'] . 
        "&cupsQid=" . $nodeArray['cupsQid'] .
        "&cupsTraceNum=" . $nodeArray['cupsTraceNum'] . 
        "&cupsTraceTime=" . $nodeArray['cupsTraceTime'] .
        "&cupsRespCode=" . $nodeArray['cupsRespCode'] . 
        "&cupsRespDesc=" . $nodeArray['cupsRespDesc'] .
        "&respCode=" . $nodeArray['respCode'];
    $respCode = SecretUtils::checkSign($checkIdentifier, UPOMP_public_key, $nodeArray['sign']);
    
    if ($respCode == '0000') {
        //验签通过
        echo "验签通过,respCode=".$nodeArray['respCode'].";queryResult=" . $nodeArray['queryResult'];
    } else {
        if ($respCode == '0001') {
            //验签失败
            echo "验签失败";
        }
        if ($respCode == '9999') {
            //验签过程发生异常
        }
    }
} else {
    echo "失败,接收返回：".$recv;
}
?>