
from object import Object
from auth import user, group
import logger

SUCCESS = 0
LOST_ARGUMENT = 1
FAILED_SIGN = 2
FAILED_PERMISSION = 3

def check_test(sign):
    return sign == 'test'

class Normal(Object):    
    
    def check(self, arg):
        return SUCCESS
    
    def filter(self, arg):
        return arg
    
class Argument(Normal):   
    
    method = ''
    appid = ''
    sign = ''
             
    def check(self, arg):
        if 'appid' not in arg or 'method' not in arg or 'sign' not in arg:
            return LOST_ARGUMENT
        appid = arg['appid']
        method = arg['method']
        sign = arg['sign']
        if not check_test(sign):
            return FAILED_SIGN
        return SUCCESS
     
    def filter(self, arg):
        arg = arg.copy()        
        self.appid = arg.pop('appid')[0]
        self.method = arg.pop('method')[0]
        self.sign = arg.pop('sign')[0]
        try:
            arg.pop('odd')
        except:
            pass
        return arg
             
class Invoke(Argument):        
    
    user = None
    group = None
    
    def check(self, arg):
        ret = Argument.check(self,arg)
        if ret != SUCCESS:
            return ret
        appid = arg['appid']
        # check appid if is in database.
        self.user = user.User.FindByAppId(appid)        
        if not self.user:
            logger.invoke.error('client send a wrong app-id: ' + appid)
            return FAILED_PERMISSION
        self.group = group.Group.FindById(self.user.gid)
        return SUCCESS
    
    def filter(self, arg):
        return Argument.filter(self, arg)
    
    