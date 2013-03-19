
# include "Core.h"
# include "CSVParser.h"

# include "../Core/Boost+WSI.h"
# include <boost/spirit/include/classic.hpp>
# include <boost/spirit/include/qi.hpp>
# include <boost/spirit/include/phoenix.hpp>

WSI_BEGIN_CXX
WSI_BEGIN_NS(parser)

using ::boost::spirit::qi::grammar;
using ::boost::spirit::qi::rule;
using ::boost::spirit::ascii::space_type; 
using ::boost::phoenix::function;

class csv_grammar;

struct _do_value
{
	template <typename T> struct result { typedef void type; };
	void operator () (csv_grammar*) const;
};
function<_do_value> const do_value = _do_value();

struct _do_row
{
	template <typename T> struct result { typedef void type; };
	void operator () (csv_grammar*) const;
};
function<_do_row> const do_row = _do_row();

class csv_grammar
	: public grammar<char const*>
{
	typedef rule<char const*> rule_t;

public:

	csv_grammar(CSVParser& _obj)
		: csv_grammar::base_type(_rule, "CSVParser"),
		object(_obj)
	{
		using ::boost::spirit::qi::alnum;
		using ::boost::spirit::qi::space;
		using ::boost::spirit::qi::blank;
		using ::boost::spirit::qi::char_;
		using ::boost::phoenix::clear;
		using ::boost::phoenix::push_back;
		using ::boost::phoenix::ref;
		using ::boost::spirit::_1;
		using ::boost::spirit::qi::eol;

		_value = +(
			alnum[push_back(ref(str_value), _1)] | 
			blank[push_back(ref(str_value), _1)] |
			char_("-!@#$%^&*()_+=[]\\{}|;:'<>?./`~")[push_back(ref(str_value), _1)]
		);

		_septor = char_(',');
		_row = _value[do_value(this)] >> *(_septor >> _value)[do_value(this)];
		_rule = *(_row >> eol)[do_row(this)] | _row[do_row(this)];
	}

	void clear()
	{
		str_value.clear();
		ptr_row = NULL;
	}

public:

	core::string str_value;
	CSVParser::row_type* ptr_row;
	CSVParser& object;

protected:

	rule_t _rule, _value, _row, _septor;

};

void _do_value::operator () (csv_grammar* gmr) const
{
	if (gmr->ptr_row == NULL)
	{
		gmr->object.rows.resize(gmr->object.rows.size() + 1);
		gmr->ptr_row = &gmr->object.rows.back();
	}

	gmr->ptr_row->push_back(gmr->str_value);
	gmr->str_value.clear();
}

void _do_row::operator () (csv_grammar* gmr) const
{
	gmr->ptr_row = NULL;
}

WSIDECL_PRIVATE_BEGIN_CXX(CSVParser)

void init()
{
	grammar = new csv_grammar(*d_owner);
}

void dealloc()
{
	safe_delete(grammar);
}

csv_grammar* grammar;

WSIDECL_PRIVATE_END_CXX

CSVParser::CSVParser()
{
	WSIDECL_PRIVATE_CONSTRUCT(CSVParser);
}

CSVParser::~CSVParser()
{
	WSIDECL_PRIVATE_DESTROY();
}

bool CSVParser::parse(core::string const& str)
{
	using ::boost::spirit::qi::phrase_parse;
	using ::boost::spirit::qi::space;

	d_ptr->grammar->clear();
	bool suc = phrase_parse(str.c_str(), str.c_str() + str.length(), *d_ptr->grammar, space);

	return suc;
}

void CSVParser::clear()
{
	this->rows.clear();
}

WSI_END_NS
WSI_END_CXX
