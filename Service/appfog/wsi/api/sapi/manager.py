
from core.callable import Api
from core import router, path, reflection
import os
import inspect
import re

PAT_MODULE_FILE = re.compile('([a-zA-Z]+).pyc?')
PAT_MODULE = re.compile('([a-zA-Z]+)')

class Manager:
    
    @staticmethod
    def FindAll(curdir, curmodu, desdir, ret, cls):
        root = desdir
        if curdir:
            root = root + '/' + curdir
        for each in os.listdir(root):
            full = root + '/' + each
            if os.path.isfile(full):
                result = PAT_MODULE_FILE.search(each)
                if not result:
                    continue
                if curmodu:
                    modu = curmodu + '.' + result.group(1)
                else:
                    modu = result.group(1)
                Manager.FindModule(modu, ret, cls)
            elif os.path.isdir(full):
                result = PAT_MODULE.search(each)
                if not result:
                    continue
                if curmodu:
                    modu = curmodu + '.' + result.group(1)
                else:
                    modu = result.group(1)
                if curdir:
                    nextdir = curdir + '/' + each
                else:
                    nextdir = each
                Manager.FindAll(nextdir, modu, desdir, ret, cls)
                
    @staticmethod
    def FindModule(modu, ret, cls):    
        if modu in ret:
            return
        try:
            exec 'import ' + modu
            exec 'mod = ' + modu
        except:
            mod = None
        if not mod:
            return
        classes = inspect.getmembers(mod, inspect.isclass)
        if not len(classes):
            return
        found = []
        for clsname, clsobj in classes:
            clsmod = clsobj.__module__
            if clsmod != modu:
                continue
            if not reflection.Class.IsChildOf(clsobj, cls):
                continue
            found.append((modu, clsname, clsobj))
        if found:
            ret.append(found)
            
class All(Api):
    '''
    @summary: List all Apis.
    '''
        
    def run(self):
        found = []
        ret = {}
        Manager.FindAll(None, None, path.WSI, found, Api)
        for each in found:
            members = {}
            for modu, clsname, clsobj in each:
                method = clsname.lower()
                info = inspect.getargspec(clsobj.run)
                if info.defaults:
                    argreq = info.args[1:-len(info.defaults)]
                    argopt = info.args[-len(info.defaults):]
                else:
                    argreq = info.args[1:]
                    argopt = []
                members[method] = [argreq, argopt]
            if len(members):
                ret[modu] = members
        return ret
    