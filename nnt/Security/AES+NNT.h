
# ifndef __NNT_SEC_AES_0EFA914D5C0D4AEAA8B12C688DDE632A_H_INCLUDED
# define __NNT_SEC_AES_0EFA914D5C0D4AEAA8B12C688DDE632A_H_INCLUDED

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX

NNTCLASS(aes);

class aes
{
public:
    
    static void encrypt(core::data const& key, core::data const& in, core::vector<byte>& out);
    static void decrypt(core::data const& key, core::data const& in, core::vector<byte>& out);
    
};

NNT_END_HEADER_CXX

# endif

# ifdef NNT_C_COMPATIABLE

NNT_BEGIN_HEADER_C

typedef struct _aes_t aes_t;

NNTAPI(aes_t*) aes_new();
NNTAPI(void) aes_free(aes_t*);
NNTAPI(void) aes_set_padding(aes_t*, int);
NNTAPI(void) aes_swap_rw(aes_t*);
NNTAPI(int) aes_set_key(aes_t*, void const* key, size_t lkey);
NNTAPI(int) aes_encrypt(aes_t*, void const* data, size_t ldata, void** outdata, size_t* loutdata);
NNTAPI(int) aes_decrypt(aes_t*, void const* data, size_t ldata, void** outdata, size_t* loutdata);
NNTAPI(void) aes_set_enkey(aes_t*, aes_t const*);
NNTAPI(void) aes_set_dekey(aes_t*, aes_t const*);

NNT_END_HEADER_C

# endif

# ifdef NNT_MACH

NNT_BEGIN_HEADER_C

typedef struct _ns_aes_t nsaes_t;

NNTAPI(nsaes_t*) nsaes_new();
NNTAPI(void) nsaes_free(nsaes_t*);
NNTAPI(void) nsaes_set_padding(nsaes_t*, int);
NNTAPI(void) nsaes_swap_rw(nsaes_t*);
NNTAPI(int) nsaes_set_key(nsaes_t*, void const* key, size_t lkey);
NNTAPI(int) nsaes_encrypt(nsaes_t*, void const* data, size_t ldata, void** outdata, size_t* loutdata);
NNTAPI(int) nsaes_decrypt(nsaes_t*, void const* data, size_t ldata, void** outdata, size_t* loutdata);

NNT_END_HEADER_C

# endif

# endif
