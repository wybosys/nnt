package nnt.cross

import sun.net.www.protocol.http.HttpURLConnection

class RpcHttp extends Rpc {
    
    var method = "GET"   

    def call(model:nnt.model.Model, url:java.net.URL) :Any = {
        trace(url)
        
        val parser = model.objparser
        if (parser == null) {
            trace("object parser is nil, skip")
            return null
        }
        
        this.begin_call()
                
        // connect.
        val cnt = url.openConnection().asInstanceOf[HttpURLConnection]
        cnt.setRequestProperty("Content-Type", parser.content_type())
        cnt.setRequestMethod(this.method)
        
        // write params.
        val params = model.get_params()
        var str_params = parser.parse_tostring(params)
        if (str_params != null) {
            cnt.setRequestProperty("Content-length", str_params.length.toString())
            var writer = new java.io.OutputStreamWriter(cnt.getOutputStream())
            writer.write(str_params)
        }
        
        // get data.
        var lines = new java.lang.StringBuilder()
        try {
            var reader = new java.io.BufferedReader(new java.io.InputStreamReader(cnt.getInputStream()))
            var line:String = null
            while ({
                line = reader.readLine()
                line != null
            }) { 
                lines.append(line)
            }
        } catch {
            case e:Exception => trace(e.getLocalizedMessage())
        }
        
        // process
        var ret:Any = null
        if (lines != null) {
            trace(lines)
            ret = parser.parse_object(lines.toString())
        } else {
            trace("null response")
        }
        
        this.end_call()
        return ret
    }
    
}

class GetHttp extends RpcHttp {
	this.method = "GET"
}

class PostHttp extends RpcHttp {
    this.method = "POST"
}