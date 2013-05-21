
# ifndef __NNT_FOUNDATION_RBTREE_f1ce72fe11644e45b73a597d598872d2_H_INCLUDED
# define __NNT_FOUNDATION_RBTREE_f1ce72fe11644e45b73a597d598872d2_H_INCLUDED

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(foundation)

NNT_BEGIN_NS(impl)

template <typename KeyT, typename MemT>
class rb_node
{
public:

    rb_node()
        : left(NULL), right(NULL)
    {
        PASS;
    }

    rb_node *left, *right;
    KeyT key;

};

NNT_END_NS

template <typename MemT>
class rbtree
{
public:



};

NNT_END_NS
NNT_END_HEADER_CXX

# endif
