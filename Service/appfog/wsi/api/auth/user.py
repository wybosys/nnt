
from core.callable import Api
from core import account
import models

class User:
    
    @staticmethod
    def FindByName(name):
        recs = models.Auth_User.objects.filter(user_name=name)
        if not recs:
            return None
        return recs.get().to_user()
    
    @staticmethod
    def FindById(id):
        recs = models.Auth_User.objects.filter(user_id=id)
        if not recs:
            return None
        return recs.get().to_user()
    
    @staticmethod
    def FindByAppId(appid):
        recs = models.Auth_User.objects.filter(app_id=appid)
        if not recs:
            return None
        return recs.get().to_user()
    
    @staticmethod
    def NewUserId(id=account.UID_USER):
        if not User.FindById(id):
            return id
        return User.NewUserId(id + 1)
    
    @staticmethod
    def NewAppId():        
        import md5, uuid
        return md5.md5(str(uuid.uuid4())).hexdigest()
    
class Add(Api):
    '''
    @summary: add a new user.
    @param name: user name.
    @param uid: user id (may auto).
    @param gid: group id (may auto).
    @param prefix: user's home directory. 
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
        ret = self.run(self.name, self.uid, self.gid, self.prefix, self.comment)
        if not ret:
            return self.failed(self.ERROR_DUPLICATE)
        return self.succeed(ret)
    
    def run(self, name, uid=account.UID_AUTO, gid=account.GID_ANONY, prefix='', comment=''):
        found = User.FindByName(name)
        if found:
            return None
        found = User.FindById(gid)
        if found:
            return None
        if uid == account.UID_AUTO:
            uid = User.NewUserId()
        one = models.Auth_User()
        one.user_name = name
        one.user_id = uid
        one.group_id = gid
        one.app_id = User.NewAppId()
        one.app_secret = ''
        one.comment = comment
        one.save()
        return {'name':name, 'uid':uid, 'gid':gid}
    
class All(Api):
    '''
    @summary: List all users.
    '''
    
    def invoke(self, req):        
        ret = []
        for each in self.run():
            ret.append({
                        'name': each.name,
                        'uid': each.uid,
                        'gid': each.gid,
                        'prefix': each.prefix
                        })
        return self.succeed(ret)
    
    def run(self):
        ret = []
        for each in models.Auth_User.objects.all():
            ret.append(each.to_user())            
        return ret

class Login(Api):
    '''
    @summary: login WAE system.
    @param user: user name.
    @param passwd: password.
    @param plain: 0 | 1, default is 0  
    '''
    
    def invoke(self, req):
        usr = self.run(self.user, self.passwd, self.plain)
        if not usr:
            return self.failed()
        ret = {'name': usr.user_name,
               'appid': usr.app_id
               }
        return self.succeed(ret)
    
    def run(self, user, passwd, plain = 0):
        user = models.Auth_User.objects.filter(user_name=user)
        if not user:
            return None
        user = user.get()
        if not user.user_passwd:
            return None
        if plain == 0:
            if user.user_passwd != passwd:
                return None
        else:
            from passwd import Encode
            key = Encode().run(passwd)
            if user.user_passwd != key:
                return None
        return user
    
