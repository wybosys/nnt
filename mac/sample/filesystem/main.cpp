
# include <wsi/WSIFoundation.h>
# include <wsi/FsSamba.h>

using namespace wsi;

int main(int argc, const char * argv[])
{
    filesystem::Samba fs;
    fs.open("192.168.144.197/shared", "wybo", "pack");
    filesystem::Samba::file_io fd = fs.fopen("README", filesystem::Samba::FLAG_READ);
    if (fd)
    {
        struct ::stat st;
        if (fs.fstat(fd, &st))
            trace_int((int)st.st_size);
        core::data stm(st.st_size);
        fs.fread(fd, stm);
        trace_msg(core::type_cast<core::string>(stm));
        fs.fclose(fd);
    }
    else
    {
        trace_msg("failed to open file");
    }
    
    return 0;
}

