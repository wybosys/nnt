
from core.callable import Api
from cross import http

class Content(Api):
    '''
    @summary: get content of url.
    @param url: destination url, don't include 'http://' like scheme.
    '''
        
    def invoke(self, req):
        return self.succeed(self.run(self.url))
    
    def run(self, url):
        req = http.Request()
        req.encoding = 'gb18030'
        return req.content(url)
    