
# include "Core.h"
# include "File+NNT.h"

NNT_BEGIN_CXX

NNTDECL_PRIVATE_BEGIN_CXX(File)

void init()
{
# ifdef NNT_MSVC
    file = NULL;
# endif
}

void dealloc()
{
	close();
}

bool is_opened() const
{
# ifdef NNT_MSVC
    return file != NULL;
# endif
}

void close()
{
    if (!is_opened())
        return;

# ifdef NNT_MSVC

# ifdef NNT_KERNEL_SPACE
    ::ZwClose(file);
    file = NULL;
# endif

# endif
}

# ifdef NNT_MSVC

HANDLE file;

# endif

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

# endif

    return d_ptr->file != NULL;
}

void File::close()
{
    d_ptr->close();
}

usize File::write(core::data const& da)
{

# ifdef NNT_MSVC

# ifdef NNT_KERNEL_SPACE

    IO_STATUS_BLOCK sta;
    ::ZwWriteFile(d_ptr->file,
        NULL,
        NULL,
        NULL,
        &sta,
        da.bytes(),
        da.length(),
        0,
        0);

    return sta.Information;

# endif

# endif

    return 0;
}

NNT_END_CXX
