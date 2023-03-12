#ifndef RBTREE_HPP
# define RBTREE_HPP

#include <iostream>
#include "tree_iterator.hpp"

namespace ft{

template <class T, class Alloc, class Comp>
class RBTree;

//node for the red-black tree, it stores the content (ft::pair<key, value>) on the stack 
template <class P>
class Node
{
	public:
		typedef P								pair_type;
		typedef	typename pair_type::first_type	key_type;
		typedef	typename pair_type::second_type	value_type;

		Node() : content(pair_type()), left(NULL), right(NULL), parent(NULL) { }
		Node(pair_type &p, Node* sentinel) : content(ft::make_pair(p.first, p.second)), left(sentinel), right(sentinel), parent(NULL), color('r') {	};
		Node(const pair_type &p, Node* sentinel) : content(ft::make_pair(p.first, p.second)), left(sentinel), right(sentinel), parent(NULL), color('r') {	};

		~Node()	{ };
		pair_type		content;
		Node			*left;
		Node			*right;
		Node			*parent;
		char			color;

		//used by the iterators and the find operations in the map
		pair_type*	getContent()
		{
			return (&content);
		}

		const pair_type*	getContent() const
		{
			return (&content);
		}

};

template <class T, class Alloc, class Comp >
class RBTree{

	public:
		typedef Node<T>											node;
		typedef RBTree<T, Alloc, Comp>							tree;
		typedef Alloc 											pair_allocator;
		typedef typename Alloc::template 						rebind<node>::other	node_allocator;
		typedef Comp											key_compare;
		typedef typename node_allocator::pointer				pointer;
		typedef typename node_allocator::const_pointer			const_pointer;
		typedef typename node_allocator::reference				reference;
		typedef typename node_allocator::const_reference		const_reference;
		typedef T												value_type;
		typedef tree_iterator<pointer, value_type>				iterator;
		typedef tree_iterator<const_pointer, const value_type>	const_iterator;

		RBTree(){
			node*	sen = n_alloc.allocate(1);
			n_alloc.construct(sen, node());

			this->_size = 0;
			sen->color = 'b';
			sen->right = sen;
			sen->left = sen;
			this->sentinel = sen;
			this->root = sentinel;
		}
		~RBTree();

		pointer insert(const value_type& p)
		{
			return (this->insertFromNode(p, &(this->root)));
		}

		pointer _find(typename node::key_type key) { return (this->findNode(key)); }
		const_pointer _find(typename node::key_type key) const { return (this->findNode(key)); }

		//insert with hint. bypassed because it's risky and inefficient
		node	*insert(iterator position, const value_type& val)
		{
			(void) position; //aka the emadriga's tribute
			return (insertFromNode(val, &root));
		}

		iterator find(typename value_type::first_type key)
		{
			return (iterator(_find(key), sentinel));
		}

		const_iterator find(typename value_type::first_type key) const
		{
			return (const_iterator(_find(key), sentinel));
		}

		void	del(typename value_type::first_type key);
		void	transplant(node* u, node *v);
		bool	deleteKeyFrom(node *node);
		size_t	max_size() const {return (node_allocator().max_size());};

		void	swap(tree& other)
		{
			node*			sw;
			node*			sentinel_swp;
			node_allocator	alloc_swp;
			size_t			size_sw;

			sw = other.root;
			sentinel_swp = other.sentinel;
			size_sw = other.size();
			alloc_swp = other.getAllocator();

			other.root = this->root;
			other._size = this->size();
			other.sentinel = this->sentinel;
			other.n_alloc = this->n_alloc;

			this->root = sw;
			this->sentinel = sentinel_swp;
			this->_size = size_sw;
			this->n_alloc = alloc_swp;
		}

		void	clear()
		{
			if (this->root == sentinel)
				this->root = NULL;
			if (this->root)
			{		
				this->freeTree(this->root);
				this->root = NULL;
			}

			this->root = sentinel;	
			this->sentinel->right = sentinel;
			this->sentinel->left = sentinel;
			this->_size = 0;
		}

		size_t	size() const;

		iterator	begin()
		{
			return (iterator(sentinel->left, sentinel));
		}

