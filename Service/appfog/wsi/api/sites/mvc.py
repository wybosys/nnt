
from django.http import HttpResponse
from core.object import Object
from django.template import loader, Context, Template

class Template(Object):
    
    template = None
    
    def fill(self, param = {}, type = Context):
        return self.template.render(type(param))
    
    
class View(Object):
    
    def trans_template(self, file):
        comps = self.__module__.split('.')
        comps = comps[3:-1]
        comps.append(file)
        file = '/'.join(comps)
        return file
    
    def load_template(self, file):
        file = self.trans_template(file)
        t = loader.get_template(file)
        if not t:
            return None
        ret = Template()
        ret.template = t
        return ret
    
    def render(self, req):
        return ''
    
def load(type, req, *args):
    obj = type()
    i = 0;
    for each in args:
        setattr(obj, 'v' + str(i), each)
    return HttpResponse(obj.render(req))