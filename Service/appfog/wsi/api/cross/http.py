
from core.object import Object
import urllib2
from urlparse import urlparse

class Request(Object):    
    
    encoding = 'utf-8'
    
    def content(self, url):
        par = urlparse(url)
        if not par.netloc:
            url = 'http://' + url
        try:
            req = urllib2.Request(url)
            conn = urllib2.urlopen(req)
            d = conn.read()
            if self.encoding != 'utf-8':
                d = d.decode(self.encoding).encode('utf-8')
            return d
        except:
            self.dexcept()
        return None
        