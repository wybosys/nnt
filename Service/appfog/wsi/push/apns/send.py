
from core.callable import Api
import manager

class One(Api):
    
    def invoke(self, req):
        if self.run(self.id, self.msg) is False:
            return self.failed()
        return self.succeed()
    
    def run(self, id, msg):
        if manager.Get().run(id) is None:
            return False
        return True

class All(Api):

    def invoke(self, req):
        return self.succeed()
    
    def run(self, msg):
        pass
    