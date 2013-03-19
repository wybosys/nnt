
from core.callable import Api
from core.router import Invoke
from auth import group, user

class Find(Api):
    '''
    @summary: Find Right of Api.
    @param target: API full method.
    '''
    
    def invoke(self, req):
        return self.succeed(self.run(self.target))
    
    def run(self, target):
        ivk = Invoke(target)        
        obj = ivk.instance()
        if not obj:
            return None
        right = obj.right
        usr = user.User.FindById(right.uid)
        grp = group.Group.FindById(right.gid)        
        return {
                'user': usr.name,
                'group': grp.name,
                'right': [right.is_execute(right.user()),
                          right.is_execute(right.group()),
                          right.is_execute(right.other())]
                }
    