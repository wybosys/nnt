
/*
 * htl-lite - a basic data structures and algorithms.
 * Copyright (C) 2009 leon hong. All rights reserved.
 * authors:
 *   leon hong <codeblocker@gmail.com>
 */

#ifndef __HTL_TREE_H__
#define __HTL_TREE_H__

#include "htl_alloc.h"
#include "htl_pair.h"
#include "htl_algo.h"
//#include <iostream>

__HTL_BEGIN_NAMESPACE

typedef bool rb_tree_color_type;
const rb_tree_color_type rb_tree_red = false;   // 红色为 0
const rb_tree_color_type rb_tree_black = true;  // 黑色为 1

// 红黑树节点的base
struct rb_tree_node_base {
    rb_tree_color_type color;       // 节点颜色
    rb_tree_node_base* parent;      // 父节点
    rb_tree_node_base* left;        // 左孩子
    rb_tree_node_base* right;       // 右孩子

    // 树的最小节点
    static rb_tree_node_base* minimum(rb_tree_node_base* x) {
        while (x->left != NULL)
            x = x->left;
        return x;
    }

    // 树的最大节点
    static rb_tree_node_base* maximum(rb_tree_node_base* x) {
        while (x->right != NULL)
            x = x->right;
        return x;
    }
};

// 红黑树节点
template <class Value>
struct rb_tree_node : public rb_tree_node_base 
{
    typedef rb_tree_node<Value>* link_type;
    Value value_filed;  // 节点值
};

//RB-TREE的iterator的base
struct rb_tree_base_iterator {
    typedef bidirectional_iterator_tag iterator_category;
    typedef rb_tree_node_base* base_ptr;
    typedef ptrdiff_t difference_type;

    // 迭代器所指的node
    base_ptr node;

    // ++操作
    void increment() {
        if (node->right != NULL) {
            node = node->right;
            while (node->left != NULL)
                node = node->left;
        }
        else {
            base_ptr y = node->parent;
            // 如果node是y的右孩子，就一直回溯
            while (node == y->right) {
                node = y;
                y = y->parent;
            }
            if (node->right != y)   // 此种情况是y为root，且没有
                node = y;           // 右孩子(也就是说++之后node指向end()),即header
        }
    }

    // --操作
    void decrement() {
        if (node->color == rb_tree_red          // node指向end()时(header), 将header的
            && node->parent->parent == node)    // 右孩子(也就是最后一个节点)赋给node
            node = node->right;
        else if (node->left != NULL) {
            node = node->left;
            while (node->right != NULL)
                node = node->right;
        }
        else {
            base_ptr y = node->parent;
            // 如果node是y的左孩子，就一直回溯
            while (node == y->left) {
                node = y;
                y = y->parent;
            }
            node = y;
        }
    }
};

// RB-TREE的iterator
template<class Value, class Ref, class Ptr>
struct rb_tree_iterator : public rb_tree_base_iterator {
    typedef Value value_type;
    typedef Ref reference;
    typedef Ptr pointer;
    typedef rb_tree_iterator<Value, Value&, Value*> iterator;
    typedef rb_tree_iterator<Value, Ref, Ptr> self;
    typedef rb_tree_node<Value>* link_type;

    // 构造函数
    rb_tree_iterator() {}
    rb_tree_iterator(link_type x){
        node = x;
    }
    rb_tree_iterator(const iterator& it) {
        node = it.node;
    }

    //以下是迭代器提供具有指针操作的operator
    reference operator*() const {
        return link_type(node)->value_filed;
    }

    pointer operator->() const {
        return &(operator*());
    }

    self& operator++() {
        increment();
        return *this;
    }

    self operator++(int) {
        self tmp = *this;
        increment();
        return tmp;
    }

    self& operator--() {
        decrement();
        return *this;
    }

    self operator--(int) {
        self tmp = *this;
        decrement();
        return tmp;
    }

};

inline bool operator==(const rb_tree_base_iterator& x,
                       const rb_tree_base_iterator& y) {
  return x.node == y.node;
}

