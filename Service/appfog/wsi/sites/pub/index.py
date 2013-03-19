
from api.sites import mvc

class View(mvc.View):
    
    def render(self, req):
        return self.load_template('index.djhtml').fill()

def Controller(req):
    return mvc.load(View, req)
