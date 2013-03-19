
# include "Core.h"
# include "UnitTest.h"

WSI_BEGIN_CXX
WSI_BEGIN_NS(ut)

Case::Case(core::string const& nm)
: name(nm),
_step(0)
{
    PASS;
}

Case::~Case()
{
    PASS;
}

void Case::step(core::string const& msg)
{
    _stepmsg = msg;
    
    ::std::cout << "step: " << _step++;
    if (msg.empty() == false)
        ::std::cout << " " << msg;
    ::std::cout << ::std::endl;
}

void Case::assert(bool exp, core::string const& msg)
{
    if (exp)
        return;
    ::std::cout << "assert error at step: " << _step;
    if (_stepmsg.empty() == false)
        ::std::cout << " " << _stepmsg;
    
    if (msg.empty() == false)
        ::std::cout << ", " << msg;
    ::std::cout << ::std::endl;
}

bool Case::prepare()
{
    return true;
}

void Case::collect()
{
    PASS;
}

Suite::Suite()
{
    
}

Suite::~Suite()
{
    core::clear_drop(_cases);
}

bool Suite::add(Case* obj)
{
    if (find(obj->name))
        return false;
    
    _cases[obj->name] = obj;
    obj->grab();
    
    return true;
}

Case* Suite::find(core::string const& name)
{
    cases_type::iterator found = _cases.find(name);
    if (found == _cases.end())
        return NULL;
    return found->second;
}

void Suite::run()
{
    // hello message.
    ::std::cout << "Suite Test Begin: " << ::std::endl;
    
    // each case.
    int idx = 0, max = _cases.size(), pass = 0, failed = 0;
    for (cases_type::iterator each = _cases.begin();
         each != _cases.end();
         ++each,
         ++idx
         )
    {
        Case* obj = each->second;
        
        // print.
        ::std::cout << "======== BEGIN " << obj->name << " ========" << ::std::endl;
        
        // prepare case.
        if (obj->prepare() == false)
        {                        
            ::std::cout << "index: " << idx << " | pass: " << pass << " | failed: " << ++failed << " | all: " << max << ::std::endl;
            
            case_error(obj);  
            
            continue;
        }
        
        // run.
        if (obj->run())
        {                        
            ::std::cout << "index: " << idx << " | pass: " << ++pass << " | failed: " << failed << " | all: " << max << ::std::endl;
            
            case_success(obj);
        }
        else
        {                        
            ::std::cout << "index: " << idx << " | pass: " << pass << " | failed: " << ++failed << " | all: " << max << ::std::endl;
            
            case_error(obj);
        }
        
        // collect.
        obj->collect();
        
    }
    
    // bye message.
    ::std::cout << "Suite Test End." << ::std::endl;
}

void Suite::case_error(Case* obj)
{
    ::std::cout << "failed to run case: " << obj->name << ::std::endl;
}

void Suite::case_success(Case* obj)
{
    ::std::cout << "========= END " << obj->name << " ========= " << ::std::endl;
}

WSI_END_NS
WSI_END_CXX

WSI_BEGIN_C

::wsi::ut::Suite* UTSuiteDefault()
{
    return new ::wsi::ut::Suite;
}

void UTSuiteFree(::wsi::ut::Suite *obj)
{
    safe_delete(obj);
}

bool UTSuiteAddCase(::wsi::ut::Case *obj, ::wsi::ut::Suite *su)
{
    return su->add(obj);
}

void UTSuiteRun(::wsi::ut::Suite* su)
{
    su->run();
}

WSI_END_C