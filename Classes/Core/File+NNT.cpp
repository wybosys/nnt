
# include "Core.h"
# include "File+NNT.h"

NNT_BEGIN_CXX
NNT_BEGIN_NS(core)

NNTDECL_PRIVATE_BEGIN_CXX(File)

void init()
{
    file = NULL;
}

void dealloc()
{
	close();
}

bool is_opened() const
{
    return file != NULL;
}

void close()
{
    if (!is_opened())
        return;

# ifdef NNT_MSVC

# ifdef NNT_USER_SPACE

    ::CloseHandle(file);

# endif

# ifdef NNT_KERNEL_SPACE
    ::ZwClose(file);
# endif
    
# else
    
    ::fclose(file);

# endif

    file = NULL;
}

owner_type::handle_type file;

NNTDECL_PRIVATE_END_CXX

File::File()
{
	NNTDECL_PRIVATE_CONSTRUCT(File);
}

File::~File()
{
	NNTDECL_PRIVATE_DESTROY();
}

bool File::open(url_type const& path, mask_t const& flag)
{
    // close last.
    close();

    // open new.
    core::string file = path.full();

# ifdef NNT_MSVC

# ifdef NNT_USER_SPACE

    d_ptr->file = ::CreateFileA(file.c_str(),
        opt<enum_t>(flag.checked<Io::read>())[GENERIC_READ] | opt<enum_t>(flag.checked<Io::write>())[GENERIC_WRITE],
        opt<enum_t>(flag.checked<Io::read>())[FILE_SHARE_READ] | opt<enum_t>(flag.checked<Io::write>())[FILE_SHARE_WRITE] << opt<enum_t>::failed(0),
        NULL,
        opt<enum_t>(flag.checked<Io::read>())[OPEN_EXISTING] | opt<enum_t>(flag.checked<Io::write>() && flag.checked<Io::create>())[CREATE_ALWAYS],
        NULL,
        NULL);

    if (d_ptr->file == INVALID_HANDLE_VALUE)
        d_ptr->file = NULL;

# endif

# ifdef NNT_KERNEL_SPACE

    OBJECT_ATTRIBUTES attr_obj;
    InitializeObjectAttributes(&attr_obj,
        file,
        OBJ_CASE_INSENSITIVE,
        NULL,
        NULL);

    IO_STATUS_BLOCK sta_io;
    ::ZwCreateFile(&d_ptr->file,
        opt<enum_t>(flag.checked<Io::read>())[GENERIC_READ] | opt<enum_t>(flag.checked<Io::write>())[GENERIC_WRITE],
        &attr_obj,
        &sta_io,
        NULL,
        FILE_ATTRIBUTE_NORMAL,
        opt<enum_t>(flag.checked<Io::read>())[FILE_SHARE_READ] | opt<enum_t>(flag.checked<Io::write>())[FILE_SHARE_WRITE],
        opt<enum_t>(flag.checked<Io::read>())[FILE_OPEN] | opt<enum_t>(flag.checked<Io::write>() && flag.checked<Io::append>())[FILE_OPEN_IF] |
        opt<enum_t>(flag.checked<Io::write>())[FILE_OVERWRITE_IF],
        FILE_SYNCHRONOUS_IO_NONALERT,
        NULL,
        0
        );

# endif
    
# else

    core::string mode = opt<core::string>(flag.checked<Io::read>())["r"] + opt<core::string>(flag.checked<Io::write>())["w"] +
    opt<core::string>(flag.checked<Io::append>())["a"] +
    opt<core::string>(flag.checked<Io::create>())["+"] +
    opt<core::string>(flag.checked<Io::binary>())["b"];
    d_ptr->file = fopen(file.c_str(), mode.c_str());

# endif

    return d_ptr->file != NULL;
}

bool File::is_opened() const
{
	return d_ptr->is_opened();
}

void File::close()
{
    d_ptr->close();
}

usize File::write(core::data const& da)
{

# ifdef NNT_MSVC

# ifdef NNT_USER_SPACE

    DWORD writen;
    ::WriteFile(d_ptr->file,
        da.bytes(),
        (DWORD)da.length(),
        &writen,
        NULL);

    return writen;

# endif

# ifdef NNT_KERNEL_SPACE

    IO_STATUS_BLOCK sta;
    ::ZwWriteFile(d_ptr->file,
        NULL,
        NULL,
        NULL,
        &sta,
        da.bytes(),
        (ULONG)da.length(),
        0,
        0);

    return sta.Information;

# endif
    
# else
    
    return fwrite(da.bytes(), sizeof(byte), da.length(), d_ptr->file);

# endif

    return 0;
}

usize File::read(core::data& da)
{
# ifdef NNT_MSVC

# ifdef NNT_USER_SPACE

    DWORD readed;
    ::ReadFile(d_ptr->file,
        da.bytes(),
        (DWORD)da.length(),
        &readed,
        NULL);

    da.set_length(readed);
    return da.length();

# endif

# ifdef NNT_KERNEL_SPACE

    IO_STATUS_BLOCK sta;
    ::ZwReadFile(d_ptr->file,
        NULL,
        NULL,
        NULL,
        &sta,
        da.bytes(),
        (ULONG)da.length(),
        0,
        0);
    da.set_length(sta.Information);
    return da.length();

# endif
    
# else
    
    ssize_t readed = fread(da.bytes(), sizeof(byte), da.length(), d_ptr->file);
    da.set_length(readed);
    return readed;

# endif

    return 0;
}

usize File::position() const
{
# ifdef NNT_MSVC
    
# else
    
    return ftell(d_ptr->file);
    
# endif
    
    return 0;
}

void File::seek(offset off, Io::seek m)
{
# ifdef NNT_MSVC
    
# else
    
    int md;
    switch (m)
    {
        case Io::seek_cur: md = SEEK_CUR; break;
        case Io::seek_end: md = SEEK_END; break;
        case Io::seek_set: md = SEEK_SET; break;
    }
    
    fseek(d_ptr->file, off, md);

# endif
}

usize File::length() const
{
    usize pos = position();
    down_const(this)->seek(0, Io::seek_end);
    usize ret = position();
    down_const(this)->seek(pos, Io::seek_set);
    return ret;
}

File::handle_type File::handle() const
{
    return d_ptr->file;
}

bool File::ReadAll(url_type const& path, core::data &da)
{
    File f;
    if (!f.open(path, mask_t().on<Io::read>()))
        return false;
    da.resize(f.length());
    f.read(da);
    f.close();
    return true;
}

bool File::SaveAll(url_type const& path, core::data const& da)
{
    File f;
    if (!f.open(path, mask_t().on<Io::write>().on<Io::create>()))
        return false;
    f.write(da);
    f.close();
    return true;
}

// fileio

FileIo::FileIo(File& f)
: _file(f)
{
    receive.resize(BUFFER_LEN);
}

FileIo::~FileIo()
{

}

bool FileIo::control(ulong code)
{
    bool ret = false;

# ifdef NNT_MSVC

# ifdef NNT_USER_SPACE

    ULONG received;
    ret = DeviceIoControl(_file.handle(),
        code,
        send.bytes_or_null(), send.length(),
        receive.bytes_or_null(), receive.length(),
        &received,
        NULL) == TRUE;

# endif

# endif

    return ret;
}

NNT_END_NS
NNT_END_CXX
