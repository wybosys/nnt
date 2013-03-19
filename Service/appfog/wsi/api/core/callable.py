
from core.object import Object
import response
import inspect
import account 

class Callable(Object):
    
    result = None    
    retcode = response.SUCCESS
    
    def check(self, arg):        
        # check params.
        argsinfo = inspect.getargspec(self.run)
        argsopt = {}
        if argsinfo.defaults != None:
            for i in range(1, 1 + len(argsinfo.defaults)):
                argsopt[argsinfo.args[-i]] = argsinfo.defaults[-i]
            argsreq = argsinfo.args[1:-len(argsopt)]
        else:
            argsreq = argsinfo.args[1:]
        if not self.parameter(arg, argsreq, argsopt):
            return False
        return True
    
    def invoke(self, req):
        self.pass_parameter()
        return self.succeed(self.run())
    
    def failed(self, code = 0):
        self.retcode = code
        return False
    
    def succeed(self, result = None):
        self.retcode = response.SUCCESS
        self.result = result
        return True
    
    def lost_parameter(self):
        return self.failed(response.ARGUMENT | response.LOST)
    
    def more_parameter(self):
        return self.failed(response.ARGUMENT | response.OVERFLOW)
        
    def invalid_parameter(self):
        return self.failed(response.ARGUMENT | response.INVALID)
        
    def pass_parameter(self):
        return self.succeed(response.SUCCESS)
        
    def file_not_found(self):
        return self.failed(response.LOST | response.HANDLE)
    
    def parameter(self, arg, requires, optionals = {}):
        des_len = len(requires)
        res_len = len(arg)
        if des_len > res_len:
            return self.lost_parameter()
        elif des_len < res_len - len(optionals):
            return self.more_parameter()
        for each in arg:
            if each not in requires:
                if each not in optionals:
                    return self.invalid_parameter()
        # check and set parameter as member.
        for each in requires:
            if each not in arg:
                return self.invalid_parameter()
            setattr(self, each, arg[each])
        for each in optionals:
            if each in arg:
                setattr(self, each, arg[each])
            else:
                setattr(self, each, optionals[each])
        return self.pass_parameter()
        
import permission

class Api(Callable):

    right = None
    user = None
    group = None
    
    def __init__(self):
        self.right = permission.Right()
    
    def nopermission(self):
        return self.failed(response.PERMISSION | response.INVALID)
    
    def check(self, arg):
        # check right.
        # if is in wheel group, run always.
        # out wheel group, compare with right of api.
        if self.user.gid != account.GID_WHEEL:
            inright = permission.Right()
            inright.uid = self.user.uid
            inright.gid = self.user.gid
            if not self.right.check(inright):
                return self.nopermission()
        # check arg.
        if not Callable.check(self, arg):
            return False
        return True
    