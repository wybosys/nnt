
# ifndef __NNT_FOUNDATION_RBTREE_f1ce72fe11644e45b73a597d598872d2_H_INCLUDED
# define __NNT_FOUNDATION_RBTREE_f1ce72fe11644e45b73a597d598872d2_H_INCLUDED

# include "./hash.hpp"

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(foundation)

NNT_BEGIN_NS(impl)

# define _RBNODE_TPL_DECL template <typename keyT, typename valT, typename treeT>
# define _RBNODE_TPL_ARG keyT, valT, treeT

template <typename keyT, typename valT, typename treeT>
class rbnode
{
    typedef rbnode<keyT, valT, treeT> node_type;
    
public:

    typedef treeT tree_type;
    typedef keyT key_type;
    typedef valT value_type;

    enum Color
    {
        COLOR_RED = 0x0000,
        COLOR_BLACK = 0x0001
    };

    enum Side
    {
        SIDE_LEFT = 0x0000,
        SIDE_RIGHT = 0x0001,
        SIDE_ERROR = 0x9999,
    };

    rbnode();
    rbnode(key_type const&, tree_type*);
    ~rbnode();

    void clear(Side);
    bool is_nil() const;
    bool is_empty() const;
    void swap_color(node_type&);
    void set_black();
    void set_red();
    bool is_black() const;
    bool is_red() const;
    Side which_side(node_type const&) const;
    static Side other_side(Side);
    static node_type const& Nil();
    node_type* brother() const;
    void attach(node_type&);
    void attach(Side, node_type&);
    node_type* detach(Side);
    node_type* detach(node_type&);
    node_type* search_max() const;
    node_type* search_min() const;
    void rotate(Side);
    void adjust_insert();
    bool insert(node_type&);
    node_type* lookup(key_type const&) const;
    void leave();
    void adjust_leave(node_type*);
    key_type const& key() const;

    template <typename conT>
    void all_keys(conT&) const;

    template <typename conT>
    void all_values(conT&) const;

    value_type val;
    
private:

    key_type _key;
    Color _color;
    node_type *_parent, *_link[2];
    tree_type *_tree;

};

NNT_END_NS

# define _RBTREE_TPL_DECL template <typename keyT, typename valT>
# define _RBTREE_TPL_ARG keyT, valT

template <typename keyT, typename valT> 
class rbtree 
{    
protected:

    typedef impl::rbnode<keyT, valT, rbtree<keyT, valT> > node_type;
    
public:

    typedef keyT key_type;
    typedef valT value_type;

    rbtree();
    ~rbtree();

    bool insert(key_type const&, value_type const&);
    node_type* lookup(key_type const&) const;
    bool remove(key_type const&);

    template <typename conT>
    void all_keys(conT&) const;

    template <typename conT>
    void all_values(conT&) const;

protected:

    void remove(node_type&);

protected:

    node_type* _root;

    _RBNODE_TPL_DECL friend class impl::rbnode;
};

NNT_BEGIN_NS(impl)

_RBNODE_TPL_DECL
template_impl rbnode<_RBNODE_TPL_ARG>::rbnode()
: _color(COLOR_BLACK), _parent(NULL), _tree(NULL)
{
    _link[SIDE_LEFT] = NULL;
    _link[SIDE_RIGHT] = NULL;
}

_RBNODE_TPL_DECL
template_impl rbnode<_RBNODE_TPL_ARG>::rbnode(key_type const& key, tree_type* tree)
: _color(COLOR_RED), _key(key), _tree(tree), _parent(NULL)
{
    _link[SIDE_LEFT] = &ntl::down_const(Nil());
    _link[SIDE_RIGHT] = &ntl::down_const(Nil());
}

_RBNODE_TPL_DECL
template_impl rbnode<_RBNODE_TPL_ARG>::~rbnode()
{
    clear(SIDE_LEFT);
    clear(SIDE_RIGHT);
}

