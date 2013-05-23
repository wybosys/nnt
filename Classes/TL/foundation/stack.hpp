
# ifndef __NNT_FOUNDATION_STACK_b12b5b1784ac44ccb2af358b20388641_H_INCLUDED
# define __NNT_FOUNDATION_STACK_b12b5b1784ac44ccb2af358b20388641_H_INCLUDED

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(foundation)

NNT_BEGIN_NS(impl)

template <typename valT>
class stack_node
{
public:

    stack_node()
        : previous(NULL)
    {
        PASS;
    }

    ~stack_node()
    {
        delete previous;
    }

    valT val;
    stack_node* previous;
    bool indie;

};

NNT_END_NS

template <typename valT>
class stack
{
    typedef impl::stack_node<valT> node_type;

public:

    typedef valT value_type;

    stack()
        : _top(NULL)
    {
        PASS;
    }

    ~stack()
    {
        clear();
    }

    void push(value_type const& val)
    {
        node_type* node = new node_type;
        node->val = val;

        if (_top == NULL)
        {
            _top = node;
        }
        else
        {
            node->previous = _top;
            _top = node;
        }
    }

    stack& operator << (value_type const& val)
    {
        push(val);
        return *this;
    }

    value_type pop()
    {
        value_type ret = _top->val;
        node_type* top = _top;
        _top = _top->previous;
        top->previous = NULL;
        delete top;
        return ret;
    }

    stack& operator >> (value_type& val)
    {
        val = pop();
        return *this;
    }

    value_type const& top() const
    {
        return _top->val;
    }

    value_type& top()
    {
        return _top->val;
    }

    bool is_empty() const
    {
        return _top == NULL;
    }

    void clear()
    {
        delete _top;
        _top = NULL;
    }

protected:

    node_type* _top;

};

NNT_END_NS
NNT_END_HEADER_CXX

# endif
