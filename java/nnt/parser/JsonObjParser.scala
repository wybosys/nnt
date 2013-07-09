package nnt.parser

class JsonObjParser extends AbstractObjParser {
	
  override def parse_object(data: String): Any = {
	 super.parse_object(data)
	 
	 val json = util.parsing.json.JSON.parseFull(data)
	 return json
  }
  
}