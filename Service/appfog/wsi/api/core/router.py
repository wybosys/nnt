
from object import Object
import logger 
import re

class Normal(Object):    
        
    def instance(self):
        pass

class Invoke(Normal):
    
    method = ''        
    user = None
    group = None
    _comps = []
    _re_comps = re.compile('([a-zA-Z0-9]+)') 
    
    def __init__(self, method):
        self.set_method(method)
        super(Invoke, self).__init__()
        
    def set_method(self, str):
        self.method = str.lower()
        self._comps = re.findall(self._re_comps, self.method)
    
    def instance(self):
        ret = None
        prefix = self.prefix()
        if prefix:        
            ret = self.direct_instance(prefix + '.')
            if not ret:
                ret = self.direct_instance('')
        else:
            ret = self.direct_instance('')
        if not ret:
            logger.invoke.error('failed to instance object: ' + self.method)
        return ret
    
    def direct_instance(self, prefix):
        modu = prefix + self.module_name()
        # load target module.
        try:
            loaded = True
            exec 'import ' + modu
        except:
            loaded = False
        if not loaded:            
            return None        
        # instance callable object.
        try:
            exec 'obj = ' + modu + '.' + self.class_name() + '()'
        except:            
            obj = None
        # try to instace impl object.
        if not obj:
            try:
                exec 'import ' + prefix + self.method
                exec 'obj = ' + prefix + self.method + '.Impl()'
            except:
                pass
        # bind run handler.
        if obj:
            obj.user = self.user
            obj.group = self.group
        return obj
    
    def prefix(self):
        if self.user:
            if self.user.prefix:
                return self.user.prefix
        if self.group:
            if self.group.prefix:
                return self.group.prefix
        return None
    
    def module_name(self):
        if len(self._comps) == 1:
            return self.method
        return '.'.join(self._comps[:-1])
    
    def class_name(self):       
        if len(self._comps) == 1:
            return 'Impl' 
        return self._comps[-1].capitalize()
    