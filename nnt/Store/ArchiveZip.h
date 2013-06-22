
# ifndef __NNT_STORE_ARCHIVE_ZIP_887D7F11C17A476CBD04E7FE22B17ED9_H_INCLUDED
# define __NNT_STORE_ARCHIVE_ZIP_887D7F11C17A476CBD04E7FE22B17ED9_H_INCLUDED

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX NNT_BEGIN_NS(store)

class Zip
{
    NNTDECL_NOCOPY(Zip);
    
public:
    Zip();
    ~Zip();
    
public:
    //! target.
    bool target(core::string const&, bool overwrite);
    
    //! close.
    void close();
    
protected:
    void* zp;
};

class UnZip
{
    NNTDECL_NOCOPY(UnZip);
    
public:
    UnZip(core::string const&);
    ~UnZip();
    
public:
    
    //! open a zip file.
    bool open(core::string const&);
    
    //! close.
    void close();
    
protected:
    void* zp;
};

NNT_END_NS NNT_END_HEADER_CXX

# endif

# endif