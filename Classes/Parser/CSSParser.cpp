
# include "Core.h"
# include "CSSParser.h"
# include "../Core/Boost+WSI.h"

# include <boost/spirit/include/classic.hpp>
# include <boost/spirit/include/phoenix.hpp>
# include <boost/spirit/include/qi.hpp>

WSI_BEGIN_CXX

using ::boost::spirit::qi::grammar;
using ::boost::spirit::qi::rule;
using ::boost::spirit::qi::unused_type;
using ::boost::phoenix::function;
using ::boost::spirit::ascii::space_type;

class css_grammar;

struct  _do_addclass  
{
	template <typename T> struct result { typedef void type; };
	void operator () (css_grammar* gmr) const;
};
function<_do_addclass> const do_addclass = _do_addclass();

struct _do_addattr
{
	template <typename T> struct result { typedef void type; };
	void operator () (css_grammar* gmr) const;
};
function<_do_addattr> const do_addattr = _do_addattr();

class css_grammar
	: public grammar<char const*>
{
	typedef rule<char const*> rule_t;

public:
    css_grammar()
    : css_grammar::base_type(_rule, "CSSParser")
    {        
		using ::boost::spirit::qi::alnum;
		using ::boost::spirit::qi::lit;
		using ::boost::phoenix::push_back;
		using ::boost::phoenix::ref;
		using ::boost::spirit::qi::_1;
        using ::boost::spirit::qi::ascii::space;
        using ::boost::spirit::qi::skip;
        using ::boost::spirit::qi::char_;

		_attr_name = skip(space)[ +( 
                       alnum[push_back(ref(this->attr_name), _1)] | 
                       lit('-')[push_back(ref(this->attr_name), '-')]
                       )];

		_attr_value = *space >> +( 
                                  alnum[push_back(ref(this->attr_value), _1)] |
                                  char_("#().\'\" \\")[push_back(ref(this->attr_value), _1)]
                                  ) >> *space;

		_attr_obj = skip(space)[
                                ( _attr_name >> lit(':') >> _attr_value >> -lit(';') )[do_addattr(this)]
                                ];
        
        _class_name = skip(space)[+(
                                    alnum[push_back(ref(this->class_name), _1)] 
                                    )];        
        
        _class_obj = skip(space)[
                                 ( _class_name >> lit('{') >> *( _attr_obj ) >> lit('}') )[do_addclass(this)]
                                 ];
        
		_rule = *( _attr_obj | _class_obj );
    }

	~css_grammar()
	{
		clear();
	}

	void clear()
	{
		core::clear_destroy(classes);
		core::clear_destroy(attrs);
	}
    
protected:
    rule_t _rule;
    rule_t _attr_name, _attr_value, _attr_obj;
    rule_t _class_name;
    rule_t _class_obj;

public:
	core::string class_name, attr_name, attr_value;

public:
	css::classes_type classes;
	css::attributes_type attrs;
};

void _do_addclass::operator () (css_grammar* gmr) const
{
	css::classes_type::iterator found = gmr->classes.find(gmr->class_name);
	css::Class* tgt_cls = NULL;
	if (found != gmr->classes.end())
	{
		tgt_cls = found->second;
	}
	else
	{
		tgt_cls = new css::Class;
		tgt_cls->name = gmr->class_name;
		gmr->classes[gmr->class_name] = tgt_cls;
	}

	// add attribute.
	for (css::attributes_type::iterator each = gmr->attrs.begin();
		each != gmr->attrs.end();
		++each)
	{
		css::Attr* src = each->second;
		// find in class.
		css::attributes_type::iterator found = tgt_cls->attributes.find(src->name);
		if (found == tgt_cls->attributes.end())
		{
            tgt_cls->attributes.insert(core::make_pair(src->name, src));
			// attribute will freed while class destroy.
		}
		else
		{
			css::Attr* tgt = found->second;
			tgt->value = src->value;
			delete src; // free unuse.
		}
	}

	// clear.
	gmr->class_name.clear();
	gmr->attrs.clear();
}

void _do_addattr::operator() (css_grammar* gmr) const
{	
	css::Attr* tgt_attr = NULL;
    
    css::attributes_type::iterator found = gmr->attrs.find(gmr->attr_name);
	if (found != gmr->attrs.end())
	{
        if (found->second->value != gmr->attr_value)
        {
            tgt_attr = new css::Attr;
            tgt_attr->name = gmr->attr_name;
            tgt_attr->value = gmr->attr_value;   
            gmr->attrs.insert(core::make_pair(gmr->attr_name, tgt_attr));             
        }
        else
        {
            tgt_attr = found->second;
        }
	}
	else
	{
		tgt_attr = new css::Attr;
		tgt_attr->name = gmr->attr_name;
        tgt_attr->value = gmr->attr_value;
        gmr->attrs.insert(core::make_pair(gmr->attr_name, tgt_attr));        
	}	

	// clear.
	gmr->attr_name.clear();
	gmr->attr_value.clear();
}

WSIDECL_PRIVATE_BEGIN_CXX(CSSParser)

void init()
{
    grammar = new css_grammar();
}

void dealloc()
{
    safe_delete(grammar);
}

// parser.
css_grammar *grammar;

WSIDECL_PRIVATE_END_CXX

CSSParser::CSSParser()
{
    WSIDECL_PRIVATE_CONSTRUCT(CSSParser);
}

CSSParser::~CSSParser()
{
    WSIDECL_PRIVATE_DESTROY();
}

bool CSSParser::parse(const core::string & str)
{
    using ::boost::spirit::qi::phrase_parse;
    using ::boost::spirit::qi::space;

	d_ptr->grammar->clear();
    bool suc = phrase_parse(str.c_str(), str.c_str() + str.length(), *d_ptr->grammar, space);

	return suc;
}

css::classes_type const& CSSParser::classes() const
{
	return d_ptr->grammar->classes;
}

css::attributes_type const& CSSParser::attributes() const
{
	return d_ptr->grammar->attrs;
}

WSI_END_CXX
