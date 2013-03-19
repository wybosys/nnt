
from django.db import models

class Counter(models.Model):
    
    class Meta:
        app_label = 'toolkit'
        
    app_name = models.TextField()
    app_identity = models.TextField()
    launch_counter = models.BigIntegerField()

class Counter_Device(models.Model):
    
    class Meta:
        app_label = 'toolkit'
    
    app_name = models.TextField()
    app_identity = models.TextField()
    launch_counter = models.BigIntegerField()
    device_id = models.TextField()
    device_net = models.TextField(null=True)    