inline bool operator!=(const rb_tree_base_iterator& x,
                       const rb_tree_base_iterator& y) {
  return x.node != y.node;
}

// RB-TREE
template<class Key,
         class Value,
         class KeyOfValue,
         class Compare,
         class Alloc = allocator>
class rb_tree {
protected:
    typedef rb_tree_node_base* base_ptr;
    typedef rb_tree_node<Value> _rb_tree_node;
    typedef simple_alloc<_rb_tree_node, Alloc> rb_tree_node_allocator;
    typedef rb_tree_color_type color_type;
public:
    typedef Value value_type;
    typedef Key key_type;
    typedef value_type* pointer;
    typedef value_type& reference;
    typedef _rb_tree_node* link_type;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    typedef rb_tree_iterator<value_type, reference, pointer> iterator;
protected:
    // 申请一个rb_node空间
    link_type get_node() {
        return rb_tree_node_allocator::allocate();
    }

    // 释放一个rb_node空间
    void put_node(link_type p) {
        return rb_tree_node_allocator::deallocate(p);
    }

    // 创建值为x的node
    link_type create_node(const value_type& x) {
        link_type tmp = get_node();
        construct(&tmp->value_filed, x);
        return tmp;
    }

    // 释放node（释放+析构）
    void destory_node(link_type p) {
        destory(&p->value_filed);
        put_node(p);
    }

    // 克隆一个node的值
    link_type clone_node(link_type x) {
        link_type tmp = create_node(x->value_field);
        tmp->color = x->color;
        tmp->left = 0;
        tmp->right = 0;
        tmp->parent = 0;
        return tmp;
    }
protected:
    // 以下为RB-TREE的数据成员
    size_type node_count;   // node节点个数
    link_type header;       // header父节点指向root,左右孩子分别指向树的最左和最右段
    Compare key_compare;    // Key function obj
protected:
    // 取得root节点
    link_type& root() const {
        return (link_type&) header->parent;
    }

    // 取得header的左孩子（最左面节点）
    link_type& leftmost() const {
        return (link_type&) header->left;
    }

    // 取得header的右孩子（最右面节点）
    link_type& rightmost() const {
        return (link_type&) header->right;
    }

    // 以下6组函数(针对link_type)方便取得节点x的各项域
    static link_type& left(link_type x) {
        return (link_type&) (x->left);
    }

    static link_type& right(link_type x) {
        return (link_type&) (x->right);
    }

    static link_type& parent(link_type x) {
        return (link_type&) (x->parent);
    }

    static reference value(link_type x) {
        return x->value_field;
    }

    static const key_type& key(link_type x){
        return (key_type&)(x->value_filed);
    }

    static color_type& color(link_type x) {
        return (color_type&) (x->color);
    }

    // 以下6组函数(针对base_ptr)方便取得节点x的各项域
    static link_type& left(base_ptr x) {
        return (link_type&) (x->left);
    }

    static link_type& right(base_ptr x) {
        return (link_type&) (x->right);
    }

    static link_type parent(base_ptr x) {
        return (link_type&) (x->parent);
    }

    static reference value(base_ptr x) {
        return ((link_type)x)->value_filed;
    }

    static const key_type& key(base_ptr x) {
        return (key_type&)(value(x));
    }

    static color_type& color(base_ptr x) {
        return (color_type&) (x->color);
    }

    // 最小值指向的node
    static link_type minimum(link_type x) {
        return (link_type) rb_tree_node_base::minimum(x);
    }

    // 最大值指向的node
    static link_type maximum(link_type x) {
        return (link_type&) rb_tree_node_base::maximum(x);
    }
private:
    // 初始化
    void init() {
        header = get_node();
        color(header) = rb_tree_red;    // 设置红色，区分root和header（在decrement中体现）
        root() = 0;
        leftmost() = header;            // 初始化header左孩子指向自己
        rightmost() = header;           // 初始化header右孩子指向自己
    }
public:
    rb_tree(const Compare& comp = Compare())
     : node_count(0), key_compare(comp) {
        init();
    }
    ~rb_tree() {
        clear();
        put_node(header);
    }

