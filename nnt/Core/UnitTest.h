
# ifndef __WSI_CORE_UNITTEST_80BD7E74F16847CAACF350555991EC76_H_INCLUDED
# define __WSI_CORE_UNITTEST_80BD7E74F16847CAACF350555991EC76_H_INCLUDED

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(ut)

class Case
: public RefObject
{
public:
    
    Case(core::string const& nm);
    virtual ~Case();
    
    //! prepare.
    virtual bool prepare();
    
    //! collect.
    virtual void collect();
    
    //! run.
    virtual bool run() = 0;
    
    //! step.
    virtual void step(core::string const& msg = core::null_string);
    
    //! assert.
    virtual void assert(bool exp, core::string const& msg = core::null_string);
    
    //! name of case.
    core::string name;
    
protected:
    
    uint _step;
    core::string _stepmsg;
    
};

class Suite
{
public:
    
    typedef core::map<core::string, Case*> cases_type;
    
    Suite();
    virtual ~Suite();
    
    //! add.
    bool add(Case* obj);
    
    //! find.
    Case* find(core::string const&);
    
    //! run.
    virtual void run();
    
    //! case is error return.
    virtual void case_error(Case*);
    
    //! case is success return.
    virtual void case_success(Case*);
    
protected:
    
    cases_type _cases;
    
};

WSI_END_NS
WSI_END_HEADER_CXX

WSI_BEGIN_HEADER_C

WSIAPI(::wsi::ut::Suite*) UTSuiteDefault();
WSIAPI(void) UTSuiteFree(::wsi::ut::Suite*);
WSIAPI(bool) UTSuiteAddCase(::wsi::ut::Case*, ::wsi::ut::Suite*);
WSIAPI(void) UTSuiteRun(::wsi::ut::Suite*);

WSI_END_HEADER_C

# endif

# endif