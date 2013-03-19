<?php
    include_once("Config.php");
    include_once("Utils.php");
    //网络获取通知内容
    //$xml = file_get_contents('php:input','r');
    //若不想网络环境测试，可打开下行注释，进行单元测试，上面一行会报WARNING,不用理会
	$xml ="<upomp application=\"TransNotify.Req\"  version=\"1.0.0\" ><transType>01</transType><merchantId>898000000000001</merchantId><merchantOrderId>22201111011010490000000506</merchantOrderId><merchantOrderAmt>1</merchantOrderAmt><settleDate>0420</settleDate><setlAmt>1</setlAmt><setlCurrency>156</setlCurrency><converRate></converRate><cupsQid>201111011016370201232</cupsQid><cupsTraceNum>020123</cupsTraceNum><cupsTraceTime>1101101637</cupsTraceTime><cupsRespCode>00</cupsRespCode><cupsRespDesc>Success!</cupsRespDesc><sign>j22MYWjysAmnRrWyeNFSU2RWQUJJie3K7o/tCEKpEsSgKvdV4aISwngMaBdlaK2GeV/JZBz86TpoD8RYit2pQbmxDdCgw2oXTmlq0lWI8c19JcPDg+hRaLGmNbg7JIjX7/cvOfKn0fkuUUPrIVT4VA8sOmxRyEKhvDkE1Y0wbIo=</sign><respCode></respCode></upomp>";
	$xmlDeal = new XmlUtils();
    // 解析获取到的xml
	$parse=$xmlDeal->readXml($xml);
    if ($parse) {
		 //获取键值对
		$nodeArray = $xmlDeal->getNodeArray();
		//验签
		$checkIdentifier = "transType=".$nodeArray['transType'].
            "&merchantId=".$nodeArray['merchantId'].
			"&merchantOrderId=".$nodeArray['merchantOrderId'].
            "&merchantOrderAmt=".$nodeArray['merchantOrderAmt'].
			"&settleDate=".$nodeArray['settleDate'].
            "&setlAmt=".$nodeArray['setlAmt'].
			"&setlCurrency=".$nodeArray['setlCurrency'].
            "&converRate=".$nodeArray['converRate'].
			"&cupsQid=".$nodeArray['cupsQid'].
            "&cupsTraceNum=".$nodeArray['cupsTraceNum'].
			"&cupsTraceTime=".$nodeArray['cupsTraceTime'].
            "&cupsRespCode=".$nodeArray['cupsRespCode'].
			"&cupsRespDesc=".$nodeArray['cupsRespDesc'].
            "&respCode=".$nodeArray['respCode'] ;
        $respCode=SecretUtils::checkSign($checkIdentifier,NOTIFY_public_key,$nodeArray['sign']);
        if($respCode=='0000'){
            //验签通过
        }else{
            if($respCode=='0001'){
                //验签失败 
            }
            if($respCode=='9999'){
                //验签过程发生异常 
            }
        }	
        //生成响应报文	
        $attrArray = array("application" =>"TransNotify.Rsp" ,"version"=>"1.0.0");
        $nodeArray = array("transType" =>$nodeArray['transType'] ,
            "merchantId"=>$nodeArray['merchantId'],
            "merchantOrderId"=>$nodeArray['merchantOrderId'],
            "respCode"=>$respCode);
        $result = XmlUtils::writeXml($attrArray,$nodeArray);
		echo $result ;
	}else{
	   echo "recieve notify message is xml";
	}
?>