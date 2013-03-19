
from core.callable import Api

class Impl(Api):
    '''
    @summary: Show 'Hello, World' message.
    '''
    
    def run(self):
        return 'Hello, World!'