_RBNODE_TPL_DECL
template_impl void rbnode<_RBNODE_TPL_ARG>::clear(Side side)
{
    if (_link[side]->is_nil() == false)
    {
        delete _link[side];
        _link[side] = &ntl::down_const(Nil());
    }
}

_RBNODE_TPL_DECL
template_impl bool rbnode<_RBNODE_TPL_ARG>::is_nil() const
{
    return this == &Nil();
}

_RBNODE_TPL_DECL
template_impl bool rbnode<_RBNODE_TPL_ARG>::is_empty() const
{
    return _link[SIDE_LEFT]->is_nil() && _link[SIDE_RIGHT]->is_nil();
}

_RBNODE_TPL_DECL
template_impl typename rbnode<_RBNODE_TPL_ARG>::node_type const& rbnode<_RBNODE_TPL_ARG>::Nil()
{
    static const node_type null_rbnode;
    return null_rbnode;
}

_RBNODE_TPL_DECL
template_impl void rbnode<_RBNODE_TPL_ARG>::swap_color(node_type& node)
{
    Color c = _color;
    _color = node._color;
    node._color = c;
}

_RBNODE_TPL_DECL
template_impl void rbnode<_RBNODE_TPL_ARG>::set_black()
{
    _color = COLOR_BLACK;
}

_RBNODE_TPL_DECL
template_impl bool rbnode<_RBNODE_TPL_ARG>::is_black() const
{
    return _color == COLOR_BLACK;
}

_RBNODE_TPL_DECL
template_impl void rbnode<_RBNODE_TPL_ARG>::set_red()
{
    _color = COLOR_RED;
}

_RBNODE_TPL_DECL
template_impl bool rbnode<_RBNODE_TPL_ARG>::is_red() const
{
    return _color == COLOR_RED;
}

_RBNODE_TPL_DECL
template_impl typename rbnode<_RBNODE_TPL_ARG>::Side rbnode<_RBNODE_TPL_ARG>::which_side(node_type const& node) const
{
    if (_link[SIDE_LEFT] == &node)
        return SIDE_LEFT;
    else if (_link[SIDE_RIGHT] == &node)
        return SIDE_RIGHT;
    NNT_ASSERT(0);
    return SIDE_ERROR;
}

_RBNODE_TPL_DECL
template_impl typename rbnode<_RBNODE_TPL_ARG>::Side rbnode<_RBNODE_TPL_ARG>::other_side(Side side)
{
    NNT_ASSERT(side == SIDE_LEFT || side == SIDE_RIGHT);
    return side == SIDE_LEFT ? SIDE_RIGHT : SIDE_LEFT;
}

_RBNODE_TPL_DECL
template_impl typename rbnode<_RBNODE_TPL_ARG>::node_type* rbnode<_RBNODE_TPL_ARG>::brother() const
{
    if (_parent == NULL)
        return NULL;

    NNT_ASSERT(_parent->_link[SIDE_LEFT] == this || _parent->_link[SIDE_RIGHT] == this);
    return _parent->_link[SIDE_LEFT] == this ?
        _parent->_link[SIDE_RIGHT] : _parent->_link[SIDE_LEFT];
}

_RBNODE_TPL_DECL
template_impl void rbnode<_RBNODE_TPL_ARG>::attach(node_type& node)
{
    NNT_ASSERT(_key != node._key);
    Side side = (node._key < _key ? SIDE_LEFT : SIDE_RIGHT);
    attach(side, node);
}

_RBNODE_TPL_DECL
template_impl void rbnode<_RBNODE_TPL_ARG>::attach(Side side, node_type& node)
{
    NNT_ASSERT(side == SIDE_LEFT || side == SIDE_RIGHT);
    NNT_ASSERT(this != &node);
    NNT_ASSERT(_link[side]->is_nil());
    _link[side] = &node;
    if (!node.is_nil())
        node._parent = this;
}

