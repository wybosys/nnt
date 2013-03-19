
import inspect

class Class:
    
    @staticmethod
    def IsChildOf(lc, rc):
        tree = inspect.getclasstree([lc])        
        clsmap = tree[0]
        if clsmap[0] == rc:
            return True
        if not clsmap[1]:
            return False
        return Class.IsChildOf(clsmap[0], rc)
    