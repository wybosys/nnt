
# set sys path.
from core import path
import sys

sys.path.insert(0, path.WSI)
sys.path.insert(0, path.API)

# dispatch
from core import response
from core import validator
from core import router

def dispatch(req):
    resp = response.Normal()
    
    # GET request.
    if req.method == 'GET':
        arg = req.GET        
        vdr = validator.Invoke()
        vdr_result = vdr.check(arg)
        if vdr_result == validator.SUCCESS:
            # remove non-use arguments.
            param = vdr.filter(arg)            
            # init response.
            resp.init(param)
            param = resp.filter(param)            
            # router request.
            rtr = router.Invoke(vdr.method)
            rtr.user = vdr.user
            rtr.group = vdr.group
            # get the object.
            obj = rtr.instance()
            if obj == None:
                return resp.failed(response.LOST | response.HANDLE)
            # check for call.
            if not obj.check(param):                  
                return resp.failed(obj.retcode)
            # call routine.
            if not obj.invoke(req):            
                return resp.failed(obj.retcode)
            return resp.succeed(obj.result)
        elif vdr_result == validator.LOST_ARGUMENT:
            return resp.failed(response.LOST | response.ARGUMENT)
        elif vdr_result == validator.FAILED_SIGN:
            return resp.failed(response.INVALID | response.ARGUMENT | response.SIGN)
        elif vdr_result == validator.FAILED_PERMISSION:
            return resp.failed(response.INVALID | response.PERMISSION)
        else:
            return resp.failed()

    # POST request.
    return resp.failed()