		const_iterator	begin() const
		{
			return (const_iterator(sentinel->left, sentinel));
		}

		const_iterator	end() const
		{
			return (const_iterator(sentinel, sentinel));
		}
		
		iterator	end()
		{
			return (iterator(sentinel, sentinel));
		}

		pointer getSentinel()
		{
			return (sentinel);
		}

		pointer getSentinel() const
		{
			return (sentinel);
		}

		node*	getNextElement(pointer n) const
		{
			node* parent;
			node* node;

			node = n;
			if (node && node->right && node->right != sentinel)
				return (getLowestNodeFrom(node->right));
			parent = node->parent;
			while (parent && node == parent->right && parent != sentinel)
			{
				node = parent;
				parent = parent->parent;
			}
			return (parent);
		}

		pointer getLowestNodeFrom(node* node) const
		{
			Node<T>* aux = NULL;

			aux = node;
			while (aux && aux->left && aux->left != sentinel)
				aux = aux->left;
			return (aux);
		};

		node*	base() { return root; };
		node_allocator	getAllocator() { return n_alloc; }

		node			*findLowerBoundNode(typename value_type::first_type key) const;
		node			*findUpperBoundNode(typename value_type::first_type key) const;

		//used for testing purposes
	/*
		void printorder(node *node)
		{
			if (node == sentinel)
				return ;
			printorder(node->left);
			std::cout << "." << node->content.first << "," << node->color << "," << node->parent->content.first << std::endl;
			printorder(node->right);
		}
	

	public:
		void	printtree()
		{
			printorder(root);
		}

*/

	private:
		node_allocator	n_alloc;
		pointer			sentinel;
		node			*root;
		size_t			_size;

		node			*insertFromNode(const value_type &p, Node<T> **r);
		void			del(node *root);
		void			freeTree(node *root);
		node			*getMaxNode(node *node);
		node			*getMinNode(node *node);
		void			updateSentinelMinMax();
		node			*findNode(typename value_type::first_type key) const;


		//Red-black tree operations

		//All the operations have been implemented following these resources:
		//- "Introduction to algorithms" (Cormen, Leiserson, Rivest, Stein), 3rd edition
		//- https://www.youtube.com/playlist?list=PL9xmBV_5YoZNqDI8qfOZgzbqahCUmUEin
		//- https://www.youtube.com/watch?v=nMExd4DthdA&list=PLpPXw4zFa0uKKhaSz87IowJnOTzh9tiBk&index=66

		/*
		 * red-black tree properties:
		 *  1. every node is either red or black
		 *  2. root is black
		 *  3. every leaf (sentinel, in this case) is black
		 *  4. if a node is red, then bot its children are black
		 *  5. for each node, all simple paths from the node to descendant leaves
		 *     contain the same number of black nodes
		 */

		//left and right rotate are used to balance the tree after some insert
		//or erase operations

		/*
		 *       Left rotate ---->
		 *
		 *	   	  x                  y
		 *   	/   \               / \
		 *	   α     y             x   γ
		 *	        / \           / \
		 * 		   β   γ         α   β
		 *
		 *            <----- Right rotate
		 * 
		 ***********************************/ 

		void	leftRotate(node *x)
		{
			node *y = x->right;

			x->right = y->left;
			if (y->left != sentinel)
				y->left->parent = x;
			y->parent = x->parent;
			if (x->parent == sentinel)
			{
				root = y;
				sentinel->right = root;
			}
			else if (x == x->parent->left)
				x->parent->left = y;
			else
				x->parent->right = y;
			y->left = x;
			x->parent = y;
		}

		void	rightRotate(node *y)
		{
			node *x = y->left;
			y->left = x->right;
			if (x->right != sentinel)
				x->right->parent = y;
			x->parent = y->parent;
			if (y->parent == sentinel)
			{
				root = x;
				sentinel->left = root;
			}
			else if (y == y->parent->right)
				y->parent->right = x;
			else
				y->parent->left = x;
			x->right = y;
			y->parent = x;
		}


