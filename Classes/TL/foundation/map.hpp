
# ifndef __NNT_FOUNDATION_MAP_6a2dc95ea3b44eff82443518e93c230d_H_INCLUDED
# define __NNT_FOUNDATION_MAP_6a2dc95ea3b44eff82443518e93c230d_H_INCLUDED

# include "./rbtree.hpp"
# include "./iterator.hpp"

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(foundation)

template <typename keyT, typename valT>
class map
    : protected rbtree<keyT, valT>
{
    typedef rbtree<keyT, valT> super, rbtree_type;

public:

    typedef keyT key_type;
    typedef pair<keyT, valT> value_type;

    class iterator
        : public basic_iterator<iterator, typename rbtree_type::node_type*>        
    {
    public:

        value_type* operator -> ()
        {
            if (this->obj != NULL)
            {
                _pair.first = this->obj->key();
                _pair.second = this->obj->val;
            }

            return &_pair;
        }

    public:

        value_type _pair;

    };

    map()
    {
        PASS;
    }

    bool insert(value_type const& val)
    {
        return super::insert(val.first, val.second);
    }

    iterator find(key_type const& key)
    {
        iterator ret;
        ret.obj = super::lookup(key);
        return ret;
    }

    iterator begin()
    {
        iterator ret;
        ret.obj = super::_root;
        return ret;
    }

    iterator const& end() const
    {
        static const iterator iter_end;
        return iter_end;
    }

    void erase(iterator const& iter)
    {
        super::remove(*iter.obj);
    }

    void clear()
    {
        super::remove(*super::_root);
    }

    template <typename conT>
    void all_keys(conT& c) const
    {
        super::all_keys(c);
    }

    template <typename conT>
    conT all_keys() const
    {
        conT t;
        all_keys(t);
        return t;
    }

    template <typename conT>
    void all_values(conT& c) const
    {
        super::all_values(c);
    }

    template <typename conT>
    conT all_values() const
    {
        conT t;
        all_values(t);
        return t;
    }

};

NNT_END_NS
NNT_END_HEADER_CXX

# endif
