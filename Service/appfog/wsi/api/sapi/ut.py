
from core.callable import Api
from core import path
from core.ut import Ut
import manager

class All(Api):
    '''
    @summary: List all unittest case.
    '''
    
    def run(self):
        found = []
        manager.Manager.FindAll(None, None, path.WSI, found, Ut)
        ret = []        
        for each in found:
            members = {}
            for modu, clsname, clsobj in each:
                method = clsname.lower()
                ret.append(method)
        return ret
