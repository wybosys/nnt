
from django.db import models
from wsi.api.core import account

class Auth_User(models.Model):
    
    class Meta:
        app_label = 'api'
    
    user_name = models.TextField()
    user_id = models.IntegerField(unique=True)
    user_passwd = models.TextField(null=True)
    group_id = models.IntegerField()
    app_id = models.TextField()
    app_secret = models.TextField()
    prefix = models.TextField(null=True)
    comment = models.TextField(null=True)
    
    def to_user(self):
        ret = account.User()
        ret.name = self.user_name
        ret.uid = self.user_id
        ret.gid = self.group_id
        ret.prefix = self.prefix
        return ret
    
class Auth_Group(models.Model):
    
    class Meta:
        app_label = 'api'
    
    group_name = models.TextField()
    group_id = models.IntegerField(unique=True)
    prefix = models.TextField(null=True)
    comment = models.TextField(null=True)
    
    def to_group(self):
        ret = account.Group()
        ret.name = self.group_name
        ret.gid = self.group_id
        ret.prefix = self.prefix
        return ret
    