_RBNODE_TPL_DECL
template_impl typename rbnode<_RBNODE_TPL_ARG>::node_type* rbnode<_RBNODE_TPL_ARG>::detach(Side side)
{
    NNT_ASSERT(side == SIDE_LEFT || side == SIDE_RIGHT);

    if (is_nil() || _link[side]->is_nil())
        return &ntl::down_const(Nil());

    rbnode *node = _link[side];
    _link[side]->_parent = NULL;
    _link[side] = &ntl::down_const(Nil());
    return node;
}

_RBNODE_TPL_DECL
template_impl typename rbnode<_RBNODE_TPL_ARG>::node_type* rbnode<_RBNODE_TPL_ARG>::detach(node_type& node)
{
    if (_link[SIDE_RIGHT] == &node)
        return detach(SIDE_RIGHT);
    else if (_link[SIDE_LEFT] == &node)
        return detach(SIDE_LEFT);

    NNT_ASSERT(0);
    return NULL;
}

_RBNODE_TPL_DECL
template_impl typename rbnode<_RBNODE_TPL_ARG>::node_type* rbnode<_RBNODE_TPL_ARG>::search_max() const
{
    if (!_link[SIDE_RIGHT]->is_nil())
        return _link[SIDE_RIGHT]->search_max();

    return ntl::down_const(this);
}

_RBNODE_TPL_DECL
template_impl typename rbnode<_RBNODE_TPL_ARG>::node_type* rbnode<_RBNODE_TPL_ARG>::search_min() const
{
    if (!_link[SIDE_LEFT]->is_nil())
        return _link[SIDE_LEFT]->search_min();
    else 
        return this;
}

_RBNODE_TPL_DECL
template_impl void rbnode<_RBNODE_TPL_ARG>::rotate(Side side)
{
    rbnode *leaf, *parent, *grand;
    Side oside = other_side(side);

    grand = _parent;
    parent = this->detach(oside);
    NNT_ASSERT(parent != NULL);

    leaf = parent->detach(side);

    if (grand) 
    {
        Side ps = grand->which_side(*this);
        grand->detach(ps);
        grand->attach(ps, *parent); 
    }
    else 
    {
        _tree->_root = parent;
    }

    parent->attach(side, *this);

    if (!leaf->is_nil())
        this->attach(oside, *leaf);
}

_RBNODE_TPL_DECL
template_impl void rbnode<_RBNODE_TPL_ARG>::adjust_insert()
{
    if (_parent == NULL) 
    {
        // this node is root
        set_black();
        return ;
    }

    if (_parent->is_red()) 
    {
        NNT_ASSERT(_parent->_parent && _parent->_parent->is_black());

        rbnode* parent = _parent;
        rbnode* grand = _parent->_parent;
        rbnode* uncle = _parent->brother();
        Side side;

        if (uncle->is_red()) 
        {
            uncle->set_black ();
            _parent->set_black ();
            grand->set_red();
            grand->adjust_insert();
        }
        else 
        { 
            if (_parent->which_side(*this) != grand->which_side(*_parent)) 
            {
                side = other_side(parent->which_side(*this));
                parent->rotate(side); 
                parent = this;
            }

            side = other_side(grand->which_side(*parent));
            grand->rotate(side);

            NNT_ASSERT(grand->is_black() && parent->is_red());
            grand->swap_color(*parent);
        }
    }
}

_RBNODE_TPL_DECL
template_impl bool rbnode<_RBNODE_TPL_ARG>::insert(node_type& node)
{
    if (_key == node._key)
    {
        // duplicated
        return false;
    }

    Side side = (node._key < _key ? SIDE_LEFT : SIDE_RIGHT);
    if (_link[side]->is_nil())
        attach(side, node);
    else
        return _link[side]->insert(node);

    node.adjust_insert();
    return true;
}

_RBNODE_TPL_DECL
template_impl typename rbnode<_RBNODE_TPL_ARG>::node_type* rbnode<_RBNODE_TPL_ARG>::lookup(key_type const& key) const
{
    if (_key == key) 
        return ntl::down_const(this);

    Side side = (key < _key ? SIDE_LEFT : SIDE_RIGHT);
    return _link[side]->is_nil() ? NULL : _link[side]->lookup(key);
}

