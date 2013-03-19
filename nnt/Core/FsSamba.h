
# ifndef __NNT_FILESYSTEM_SAMBA_B9E6885C88E84E4AAA58252FCE471C8A_H_INCLUDED
# define __NNT_FILESYSTEM_SAMBA_B9E6885C88E84E4AAA58252FCE471C8A_H_INCLUDED

# ifdef NNT_CXX

# include "Filesystem.h"

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(filesystem)

NNTDECL_PRIVATE_HEAD_CXX(Samba);

class Samba
: public Filesystem
{
    NNTDECL_PRIVATE_CXX(Samba);
    NNTDECL_NOCOPY(Samba);
 
public:
    Samba();
    virtual ~Samba();
    
    //! open a new.
    bool open(core::string const& url, core::string const& accout, core::string const& passwd);
    
    //! close.
    void close();
    
public:
    
    file_io fopen(core::string const&, flag_t) const;
    void fclose(file_io) const;
    bool stat(core::string const&, struct stat*) const;
    bool fstat(file_io, struct stat*) const;
    int fread(file_io, core::data&) const;
    int fwrite(file_io, core::data const&) const;
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif