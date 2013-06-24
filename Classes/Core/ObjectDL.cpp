
# include "Core.h"
# include "ObjectDL.h"
 
NNT_BEGIN_CXX
NNT_BEGIN_NS(lang)

class DLObject
{
public:

    DLObject();
    ~DLObject();
    
    typedef core::map<core::string, Namespace> namespaces_type;
    namespaces_type namespaces;

    static DLObject& signleton()
    {
        static DLObject __gs_dl;
        return __gs_dl;
    }

};

DLObject::DLObject()
{
    namespaces.insert(core::make_pair("", Namespace()));
}

DLObject::~DLObject()
{
    PASS;   
}

Namespace* getNamespace(core::string const& name)
{
    DLObject::namespaces_type::iterator found = DLObject::signleton().namespaces.find(name);
    if (found == DLObject::signleton().namespaces.end())
        return NULL;
    return &found->second;
}

Namespace* addNamespace(core::string const& name)
{
    DLObject::namespaces_type::iterator found = DLObject::signleton().namespaces.find(name);
    if (found != DLObject::signleton().namespaces.end())
        return &found->second;
    DLObject::signleton().namespaces.insert(core::make_pair(name, Namespace()));
    return getNamespace(name);
}

Object* instanceObject(Namespace const* ns, Class const* cls)
{
    Namespace::classes_type::const_iterator cls_found = ns->classes.find(cls->name);
    if (cls_found == ns->classes.end())
        return NULL;
    Class const* tgt_cls = cls_found->second;
    if (false == tgt_cls->could_instance(cls))
        return NULL;
    
    Object* obj = (*tgt_cls->instance)();
    
    return obj;
}

Class const* findDeclClass(Namespace const* ns, Class const* cls)
{
    Namespace::classes_type::const_iterator cls_found = ns->classes.find(cls->name);
    if (cls_found == ns->classes.end())
        return NULL;
    Class const* tgt_cls = cls_found->second;
    return tgt_cls;
}

INVOKE_STA invokeClass(Object* obj, Class const* cls, void* data)
{
    INVOKE_STA ret = INVOKE_SUCCESS;
    
    for (Class::methods_type::const_iterator each = cls->methods.begin();
         each != cls->methods.end();
         ++each)
    {
        Method* method = *each;        
        Method::method_type handle = method->method;
        
        int sta = (obj->*handle)(method->params, method->returns, data);
        if (sta != 0)
        {
            ret = INVOKE_ERROR;
            break;
        }
    }
    
    return ret;
}

INVOKE_STA invokeClass(Object* obj, Class const* objcls, Class const* declcls, void* data)
{
    INVOKE_STA ret = INVOKE_SUCCESS;
    bool method_found = false;
    
    for (Class::methods_type::const_iterator each = objcls->methods.begin();
         (each != objcls->methods.end()) && (ret == INVOKE_SUCCESS);
         ++each)
    {
        Method* method = *each;                      
        
        // find decl method.        
        for (Class::methods_type::const_iterator each = declcls->methods.begin();
             each != declcls->methods.end();
             ++each)
        {
            if ((method_found = method->is_equal(*each)))
            {
                Method* decl_method = *each;
                
                // prepare.
                Method::method_type handle = decl_method->method;
                method->clear_returns();
                for (Method::returns_type::const_iterator each = decl_method->returns.begin();
                     each != decl_method->returns.end();
                     ++each)
                {
                    Field* nfid = each->second->clone();
                    method->returns.insert(core::make_pair(nfid->name, nfid));
                }
                
                // invoke.
                ret = (obj->*handle)(method->params, method->returns, data);
                if (ret != 0)
                {
                    ret = INVOKE_ERROR;
                    break;
                }
                
                // next.
                if (method_found)
                    break;
            }
        }       
        
        if (method_found == false)
        {
            ret = METHOD_NOTFOUND;
            break;
        }
       
    }
    
    if (method_found == false)
        ret = METHOD_NOTFOUND;
    
    return ret;
}

NNT_END_NS
NNT_END_CXX
