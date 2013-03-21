
# ifndef __NNT_FILE_7CB37C719B3749E9B3D2127DE02EFB29_H_INCLUDED
# define __NNT_FILE_7CB37C719B3749E9B3D2127DE02EFB29_H_INCLUDED

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX

NNTDECL_PRIVATE_HEAD_CXX(File);

class File
	: public cxx::Object<>
{
	NNTDECL_PRIVATE_CXX(File);

public:

	File();
	~File();

	//! read file.
	bool read(core::string const& path);

	//! read line.
	bool getline(core::string&);

	//! read all.
	void getall(core::string&);

	//! is eof.
	bool is_eof() const;

	//! close.
	void close();

};

NNT_END_HEADER_CXX

# endif

# endif
