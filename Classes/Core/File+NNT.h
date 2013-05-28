
# ifndef __NNT_FILE_7CB37C719B3749E9B3D2127DE02EFB29_H_INCLUDED
# define __NNT_FILE_7CB37C719B3749E9B3D2127DE02EFB29_H_INCLUDED

# ifdef NNT_CXX

# include "../TL/URL+NNT.h"

NNT_BEGIN_HEADER_CXX

class Io
{
public:

    typedef ntl::position_t<0> read;
    typedef ntl::position_t<1> write;
    typedef ntl::position_t<2> create;
    typedef ntl::position_t<3> close;
    typedef ntl::position_t<4> binary;
    typedef ntl::position_t<5> append;

};

NNTCLASS(File);

NNTDECL_PRIVATE_HEAD_CXX(File);

class File
	: public cxx::Object<>
{
	NNTDECL_PRIVATE_CXX(File);

public:

    typedef core::FileUrl<core::string> url_type;

# ifdef NNT_MSVC
    typedef HANDLE handle_type;
# else
    typedef void* handle_type;
# endif

	File();
	~File();

    bool open(url_type const& path, mask_t const& flag);
    void close();

    usize write(core::data const&);
    usize read(core::data&);

    handle_type handle() const;

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

NNT_END_HEADER_CXX

# endif

# endif
