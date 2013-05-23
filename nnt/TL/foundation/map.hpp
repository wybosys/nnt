
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
        : public basic_iterator<iterator, typename rbtree_type::node_type*>,
        public value_type
    {
    public:

        iterator()
            : _root(NULL)
        {
            obj = NULL;
        }

        void update()
        {
            if (obj == NULL)
                return;

            this->first = obj->key();
            this->second = obj->val;

            if (_root == NULL)
            {
                _root = obj;
            }
        }

        iterator& operator ++ ()
        {
            update();
            return *this;
        }

    protected:

        object_type _root;

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
        ret.update();
        return ret;
    }

    iterator begin()
    {
        iterator ret;
        ret.obj = super::_root;
        ret.update();
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

};

NNT_END_NS
NNT_END_HEADER_CXX

# endif