	rb_tree<Key,Value,KeyOfValue,Compare,Alloc>& 
		operator=(const rb_tree<Key,Value,KeyOfValue,Compare,Alloc>& x);
public:
    Compare key_comp() const {
        return key_compare;
    }

    // begin()为header的左孩子
    iterator begin() {
        return leftmost();
    }

    // end为header
    iterator end() {
        return header;
    }

    bool empty() const {
        return node_count == 0;
    }

    size_type size() const {
        return node_count;
    }

    // 得到root节点
    link_type get_root() {
        return root();
    }
    // 中序遍历
    void mid_visit(link_type p);

    // 将x插入到RB-TREE中，节点可以重复
    iterator insert_equal(const value_type& v);

    // 将x插入到RB-TREE中，节点不可以重复
    pair<iterator, bool> insert_unique(const value_type& v);

    // 删除迭代器所指的node
    void erase(iterator pos);

    // 删除key值为x的节点
    size_type erase(const Key& x);

    // 删除first~last之间的node
    void erase(iterator first, iterator last);

    // 查找key值
    iterator find(const key_type& k);

    // 删除所有节点（不包括herader,回到初始化状态）
    void clear();

    // 返回key值为x的的范围
    pair<iterator,iterator> equal_range(const key_type& x);

    // 返回第一个大于等于x的值
    iterator lower_bound(const key_type& x);

    // 返回可插入x的最后一个位置
    iterator upper_bound(const key_type& x);

    // 返回key值为x的个数
    size_type count(const Key& k);
private:
    // x是插入点，y是x的孩子夫节点,插入值为v
    iterator insert(link_type x, link_type y, const value_type& v);

    // insert节点z之后,需要调整树形及节点颜色，维持红黑树结构
    void insert_fixup(base_ptr z);

    // 删除节点之后，需要调整树形及节点颜色，维持红黑树结构
    void erase_fixup(base_ptr x_parent, base_ptr x);

    // 左旋转
    void left_rotate(base_ptr x);

    // 右旋转
    void right_rotate(base_ptr y);

    // 内部使用erase_aux,不考虑红黑情况下，直接删除所有节点
    void erase_aux(link_type x);

    // 求出x的后继
    base_ptr tree_successor(base_ptr x);

    // 打印Value
    void print_node(link_type p) {
        //std::cout << p <<" Value : " <<
        //    p->value_filed << " " << "color : ";
        //std::cout << (p->color ?  "black" : "red") << std::endl;
    }
};


template <class Key, class Value, class KeyOfValue, class Compare,
class Alloc>
	rb_tree<Key, Value, KeyOfValue, Compare, Alloc>& 
	rb_tree<Key, Value, KeyOfValue, Compare, Alloc>
	::operator=(const rb_tree<Key,Value,KeyOfValue,Compare,Alloc>& x)
{
	if (this != &x) {
		// Note that _Key may be a constant type.
		clear();
		node_count = 0;
		key_compare = x.key_compare;        
		if (x.root() == 0) {
			root() = 0;
			leftmost() = header;
			rightmost() = header;
		}
		else {
			root() = copy(x.root(), header);
			leftmost() = minimum(root());
			rightmost() = maximum(root());
			node_count = x.node_count;
		}
	}
	return *this;
}

template<class Key, class Value, class KeyOfValue, class Compare,
         class Alloc>
void rb_tree<Key, Value, KeyOfValue,
Compare, Alloc>::mid_visit(link_type p) {
    if (p == NULL) {
        //std::cout << "has no node\n";
        return;
    }
	if (p->left) {
		if (((link_type)p->left)->value_filed > ((link_type)p)->value_filed)
			//std::cout << "wrong left\n";
		//assert(((link_type)p->left)->value_filed <= ((link_type)p)->value_filed);
		mid_visit((link_type)p->left);
	}
	print_node(p);
	if (p->right) {
		if (((link_type)p->right)->value_filed < ((link_type)p)->value_filed)
			//std::cout << "wrong right\n";
		//assert(((link_type)p->right)->value_filed >= ((link_type)p)->value_filed);
		mid_visit((link_type)p->right);
	}
}
template<class Key, class Value, class KeyOfValue, class Compare,
         class Alloc>
typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::iterator
rb_tree<Key, Value, KeyOfValue,
Compare, Alloc>::insert_equal(const value_type& v) {
    link_type y = header;
    link_type x = root();
    while (x != NULL) {
		key_type aKeyV = KeyOfValue()(v);
		key_type aKeyX = key(x);

        y = x;
        x = key_compare(aKeyV, aKeyX) ? left(x) : right(x);
    }
    return insert(x, y, v);
}

template<class Key, class Value, class KeyOfValue, class Compare,
         class Alloc>
pair<typename rb_tree<Key, Value, KeyOfValue,Compare, Alloc>::iterator, bool>
rb_tree<Key, Value, KeyOfValue,
Compare, Alloc>::insert_unique(const value_type& v) {
    link_type y = header;
    link_type x = root();
    bool comp = true;   // 标识左侧插入还是右侧插入
    while (x != NULL) {
        y = x;
		key_type aKeyValue = KeyOfValue()(v);
		key_type aKeyValueX = key(x);
        comp = key_compare(aKeyValue, aKeyValueX);
        x = comp ? left(x) : right(x);
    }
    iterator it = iterator(y);  // 插入点的父节点
    if (comp) {
        // 表示在y的左侧插入，分为俩种情况:(1). 如果是最左面直接插入.
        // (2).否则，回退(因为是左侧插入，所以该值一定小于y,所以只需要和比较第一比y小的值比较即可)
        if (it == begin())
            return pair<iterator, bool>(insert(x, y, v), true);
        else
            --it;
    }
    // comp为假，右侧插入
	key_type aKeyValueNode = key(it.node);
	key_type aKeyValueV = KeyOfValue()(v);

    if (key_compare(aKeyValueNode, aKeyValueV))  // 如果插入值和it的值不相等(it即第一个大于等于插入值的值)
        return pair<iterator, bool>(insert(x, y, v), true);
    // 其他情况都为都为重复
    return pair<iterator, bool>(it, false);
}
template<class Key, class Value, class KeyOfValue, class Compare,
         class Alloc>
typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::iterator
rb_tree<Key, Value, KeyOfValue,
Compare, Alloc>::insert(link_type x, link_type y, const value_type& v) {
    link_type z = create_node(v);
	key_type aKeyValueV = KeyOfValue()(v);
	key_type aKeyY = key(y);

	/*link_type z = create_node(v);
	key_type aKeyValueV = KeyOfValue()(v);
	key_type aKeyValueX;
	if (x != NULL)
	{
		aKeyValueX = key(x);
	}
	
    if (y == header) {
        // 如果是header
        root() = z;
        left(y) = z;
        right(y) = z;
    }
    else if (key_compare(aKeyValueV, aKeyValueX)){
        // 如果v小于y,则在y的左孩子插入
        left(y) = z;
        // 是否需要更新leftmost
        if (y == leftmost())
            leftmost() = z;
    }*/
	if (y == header || x != NULL || 
		key_compare(aKeyValueV, aKeyY)) {
			left(y) = z;               // also makes _M_leftmost() = __z 
			//    when __y == _M_header
			if (y == header) {
				root() = z;
				rightmost() = z;
			}
			else if (y == leftmost())
				leftmost() = z;   // maintain _M_leftmost() pointing to min node
	}
    else {
        // v大于y，在y的右孩子插入
        right(y) = z;
        // 是否需要更新rightmost
        if (y == rightmost())
            rightmost() = z;
    }
    parent(z) = y;
    left(z) = 0;
    right(z) = 0;
    // 新增节点设为红
    color(z) = rb_tree_red;
    // 调整颜色，已维持RB-TREE特性
    insert_fixup(z);
    ++node_count;
    // 返回插入节点的iterator
    return iterator(z);
}

