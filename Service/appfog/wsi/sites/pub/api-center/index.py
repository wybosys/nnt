
from api.sites import mvc
from api.sapi import manager

class View(mvc.View):
    
    def render(self, req):
        apis = manager.All().run()
        return self.load_template('index.djhtml').fill({'apis':apis})

def Controller(req):
    return mvc.load(View, req)
