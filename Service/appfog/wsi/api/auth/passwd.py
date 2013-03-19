
from core.callable import Api
import md5

class Encode(Api):
    '''
    @summary: encode plain password to security password.
    @param plain: plain password.
    '''
    
    def invoke(self, req):
        return self.succeed(self.run(self.plain))
    
    def run(self, plain):
        mtd = 'wae/' + plain
        res = md5.md5(mtd).hexdigest().lower()
        res = md5.md5(res).hexdigest().lower()
        return res
    
