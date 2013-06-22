
# ifndef __NNT_PARSER_CSV_7246C23BD5474CCD881B2086E7AA445A_H_INCLUDED
# define __NNT_PARSER_CSV_7246C23BD5474CCD881B2086E7AA445A_H_INCLUDED

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(parser)

NNTCLASS(CSVParser);

NNTDECL_PRIVATE_HEAD_CXX(CSVParser);

class CSVParser
	: public cxx::Object<>
{

	NNTDECL_PRIVATE_CXX(CSVParser);

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

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif
