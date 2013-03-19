
# include "Core.h"
# include "StateMachine.h"

WSI_BEGIN_CXX
WSI_BEGIN_NS(wf)

State::State(int v)
: scalar(v)
{
    
}

State::State(core::string const& v)
: name(v),
scalar(0)
{
    
}

bool State::operator < (State const& r) const
{
    if (scalar == 0)
        return name < r.name;
    return scalar < r.scalar;
}

Machine::Machine()
{
    
}

Machine::~Machine()
{
    clear();
}

void Machine::clear()
{
    _states.clear();
}

Operation* Machine::look(State const& sta, Operation* ope)
{
    states_type::iterator found = _states.find(sta);
    if (found != _states.end())
    {
        found->second.push_back(ope);
        ope->grab();
        return ope;
    }
    
    _states[sta].push_back(ope);
    ope->grab();
    return ope;
}

void Machine::process(State const& sta, void* param)
{
    states_type::iterator found = _states.find(sta);
    if (found == _states.end())
        return;
    
    operations_type& opers = found->second;
    operations_type::iterator each = opers.begin();
    while (each != opers.end())
    {
        int rc = (*each)->run(param);
        if (rc < 0)
        {
            // failed.
# ifdef WSI_DEBUG
            
            core::string msg = "failed to run a operation of state: ";
            if (sta.scalar)
                msg += "scalar = " + core::tostr(sta.scalar) + ", ";
            if (!sta.name.empty())
                msg += "name = " + sta.name;
            trace_msg(msg);
            
# endif
            if (MASK_CHECK(Operation::RESULT_BREAK, rc))
                break;
        }
        else
        {
            if (MASK_CHECK(Operation::RESULT_COMPLETE, rc))
            {
                each = opers.erase(each);
                continue;
            }
        }
        
        ++each;
    }
    
    // if is empty, then remove.
    if (opers.size() == 0)
    {
        _states.erase(found);
    }
}

bool Machine::exist(State const& sta) const
{
    states_type::const_iterator found = _states.find(sta);
    return found != _states.end();
}

bool Machine::exist(State const& sta, Operation const* ope) const
{
    states_type::const_iterator found = _states.find(sta);
    if (found == _states.end())
        return false;
    operations_type::const_iterator iter = ::std::find(found->second.begin(), found->second.end(), ope);
    return iter != found->second.end();
}

void Machine::remove(State const& sta)
{
    states_type::iterator found = _states.find(sta);
    if (found != _states.end())
        _states.erase(found);
}

void Machine::remove(State const& sta, Operation const* ope)
{
    states_type::iterator found = _states.find(sta);
    if (found == _states.end())
        return;
    operations_type::iterator iter = ::std::find(found->second.begin(), found->second.end(), ope);
    if (iter == found->second.end())
        return;
    
    found->second.erase(iter);
}

WSI_END_NS
WSI_END_CXX
