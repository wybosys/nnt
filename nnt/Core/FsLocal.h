
# ifndef __NNT_CORE_FS_LOCAL_0FEF86C0EB2946BDB848E4A729428AD1_H_INCLUDED
# define __NNT_CORE_FS_LOCAL_0FEF86C0EB2946BDB848E4A729428AD1_H_INCLUDED

# include "Filesystem.h"

# ifdef NNT_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ns)

class Local
{
public:
    
    static bool copy(ns::URL const& to, ns::URL const& from);
    
};

NNT_END_NS
NNT_END_HEADER

# endif

# endif

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(fs)

NNTCLASS(Local);

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

NNTAPI(bool) save(core::data const& data, core::string const& name);

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif
