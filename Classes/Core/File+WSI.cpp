
# include "Core.h"
# include "File+WSI.h"
# include <iostream>
# include <fstream>
# include <boost/iostreams/filtering_stream.hpp>

WSI_BEGIN_CXX

WSIDECL_PRIVATE_BEGIN_CXX(File)

void init()
{
	in = NULL;
	out = NULL;
}

void dealloc()
{
	close();
}

void close()
{
	safe_delete(in);
	safe_delete(out);

	fin.clear();
	fout.clear();
}

::std::ifstream* in;
::std::ofstream* out;
::boost::iostreams::filtering_istream fin;
::boost::iostreams::filtering_ostream fout;

WSIDECL_PRIVATE_END_CXX

File::File()
{
	WSIDECL_PRIVATE_CONSTRUCT(File);
}

File::~File()
{
	WSIDECL_PRIVATE_DESTROY();
}

bool File::read(core::string const& path)
{
	d_ptr->in = new ::std::ifstream(path.c_str(), ::std::ios::in | ::std::ios::binary);
	if (d_ptr->in->is_open() == false)
	{
		safe_delete(d_ptr->in);
		return false;
	}

	d_ptr->fin.clear();
	d_ptr->fin.push(*d_ptr->in);

	return true;
}

bool File::getline(core::string& str)
{
	if (d_ptr->in->eof())
		return false;
	::std::getline(d_ptr->fin, str);
	return true;
}

void File::getall(core::string& str)
{
	str = std::string(::std::istreambuf_iterator<char>(d_ptr->fin), ::std::istreambuf_iterator<char>());
}

bool File::is_eof() const
{
	return d_ptr->in->eof();
}

void File::close()
{
	d_ptr->close();
}

WSI_END_CXX
