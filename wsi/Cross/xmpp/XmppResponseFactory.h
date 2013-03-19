
# ifndef __XMPP_RESPONSE_FACTORY_8F7B97800A3C488B8A395E428FBCFAC0_H_INCLUDED
# define __XMPP_RESPONSE_FACTORY_8F7B97800A3C488B8A395E428FBCFAC0_H_INCLUDED

# include "XmppClient.h"
# include "XmppObject.h"

XMPP_HEADER_BEGIN

WSICLASS(AbstractResponseFactory);

class AbstractResponseFactory
: public RefObject
{
public:

    typedef core::vector<FactoryObject> factory_objects;
    
    AbstractResponseFactory();
    virtual ~AbstractResponseFactory();
    
    //! set client.
    virtual void set_client(Client& client);
    
    //! process data.
    virtual bool process(core::data const& da);
    
    //! process xml.
    virtual bool process(xmlnode_t const* node);
    
    //! register object.
    virtual void register_object(FactoryObject const&);
    
    //! unregister object.
    virtual void unregister_object(FactoryObject const&);
    
    //! process object.
    virtual bool process_object(FactoryObject const&, xmlnode_t const*);
    
protected:
    
    bool _process_children(xmlnode_t const* node);
    bool _process_self(xmlnode_t const* node);
    
    //! pointer to client.
    Client* _client;
    
    //! factory objects.
    factory_objects _objects;

};

WSIDECL_PRIVATE_HEAD_CXX(ResponseFactory);

class MessageFactory;
class PresenceFactory;
class InfoqueryFactory;

WSICLASS(ResponseFactory);

class ResponseFactory
: public AbstractResponseFactory
{
    typedef AbstractResponseFactory super;
    WSIDECL_PRIVATE_CXX(ResponseFactory);
    
public:
    
    ResponseFactory();
    virtual ~ResponseFactory();
    
    //! register factory for other response.
    void register_factory(AbstractResponseFactory*);
    
    //! override.
    virtual void set_client(Client&);
    virtual bool process(core::data const& da);
    virtual bool process(xmlnode_t const* node);
    
public:
    
    //! get standard factory.
    MessageFactory* factory_message() const;
    PresenceFactory* factory_presence() const;
    InfoqueryFactory* factory_iq() const;
    
};

XMPP_HEADER_END

# endif