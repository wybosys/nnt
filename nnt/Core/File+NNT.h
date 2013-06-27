
# ifndef __NNT_FILE_7CB37C719B3749E9B3D2127DE02EFB29_H_INCLUDED
# define __NNT_FILE_7CB37C719B3749E9B3D2127DE02EFB29_H_INCLUDED

# ifdef NNT_CXX

# include "../TL/URL+NNT.h"

NNT_BEGIN_HEADER_CXX

class Io
{
public:
    
    typedef ntl::mpl::position<0> read;
    typedef ntl::mpl::position<1> write;
    typedef ntl::mpl::position<2> create;
    typedef ntl::mpl::position<3> close;
    typedef ntl::mpl::position<4> binary;
    typedef ntl::mpl::position<5> append;
    
    enum seek
    {
        seek_cur = 0,
        seek_end = 1,
        seek_set = 2,
    };
    
};

NNT_BEGIN_NS(core)

class IoStream
: public VirObject
{
public:
    
    virtual usize write(core::data const&) = 0;
    virtual usize read(core::data&) = 0;
    virtual usize position() const = 0;
    virtual void seek(offset, Io::seek) = 0;
    virtual usize length() const = 0;
    
};

NNTCLASS(File);

NNTDECL_PRIVATE_HEAD_CXX(File);

class File
	: public cxx::Object<>,
public IoStream
{
	NNTDECL_PRIVATE_CXX(File);

public:

    typedef core::FileUrl<core::string> url_type;

# ifdef NNT_MSVC
    typedef HANDLE handle_type;
# else
    typedef FILE* handle_type;
# endif

	File();
	~File();

    bool open(url_type const& path, mask_t const& flag);
    void close();

    virtual usize write(core::data const&);
    virtual usize read(core::data&);
    virtual usize position() const;
    virtual void seek(offset, Io::seek);
    virtual usize length() const;

    //! return in-os file handle.
    handle_type handle() const;
    
    //! control contents from file.
    static bool ReadAll(url_type const& path, core::data&);
    static bool SaveAll(url_type const& path, core::data const&);
    
};

NNTCLASS(FileIo);

class FileIo
    : public cxx::Object<>
{
public:

    enum {BUFFER_LEN = 256};

    FileIo(File&);
    ~FileIo();

    bool control(ulong);

    core::data send, receive;

protected:

    File& _file;

};

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif
