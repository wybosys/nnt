
from django.conf.urls.defaults import *
import index

urlpatterns = patterns('',
    (r'^$', index.Controller),
    (r'^api-center/', include('wsi.sites.pub.api-center'))
)
