
# ifndef __BAISON_BSESERVER_31643170B72A43E7901A192219A53682_H_INCLUDED
# define __BAISON_BSESERVER_31643170B72A43E7901A192219A53682_H_INCLUDED

// BSEServer is Basion Security Exchange Server.

# include "../Cross/SocketServer.h"
# include "../Core/ObjectDL.h"
# include "../Cross/SoapObject.h"
# include "../Core/Time+WSI.h"

WSI_BEGIN_HEADER_CXX 
WSI_BEGIN_NS(baison)

WSICLASS(BSEServer);
WSICLASS(BSEService);

WSIDECL_PRIVATE_HEAD_CXX(BSEServer);

struct BSEServerCommand
{    
public:
    core::data ret;
};

class BSEServer
: public wsi::cxx::Class<cross::SocketServer>
{    
    WSIDECL_PRIVATE_CXX(BSEServer);
	friend class BSEService;
    
public:    
    BSEServer();
    ~BSEServer();
    
public:
    
    //! add identity to server, it will alloc a datastore or open the exist datastore.
    bool add_identity(core::string const& identity);
    
    //! exist identity.
    bool exist_identity(core::string const& identity) const;
    
    //! register class.
    bool add_class(core::string const& identity, lang::Class* cls);
    
protected:
    
    //! command name.
    virtual core::string command_name(core::string const& identity, core::string const& name) const;

	//! login.
	virtual bool login(core::data const&) const;
    
    //! open a data store.
    virtual void* open_datastore(core::string const& identity);
    
    //! destroy a data store.
    virtual void destroy_datastore(void*);
    
    //! create security method.
    virtual void* create_security(bool gen);
    
    //! destroy security method.
    virtual void destroy_security(void*);
    
    //! get pubkey.
    virtual core::vector<byte> get_pubkey(void*) const;
    
    //! set pubkey.
    virtual bool set_pubkey(void*, byte const*, usize);
    
    //! encrypt.
    virtual bool encrypt(void*, core::data const& in, core::vector<byte>& out) const;
    virtual bool decrypt(void*, core::data const& in, core::vector<byte>& out) const;
    
    //! logger.
    virtual void notice(core::string const&) const;
    virtual void warnning(core::string const&) const;
    
public:

    //! version of server.
    byte version;

	//! timeout for each procedure.
	core::Timeout timeout;
       
};

class BSEService
: public soap::Object
{
public:
    BSEService(core::string const& name = "");
    ~BSEService();
    
public:
    
    //! register self to server.
    void register_to_server(BSEServer*);
    
    //! register class.
    void register_class(BSEServer*, lang::Class*);
    
    
public:
    core::string name;
};

WSI_END_NS 
WSI_END_HEADER_CXX

# endif
