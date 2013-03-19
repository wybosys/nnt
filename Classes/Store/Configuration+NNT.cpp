
# include "Core.h"
# include "NNTConfiguration.h"
# include "NNTBdb.h"

NNT_BEGIN_CXX 
NNT_BEGIN_NS(store)

NNTDECL_PRIVATE_BEGIN_CXX(Configuration)

void init()
{
    db = new store::Bdb;
    db->dup = false;
    db->readonly = false;
}

void dealloc()
{
    safe_delete(db);
}

store::Bdb* db;

NNTDECL_PRIVATE_END_CXX

Configuration& Configuration::getInstance()
{
    static Configuration __gs_configuration(".wsi.config");
    return __gs_configuration;
}

Configuration::Configuration()
{
    NNTDECL_PRIVATE_CONSTRUCT(Configuration);
}

Configuration::Configuration(core::string const& file)
{
    NNTDECL_PRIVATE_CONSTRUCT(Configuration);
    
    this->open(file);
}

void Configuration::_init()
{
    NNTDECL_PRIVATE_CONSTRUCT(Configuration);    
}

Configuration::~Configuration()
{
    NNTDECL_PRIVATE_DESTROY();
}

bool Configuration::open(const core::string & file)
{
    store::connection_info info;
    info.url = file;
    return d_ptr->db->connect(info);
}

bool Configuration::_connect(connection_info const& info)
{
    return d_ptr->db->connect(info);
}

bool Configuration::add(void* key, usize klen, void* data, usize dlen)
{
    if (false == d_ptr->db->put(data, dlen, key, klen))
        return false;
    d_ptr->db->sync();
    return true;
}

bool Configuration::set(void* key, usize klen, void* data, usize dlen)
{
    if (false == d_ptr->db->over(data, dlen, key, klen))
        return false;
    d_ptr->db->sync();
    return true;
}

bool Configuration::find(void* key, usize klen, core::data& da) const
{
    void* _data = NULL;
    uint _dlen = 0;
    bool suc = d_ptr->db->get(key, klen, &_data, &_dlen);
    if (suc == false)
        return false;
    da = core::data((byte*)_data, _dlen, core::assign);
    return true;
}

bool Configuration::find(void* key, usize klen, core::list<core::data>& datas) const
{
    void* iter = d_ptr->db->range_begin(key, klen);
    if (iter == NULL)
        return false;
    
    do 
    {
        void* data;
        uint dlen;
        d_ptr->db->iterator_retrive(iter, NULL, NULL, &data, &dlen);
        core::data da((byte*)data, dlen, core::copy);
        datas.push_back(da);
    } while (d_ptr->db->range_next(iter));
    
    d_ptr->db->iterator_end(iter);
    return true;
}

bool Configuration::remove(void *key, usize klen)
{
    if (!d_ptr->db->del(key, klen))
        return false;
    d_ptr->db->sync();
    return true;
}

void Configuration::clear()
{
    d_ptr->db->clear();
}

NNT_END_NS 
NNT_END_CXX
