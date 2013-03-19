
# include "Core.h"
# include "BSEServer.h"
# include "../Store/WSIBdb.h"
# include "../Security/RSA+WSI.h"
# include "../Core/WSIChar.h"
# include "../Core/ObjectDL.h"
# include "../Cross/SoapObject.h"
# include "../Parser/SOAPParser.h"
# include "../Cross/SocketStream.h"

WSI_BEGIN_CXX 
WSI_BEGIN_NS(baison)

WSIDECL_PRIVATE_BEGIN_CXX(BSEServer)

# define WARNING_CLOSE(msg, stm) \
{ \
	cross::NetAddress addr = stm->remote_address(); \
	core::string info = (addr.address + ": ") + msg; \
	trace_msg(info); \
	d_owner->warnning(info); \
	stm->close(); \
}

# define NOTICE_ADDR(msg, stm) \
{ \
	cross::NetAddress addr = stm->remote_address(); \
	core::string info = (addr.address + ": ") + msg; \
	trace_msg(info); \
	d_owner->notice(info); \
}

struct token_t
{
    void* db; //! db for store information.
    void* key_server; //! key for server.
    core::string identity; //! identity.
};

typedef core::map<core::string, token_t> token_store;
token_store token;

void init()
{
    d_owner->connect(kSignalConnected, _cxxaction(self_type::evt_newclient), this);
    d_owner->version = 0x1;
}

void dealloc()
{
    for (token_store::iterator iter = token.begin(); iter != token.end(); ++iter)
    {
        token_t& tk = iter->second;
        d_owner->destroy_datastore(tk.db);   
        d_owner->destroy_security(tk.key_server);
    }
}

void evt_newclient(eventobj_t& evt)
{
    cross::SocketStream* stm = (cross::SocketStream*)evt.data;
    
    // send 'accept'.
    ::std::stringstream accept;
    accept << "ACCEPT" << __gs_byte_to_hex_str[d_owner->version];
    stm->write(core::type_cast<core::data>(accept.str()));

	// login.
	core::data_be sz((short)0);
	if (false == stm->read(sz, d_owner->timeout)) 
	{
		WARNING_CLOSE("failed to login.", stm);
		return;
	}

	// check.
	if (!core::between((short)sz, (short)0, (short)1024))
	{
		WARNING_CLOSE("login data is overflow.", stm);
		return;
	}

	core::data login((short)sz);
	if (false == stm->read(login, d_owner->timeout)) 
	{
		WARNING_CLOSE("failed to login.", stm);
		return;
	}
	if (d_owner->login(login) == false)
	{
		WARNING_CLOSE("failed to login.", stm);
		return;
	}

	NOTICE_ADDR("Success login.", stm);    

    // header commucation.
    stm->connect(kSignalBytesAvailable, _cxxaction(self_type::evt_accept), this)->shotcount = 1;
    // command.
    stm->connect(kSignalBytesAvailable, _cxxaction(self_type::evt_command), this);
    // close.
    stm->connect(kSignalClosed, _cxxaction(self_type::evt_close), this);
}

void evt_close(eventobj_t& evt)
{
    cross::SocketStream* stm = (cross::SocketStream*)evt.data;
    void* key = stm->attach_find("key");
    d_owner->destroy_security(key);
}

// slots.

void evt_accept(eventobj_t& evt)
{
    cross::SocketStream* stm = (cross::SocketStream*)evt.sender;
    stm->block(kSignalBytesAvailable);
    stm->wait = false;
    
    // get identity.
    core::data_be sz((short)0);
    if (false == stm->read(sz, d_owner->timeout))
	{
		WARNING_CLOSE("failed to get identity from client.", stm);
        return;
	}

    core::data id((short)sz);
    if (false == stm->read(id, d_owner->timeout))
	{
		WARNING_CLOSE("failed to get identity from client.", stm);
        return;
	}
    core::string id_str = core::type_cast<core::string>(id);
            
    // find identity.
    if (false == d_owner->exist_identity(id_str))
	{
		WARNING_CLOSE("identity is not found.", stm);
        return;
	}

	// get identity.
    token_t& tk = this->token.find(id_str)->second;
    stm->attach_set("token", &tk);
    
    // send pubkey of server. 
    core::vector<byte> pubkey_server = d_owner->get_pubkey(tk.key_server);
    stm->write(core::data_be((short)pubkey_server.size()));
    stm->write(core::data(core::pointer(pubkey_server), pubkey_server.size()));
    
    // accept pubkey of client.
    if (false == stm->read(sz, d_owner->timeout))
	{
		WARNING_CLOSE("failed to get public key from client.", stm);
        return;
	}
    core::data pubkey_client((short)sz);
    if (false == stm->read(pubkey_client, d_owner->timeout))
	{
		WARNING_CLOSE("failed to get public key from client.", stm);
        return;
	}
    
    // set client key.
    void* key_client = d_owner->create_security(false);
    stm->attach_set("key", key_client);
    if (false == d_owner->set_pubkey(key_client, core::pointer(pubkey_client), pubkey_client.length()))
	{
		WARNING_CLOSE("public key of client is invalid.", stm);
        return;
	}
    
    // wait for command.
    evt.veto = true;
	stm->wait = true;
    stm->unblock(kSignalBytesAvailable);    
    
    // send command.
    stm->write(core::type_cast<core::data>("COMMAND"));
}

