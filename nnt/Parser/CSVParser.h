
# ifndef __WSI_PARSER_CSV_7246C23BD5474CCD881B2086E7AA445A_H_INCLUDED
# define __WSI_PARSER_CSV_7246C23BD5474CCD881B2086E7AA445A_H_INCLUDED

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(parser)

WSICLASS(CSVParser);

WSIDECL_PRIVATE_HEAD_CXX(CSVParser);

class CSVParser
	: public cxx::Object<>
{

	WSIDECL_PRIVATE_CXX(CSVParser);

public:

	CSVParser();
	~CSVParser();

	typedef core::vector<core::string> row_type;
	typedef core::vector<row_type> rows_type;

	//! parse string.
	bool parse(core::string const&);

	//! clear data.
	void clear();

	//! rows data.
	rows_type rows;

};

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif
