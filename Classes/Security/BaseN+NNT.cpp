
# include "Core.h"
# include "BaseN+NNT.h"

NNT_BEGIN_HEADER_C

# include <openssl/pem.h>

NNT_END_HEADER_C

NNT_BEGIN_CXX

void base64::encode(void *data, usize dlen, core::vector<byte> &out)
{
    BIO* bio = BIO_new(BIO_f_base64());
    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);
    BIO_push(bio, BIO_new(BIO_s_mem()));
    BIO_write(bio, data, dlen);
    if(BIO_flush(bio)) {};
    BUF_MEM* mem;
    BIO_get_mem_ptr(bio, &mem);    
    
    out.resize(mem->length);
    memcpy(core::pointer(out), mem->data, mem->length);
    
    BIO_free_all(bio);
}

void base64::decode(void *data, usize dlen, core::vector<byte> &out)
{    
    BIO* bio = BIO_new(BIO_f_base64());
    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);
    BIO* bmem = BIO_new_mem_buf(data, dlen);
    BIO_push(bio, bmem);
    out.resize(dlen);
    int len = BIO_read(bio, core::pointer(out), dlen);
    out.resize(len);
    BIO_free_all(bio);
}

void base64::encode(core::string const& l, core::string& r)
{
    BIO* bio = BIO_new(BIO_f_base64());
    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);
    BIO_push(bio, BIO_new(BIO_s_mem()));
    BIO_write(bio, l.c_str(), l.size());
    if(BIO_flush(bio)) {};
    BUF_MEM* mem;
    BIO_get_mem_ptr(bio, &mem);    
    
    char* buf = (char*)malloc(mem->length);
    memcpy(buf, mem->data, mem->length);
    r = buf;
    free(buf);
    
    BIO_free_all(bio);
}

core::string base64::encode(core::string const& str)
{
    core::string ret;
    base64::encode(str, ret);
    return ret;
}

void base64::decode(core::string const& l, core::string& r)
{
    void* data = (void*)l.c_str();
    uint ldata = l.size();
    
    BIO* bio = BIO_new(BIO_f_base64());
    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);
    BIO* bmem = BIO_new_mem_buf(data, ldata);
    BIO_push(bio, bmem);
    char* buf = (char*)malloc(ldata);
    int len = BIO_read(bio, buf, ldata);
    r = core::string(buf, len);
    free(buf);
    BIO_free_all(bio);
}

void base64::decode(core::data const& l, core::string& r)
{
    void* data = (void*)l.bytes();
    uint ldata = l.length();
    
    BIO* bio = BIO_new(BIO_f_base64());
    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);
    BIO* bmem = BIO_new_mem_buf(data, ldata);
    BIO_push(bio, bmem);
    char* buf = (char*)malloc(ldata);
    int len = BIO_read(bio, buf, ldata);
    r = core::string(buf, len);
    free(buf);
    BIO_free_all(bio);
}

void base64::decode(core::string const& l, core::data& r)
{
    void* data = (void*)l.c_str();
    uint ldata = l.size();
    
    BIO* bio = BIO_new(BIO_f_base64());
    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);
    BIO* bmem = BIO_new_mem_buf(data, ldata);
    BIO_push(bio, bmem);
    char* buf = (char*)malloc(ldata);
    int len = BIO_read(bio, buf, ldata);
    r = core::data((byte*)buf, len, core::copy);
    free(buf);
    BIO_free_all(bio);
}

core::data base64::encode(core::data const& da)
{
    BIO* bio = BIO_new(BIO_f_base64());
    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);
    BIO_push(bio, BIO_new(BIO_s_mem()));
    BIO_write(bio, da.bytes(), da.length());
    
    if(BIO_flush(bio)) {};
    BUF_MEM* mem;
    BIO_get_mem_ptr(bio, &mem);    
    
    core::data ret((byte*)mem->data, mem->length, core::copy);
    
    BIO_free_all(bio);
    
    return ret;
}

core::data base64::decode(core::data const& da)
{
    BIO* bio = BIO_new(BIO_f_base64());
    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);
    BIO* bmem = BIO_new_mem_buf((void*)da.bytes(), da.length());
    BIO_push(bio, bmem);        
    
    core::data ret(da.length());
    int len = BIO_read(bio, (void*)ret.bytes(), ret.length());
    ret.set_length(len);
    BIO_free_all(bio);
    
    return ret;
}

NNT_END_CXX