		// insert-fixup: method used to fix the tree when a insertion produces 
		// a violation of rb-tree rules
		void	insertFixup(node *inserted)
		{
			node*	z;
			node*	y;

			z = inserted; // initially, z points to the inserted node. then we'll use to fix from bottom to top all rbtree properties violations
			while (z->parent->color == 'r')
			{
				if (z->parent == z->parent->parent->left) // operations on the left side of the grandfather subtree where z is pointing to
				{
					y = z->parent->parent->right;
					if (y->color == 'r') // case 1: z's uncle y is red. fix by changing colors
					{
						z->parent->color = 'b';
						y->color = 'b';
						z->parent->parent->color = 'r';
						z = z->parent->parent;
					}
					else
					{	// case 2: z's uncle y is black and z is a right child
						// rotation to make z parent's a left child of z to force case 3
						if (z == z->parent->right && z->parent != sentinel)
						{
							z = z->parent;
							leftRotate(z);
						}
						//case 3: z's uncle y is black and z is a left child
						// conversion of z grandfather in z parent's right child
						z->parent->color = 'b';
						z->parent->parent->color = 'r';
						rightRotate(z->parent->parent);
					}
				}
				else if (z->parent == z->parent->parent->right) //mirror when z is at the right side of the subtree
				{
					y = z->parent->parent->left;
					if (y->color == 'r')
					{
						z->parent->color = 'b';
						y->color = 'b';
						z->parent->parent->color = 'r';
						z = z->parent->parent;
					}
					else
					{
						if (z == z->parent->left && z->parent != sentinel)
						{
							z = z->parent;
							rightRotate(z);
						}
						z->parent->color = 'b';
						z->parent->parent->color = 'r';
						leftRotate(z->parent->parent);
					}
				}
			}
			root->color = 'b';
		}

