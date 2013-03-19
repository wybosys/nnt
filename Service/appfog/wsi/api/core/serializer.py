
class Normal:
    
    def write(self, obj):
        return repr(obj)
    
import json

class Json(Normal):
    
    def write(self, obj):
        return json.dumps(obj, indent=1)
    