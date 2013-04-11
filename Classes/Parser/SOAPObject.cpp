
# include "Core.h"
# include "../Core/ObjectDL.h"
# include "SOAPObject.h"
# include "../Parser/SOAPParser.h"

NNT_BEGIN_CXX 
NNT_BEGIN_NS(soap)

Invoker::Invoker(parser::SoapDocument& doc)
: _doc(&doc)
{
    PASS;
}

lang::Class* Invoker::to_class() const
{        
    parser::XmlNode const* nbody = _doc->root()->node("Body");
    if (nbody == NULL)
        return NULL;
    parser::XmlAttribute const* nclass = nbody->attribute("xmlns:m");
    if (nclass == NULL)
        return NULL;
    
    lang::Class* cls = new lang::Class;
    cls->name = nclass->value;
    
    // get all methods.
    for (parser::XmlNode::nodes_type::const_iterator each = nbody->children.begin();
         each != nbody->children.end();
         ++each)
    {        
        parser::XmlNode const* nmethod = each->second;
        
        lang::Method* method = new lang::Method;
        method->name = nmethod->name;
        
        // get all params.
        for (parser::XmlNode::nodes_type::const_iterator each = nmethod->children.begin();
             each != nmethod->children.end();
             ++each)
        {
            parser::XmlNode const* nfield = each->second;
            
            lang::Parameter* param = new lang::Parameter;
            param->name = nfield->name;
            param->value = variant_t(nfield->value.c_str(), core::copy);
            
            // add field.
            method->params.insert(core::make_pair(param->name, param));
        }
        
        // add method.
        cls->methods.push_back(method);        
    }
    
    return cls;
}

void Invoker::free(lang::Class *cls) const
{
    cls->drop();
}

lang::Object* Invoker::instance() const
{
    lang::Class* cls = this->to_class();
    lang::Object* obj = this->instance(cls);
    this->free(cls);
    return obj;
}

lang::Object* Invoker::instance(lang::Class const* cls) const
{
    lang::Namespace const* ns = soap::getNamespace();
    return lang::instanceObject(ns, cls);
}

static void add_fault_node(parser::XmlNode* nbody, int _code, core::string const& _msg, core::string const& _actor)
{
    using parser::XmlNode;
    
    XmlNode* fault = new XmlNode;
    fault->name = "soap:Fault";
    
    XmlNode* code = new XmlNode;
    code->name = "faultcode";
    code->value = core::tostr(_code);
    
    XmlNode* msg = new XmlNode;
    msg->name = "faultstring";
    msg->value = _msg;
    
    XmlNode* actor = new XmlNode;
    actor->name = "faultactor";
    actor->value = _actor;
    
    fault->add(code); code->drop();
    fault->add(msg); msg->drop();
    fault->add(actor); actor->drop();        
    nbody->add(fault); fault->drop();
}

void Invoker::invoke(void *data, lang::Namespace* ns)
{
    this->_invoke(data, ns);
}

void Invoker::invoke(lang::Namespace * ns, void* data)
{
    this->_invoke(data, ns);
}

void Invoker::_invoke(void* _da, lang::Namespace* _ns)
{        
    using parser::XmlNode;
    
    // new obj.
    lang::Class* cls = this->to_class();
    if (cls == NULL)
    {
        trace_msg("cannot convert soap data to class.");
        return;
    }

    lang::Namespace const* ns = _ns ? _ns : soap::getNamespace();    
    lang::Class const* declcls = lang::findDeclClass(ns, cls);    
    
    // generate respone.
    XmlNode* nbody = _doc->root()->node("Body");
    if (nbody == NULL)
    {
        trace_msg("cannot find soap body element");
        return;
    }

    nbody->clear_children();
    
    if (declcls == NULL)
    {
        add_fault_node(nbody, 
                       lang::CLASS_NOTFOUND, 
                       "CLASS NOT FOUND", 
                       "::nnt::parser::SoapDocument::invoke");
        
        // free.
        this->free(cls);
        return;
    }
    
    soap::Object* obj = (soap::Object*)lang::instanceObject(ns, cls);
    if (obj == NULL)
    {
        add_fault_node(nbody,
                       lang::INSTANCE_FAILED,
                       "CAN'T INSTANCE CLASS OBJECT",
                       "::nnt::lang::instanceObject");
        
        // free
        this->free(cls);
        return;
    }
    
    // deqeue invoke method.
    lang::INVOKE_STA sta = lang::invokeClass(obj, cls, declcls, _da);        
    
    // check if success.
    switch (sta)
    {
        case lang::INVOKE_SUCCESS:
        {
            // add response.
            for (lang::Class::methods_type::const_iterator each = cls->methods.begin();
                 each != cls->methods.end();
                 ++each)
            {
                // add method's response.
                lang::Method const* method = *each;
                XmlNode* node = new XmlNode;
                node->name = "m:" + method->name + "Response";
                
                // add return value.
                for (lang::Method::returns_type::const_iterator each = method->returns.begin();
                     each != method->returns.end();
                     ++each)
                {
                    lang::Field const* field = each->second;
                    ::std::stringstream ss;
                    ss << field->value;
                    
                    XmlNode* nvalue = new XmlNode;
                    nvalue->name = "m:" + field->name;
                    nvalue->value = ss.str();
                    
                    node->add(nvalue);
                    nvalue->drop();
                }
                
                nbody->add(node);
                node->drop();
            }
            
        } break;
            
        case lang::INVOKE_ERROR:
        {
            add_fault_node(nbody, 
                           obj->fault.code, 
                           obj->fault.message, 
                           obj->fault.actor);
        } break;
            
        case lang::METHOD_NOTFOUND:
        {            
            add_fault_node(nbody,
                           lang::METHOD_NOTFOUND,
                           "METHOD NOT FOUND",
                           "::nnt::parser::SoapDocument::invoke");
        } break;
            
        default:
        {
            add_fault_node(nbody,
                           obj->fault.code != 0 ? obj->fault.code : -1,
                           !obj->fault.message.empty() ? obj->fault.message : "UNDEFINED ERROR",
                           !obj->fault.actor.empty() ? obj->fault.actor : "::nnt::parser::SoapDocument::invoke");
        } break;
            
    }
    
    // free.
    zero_drop(obj);
    this->free(cls);
}

NNT_END_NS 
NNT_END_CXX
