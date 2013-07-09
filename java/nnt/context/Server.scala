package nnt.context

import nnt.model.Model
import scala.actors._, Actor._

trait IServer extends nnt.core.Object {
    
    def retrieve_model (model:Model) :Boolean
    def retrieve_model_async (model:Model, obj:Object, sel:SEL) :Unit
    
}

class Server extends IServer {
    
    var classRpc:CLASS = null

    def retrieve_model (model: Model) :Boolean = {
        // get class for rpc.
        val cls_rpc = 
            if (model.classRpc != null) model.classRpc 
            else this.classRpc
        if (cls_rpc == null)
            return false     
            
        // get url for rpc.
        val url = model.get_url()
        
        // get data from cache.
        var result:Any = null
        if (model.cacheUpdate)
            result = null
        
        // get data from server.
        if (result == null) {            
            val rpc = cls_rpc.newInstance().asInstanceOf[nnt.cross.IRpc]
            result = rpc.call(model, url)
        }
        
        // process
        var ret:Boolean = false 
        if (result != null) {
            ret = model.process(result)                       
        }      
        
        return ret
    } 
    
    def retrieve_model_async(model:Model, obj:Object, sel:SEL) :Unit = {       
        val act = 
            actor {
        		var stop = false
        		while (stop == false) {
        		    receive {
        		        case "exit" => stop = true
        		        case params:List[Any] => {
        		            val model = params(0).asInstanceOf[Model]
        		            val obj = params(1).asInstanceOf[Object]
        		            val sel = params(2).asInstanceOf[SEL]
        		            if (true == this.retrieve_model(model)) {
        		                val params = sel.getParameterTypes()
        		                params.length match {
        		                    case 0 => {
        		                        sel.invoke(obj)
        		                    }
        		                    case 1 => {
        		                        sel.invoke(obj, model)
        		                    }
        		                }
        		            } else {
        		            	trace("failed to fetch model")
        		            }
        		        }
        		    }
        		}
        	}
        
        // run model
        act ! List(model, obj, sel)
    }
    
}

object SERV extends Server {       
    
}