

from django.conf.urls.defaults import *
import index, lookup

urlpatterns = patterns('',                
    (r'^$', index.Controller),
    (r'^lookup/(?P<api>\S+)', lookup.Controller)
)
