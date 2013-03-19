
from core.callable import Api
from core.router import Invoke

class Find(Api):
    '''
    @summary: Find doc for target.    
    @param target: a module is known as method.
    '''
    
    def invoke(self, req):
        ret = self.run(self.target)
        if ret == None:
            self.file_not_found()
            return False
        return self.succeed(ret)
    
    def run(self, target):        
        ivk = Invoke(target)        
        obj = ivk.instance()
        if not obj:
            return None
        if obj.__doc__:
            return obj.__doc__
        return ''
