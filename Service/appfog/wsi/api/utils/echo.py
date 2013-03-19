
from core.callable import Api

class Impl(Api):    
    '''
    @summary: like 'echo' command, print input message.
    @param data: message.
    '''
            
    def invoke(self, req):        
        return self.succeed(self.run(self.data))

    def run(self, data):
        return data
    