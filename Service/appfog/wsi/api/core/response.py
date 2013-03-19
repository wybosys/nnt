
from django.http import HttpResponse
import serializer

# predefined status.
SUCCESS = 0

# 0x10000000
FAILED = 0 - (0x1 << 28)

# 0x00000F00
NOMETHOD = 0x1 << 8
ARGUMENT = 0x2 << 8
PERMISSION = 0x4 << 8
HANDLE = 0x8 << 8
TIMEOUT = 0x10 << 8
SIGN = 0x20 << 8

# 0x0F000000
LOST = 0x1 << 24
OVERFLOW = 0x2 << 24
INVALID = 0x3 << 24
DUPLICATE = 0x4 << 24
    
# predefined object.
Empty = None
    
def Format(fmt, code, result):
    obj = {'code':code, 'result':result}
    obj = fmt.write(obj)
    return HttpResponse(obj)
    
def Success(fmt, result=Empty):
    return Format(fmt, SUCCESS, result)
    
def Failed(fmt, code=0, result=Empty):
    tcode = FAILED - code
    return Format(fmt, tcode, result)

class Normal:
    
    serializer = serializer.Json()
    
    def init(self, arg):
        if 'type' in arg:
            self.serializer = {
             'json': lambda: serializer.Json(),
             'raw': lambda: serializer.Normal(),
            } [arg['type']]()
    
    def filter(self, arg):
        arg = arg.copy()
        try:
            arg.pop('format')
        except:
            pass
        return arg
    
    def succeed(self, result=Empty):
        return Success(self.serializer, result)
        
    def failed(self, code=0, result=Empty):
        return Failed(self.serializer, code, result)
    