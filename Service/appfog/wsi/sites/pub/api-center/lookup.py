
from api.sites import mvc
from api.sapi import doc, right
from pyparsing import *

class View(mvc.View):
    
    def render(self, req):
        str = doc.Find().run(self.v0)
        if not str:
            str = ''
        # analyze doc str.
        pat_name = Literal("@") + Word(alphas)
        pat_arg = Word(alphas) + Literal(":")
        pat_seq = Literal(":")
        pat_val = restOfLine
        pat = pat_name + (pat_arg | pat_seq) + pat_val
        docobj = {'summary':'', 'param':{}, 'return':''}
        for each in str.split('\n'):
            if not each:
                continue
            try:
                res = pat.parseString(each)
            except:
                continue
            param = res[1]
            if len(res) == 4:
                arg = ''
            else:
                arg = res[2]
            val = res[-1]
            obj = docobj[param]
            if isinstance(obj, dict):
                obj[arg] = val
            if not arg:
                docobj[param] = val
        # find right.
        rt = right.Find().run(self.v0)
        return self.load_template('lookup.djhtml').fill({'method': self.v0,
                                                         'doc': docobj,
                                                         'right': rt})

def Controller(req, api):
    return mvc.load(View, req, api)