		void	deleteFixup(node *replaced)
		{
			node*	x;
			node*	w; //sibling

			x = replaced;
			while (x != root && x->color == 'b')
			{
				if (x == x->parent->left)
				{
					w = x->parent->right;
					if (w->color == 'r')
					{
						w->color = 'b';
						x->parent->color = 'r';
						leftRotate(x->parent);
						w = x->parent->right;
					}
					if (w->left->color == 'b' && w->right->color == 'b')
					{
						w->color = 'r';
						x = x->parent;
					}
					else 
					{
						if (w->right->color == 'b')
						{
							w->left->color = 'b';
							w->color = 'r';
							rightRotate(w);
							w = x->parent->right;
						}
						w->color = x->parent->color;
						x->parent->color = 'b';
						w->right->color = 'b';
						leftRotate(x->parent);
						x = root;
					}
				}
				else
				{
					w = x->parent->left;
					if (w->color == 'r')
					{
						w->color = 'b';
						x->parent->color = 'r';
						rightRotate(x->parent);
						w = x->parent->left;
					}
					if (w->right->color == 'b' && w->left->color == 'b')
					{
						w->color = 'r';
						x = x->parent;
					}
					else 
					{
						if (w->left->color == 'b')
						{
							w->right->color = 'b';
							w->color = 'r';
							leftRotate(w);
							w = x->parent->left;
						}
						w->color = x->parent->color;
						x->parent->color = 'b';
						w->left->color = 'b';
						rightRotate(x->parent);
						x = root;
					}
				}
			}
			x->color = 'b';


		}

};

template <class T, class Alloc, class Comp>
void	RBTree<T, Alloc, Comp>::del(typename T::first_type key)
{
	Node<T>* found;

	found = this->_find(key);
	if (found && found != sentinel)
		this->deleteKeyFrom(found);
}

//template <class T>
template <class T, class Alloc, class Comp>
bool	RBTree<T, Alloc, Comp>::deleteKeyFrom(node *node)
{
	size_t	old_size;

	old_size = this->_size;
	del(node);
	return (old_size - _size);
}

//new transplant
template <class T, class Alloc, class Comp>
void	RBTree<T, Alloc, Comp>::transplant(node* u, node *v)
{
	if (u->parent == sentinel)
	{
		this->root = v;
	}
	else if (u == u->parent->left)
		u->parent->left = v;
	else
		u->parent->right = v;
	v->parent = u->parent;
}

template <class T, class Alloc, class Comp>
void	RBTree<T, Alloc, Comp>::del(node *node)
{
	Node<T>*	y;
	Node<T>*	x;
	Node<T>*	old_node;
	char		y_original_color;

	old_node = node;
	y = node;
	y_original_color = y->color;
	if (!node)
		return;
	if (node->left == sentinel)
	{
		x = node->right;
		transplant(node, node->right);
	}
	else if (node->right == sentinel)
	{
		x = node->left;
		transplant(node, node->left);
	}
	else if (node)
	{
		y = getMinNode(node->right);
		y_original_color = y->color;
		x = y->right;
		if (y->parent == node)		
			x->parent = y;
		else
		{
			transplant(y, y->right);
			y->right = node->right;
			y->right->parent = y;
		}
		transplant(node, y);
		y->left = node->left;
		y->left->parent = y;
		y->color = node->color;
	}
	
	n_alloc.destroy(old_node);
	n_alloc.deallocate(old_node, 1);
	this->_size--;
	if (this->_size == 0)
	{
		this->root = sentinel;
		this->sentinel->right = this->root;
		this->sentinel->left = this->root;
		return ;
	}
	if (y_original_color == 'b')
	{
		deleteFixup(x);
	}
	updateSentinelMinMax();
}
/*
template <class T, class Alloc, class Comp>
void	RBTree<T, Alloc, Comp>::deleteFixup(node *replaced)
{
	node*	x;
	node*	w; //sibling

	x = replaced;
	while (x != root && x->color == 'b')
	{
		if (x == x->parent->left)
		{
			w = x->parent->right;
			if (w->color == 'r')
			{
				w->color = 'b';
				x->parent->color = 'r';
				leftRotate(x->parent);
				w = x->parent->right;
			}
			if (w->left->color == 'b' && w->right->color == 'b')
			{
				w->color = 'r';
				x = x->parent;
			}
			else 
			{
				if (w->right->color == 'b')
				{
					w->left->color = 'b';
					w->color = 'r';
					rightRotate(w);
					w = x->parent->right;
				}
				w->color = x->parent->color;
				x->parent->color = 'b';
				w->right->color = 'b';
				leftRotate(x->parent);
				x = root;
			}
		}
		else
		{
			w = x->parent->left;
			if (w->color == 'r')
			{
				w->color = 'b';
				x->parent->color = 'r';
				rightRotate(x->parent);
				w = x->parent->left;
			}
			if (w->right->color == 'b' && w->left->color == 'b')
			{
				w->color = 'r';
				x = x->parent;
			}
			else 
			{
				if (w->left->color == 'b')
				{
					w->right->color = 'b';
					w->color = 'r';
					leftRotate(w);
					w = x->parent->left;
				}
				w->color = x->parent->color;
				x->parent->color = 'b';
				w->left->color = 'b';
				rightRotate(x->parent);
				x = root;
			}
		}
	}
	x->color = 'b';
}
*/

template <class T, class Alloc, class Comp>
typename RBTree<T, Alloc, Comp>::node*	RBTree<T, Alloc, Comp>::getMaxNode(Node<T> *node)
{
	Node<T>* aux;

	aux = node;
	while (aux->right && aux->right != sentinel)
		aux = aux->right;
	return (aux);
}


template <class T, class Alloc, class Comp>
typename RBTree<T, Alloc, Comp>::node*	RBTree<T, Alloc, Comp>::getMinNode(Node<T> *node)
{
	Node<T>* aux;

	aux = node;
	while (aux->left && aux->left != sentinel)
		aux = aux->left;
	return (aux);
}

template <class T, class Alloc, class Comp>
typename RBTree<T, Alloc, Comp>::node*	RBTree<T, Alloc, Comp>::findNode(typename T::first_type key) const
{
	key_compare comp = Comp(); 
	Node<T>		*node;

	node = root;	
	while (node != sentinel)
	{
		if (node && node->getContent()->first == key)
			return (node);
		else if (node && node->left && comp(key, node->getContent()->first))
			node = node->left;
		else if (node && node->right && comp(node->getContent()->first, key))
			node = node->right;
	}
	return (node);
}

template <class T, class Alloc, class Comp>
typename RBTree<T, Alloc, Comp>::node*	RBTree<T, Alloc, Comp>::findLowerBoundNode(typename T::first_type key) const
{
	key_compare comp = Comp(); 
	Node<T>		*node;

	node = root;	
	while (node != sentinel)
	{
		if (node && node->getContent()->first == key)
			return (node);
		else if (node && node->left && comp(key, node->getContent()->first))
		{
			if (node->left == sentinel)
				return (node);
			node = node->left;
		}
		else if (node && node->right && comp(node->getContent()->first, key))
		{
			if (node->right == sentinel)
				return (getNextElement(node));
			node = node->right;
		}
	}
	return (node);
}

template <class T, class Alloc, class Comp>
typename RBTree<T, Alloc, Comp>::node*	RBTree<T, Alloc, Comp>::findUpperBoundNode(typename T::first_type key) const
{
	key_compare comp = Comp(); 
	Node<T>		*node;

	node = root;	
	while (node != sentinel)
	{

		if (node && node->left && comp(key, node->getContent()->first))
		{
			if (node->left == sentinel)
				return (node);
			node = node->left;
		}
		else if (node && node->right && comp(node->getContent()->first, key))
		{
			if (node->right == sentinel)
				return (getNextElement(node));
			node = node->right;
		}
		else if (node && node->getContent()->first == key)
			return (getNextElement(node));
	}
	return (node);
}

template <class T, class Alloc, class Comp>
size_t	RBTree<T, Alloc, Comp>::size() const
{
	return (this->_size);
}

template <class T, class Alloc, class Comp>
RBTree<T, Alloc, Comp>::~RBTree()
{
	if (this->root && this->root != sentinel)
	{
		this->freeTree(this->root);
		this->root = NULL;
	}
	if (sentinel)
	{
		n_alloc.destroy(sentinel);
		n_alloc.deallocate(sentinel, 1);
		sentinel = NULL;
	}
	
}

template <class T, class Alloc, class Comp>
void RBTree<T, Alloc, Comp>::freeTree(node *r)
{
	if (!r || r == sentinel)
		return;
	if (r->left && r->left != sentinel)
		freeTree(r->left);
	if (r->right && r->right != sentinel)
		freeTree(r->right);
	n_alloc.destroy(r);
	n_alloc.deallocate(r, 1);
	_size--;
	r = NULL;
}

template <class T, class Alloc, class Comp>
typename RBTree<T, Alloc, Comp>::node*	RBTree<T, Alloc, Comp>::insertFromNode(const typename RBTree<T, Alloc, Comp>::value_type &p, Node<T> **r)
{
	key_compare comp = Comp();
	Node<T>	*y = sentinel;
	Node<T>	*x = *r;
	Node<T>	*insert = n_alloc.allocate(1);
	n_alloc.construct(insert, node(p, sentinel));

	insert->color = 'r';
	insert->right = sentinel;
	insert->left = sentinel;
	while (x != sentinel)
	{
		y = x;
		if (comp(insert->getContent()->first, x->getContent()->first))
			x = x->left;
		else if (insert->getContent()->first == x->getContent()->first)
		{
			n_alloc.destroy(insert);
			n_alloc.deallocate(insert, 1);
			return (x);
		}
		else
			x = x->right;
	}
	insert->parent = y;
	if (y == sentinel) // empty tree
	{
		*r = insert;
		sentinel->right = insert;
		sentinel->left = insert;
	}
	else if (comp(insert->getContent()->first, y->getContent()->first))
		y->left = insert;
	else
		y->right = insert;
	this->_size++;
	insertFixup(insert);
	if (y != sentinel)
		updateSentinelMinMax();
	return (insert);
}

template <class T, class Alloc, class Comp>
void RBTree<T, Alloc, Comp>::updateSentinelMinMax()
{
	sentinel->left = getMinNode(root);
	sentinel->right = getMaxNode(root);
}


}//end of ft namespace

#endif