void evt_command(eventobj_t& evt)
{
    cross::SocketStream* stm = (cross::SocketStream*)evt.sender;
    stm->block(kSignalBytesAvailable);
    stm->wait = false;
    
    trace_msg("got command.");
    
    // get token.
    token_t const* tk = (token_t const*)stm->attach_find("token");
    
    core::data_be sz((short)0);
    if (false == stm->read(sz, d_owner->timeout))
	{
		WARNING_CLOSE("failed to get command data.", stm);
        return;
	}
    core::data cmd((short)sz);
    if (false == stm->read(cmd, d_owner->timeout))
	{
		WARNING_CLOSE("failed to get command data.", stm);  
        return;
	}
    
    core::vector<byte> data;
    // decode command name.
    if (false == d_owner->decrypt(tk->key_server, cmd, data))
	{
		WARNING_CLOSE("failed to decrypt command data.", stm);
        return;
	}
    
    core::string str_cmd((char const*)core::pointer(data), data.size());
    str_cmd = d_owner->command_name(tk->identity, str_cmd);
	trace_msg(str_cmd);
    
    // execute command.
    // command as soap class.
    // parser as soap document.
    parser::SoapDocument soap;
    if (soap.parse_string(str_cmd))
    {
        lang::Namespace* ns = lang::getNamespace(tk->identity);
        // invoke.
        soap::Invoker invoker(soap);
        invoker.invoke(ns, stm);
        // get response.
        core::string response = soap.to_string();
        core::data response_data = core::type_cast<core::data>(response);
        // encrypt.
        void* key_client = stm->attach_find("key");
        d_owner->encrypt(key_client, response_data, data);
        stm->write(core::data_be((short)data.size()));
        stm->write(core::data(core::pointer(data), data.size()));
    }    
	else
	{
		NOTICE_ADDR("failed to parse soap request.", stm);
	}
    
	stm->wait = true;
    stm->unblock(kSignalBytesAvailable);    
}

WSIDECL_PRIVATE_END_CXX

BSEServer::BSEServer()
{
    WSIDECL_PRIVATE_CONSTRUCT(BSEServer);
}

BSEServer::~BSEServer()
{
    WSIDECL_PRIVATE_DESTROY();
}

core::string BSEServer::command_name(core::string const& identity, core::string const& name) const
{
    return name;
}

bool BSEServer::add_identity(const core::string & identity)
{
    // register to server.
    private_type::token_store::const_iterator found = d_ptr->token.find(identity);
    if (found != d_ptr->token.end())
        return true;
    void* store = this->open_datastore(identity);
    if (store == nil)
        return false;
    
    private_type::token_t tk;
    tk.identity = identity;
    tk.db = store;
    
    // gen new host pair keys.
    tk.key_server = this->create_security(true);
# ifdef WSI_DEBUG
    if (tk.key_server == NULL)
        trace_msg("the security for BSEServer is NULL.");
# endif
        
    d_ptr->token.insert(core::make_pair(identity, tk));
    
    // add to namespace.
    lang::addNamespace(identity);
    
    return true;
}

bool BSEServer::add_class(const core::string &identity, lang::Class *cls)
{
    lang::Namespace* ns = lang::getNamespace(identity);
    if (ns == NULL)
        return false;
    ns->classes[cls->name] = cls;
    return true;
}

bool BSEServer::exist_identity(const core::string &identity) const
{
    private_type::token_store::const_iterator found = d_ptr->token.find(identity);
    return found != d_ptr->token.end();
}

void* BSEServer::open_datastore(core::string const& identity)
{
    store::Bdb* bdb = new store::Bdb();
	store::connection_info info = { identity + ".token" };
    bool sta = bdb->connect(info);
    if (sta == false)
    {
        trace_msg("failed to open datastore " + identity);
        safe_delete(bdb);
        return bdb;
    }
    
    return bdb;
}

void BSEServer::destroy_datastore(void *ptr)
{
    store::Bdb* bdb = static_cast<store::Bdb*>(ptr);
    safe_delete(bdb);
}

void* BSEServer::create_security(bool gen)
{
    // create rsa security.
    rsa *sec = new rsa();
    
    if (gen && sec->generate() == false)
    {
        safe_delete(sec);
        return NULL;
    }
        
    return sec;
}

void BSEServer::destroy_security(void *sec)
{
    safe_delete_type(sec, rsa*);
}

core::vector<byte> BSEServer::get_pubkey(void *d) const
{
    rsa* sec = (rsa*)d;
    core::vector<byte> pubkey = sec->public_key();
    return pubkey;
}

bool BSEServer::set_pubkey(void* d, byte const* key, usize klen)
{
    rsa* sec = (rsa*)d;
    return sec->set_public_key(key, klen);
}

bool BSEServer::encrypt(void* d, core::data const& in, core::vector<byte>& out) const
{
    rsa* sec = (rsa*)d;
    return sec->encrypt(in, out);
}

bool BSEServer::decrypt(void* d, core::data const& in, core::vector<byte>& out) const
{
    rsa* sec = (rsa*)d;
    return sec->decrypt(in, out);
}

bool BSEServer::login(core::data const&) const
{
	return true;
}

void BSEServer::notice(core::string const&) const
{
    PASS;    
}

void BSEServer::warnning(core::string const&) const
{
    PASS;
}

# pragma mark service

BSEService::BSEService(core::string const& nm)
: name(nm)
{
    PASS;
}

BSEService::~BSEService()
{
    PASS;
}

void BSEService::register_to_server(BSEServer *serv)
{
    serv->add_identity(this->name);
}

void BSEService::register_class(BSEServer* serv, lang::Class * cls)
{
    serv->add_class(this->name, cls);
}

WSI_END_NS 
WSI_END_CXX
