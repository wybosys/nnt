
# include "Core.h"
# include "MaeSApi.h"

WAE_MODEL_BEGIN_NS(sapi)

List::List()
{
    set_method(@"api.sapi.manager.all");
}

void List::success(id res)
{
    classes.clear();
    
    for (id key in res)
    {
        Class& cls = classes.add();
        cls.name = key;
        
        id members = [res objectForKey:key];
        for (id mem in members)
        {
            Method mtd;
            mtd.name = mem;
            
            ns::Array param = [members objectForKey:mem];
            ns::Array reqs = param[0];
            ns::Array opts = param[1];
            
            for (uint i = 0; i < reqs.size(); ++i)
            {
                mtd.requires.push_back(reqs[i]);
            }
            
            for (uint i = 0; i < opts.size(); ++i)
            {
                mtd.optionals.push_back(opts[i]);
            }
            
            cls.methods.push_back(mtd);
        }
    }
}

FindDoc::FindDoc()
{
    set_method(@"api.sapi.doc.find");
}

void FindDoc::params(ns::MutableArray& arr) const
{
    arr.add(ns::Pair(@"target", method));
}

void FindDoc::success(id res)
{
    doc = res;
}

WAE_MODEL_END_NS
