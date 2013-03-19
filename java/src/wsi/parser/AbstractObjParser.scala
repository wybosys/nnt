package wsi.parser

abstract class AbstractObjParser extends IObjParser {
  
  def parse_tostring(obj: Any): String = null
  
  def content_type(): String = "text/plain"
    
  def parse_object(data: String): Any = {
	this.byteCount += data.length
	null
  }
    
  var byteCount: Long = 0
  
}