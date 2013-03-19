
from core.callable import Api
from toolkit import models
from core import account

class Increase(Api):
    '''
    @summary: increase launch counter.
    @param name: name of app.
    @param id: identity of app. (bundle identity in iOS)
    @param devid: dev identity of app.
    @param devnet: net address of dev. 
    '''
        
    def __init__(self):
        super(Increase, self).__init__()
        self.right.uid = account.UID_TOOLKIT
        self.right.gid = account.GID_TOOLKIT
        self.right.discard_other()
        
    def invoke(self, req):        
        addr = None
        if 'REMOTE_ADDR' in req.META:
            addr = req.META['REMOTE_ADDR']
        self.run(self.name, self.id, self.devid, addr)
        return self.succeed()
    
    def run(self, name, id, devid, devnet = None):
        rec = models.Counter_Device.objects.filter(app_name=name).filter(app_identity=id).filter(device_id=devid)
        if len(rec):
            rec = rec[0]
            rec.launch_counter = rec.launch_counter + 1
            rec.device_net = devnet
            rec.save()
        else:
            rec = models.Counter_Device()
            rec.app_name = name
            rec.app_identity = id
            rec.device_id = devid    
            rec.device_net = devnet        
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
        for each in models.Counter_Device.objects.all():
            ret.append({'name': each.app_name, 
                        'id': each.app_identity,
                        'dev': each.device_id,
                        'addr': each.device_net,
                        'sum': each.launch_counter})
        return ret
