package wsi.test

import wsi.context.SERV

object Context extends Test {

    def run() :Unit = {
        
        class PTest extends wsi.parser.JsonObjParser {
            
        }

        class MTest extends wsi.model.Model {
            this.url = "http://192.168.158.151/?app_fmt=json&app_act=sapi/sapi/test"
            this.classRpc = classOf[wsi.cross.RpcHttp]      
            this.objparser = new PTest()
        }
     
        SERV.retrieve_model(new MTest())
        SERV.retrieve_model_async(new MTest, this, this.method("mdl_test"))
        SERV.retrieve_model_async(new MTest, this, this.method("mdl_model", classOf[wsi.model.Model]))
    }   
    
    def mdl_test() = {
        trace("mdl")
    }
    
    def mdl_model(mdl:wsi.model.Model) = {
        trace("mmm")
    }
    
}