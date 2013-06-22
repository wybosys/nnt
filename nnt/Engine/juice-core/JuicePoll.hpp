
# ifndef __JUICE_POLL_B6E36CB1015F470E9D53F30EC6D75217_H_INCLUDED
# define __JUICE_POLL_B6E36CB1015F470E9D53F30EC6D75217_H_INCLUDED

JUICE_BEGIN

template <typename entry>
class PollEntry
: public entry
{
public:
    
    PollEntry()
    :
    index(0),
    count(0)
    {
        PASS;
    }
    
    uint index;
    uint count;
    
};

template <typename entry,
typename pollentry = PollEntry<entry>,
uint PollSegment = 32>
class Poll
{
public:
    
    typedef entry entry_type;
    typedef pollentry item_type;
    typedef ::nnt::core::vector<item_type> items_type;
    typedef ::nnt::core::stack<item_type*> unuseditems_type;
    
    Poll()
    {
        PASS;
    }
    
    ~Poll()
    {
        PASS;
    }
    
    entry_type& attach()
    {
        if (_unuseditems.size())
        {
            return *_unuseditems.pop();
        }
        
        uint const sz = items.size();
        items.resize(sz + PollSegment);
        item_type* ptr = &items.at(sz);
        for (uint i = 0; i < PollSegment; ++i)
        {
            ptr->index = sz + i;
            ptr->count = 1;
            _unuseditems.push(ptr++);
        }
        
        return *_unuseditems.pop();
    }
    
    void clear()
    {
        items.clear();
        _unuseditems.clear();
    }
    
    items_type items;
    
protected:
    
    unuseditems_type _unuseditems;
    
};

JUICE_END

# endif
