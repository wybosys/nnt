
# include "Core.h"
# include "FsLocal.h"
# include <iostream>

WSI_BEGIN_CXX
WSI_BEGIN_NS(fs)

Local::Local()
{
    
}

file_io Local::fopen(const core::string &file, flag_t flag) const
{
    core::string fg;
    if (MASK_CHECK(Local::FLAG_READ, flag))
        fg += "r";
    if (MASK_CHECK(Local::FLAG_WRITE, flag))
        fg += "w";
    if (MASK_CHECK(Local::FLAG_APPEND, flag))
        fg += "a";
    if (MASK_CHECK(Local::FLAG_READPLUS, flag))
        fg += "r+";
    if (MASK_CHECK(Local::FLAG_WRITEPLUS, flag))
        fg += "w+";
    if (MASK_CHECK(Local::FLAG_APPENDPLUS, flag))
        fg += "a+";
    
    return (file_io)::fopen(file.c_str(), fg.c_str());
}

void Local::fclose(file_io fd) const
{
    ::fclose((FILE*)fd);
}

int Local::fwrite(file_io fd, const core::data & da) const
{
    return ::fwrite(da.bytes(), 1, da.size(), (FILE*)fd);
}

bool save(core::data const& data, core::string const& name)
{
    Local fs;
    file_io fd = fs.fopen(name, Local::FLAG_WRITE);
    if (fd == NULL)
        return false;
    
    fs.fwrite(fd, data);
    fs.fclose(fd);
    
    return true;
}

WSI_END_NS
WSI_END_CXX
