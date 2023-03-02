#ifndef BSTREE_HPP
# define BSTREE_HPP

#include <iostream>
#include "tree_iterator.hpp"

namespace ft{

template <class T, class Comp>
class BSTree;

template <class P, class Comp>
class Node
{
	public:
		typedef P	value_type;

		Node() : content(NULL), left(NULL), right(NULL), parent(NULL) { }
		Node(value_type *p, Node* sentinel) : content(p), left(sentinel), right(sentinel), parent(NULL), color('r') {	};
		~Node()
		{
			if (content)
			{
				delete content;
				content = NULL;
			}
		}
		value_type		*content;
		Node			*left;
		Node			*right;
		Node			*parent;
		char			color;

		value_type&	getContent() const
		{
			return (content);
		}

		Node& operator= (Node& o)
		{
			this->content = o.getContent();
			this->parent= o.parent;
			this->left= o.left;
			this->right = o.right;
			this->color = o.color;
			return (*this);
		}

		Node& operator=( const Node& o )
		{
			this->content = o.getContent();
			this->parent= o.parent;
			this->left= o.left;
			this->right = o.right;
			this->color = o.color;
			return (*this);
		}

};

template <class T, class Comp = std::less<typename T::first_type> >
class BSTree{

	public:
		typedef Node<T, Comp>			node;
		typedef BSTree<T, Comp>		tree;
		typedef typename std::allocator<T>::template rebind<node>::other		node_allocator;
		typedef Comp		key_compare;
		typedef typename node_allocator::pointer							pointer;
		typedef typename node_allocator::const_pointer						const_pointer;
		typedef typename node_allocator::reference							reference;
		typedef typename node_allocator::const_reference					const_reference;
		typedef T				value_type;
		typedef tree_iterator<pointer, value_type>	iterator;
		typedef tree_iterator<const_pointer, const value_type>	const_iterator;

		BSTree() : sentinel(new Node<T, Comp>(new value_type(), NULL)), _size(0) { this->root = sentinel; this->sentinel->color = 'b'; };
		~BSTree();

		pointer insert(const value_type& p);

		pointer _find(typename value_type::first_type key);
		const_pointer _find(typename value_type::first_type key) const;

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
		void	clear()
		{
			if (this->root == sentinel)
				this->root = NULL;
			if (this->root)
			{		
				this->freeTree(this->root);
				this->root = NULL;
			}
			if (sentinel)
			{
				delete sentinel;
				sentinel = NULL;
			}
			this->_size = 0;
		}
		size_t	size() const;


		pointer	getHighestNodeFrom(node *node)
		{
			Node<T, Comp>* aux = NULL;

			aux = node;
			while (aux && aux->right && aux->right!= sentinel)
				aux = aux->right;
			return (aux);
		}

		const_pointer getHighestNodeFrom(node *node) const
		{
			Node<T, Comp>* aux = NULL;

			aux = node;
			while (aux && aux->right && aux->right!= sentinel)
				aux = aux->right;
			return (aux);
		}

		pointer getLowestNodeFrom(node* node) 
		{
			Node<T, Comp>* aux = NULL;

			aux = node;
			while (aux && aux->left && aux->left != sentinel)
				aux = aux->left;
			return (aux);
		};

		const_pointer getLowestNodeFrom(node* node) const
		{
			const Node<T, Comp>* aux = NULL;

			aux = node;
			while (aux && aux->left && aux->left != sentinel)
				aux = aux->left;
			return (aux);
		};

		pointer getHighestNode()
		{
			if (this->_size == 0)
				return (sentinel);
			return (getHighestNodeFrom(root));
		}

		const_pointer getHighestNode() const
		{
			if (this->_size == 0)
				return (sentinel);
			return (getHighestNodeFrom(root));
		}

		pointer getLowestNode()
		{
			if (this->_size == 0)
				return (sentinel);
			return (getLowestNodeFrom(root));
		}

		const_pointer getLowestNode() const
		{
			if (this->_size == 0)
				return (sentinel);
			return (getLowestNodeFrom(root));
		}