/**********************************************************
	插入节点z之后，需要调整颜色，保持红黑树特性
	共分3种情况：
	(1). z的叔叔是红色
	(2). z的叔叔是黑色，而且z是右孩子(情况2调整为情况3一起处理)
	(3). z的叔叔是黑色，而且z是左孩子
**********************************************************/
template<class Key, class Value, class KeyOfValue, class Compare,
         class Alloc>
void rb_tree<Key, Value, KeyOfValue,
Compare, Alloc>::insert_fixup(base_ptr z) {
    while (z != root() && z->parent->color == rb_tree_red) {
		if (z->parent == z->parent->parent->left) {
			base_ptr y = z->parent->parent->right;
			if (y && y->color == rb_tree_red) {	// 如果z的叔叔y为红 (条件1)
				z->parent->color = rb_tree_black;
				y->color = rb_tree_black;
				z->parent->parent->color = rb_tree_red;
				z = z->parent->parent; // 调整z，为一下次迭代
			}
			else { // 如果z的叔叔y为黑
				if (z == z->parent->right) { // 旋转z的父亲，使变成外侧点（条件3），此步是将条件2变成条件3一起处理
					z = z->parent;
					left_rotate(z);
				}
				// 条件3
				z->parent->color = rb_tree_black;
				z->parent->parent->color = rb_tree_red;
				right_rotate(z->parent->parent);
			}
		}
		else if (z->parent->parent != NULL) { // z->p == z->p->p->right
			base_ptr y = z->parent->parent->left;
			if (y && y->color == rb_tree_red) {
				z->parent->color = rb_tree_black;
				y->color = rb_tree_black;
				z->parent->parent->color = rb_tree_red;
				z = z->parent->parent;
			}
			else {
				if (z == z->parent->left) {
					z = z->parent;
					right_rotate(z);
				}
				z->parent->color = rb_tree_black;
				z->parent->parent->color = rb_tree_red;
				left_rotate(z->parent->parent);
			}
		}
	} // end while
	root()->color = rb_tree_black;
}

/**********************************************************
                    将X左旋转
        X                            Y
      /   \                        /   \
     a     Y           ====>      X     c
         /   \                  /   \
        b     c                a      b
**********************************************************/
template<class Key, class Value, class KeyOfValue, class Compare,
         class Alloc>
void rb_tree<Key, Value, KeyOfValue,
Compare, Alloc>::left_rotate(base_ptr x) {
    base_ptr y = x->right;
	x->right = y->left;
	if (y->left != NULL)
		y->left->parent = x;
	y->parent = x->parent;
	if (x == root()) {
		root() = (link_type)y;
	}
	else {
		if (x == x->parent->left)
			x->parent->left = y;
		else // x == x->p->right
			x->parent->right = y;
	}
	y->left = x;
	x->parent = y;
}

/**********************************************************
                    将y右旋转
        X                            Y
      /   \                        /   \
     a     Y           <====      X     c
         /   \                  /   \
        b     c                a      b
**********************************************************/
template<class Key, class Value, class KeyOfValue, class Compare,
         class Alloc>
void rb_tree<Key, Value, KeyOfValue,
Compare, Alloc>::right_rotate(base_ptr y) {
	base_ptr x = y->left;
	y->left = x->right;
	if (x->right != NULL)
		x->right->parent = y;
	x->parent = y->parent;
	if (y == root()) {
		root() = (link_type)x;
	}
	else {
		if (y == y->parent->right)
			y->parent->right = x;
		else
			y->parent->left = x;
	}
	x->right = y;
	y->parent = x;
}

/**********************************************************
	求一个x节点的后继
**********************************************************/
template<class Key, class Value, class KeyOfValue, class Compare,
         class Alloc>
typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::base_ptr
rb_tree<Key, Value, KeyOfValue,
Compare, Alloc>::tree_successor(base_ptr x) {
    if (x->right != NULL)
		return rb_tree_node_base::minimum(x->right);
	base_ptr y = x->parent;
	while (y != root() && x == y->right) {
		x = y;
		y = y->parent;
	}
	return y;
}

