
# ifndef __WSI_WTL_REGEX_3AB3DDFE16D64DDD8120FE38B3FB9ACE_H_INCLUDED
# define __WSI_WTL_REGEX_3AB3DDFE16D64DDD8120FE38B3FB9ACE_H_INCLUDED

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(wtl)

typedef vector<string> regex_matched_t;
typedef vector< regex_matched_t > regex_captured_t;

WSIAPI(bool) regex_match(string const& regex, string const& str);
WSIAPI(bool) regex_grep(string const& regex, string const& str, regex_matched_t& result);
WSIAPI(bool) regex_capture(string const& regex, string const& str, regex_captured_t& result);
WSIAPI(core::string) regex_replace(string const& regex, string const& replace, string const& str);

class regex
{
public:
    
    regex(string const& re);
    ~regex();
    
public:
    
    bool grep(string const& str, regex_matched_t& result) const;
    regex_matched_t grep(string const& str) const;
    
    void capture(string const& str, regex_captured_t& result) const;
    regex_captured_t capture(string const& str) const;
    
    core::string replace(string const& fmt, string const& str) const;
    
protected:
    
    void* _re;
    
};

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif