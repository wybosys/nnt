<?php
include_once ("Config.php");
include_once ("Utils.php");
define("CANCEL","31");
define("REFUND","04");

class CancelRefundEntity
{
    static function getXml($transType,$merchantOrderId, $merchantOrderTime,$merchantOrderAmt,$cupsQid,$backEndUrl)
    {
        $merchantPublicCert = SecretUtils::getPublicKeyBase64(MY_public_key);
        // echo  $merchantPublicCert;
        $merchantId = MY_id;
        $strForSign = "merchantId=" . $merchantId .
            "&merchantOrderId=" . $merchantOrderId . 
            "&merchantOrderTime=" . $merchantOrderTime.
            "&merchantOrderAmt=" . $merchantOrderAmt .
            "&cupsQid=" . $cupsQid.
            "&backEndUrl=" .$backEndUrl;
        //echo $strForSign;
        $sign = SecretUtils::sign($strForSign, MY_private_key, MY_prikey_password);
        $application="";
        if($transType==CANCEL)
            $application="Cancel.Req";
        else if($transType==REFUND)
            $application="Refund.Req";
        $attrArray = array("application" => $application, "version" => "1.0.0");
        $nodeArray = array("merchantId" => $merchantId,
            "merchantOrderId" => $merchantOrderId, 
            "merchantOrderTime" => $merchantOrderTime,
            "merchantOrderAmt"=>$merchantOrderAmt,
            "cupsQid"=>$cupsQid,
            "backEndUrl"=>$backEndUrl,
            "sign" => $sign, 
            "merchantPublicCert" => $merchantPublicCert);
        $result = XmlUtils::writeXml($attrArray, $nodeArray);
        return $result;
    }
}
//退货REFUND，或者$transType="04"  
//撤销CANCEL，或者$transType="31"
$transType=REFUND;
$merchantOrderId="201110121032192";
$merchantOrderTime="20111012103219";
$merchantOrderAmt="1";
$cupsQid="015582";
$backEndUrl="WWW.163.COM";
$xml = CancelRefundEntity::getXml($transType,$merchantOrderId, $merchantOrderTime,$merchantOrderAmt,$cupsQid,$backEndUrl);
$postDeal = new PostUtils();
$recv = $postDeal->submitByPost(SUBMIT_url, $xml);
$xmlDeal = new XmlUtils();
$parse= $xmlDeal->readXml($recv);
if ($parse) { 
    $nodeArray = $xmlDeal->getNodeArray();
    //验签
    $checkIdentifier = "merchantId=" . $nodeArray['merchantId'] .
        "&merchantOrderId=" . $nodeArray['merchantOrderId'] . 
        "&merchantOrderTime=" . $nodeArray['merchantOrderTime'] .
        "&merchantOrderAmt=" . $nodeArray['merchantOrderAmt'] . 
        "&cupsQid=" . $nodeArray['cupsQid'] .
        "&respCode=" . $nodeArray['respCode'] ;
    $respCode = SecretUtils::checkSign($checkIdentifier, UPOMP_public_key, $nodeArray['sign']);
    
    if ($respCode == '0000') {
        //验签通过
        echo "验签通过,respCode=".$nodeArray['respCode'];
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