		iterator	begin()
		{
			node*	found;
			found = getLowestNode();

			return (iterator(found, sentinel));
		}

		const_iterator	begin() const
		{
			if (this->_size == 0)
				return (const_iterator(sentinel, sentinel));
			return (const_iterator(getLowestNodeFrom(root), sentinel));
		}

		const_iterator	end() const
		{
			return (const_iterator(sentinel), sentinel);
		}
		
		iterator	end()
		{
			return (iterator(sentinel, sentinel));
		}

		pointer getSentinel()
		{
			return (sentinel);
		}

		node*	base() { return root; };

	private:
		node			*sentinel;
		node			*root;
		size_t			_size;

		node			*insertFromNode(const value_type &p, Node<T, Comp> **r);
		void			del(node *root);
		void			freeTree(node *root);
		node			*getMaxNode(node *node);
		node			*getMinNode(node *node);
		node			*findNode(typename value_type::first_type key);


		//tree operations
		
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
				x->right->parent = x;
			x->parent = y->parent;
			if (y->parent == sentinel)
			{
				root = x;
				sentinel->right = root;
			}
			else if (y == y->parent->right)
				y->parent->right = x;
			else
				y->parent->left = x;
			x->right = y;
			y->parent = x;
		}


		/*
		 * red-black tree properties:
		 *  1. every node is either red or black
		 *  2. root is black
		 *  3. every leaf (sentinel, in this case) is black
		 *  4. if a node is red, then bot its children are black
		 *  5. for each node, all simple paths from the node to descendant leaves
		 *     contain the same number of black nodes
		 */

		// insert-fixup
		void	insertFixup(node *inserted)
		{
			node*	z;
			node*	y;

			z = inserted;
			while (z->parent->color == 'r')
			{
				if (z->parent == z->parent->parent->left)
				{
					y = z->parent->parent->left;
					if (y->color == 'r')
					{
						z->parent->color = 'b';
						y->color = 'b';
						z->parent->parent->color = 'r';
						z = z->parent->parent;
					}
					else if (z == z->parent->right)
					{
						z = z->parent;
						leftRotate(z);
					}
					z->parent->color = 'b';
					z->parent->parent->color = 'r';
					rightRotate(z->parent->parent);
				}
				else
				{
					y = z->parent->parent->right;
					if (y->color == 'r')
					{
						z->parent->color = 'b';
						y->color = 'b';
						z->parent->parent->color = 'r';
						z = z->parent->parent;
					}
					else if (z == z->parent->left)
					{
						z = z->parent;
						rightRotate(z);
					}
					z->parent->color = 'b';
					z->parent->parent->color = 'r';
					leftRotate(z->parent->parent);
				}
			}
			root->color = 'b';
			sentinel->right = root;
			std::cout << "fixup" << std::endl;
//			std::cout << "fixup" << std::endl;
		}


		//currently unused:
		size_t			count_nodes(const Node<T, Comp> *root) const;
};

template <class T, class Comp>
void	BSTree<T, Comp>::del(typename T::first_type key)
{
	Node<T, Comp>* found;

	found = this->_find(key);
	if (found && found != sentinel)
		this->deleteKeyFrom(found);
}

//template <class T>
template <class T, class Comp>
typename BSTree<T, Comp>::pointer	BSTree<T, Comp>::_find(typename T::first_type key)
{
	return (this->findNode(key));
}

template <class T, class Comp>
typename BSTree<T, Comp>::const_pointer	BSTree<T, Comp>::_find(typename T::first_type key) const
{
	return (this->findNode(key));
}

//template <class T>
template <class T, class Comp>
bool	BSTree<T, Comp>::deleteKeyFrom(node *node)
{
	size_t	old_size;

	old_size = this->_size;
	del(node);
	return (old_size - _size);
}

//template <class T>
template <class T, class Comp>
void	BSTree<T, Comp>::transplant(node* u, node *v)
{
	if (u->parent == sentinel)
	{
		this->root = v;
		sentinel->right = this->root;
	}
	else if (u == u->parent->left)
		u->parent->left = v;
	else
		u->parent->right = v;
	if (v != sentinel)
		v->parent = u->parent;
}

