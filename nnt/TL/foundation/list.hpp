
# ifndef __NNT_FOUNDATION_LIST_e6b52ff769904aa98970c9cc884854e3_H_INCLUDED
# define __NNT_FOUNDATION_LIST_e6b52ff769904aa98970c9cc884854e3_H_INCLUDED

# include "./iterator.hpp"

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(foundation)

NNT_BEGIN_NS(impl)

template <typename valT>
class list_node
{
public:

    list_node()
        : _previous(NULL), _next(NULL)
    {
        PASS;
    }

    ~list_node()
    {
        delete _next;
    }

    void bind_next(list_node& node)
    {
        list_node* pnext = _next;
        _next = &node;
        node._next = pnext;

        node._previous = this;
        if (pnext)
            pnext->_previous = &node;
    }

    valT val;

    list_node* next()
    {
        return _next;
    }

    list_node* previous()
    {
        return _previous;
    }

    void leave()
    {
        if (_previous)
            _previous->_next = _next;
        if (_next)
            _next->_previous = _previous;
        _previous = _next = NULL;
    }

protected:

    list_node *_previous, *_next;

};

NNT_END_NS

template <typename valT>
class list
{

    typedef impl::list_node<valT> node_type;

public:

    typedef valT value_type;

    list()
        : _begin(NULL), _end(NULL), _cnt(0)
    {
        PASS;
    }

    ~list()
    {
        clear();
    }

    list& operator << (value_type const& val)
    {
        push_back(val);
        return *this;
    }

    void push_back(value_type const& val)
    {
        node_type* node = new node_type;
        node->val = val;

        if (_end == NULL)
        {
            _begin = _end = node;
        }
        else
        {
            _end->bind_next(*node);
            _end = node;
        }

        ++_cnt;
    }

    void push_front(value_type const& val)
    {
        node_type* node = new node_type;
        node->val = val;

        if (_begin == NULL)
        {
            _begin = _end = node;
        }
        else
        {
            node->bind_next(_begin);
            _begin = node;
        }

        ++_cnt;
    }

    usize size() const
    {
        return _cnt;
    }

    class iterator
        : public basic_iterator<iterator, node_type*>
    {
    public:

        value_type& operator * ()
        {
            return this->obj->val;
        }

    };

    class const_iterator
        : public iterator
    {
    public:

        value_type const& operator * () const
        {
            return this->obj->val;
        }

    };

    iterator begin()
    {
        return iterator::Instance(_begin);
    }

    const_iterator begin() const
    {
        return const_iterator::Instance(_begin);
    }

    iterator end()
    {
        return iterator::Nil();
    }

    const_iterator end() const
    {
        return const_iterator::Nil();
    }

    void clear()
    {
        delete _begin;
        _begin = _end = NULL;
        _cnt = 0;
    }

    void erase(iterator const& iter)
    {
        if (iter.obj == _begin)
            _begin = iter.obj->next();
        if (iter.obj == _end)
            _end = iter.obj->previous();

        iter.obj->leave();
        delete iter.obj;
        --_cnt;
    }

    bool is_empty() const
    {
        return _cnt == 0;
    }

private:

    node_type *_begin, *_end;
    usize _cnt;

};

NNT_END_NS
NNT_END_HEADER_CXX

# endif
