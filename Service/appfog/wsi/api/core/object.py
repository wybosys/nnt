
import settings

def dtrace(obj):
    if settings.DEBUG:
        print repr(obj)
        
def dthrow(obj):
    if settings.DEBUG:
        raise obj

class Object(object):
    
    def __init__(self):
        pass
    
    def run(self):        
        return None
    
    def is_debug(self):
        return settings.DEBUG
    
    def is_release(self):
        return not settings.DEBUG
    
    def dtrace(self, obj):
        dtrace(obj)
        
    def dexcept(self):
        if settings.DEBUG:
            raise
        
    def dthrow(self, obj):
        dthrow(obj)
    