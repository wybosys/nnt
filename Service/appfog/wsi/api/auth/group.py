
from core.callable import Api
from core import account
import models

class Group:
    
    @staticmethod
    def FindByName(name):
        recs = models.Auth_Group.objects.filter(group_name=name)
        if not recs:
            return None
        return recs.get().to_group()
        
    @staticmethod
    def FindById(id):
        recs = models.Auth_Group.objects.filter(group_id=id)
        if not recs:
            return None
        return recs.get().to_group()
        
    @staticmethod
    def NewGroupId(id=account.GID_USER):
        if not Group.FindById(id):
            return id
        return Group.NewGroupId(id + 1)

class Add(Api):
    '''
    @summary: add a new group.
    @param name: group name.
    @param gid: group id (may auto).
    @param prefix: group's home directory.
    @param comment: comment.
    @return: 0x1 => ERROR_DUPLICATE
    '''
    
    ERROR_DUPLICATE = 0x1
    
    def __init__(self):
        super(Add, self).__init__()
        self.right.uid = account.UID_ROOT
        self.right.gid = account.GID_WHEEL
        self.right.discard_other()   
    
    def invoke(self, req):
        ret = self.run(self.name, self.gid, self.prefix, self.comment)
        if not ret:
            return self.failed(self.ERROR_DUPLICATE)
        return self.succeed(ret)
    
    def run(self, name, gid=account.GID_AUTO, prefix='', comment=''):
        found = Group.FindByName(name)
        if found:
            return None
        found = Group.FindById(gid)
        if found:
            return None
        if gid == account.GID_AUTO:
            gid = Group.NewGroupId()
        one = models.Auth_Group()
        one.group_name = name
        one.group_id = gid
        one.prefix = prefix
        one.comment = comment
        one.save()
        return {'name':name, 'gid':gid}
    
class All(Api):
    '''
    @summary: List all groups.
    '''
    
    def invoke(self, req):
        grps = self.run()
        ret = []
        for each in grps:
            ret.append({
                        'name': each.name,
                        'gid': each.gid,
                        'prefix': each.prefix
                        })
        return self.succeed(ret)
    
    def run(self):
        ret = []
        for each in models.Auth_Group.objects.all():
            ret.append(each.to_group())
        return ret
    
class Find(Api):
    '''
    @summary: Find a group.
    '''
    
    def invoke(self, req):
        grp = self.run(self.id, self.name)
        try:       
            grp = grp.get().to_group()
            ret = {
                   'name': grp.name,
                   'gid': grp.gid,
                   'prefix': grp.prefix
                   }
        except:
            ret = None
        if not ret:
            return self.failed()
        return self.succeed(ret)
    
    def run(self, id=None, name=None):
        recs = models.Auth_Group.objects
        if id:
            recs = recs.filter(group_id=id)
        if name:
            recs = recs.filter(group_name=name)        
        return recs
    