_RBNODE_TPL_DECL
template_impl void rbnode<_RBNODE_TPL_ARG>::leave()
{
    // only detach from tree, balancing color & tree in adjustLeave ()
    rbnode *parent = _parent;

    if (_link[SIDE_LEFT]->is_nil() && _link[SIDE_RIGHT]->is_nil()) 
    {
        if (parent) 
        {
            Side side = parent->which_side(*this);
            parent->detach(*this);

            if (is_black()) 
            {
                parent->_link[side]->adjust_leave(parent);
            }
        }
        else  
        {
            _tree->_root = NULL;	
        }
    }
    else if (_link[SIDE_LEFT]->is_nil() ^ _link[SIDE_RIGHT]->is_nil())
    {
        Side side = _link[SIDE_LEFT]->is_nil() ? SIDE_RIGHT : SIDE_LEFT;
        node_type* target = detach(side);

        if (parent) 
        {
            parent->detach(*this);
            parent->attach(*target);
        }
        else 
        {
            _tree->_root = target;
        }

        if (is_black())
            target->adjust_leave(parent);
    }
    else 
    {
        // swap target node & maximum node in left subtree
        NNT_ASSERT(!_link[SIDE_LEFT]->is_nil() && !_link[SIDE_RIGHT]->is_nil());

        node_type* node_max = _link[SIDE_LEFT]->search_max();
        node_type* max_parent = node_max->_parent;
        node_type* node_left  = detach(SIDE_LEFT);
        node_type* node_right = detach(SIDE_RIGHT);
        node_type* max_left  = node_max->detach(SIDE_LEFT);

        attach(*max_left);

        if (parent) 
            parent->detach(*this);
        else 
            _tree->_root = NULL;

        if (node_max != node_left) 
        {
            // Max have more 1 hop from THIS
            max_parent->detach(*node_max);
            max_parent->attach(*this);
            node_max->attach(SIDE_LEFT, *node_left);
            node_max->attach(SIDE_RIGHT, *node_right);
        }
        else 
        {
            // Max == Left (Max is left node of THIS)
            NNT_ASSERT(node_max->_link[SIDE_RIGHT]->is_nil());	 
            node_max->attach(SIDE_RIGHT, *node_right);
            node_max->attach(SIDE_LEFT,  *this);
        }

        if (parent) 
            parent->attach(*node_max);
        else 
            _tree->_root = node_max;

        swap_color(*node_max);
        leave();
    }   
}

_RBNODE_TPL_DECL
template_impl void rbnode<_RBNODE_TPL_ARG>::adjust_leave(node_type* parent)
{
    // nothing to do when node is root
    if (parent == NULL)
    {
        set_black();
        return;
    }

    if (is_red()) 
    {
        set_black();
        return;
    }

    node_type* neighbor = parent->_link[other_side(parent->which_side(*this))];
    NNT_ASSERT(neighbor != NULL);

    if (neighbor->is_red()) 
    {
        Side side = parent->which_side(*this);
        NNT_ASSERT(parent->is_black());
        parent->swap_color(*neighbor);
        parent->rotate(side);
        neighbor = parent->_link[other_side(side)];
    }
    else if (parent->is_black() && 
        neighbor->_link[SIDE_LEFT]->is_black() && 
        neighbor->_link[SIDE_RIGHT]->is_black()) 
    {
        NNT_ASSERT(neighbor->is_black());
        neighbor->set_red();
        return parent->adjust_leave(parent->_parent);
    }      

    if (parent->is_red() && 
        neighbor->_link[SIDE_LEFT]->is_black() && 
        neighbor->_link[SIDE_RIGHT]->is_black()) 
    {
        NNT_ASSERT(neighbor->is_black());
        parent->swap_color(*neighbor);
    }
    else 
    {
        Side neighbor_side = parent->which_side(*neighbor); // Neighbor side
        Side neighbor_oside = other_side(neighbor_side); // Other side

        if (neighbor->_link[neighbor_oside]->is_red() &&
            neighbor->_link[neighbor_side]->is_black()) 
        {	  
            neighbor->swap_color(*neighbor->_link[neighbor_oside]);
            neighbor->rotate(neighbor_side);
            neighbor = parent->_link[neighbor_side];
        }

        if (neighbor->_link[neighbor_side]->is_red()) 
        {
            neighbor->_link[neighbor_side]->set_black();
            parent->swap_color(*neighbor);
            parent->rotate(neighbor_oside);
        }
    }      
}