/**********************************************************
	删除操作分为3情况：
	(1). z无子节点
	(2). z有一个子节点
	(3). z有俩个子节点
**********************************************************/
template<class Key, class Value, class KeyOfValue, class Compare,
         class Alloc>
void rb_tree<Key, Value, KeyOfValue,
Compare, Alloc>::erase(iterator pos) {
    base_ptr z = pos.node;
	base_ptr x_parent = NULL;
	base_ptr y = NULL;
	if (z->left == NULL || z->right == NULL)
		y = z;
	else
		y = tree_successor(z);
	base_ptr x = NULL;
	if (y->left != NULL)
		x = y->left;
	else
		x = y->right;
	if (x != NULL)
		x->parent = y->parent;
	if (y == root()) {
		root() = (link_type) x;
		x_parent = header;
	}
	else {
		if (y == y->parent->left)
			y->parent->left = x;
		else
			y->parent->right = x;
		x_parent = y->parent;
	}
	if (y != z) {
		((link_type)z)->value_filed = ((link_type)y)->value_filed;
	}
	else {  // y == z
        if ((((base_ptr)(header))->left) == y)  // 如果要删除的节点y是leftmost
            if (y->right == NULL)   // 此时y->left也一定为空，因为如果不为空，则leftmost != y
                ((base_ptr)(header))->left = y->parent;
            else    // y->right != NULL
                ((base_ptr)(header))->left = rb_tree_node_base::minimum(x);
        if ((((base_ptr)(header))->right) == y)
            if (y->left == NULL)
                ((base_ptr)(header))->right = y->parent;
            else
                ((base_ptr)(header))->right = rb_tree_node_base::maximum(x);
    }
	if (y->color == rb_tree_black)	// 如果被删除点是黑色，需要调整该删除点的子节点
        erase_fixup(x_parent, x);
    destory_node((link_type)y);
    --node_count;
}

/***********************************************************
	删除y之后，需要调整y的子节点x，来保持红黑树特性
	4种情况 :
	(1). x的兄弟w是红色
	(2). x的兄弟w是黑色,而且w的俩个孩子是黑色
	(3). x的兄弟w是黑色,w的左孩子是红色的，右孩子是黑色的
	(4). x的兄弟w是黑色,w的右孩子是红色
***********************************************************/
template<class Key, class Value, class KeyOfValue, class Compare,
         class Alloc>
void rb_tree<Key, Value, KeyOfValue,
Compare, Alloc>::erase_fixup(base_ptr x_parent, base_ptr x) {
    while (x != root() && (x == NULL || x->color == rb_tree_black)) {
		if (x == x_parent->left) {
			base_ptr w = x_parent->right;
			if (w->color == rb_tree_red) {	// 情况(1)
				w->color = rb_tree_black;
				x_parent->color = rb_tree_red;
				left_rotate(x_parent);
				// 更新兄弟节点
				w = x_parent->right;
			}
			if ((w->left == NULL || w->left->color == rb_tree_black)
				&& (w->right == NULL || w->right->color == rb_tree_black)) { // 情况(2)
				w->color = rb_tree_red;
				x = x_parent;	// 更新x 和x的父节点
				x_parent = x_parent->parent;
			}
			else {
				if (w->right == NULL || w->right->color == rb_tree_black) { // 情况(3)
					w->left->color = rb_tree_black;
					w->color = rb_tree_red;
					right_rotate(w);
					w = x_parent->right;
				}
				// 情况(4)
				w->color = x_parent->color;
				x_parent->color = rb_tree_black;
				w->right->color = rb_tree_black;
				left_rotate(x_parent);
				x = root();
			}
		}
		else { // x == x_parent->right
			base_ptr w = x_parent->left;
			if (w->color == rb_tree_red) {	// 情况(1)
				w->color = rb_tree_black;
				x_parent->color = rb_tree_red;
				right_rotate(x_parent);
				// 更新兄弟节点
				w = x_parent->left;
			}
			if ((w->right == NULL || w->right->color == rb_tree_black)
				&& (w->left == NULL || w->left->color == rb_tree_black)) { // 情况(2)
				w->color = rb_tree_red;
				x = x_parent;	// 更新x 和x的父节点
				x_parent = x_parent->parent;
			}
			else {
				if (w->left == NULL || w->left->color == rb_tree_black) { // 情况(3)
					w->right->color = rb_tree_black;
					w->color = rb_tree_red;
					left_rotate(w);
					w = x_parent->left;
				}
				// 情况(4)
				w->color = x_parent->color;
				x_parent->color = rb_tree_black;
				w->left->color = rb_tree_black;
				right_rotate(x_parent);
				x = root();
			}
		}
	}
	if (x != NULL)
		x->color = rb_tree_black;
}