//template <class T>
template <class T, class Comp>
void	BSTree<T, Comp>::del(node *node)
{
	Node<T, Comp>*	y;
	Node<T, Comp>*	old_node;

	old_node = node;
	if (!node)
		return;
	if (node->left == sentinel)
		transplant(node, node->right);
	else if (node->right == sentinel)
		transplant(node, node->left);
	else if (node)
	{
		y = getMinNode(node->right);
		if (y->parent != node)
		{
			transplant(y, y->right);
			y->right = node->right;
			y->right->parent = y;
		}
		transplant(node, y);
		y->left = node->left;
		y->left->parent = y;
	}
	delete old_node;
	this->_size--;
	if (this->_size == 0)
	{
		this->root = sentinel;
		this->sentinel->right = this->root;
	}
}

template <class T, class Comp>
typename BSTree<T, Comp>::node*	BSTree<T, Comp>::getMaxNode(Node<T, Comp> *node)
{
	Node<T, Comp>* aux;

	aux = node;
	while (aux->right && aux->right != sentinel)
		aux = aux->right;
	return (aux);
}


template <class T, class Comp>
typename BSTree<T, Comp>::node*	BSTree<T, Comp>::getMinNode(Node<T, Comp> *node)
{
	Node<T, Comp>* aux;

	aux = node;
	while (aux->left && aux->left != sentinel)
		aux = aux->left;
	return (aux);
}

template <class T, class Comp>
typename BSTree<T, Comp>::node*	BSTree<T, Comp>::findNode(typename T::first_type key)
{
	key_compare comp = Comp(); 
	Node<T, Comp>		*node;

	node = root;	
	while (node != sentinel)
	{
		if (node && node->content->first == key)
			return (node);
		else if (node && node->left && comp(key, node->content->first))
			node = node->left;
		else if (node && node->right && comp(node->content->first, key))
			node = node->right;
	}
	return (node);	
}

template <class T, class Comp>
size_t	BSTree<T, Comp>::count_nodes(const Node<T, Comp> *root) const
{
	size_t	count;

	if (!root)
		return (0);
	count = 1;
	if (root->left)
		count += count_nodes(root->left);
	if (root->right)
		count += count_nodes(root->right);
	return (count);
}

template <class T, class Comp>
size_t	BSTree<T, Comp>::size() const
{
	return (this->_size);
}

template <class T, class Comp>
BSTree<T, Comp>::~BSTree()
{
	if (this->root)
	{		
		this->freeTree(this->root);
		this->root = NULL;
	}
	if (sentinel)
	{
		delete sentinel;
		sentinel = NULL;
	}
}

template <class T, class Comp>
void BSTree<T, Comp>::freeTree(node *root)
{
	if (!root)
		return;
	if (root->left && root->left != sentinel)
		freeTree(root->left);
	if (root->right && root->right != sentinel)
		freeTree(root->right);	
	delete root;
	_size--;
	root = NULL;
}

template <class T, class Comp>
typename BSTree<T, Comp>::pointer	BSTree<T, Comp>::insert(const typename BSTree<T, Comp>::value_type &p)
{
	return (this->insertFromNode(p, &(this->root)));
}

template <class T, class Comp>
typename BSTree<T, Comp>::node*	BSTree<T, Comp>::insertFromNode(const typename BSTree<T, Comp>::value_type &p, Node<T, Comp> **r)
{
	key_compare comp = Comp();
	Node<T, Comp>	*y = sentinel;
	Node<T, Comp>	*x = *r;
	Node<T, Comp>	*insert = new Node<T, Comp>(new value_type(p), sentinel);

	while (x != sentinel)
	{
		y = x;
		if (comp(insert->content->first, x->content->first))
			x = x->left;
		else if (insert->content->first == x->content->first)
		{
			delete insert;
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
	}
	else if (comp(insert->content->first, y->content->first))
		y->left = insert;
	else
		y->right = insert;
	this->_size++;
	insertFixup(insert);
//	insert-fixup(insert);
	return (insert);
}

}//end of ft namespace

#endif
