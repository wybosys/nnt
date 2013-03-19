
# include <nnt/NNTFoundation.h>
# include "DrvSafenetUsbKey.h"

NNT_BEGIN_C

char const* sfnt_tostring(sfnt_t* s) {
    return (char const*)s->buf;
}

int sfnt_toint(sfnt_t* s) {
    return *(int*)(s->buf);
}

bool sfnt_failed(sfnt_t* s) {
    return s->errid != SP_SUCCESS;
}

dword sfnt_errid(sfnt_t* s) {
    return s->errid;
}

sfnt_t* sfnt_init() {
    sfnt_t* sfnt = (sfnt_t*)calloc(1, sizeof(sfnt_t));
    sfnt->handle = NULL;
    sfnt->errid = SP_SUCCESS;
    return sfnt;
}

void sfnt_fin(sfnt_t* sfnt) {
    if (sfnt->handle) {
        SFNTReleaseLicense(sfnt->handle);
        sfnt->handle = NULL;
    }
    free(sfnt);
}

void sfnt_getlicense(dword d, byte* sk, dword l, dword f, sfnt_t* s) {
    s->errid = SFNTGetLicense(d, sk, l, f, &s->handle);
}

void sfnt_queryfeature(dword f, dword fg, byte* q, dword l, dword rl, sfnt_t* s) {
    s->errid = SFNTQueryFeature(s->handle, f, fg, q, l, s->buf, rl/*BUFFER_SIZE*/);
}

void sfnt_readstring(dword f, sfnt_t* s) {
    s->errid = SFNTReadString(s->handle, f, (SPP_CHAR)s->buf, SFNT_BUFFER_SIZE);
}

void sfnt_readinteger(dword f, sfnt_t* s) {
    s->errid = SFNTReadInteger(s->handle, f, (SPP_DWORD)s->buf);
}

void sfnt_counterdecrement(dword f, dword v, sfnt_t* s) {
    s->errid = SFNTCounterDecrement(s->handle, f, v);
}

NNT_END_C

NNT_BEGIN_CXX NNT_BEGIN_NS(sfnt)

Standalone::Standalone()
    : _key(NULL), _cfg(NULL)
{
}

Standalone::~Standalone()
{
    this->close();
    delete _cfg;
}

void Standalone::close()
{
    if (_key) {
        sfnt_fin(_key);
        _key = NULL;
    }
}

bool Standalone::config(Config const* cfg)
{
    sfnt_t* key = sfnt_init();
    if (key == NULL)
        return false;
    
    // init key.
    sfnt_getlicense(cfg->develop_id,
                    (byte*)cfg->software_key.bytes(),
                    cfg->license_id,
                    cfg->key_flag,
                    key);
    if (sfnt_failed(key)) {
        trace_msg("failed to init usbkey.");
        sfnt_fin(key);
        return false;
    }

    // obtain the key.
    this->close();
    _cfg = cfg;
    _key = key;
    return true;
}

bool Standalone::is_failed() const
{
    return sfnt_failed(_key);
}

dword Standalone::errid() const
{
    return sfnt_errid(_key);
}

core::string Standalone::result_string() const
{
    char const* str = sfnt_tostring(_key);
    return str ? str : core::null_string;
}

int Standalone::result_int() const
{
    return sfnt_toint(_key);
}

core::string Standalone::query_feature(dword fid, dword flg, core::data const& qry, dword tgtlen) const
{
    sfnt_queryfeature(fid, 
                      flg, 
                      (byte*)qry.bytes(), 
                      qry.length(), 
                      tgtlen,
                      _key);
    if (sfnt_failed(_key))
        return core::null_string;
    return result_string();
}

core::string Standalone::read_string(dword fid) const
{
    sfnt_readstring(fid, _key);
    if (sfnt_failed(_key))
        return core::null_string;
    return result_string();
}

int Standalone::read_integer(dword fid) const
{
    sfnt_readinteger(fid, _key);
    if (sfnt_failed(_key))
        return 0;
    return result_int();
}

NNT_END_NS NNT_END_CXX