_RBNODE_TPL_DECL
template_impl typename rbnode<_RBNODE_TPL_ARG>::key_type const& rbnode<_RBNODE_TPL_ARG>::key() const
{
    return _key;
}

_RBNODE_TPL_DECL
template <typename conT>
template_impl void rbnode<_RBNODE_TPL_ARG>::all_keys(conT& c) const
{
    if (is_nil())
        return;
    c.push_back(_key);
    if (_link[SIDE_LEFT]->is_nil() == false)
        _link[SIDE_LEFT]->all_keys(c);
    if (_link[SIDE_RIGHT]->is_nil() == false)
        _link[SIDE_RIGHT]->all_keys(c);
}

_RBNODE_TPL_DECL
template <typename conT>
template_impl void rbnode<_RBNODE_TPL_ARG>::all_values(conT& c) const
{
    if (is_nil())
        return;
    c.push_back(val);
    if (_link[SIDE_LEFT]->is_nil() == false)
        _link[SIDE_LEFT]->all_values(c);
    if (_link[SIDE_RIGHT]->is_nil() == false)
        _link[SIDE_RIGHT]->all_values(c);
}

NNT_END_NS

_RBTREE_TPL_DECL
template_impl rbtree<_RBTREE_TPL_ARG>::rbtree()
: _root(NULL)
{

}

_RBTREE_TPL_DECL
template_impl rbtree<_RBTREE_TPL_ARG>::~rbtree()
{
    delete _root;
}

_RBTREE_TPL_DECL
template_impl bool rbtree<_RBTREE_TPL_ARG>::insert(key_type const& key, value_type const& val)
{
    node_type* node = new node_type(key, this);
    node->val = val;

    if (_root) 
    {
        if (!_root->insert(*node)) 
        {
            delete node;
            return false;
        }
    }
    else 
    {
        _root = node;
        node->set_black();
    }

    return true;
}

_RBTREE_TPL_DECL
template_impl typename rbtree<_RBTREE_TPL_ARG>::node_type* rbtree<_RBTREE_TPL_ARG>::lookup(key_type const& key) const
{
    if (NULL == _root)
        return NULL; 

    return _root->lookup(key);
}

_RBTREE_TPL_DECL
template_impl bool rbtree<_RBTREE_TPL_ARG>::remove(key_type const& key)
{
    if (NULL == _root)
        return false;

    node_type* node = _root->lookup(key);
    if (NULL == node)
        return false;

    node->leave();
    delete node;

    return true;
}

_RBTREE_TPL_DECL
template_impl void rbtree<_RBTREE_TPL_ARG>::remove(node_type& node)
{
    if (_root == &node)
        _root = NULL;

    node.leave();
    delete &node;
}

_RBTREE_TPL_DECL
template <typename conT>
template_impl void rbtree<_RBTREE_TPL_ARG>::all_keys(conT& con) const
{
    if (_root == NULL)
        return;
    _root->all_keys(con);
}

_RBTREE_TPL_DECL
template <typename conT>
template_impl void rbtree<_RBTREE_TPL_ARG>::all_values(conT& con) const
{
    if (_root == NULL)
        return;
    _root->all_values(con);
}

NNT_END_NS
NNT_END_HEADER_CXX

# endif
