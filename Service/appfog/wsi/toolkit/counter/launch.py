
from core.callable import Api
from toolkit import models
from core import account

class Increase(Api):
    '''
    @summary: Increase launch counter.
    @param name: name of app.
    @param id: identity of app. (bundle identity in iOS)
    '''
    
    def __init__(self):
        super(Increase, self).__init__()
        self.right.uid = account.UID_TOOLKIT
        self.right.gid = account.GID_TOOLKIT
        self.right.discard_other()
        
    def invoke(self, req):        
        self.run(self.name, self.id)
        return self.succeed()
    
    def run(self, name, id):
        rec = models.Counter.objects.filter(app_name=name).filter(app_identity=id)
        if len(rec):
            rec = rec[0]
            rec.launch_counter = rec.launch_counter + 1
            rec.save()
        else:
            rec = models.Counter()
            rec.app_name = name
            rec.app_identity = id
            rec.launch_counter = 1
            rec.save()

class All(Api):
    '''
    @summary: List all records.
    '''
    
    def invoke(self, req):
        return self.succeed(self.run())
    
    def run(self):
        ret = []
        for each in models.Counter.objects.all():
            ret.append({'name':each.app_name, 
                        'id':each.app_identity, 
                        'sum':each.launch_counter})
        return ret
    