template<class Key, class Value, class KeyOfValue, class Compare,
         class Alloc>
void rb_tree<Key, Value, KeyOfValue,
Compare, Alloc>::erase_aux(link_type x) {
    while (x != NULL) {
        // 因为右孩子和左孩子做同样的事，写出删除左孩子过程，递归右孩子即可
        erase_aux(right(x));
        link_type y = left(x);
        destory_node(x);
        x = y;
    }
}

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
void rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::erase(iterator first,
                                                            iterator last) {
    if (first == begin() && last == end())
        clear();
    else
        while (first != last)
            erase(first++);
}

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::size_type
rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::erase(const Key& x) {
    pair<iterator,iterator> p = equal_range(x);
    size_type n = 0;
    distance(p.first, p.second, n);
    erase(p.first, p.second);
    return n;
}

template<class Key, class Value, class KeyOfValue, class Compare,
         class Alloc>
void rb_tree<Key, Value, KeyOfValue,
Compare, Alloc>::clear() {
    if (node_count != 0) { // 如果已经没有节点了(除了header),就不删除
        erase_aux(root());
        leftmost() = header;
        root() = 0;
        rightmost() = header;
        node_count = 0;
    }
}

template<class Key, class Value, class KeyOfValue, class Compare,
         class Alloc>
typename rb_tree<Key, Value, KeyOfValue,Compare, Alloc>::iterator
rb_tree<Key, Value, KeyOfValue,Compare, Alloc>::find(const key_type& k) {
    link_type y = header;   // y存储最后一个大于等于k值得节点
    link_type x = root();
    while (x != NULL) {
    //key_type m = key(x);
    //key_type n = key(y);
        if (!key_compare(key(x), k)) // x的key >= k
            y = x, x = left(x);
        else    // x的key < k
            x = right(x);
    }
    //key_type aKey = key(y);
    iterator it = iterator(y);
    //aKey = key(it.node);
	key_type aKeyIt = key(it.node);

    return (it == end() || key_compare(k, aKeyIt)) ? end() : it;
}

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::iterator
rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::lower_bound(const Key& k) {
    link_type y = header; // y存储最后一个大于等于k值得节点(>=)
    link_type x = root();
    while (x != 0)
	{
		key_type aKey = key(x);
		if (!key_compare(aKey, k))
			y = x, x = left(x);
		else
			x = right(x);
	}
    return iterator(y);
}

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::iterator
rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::upper_bound(const Key& k) {
    link_type y = header; // y存储最后一个大于k值得节点(>)
    link_type x = root();
    while (x != 0)
	{
		key_type aKey = key(x);
		if (key_compare(k, aKey))
			y = x, x = left(x);
		else
			x = right(x);
	}
    return iterator(y);
}

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
inline pair<typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::iterator,
            typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::iterator>
rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::equal_range(const Key& k) {
    return pair<iterator, iterator>(lower_bound(k), upper_bound(k));
}


template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::size_type
rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::count(const Key& k){
    pair<iterator, iterator> p = equal_range(k);
    size_type n = 0;
    distance(p.first, p.second, n);
    return n;
}

__HTL_END_NAMESPACE

#endif
