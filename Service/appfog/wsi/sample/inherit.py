
from core.callable import Api

class Base(Api):
    '''
    @summary: base api class.
    '''
    
    def run(self):
        return 'Base'
    
class Impl(Base):
    '''
    @summary: show how to inhert a api class.
    '''
    
    def run(self):
        return super(Impl, self).run() + ' Impl'
    