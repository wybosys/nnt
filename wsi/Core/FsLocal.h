
# ifndef __WSI_CORE_FS_LOCAL_0FEF86C0EB2946BDB848E4A729428AD1_H_INCLUDED
# define __WSI_CORE_FS_LOCAL_0FEF86C0EB2946BDB848E4A729428AD1_H_INCLUDED

# include "Filesystem.h"

# ifdef WSI_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(ns)

class Local
{
public:
    
    static bool copy(ns::URL const& to, ns::URL const& from);
    
};

WSI_END_NS
WSI_END_HEADER

# endif

# endif

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(fs)

WSICLASS(Local);

class Local
: public Filesystem
{
public:
    
    Local();
    
    //! open a file.
    file_io fopen(core::string const&, flag_t) const;
    
    //! close a file.
    void fclose(file_io) const;
    
    //! stat.
    bool stat(core::string const&, struct stat*) const;
    bool fstat(file_io, struct stat*) const;
    
    //! read.
    int fread(file_io, core::data&) const;
    
    //! write.
    int fwrite(file_io, core::data const&) const;
    
};

WSIAPI(bool) save(core::data const& data, core::string const& name);

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif
