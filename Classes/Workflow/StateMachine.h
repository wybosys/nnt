
# ifndef __WSI_WF_STATEMACHINE_4F0CA524AA174D08ACDE237824C385DD_H_INCLUDED
# define __WSI_WF_STATEMACHINE_4F0CA524AA174D08ACDE237824C385DD_H_INCLUDED

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(wf)

class State
{
public:
    
    explicit State(int scalar);
    explicit State(core::string const& name);
    
    //! must != 0. if == 0, will use name for map's key.
    int scalar;
    core::string name;
  
    // for map.
    bool operator < (State const& r) const;
};

class Operation
: public RefObject
{
public:
    
    enum
    {
        RESULT_FAILED = 0xF0000000, // mask for failed, < 0
        RESULT_SUC = 0x00000000, // mask for suc, >= 0
        
        RESULT_COMPLETE = 0x1, // some return code.
        RESULT_BREAK = 0x2, // break on failure.
    };
    
    virtual int run(void*) { return RESULT_SUC; }
        
};

class Machine
{
public:
    
    Machine();
    ~Machine();
    
    typedef core::refpointer_vector<Operation> operations_type;
    typedef core::map<State, operations_type> states_type;
    
public:
    
    //! clear all states.
    void clear();
    
    //! add state.
    Operation* look(State const&, Operation*);
    
    template <typename valT, typename keyT>
    valT* look(keyT const& key, valT* val)
    {
        return (valT*)look(State(key), (Operation*)val);
    }
    
    template <typename valT, typename keyT>
    valT* look(keyT const& key)
    {
        return (valT*)look(State(key), core::smart_drop<valT>::instance());
    }
    
    //! process a state.
    void process(State const&, void* = NULL);
    
    //! exist.
    bool exist(State const&) const;
    
    //! exist.
    bool exist(State const&, Operation const*) const;
    
    //! remove.
    void remove(State const&);
    
    //! remove.
    void remove(State const&, Operation const*);
        
protected:
    
    states_type _states;
    
};

WSI_END_NS
WSI_END_HEADER_CXX

# endif
