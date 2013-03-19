
# ifndef __WSI_FILESYSTEM_SAMBA_B9E6885C88E84E4AAA58252FCE471C8A_H_INCLUDED
# define __WSI_FILESYSTEM_SAMBA_B9E6885C88E84E4AAA58252FCE471C8A_H_INCLUDED

# ifdef WSI_CXX

# include "Filesystem.h"

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(filesystem)

WSIDECL_PRIVATE_HEAD_CXX(Samba);

class Samba
: public Filesystem
{
    WSIDECL_PRIVATE_CXX(Samba);
    WSIDECL_NOCOPY(Samba);
 
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

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif