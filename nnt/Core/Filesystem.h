
# ifndef __NNT_CORE_FILESYSTEM_E377F010F918425EBDB35527567C33A0_H_INCLUDED
# define __NNT_CORE_FILESYSTEM_E377F010F918425EBDB35527567C33A0_H_INCLUDED

# ifdef NNT_CXX

# include <sys/stat.h>

NNT_BEGIN_HEADER_CXX

struct _file_io {};
typedef _file_io *file_io;

class Filesystem
: public cxx::Object<>
{
public:
    
    Filesystem();
    ~Filesystem();
        
    typedef enum
    {
        FLAG_READ = 1, //! Open a file for reading. The file must exist.
        FLAG_WRITE = 2, //! Create an empty file for writing. If a file with the same name already exists its content is erased and the file is treated as a new empty file.
        FLAG_APPEND = 4, //! Append to a file. Writing operations append data at the end of the file. The file is created if it does not exist.
        FLAG_READPLUS = 8, //! Open a file for update both reading and writing. The file must exist.
        FLAG_WRITEPLUS = 0x10, //! Create an empty file for both reading and writing. If a file with the same name already exists its content is erased and the file is treated as a new empty file.
        FLAG_APPENDPLUS = 0x20, //! Open a file for reading and appending. All writing operations are performed at the end of the file, protecting the previous content to be overwritten. You can reposition (fseek, rewind) the internal pointer to anywhere in the file for reading, but writing operations will move it back to the end of file. The file is created if it does not exist.
        
    } flag_t;
    
public:
    
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

NNT_END_HEADER_CXX

# endif

# endif