
from core.callable import Api
import uuid

class New(Api):
    
    def invoke(self, req):
        return self.succeed(self.run())
    
    def run(self):
        return str(uuid.uuid4())
    