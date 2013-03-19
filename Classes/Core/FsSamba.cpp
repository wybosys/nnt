
# include "Core.h"
# include "FsSamba.h"
# include <smb/libsmbclient.h>

NNT_BEGIN_HEADER_C

char const* res_9_dn_expand(char const*, char const*, char const*, char const*, int);
char const* res_9_query();
char const* res_9_dn_expand(char const*, char const*, char const*, char const*, int) { return NULL; }
char const* res_9_query() { return NULL; }

NNT_END_HEADER_C

NNT_BEGIN_CXX
NNT_BEGIN_NS(filesystem)

NNTDECL_PRIVATE_BEGIN_CXX(Samba)

void init()
{
    ctx = NULL;
}

void dealloc()
{
    this->close();
}

void close()
{
    if (ctx)
    {
        smbc_free_context(ctx, 1);
        ctx = NULL;
    }
}

SMBCCTX* ctx;
core::string url;

NNTDECL_PRIVATE_END_CXX

Samba::Samba()
{
    NNTDECL_PRIVATE_CONSTRUCT(Samba);
}

Samba::~Samba()
{
    NNTDECL_PRIVATE_DESTROY();
}

static core::string _gs_acc, _gs_passwd, _gs_workgroup;

static void smbc_auth_fn(
                         const char      *server,
                         const char      *share,
                         char            *wrkgrp, int wrkgrplen,
                         char            *user,   int userlen,
                         char            *password, int passwdlen)
{
    strncpy(wrkgrp, _gs_workgroup.c_str(), wrkgrplen - 1); wrkgrp[wrkgrplen - 1] = 0;
    strncpy(user, _gs_acc.c_str(), userlen - 1); user[userlen - 1] = 0;
    strncpy(password, _gs_passwd.c_str(), passwdlen - 1); password[passwdlen - 1] = 0;
}

bool Samba::open(const core::string &url, const core::string &account, const core::string &passwd)
{
    SMBCCTX* ctx = smbc_new_context();
    
    smbc_setDebug(ctx, 0);
    smbc_setFunctionAuthData(ctx, smbc_auth_fn);
    
    if (NULL == smbc_init_context(ctx))
    {
        smbc_free_context(ctx, 1);
        return false;
    }
    
    core::string dir = "smb://" + url;
    _gs_acc = account;
    _gs_workgroup = "WORKGROUP";
    _gs_passwd = passwd;
    
    SMBCFILE *fd = smbc_getFunctionOpendir(ctx)(ctx, dir.c_str());
    if (fd == NULL)
    {
        smbc_free_context(ctx, 1);
        return false;
    }

    this->close();
    d_ptr->ctx = ctx;
    d_ptr->url = dir + "/";
    return true;
}

void Samba::close()
{
    d_ptr->close();
}

file_io Samba::fopen(const core::string & nm, flag_t fg) const
{
    int flag = 0;
    if (MASK_CHECK(FLAG_READ, fg) && !MASK_CHECK(FLAG_WRITE, fg)) 
        flag |= O_RDONLY;
    else if (MASK_CHECK(FLAG_WRITE, fg) && !MASK_CHECK(FLAG_READ, fg))
        flag |= O_WRONLY;
    else if (MASK_CHECK(FLAG_READ, fg) && MASK_CHECK(FLAG_WRITE, fg))
        flag |= O_RDWR;

    mode_t md = 0;
    
    core::string file = d_ptr->url + nm;
    SMBCFILE *fd = smbc_getFunctionOpen(d_ptr->ctx)(d_ptr->ctx, file.c_str(), flag, md);
    if (fd == NULL)
        return NULL;    
    return (file_io)fd;
}

void Samba::fclose(file_io fd) const
{
    smbc_getFunctionClose(d_ptr->ctx)(d_ptr->ctx, (SMBCFILE*)fd);
}

bool Samba::stat(core::string const& nm, struct stat* st) const
{
    core::string file = d_ptr->url + nm;
    int sta = smbc_getFunctionStat(d_ptr->ctx)(d_ptr->ctx, file.c_str(), (struct ::stat*)st);
    return sta == 0;
}

bool Samba::fstat(file_io fd, struct stat* st) const
{
    int sta = smbc_getFunctionFstat(d_ptr->ctx)(d_ptr->ctx, (SMBCFILE*)fd, (struct ::stat*)st);
    return sta == 0;
}

int Samba::fread(file_io fd, core::data& da) const
{
    int sta = smbc_getFunctionRead(d_ptr->ctx)(d_ptr->ctx, (SMBCFILE*)fd, (void*)da.bytes(), da.length());
    da.set_length(sta);
    return sta;
}

int Samba::fwrite(file_io fd, core::data const& da) const
{
    int sta = smbc_getFunctionWrite(d_ptr->ctx)(d_ptr->ctx, (SMBCFILE*)fd, (void*)da.bytes(), da.length());
    return sta;
}

NNT_END_NS
NNT_END_CXX
