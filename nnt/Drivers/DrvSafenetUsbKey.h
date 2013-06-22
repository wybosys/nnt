
# ifndef __NNT_DRIVER_SAFENETUSBKEY_6163e98bc03348c6add2f4bbb96a78df_H_INCLUDED
# define __NNT_DRIVER_SAFENETUSBKEY_6163e98bc03348c6add2f4bbb96a78df_H_INCLUDED

NNT_BEGIN_HEADER_C

# include <SentinelKeys.h>

# define SFNT_BUFFER_SIZE 1024

typedef struct {
    void *handle;
    dword errid;
    byte buf[SFNT_BUFFER_SIZE];
} sfnt_t;

//! to string
NNTAPI(char const*)
sfnt_tostring(sfnt_t*);

//! to int
NNTAPI(int)
sfnt_toint(sfnt_t*);

//! is suc
NNTAPI(bool)
sfnt_failed(sfnt_t*);

//! get errid
NNTAPI(dword)
sfnt_errid(sfnt_t*);

//! init
NNTAPI(sfnt_t*) 
sfnt_init();

//! fin
NNTAPI(void)
sfnt_fin(sfnt_t*);

//! get license
NNTAPI(void)
sfnt_getlicense(dword devid, byte* softwarekey, dword licid, dword flags, sfnt_t* sfnt);

//! query feature
NNTAPI(void)
sfnt_queryfeature(dword featureid, dword flags, byte* query, dword length, dword rlen, sfnt_t* sfnt);

//! read string
NNTAPI(void)
sfnt_readstring(dword featureid, sfnt_t* sfnt);

//! read integer
NNTAPI(void)
sfnt_readinteger(dword featureid, sfnt_t* sfnt);

//! counter dec
NNTAPI(void)
sfnt_counterdecrement(dword featureid, dword value, sfnt_t* fnt);

NNT_END_HEADER_C

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX NNT_BEGIN_NS(sfnt)

class Config
{
 public:
    virtual ~Config() {}

    udword develop_id;
    uword license_id;
    uword key_flag;
    core::data software_key;
    dword LEN_OF_QR;
    dword LEN_OF_SIMPLE_QUERY;
    dword LEN_OF_ALL_SERVERS;
};

//NNTCLASS(Standalone);

class Standalone
{
 public:
    Standalone();
    ~Standalone();

    //! close the key.
    void close();

    //! config key.
    bool config(Config const* cfg);

    //! is failed.
    bool is_failed() const;
    dword errid() const;

    //! result.
    core::string result_string() const;
    int result_int() const;

    //! query.
    core::string query_feature(dword fid, dword flg, core::data const& qry, dword tgtlen) const;
    core::string read_string(dword fid) const;
    int read_integer(dword fid) const;

	//! get config.
	Config const* config() const { return _cfg; } 
    
 protected:
    sfnt_t* _key;
    Config const* _cfg;
};

NNT_END_NS NNT_END_HEADER_CXX

# endif

# endif
