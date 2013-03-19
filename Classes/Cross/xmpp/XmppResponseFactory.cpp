
# include "Core.h"
# include "XmppResponseFactory.h"
# include "XmppObject.h"

# include "XmppStreamFactory.h"
# include "XmppMessageFactory.h"
# include "XmppInfoqueryFactory.h"
# include "XmppPresenceFactory.h"
# include "XmppChallengeFactory.h"
# include "XmppSuccessFactory.h"
# include "XmppBlackholeFactory.h"

XMPP_BEGIN

AbstractResponseFactory::AbstractResponseFactory()
: _client(NULL)
{
    PASS;
}

AbstractResponseFactory::~AbstractResponseFactory()
{
    PASS;
}

void AbstractResponseFactory::set_client(Client &client)
{
    _client = &client;
}

bool AbstractResponseFactory::process(core::data const& da)
{
    if (da.size() < 2)
        return false;
    
    parser::XmlDocument xml;
    bool suc = true;
    
    if (da[0] == '<' &&
        da[1] == '?')
    {
        suc = xml.parse_data(da);
    }
    else if (da[0] == '<' &&
             da[1] == '/')
    {
        return false;
    }
    else
    {
        core::data fullxml;
        fullxml.append("<root>");
        fullxml.append(da);
        fullxml.append("</root>");
        
        if (false == xml.parse_data(fullxml))
        {
            trace_msg("failed to parse data from server.");
            return false;
        }
        
        for (parser::XmlNode::nodes_type::const_iterator iter = xml.root()->children.begin();
             suc && (iter != xml.root()->children.end());
             ++iter)
        {
            suc &= process(iter->second);
        }
        
        return suc;
    }
        
    if (!suc)
    {
        trace_msg("failed to parse data from server.");
        return false;
    }
    
    return process(xml.root());
}

bool AbstractResponseFactory::process(xmlnode_t const* node)
{
    if (node->children.size() == 0)
        return _process_self(node);
    return _process_children(node);
}

bool AbstractResponseFactory::process_object(FactoryObject const& facobj, xmlnode_t const* node)
{
    bool suc = false;
    if ((*facobj.couldload)(node))
    {
        xmpp::Object* obj = (*facobj.instance)();
        if (( suc = obj->load(node) ))
        {
            typedef ResponseObject<xmpp::Object> obj_type;
            obj_type* target = (obj_type*)(ptr_offset(obj, sizeof(xmpp::Object)));
            target->process(*_client);
        }
        obj->drop();
    }
    return suc;
}

bool AbstractResponseFactory::_process_children(xmlnode_t const* node)
{
    bool suc = false;
    
    for (xmlnode_t* eachnode = node->first;
         eachnode;
         eachnode = eachnode->next)
    {
        for (factory_objects::const_iterator each = _objects.begin();
             each != _objects.end();
             ++each)
        {
            suc |= this->process_object(*each, eachnode);
        }
    }
    
    return suc;
}

bool AbstractResponseFactory::_process_self(xmlnode_t const* node)
{
    bool suc = false;
    
    for (factory_objects::const_iterator each = _objects.begin();
         each != _objects.end();
         ++each)
    {
        suc |= this->process_object(*each, node);
    }
    
    return suc;
}

void AbstractResponseFactory::register_object(FactoryObject const& obj)
{
    _objects.push_back(obj);
}

void AbstractResponseFactory::unregister_object(FactoryObject const& obj)
{
    _objects.erase(obj);
}

// impl.

WSIDECL_PRIVATE_BEGIN_CXX(ResponseFactory)

void init()
{
    PASS;
}

void dealloc()
{
    factories.clear_drop();
}

typedef core::vector<AbstractResponseFactory*> factories_type;
factories_type factories;

StreamFactory fct_stream;
MessageFactory fct_message;
PresenceFactory fct_presence;
InfoqueryFactory fct_iq;
ChallengeFactory fct_challenge;
SuccessFactory fct_success;
BlackholeFactory fct_blackhole;

WSIDECL_PRIVATE_END_CXX

ResponseFactory::ResponseFactory()
{
    WSIDECL_PRIVATE_CONSTRUCT(ResponseFactory);
}

ResponseFactory::~ResponseFactory()
{
    WSIDECL_PRIVATE_DESTROY();
}

void ResponseFactory::set_client(Client & client)
{
    super::set_client(client);
    
    d_ptr->fct_stream.set_client(client);
    d_ptr->fct_message.set_client(client);
    d_ptr->fct_presence.set_client(client);
    d_ptr->fct_iq.set_client(client);
    d_ptr->fct_challenge.set_client(client);
    d_ptr->fct_success.set_client(client);
    d_ptr->fct_blackhole.set_client(client);
    
    for (private_type::factories_type::iterator iter = d_ptr->factories.begin();
         iter != d_ptr->factories.end();
         ++iter)
    {
        (*iter)->set_client(client);
    }
}

bool ResponseFactory::process(core::data const& da)
{
    return super::process(da);
}

bool ResponseFactory::process(xmlnode_t const* node)
{    
    if (d_ptr->fct_stream.process(node))
        return true;
    
    if (d_ptr->fct_message.process(node))
        return true;
    
    if (d_ptr->fct_presence.process(node))
        return true;
    
    if (d_ptr->fct_iq.process(node))
        return true;
    
    if (d_ptr->fct_challenge.process(node))
        return true;
    
    if (d_ptr->fct_success.process(node))
        return true;
    
    for (private_type::factories_type::iterator iter = d_ptr->factories.begin();
         iter != d_ptr->factories.end();
         ++iter)
    {
         if ((*iter)->process(node))
             return true;
    }
    
    // other must above balckhole, because it will true always.
    if (d_ptr->fct_blackhole.process(node))
        return true;
    
    return false;
}

void ResponseFactory::register_factory(AbstractResponseFactory* fac)
{
    // insert to store.
    d_ptr->factories.push_back(fac);
    
    // grab rc.
    fac->grab();
    
    // set client.
    fac->set_client(*_client);
}

MessageFactory* ResponseFactory::factory_message() const
{
    return &d_ptr->fct_message;
}

PresenceFactory* ResponseFactory::factory_presence() const
{
    return &d_ptr->fct_presence;
}

InfoqueryFactory* ResponseFactory::factory_iq() const
{
    return &d_ptr->fct_iq;
}

XMPP_END
