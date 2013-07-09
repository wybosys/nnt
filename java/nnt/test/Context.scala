package nnt.test

import nnt.context.SERV

object Context extends Test {

    def run() :Unit = {
        
        class PTest extends nnt.parser.JsonObjParser {
            
        }

        class MTest extends nnt.model.Model {
            this.url = "http://192.168.158.151/?app_fmt=json&app_act=sapi/sapi/test"
            this.classRpc = classOf[nnt.cross.RpcHttp]      
            this.objparser = new PTest()
        }
     
        SERV.retrieve_model(new MTest())
        SERV.retrieve_model_async(new MTest, this, this.method("mdl_test"))
        SERV.retrieve_model_async(new MTest, this, this.method("mdl_model", classOf[nnt.model.Model]))
    }   
    
    def mdl_test() = {
        trace("mdl")
    }
    
    def mdl_model(mdl:nnt.model.Model) = {
        trace("mmm")
    }
    
}