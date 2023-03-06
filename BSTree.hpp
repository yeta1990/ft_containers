#ifndef BSTREE_HPP
# define BSTREE_HPP

#include <iostream>
#include "tree_iterator.hpp"

namespace ft{

template <class T, class Alloc, class Comp>
class BSTree;

template <class P>
class Node
{
	public:
		typedef P							pair_type;
//		typedef	typename pair_type::first	key_type;
//		typedef	typename pair_type::first	value_type;


		Node() : content(pair_type()), left(NULL), right(NULL), parent(NULL) { }
//		Node(pair_type *p, Node* sentinel) : content(p), left(sentinel), right(sentinel), parent(NULL), color('r') {	};
		Node(pair_type &p, Node* sentinel) : content(ft::make_pair(p.first, p.second)), left(sentinel), right(sentinel), parent(NULL), color('r') {	};
		Node(const pair_type &p, Node* sentinel) : content(ft::make_pair(p.first, p.second)), left(sentinel), right(sentinel), parent(NULL), color('r') {	};

		~Node()	{ };
		pair_type		content;
		Node			*left;
		Node			*right;
		Node			*parent;
		char			color;

		pair_type*	getContent() 
		{
			return (&content);
		}

		const pair_type*	getContent() const
		{
			return (&content);
		}

		typename pair_type::first_type& getFirst()
		{
			return (content.first);
		}

};

template <class T, class Alloc, class Comp >
class BSTree{

	public:
		typedef Node<T>		node;
		typedef BSTree<T, Alloc, Comp>		tree;

		typedef Alloc 						pair_allocator;

		typedef typename Alloc::template 				rebind<node>::other	node_allocator;
//		typedef typename std::allocator<T>::template rebind<node>::other		node_allocator;
		typedef Comp		key_compare;

		typedef typename node_allocator::pointer							pointer;
		typedef typename node_allocator::const_pointer						const_pointer;
		typedef typename node_allocator::reference							reference;
		typedef typename node_allocator::const_reference					const_reference;
		typedef T				value_type;
		typedef tree_iterator<pointer, value_type>	iterator;
		typedef tree_iterator<const_pointer, const value_type>	const_iterator;

		BSTree(){
//			std::cout << "bstree constructor" << std::endl;
			node*	sen = n_alloc.allocate(1);
			n_alloc.construct(sen, node());

			this->_size = 0;
//			sen->content = new value_type();
			sen->color = 'b';
			sen->right = sen;
			sen->left = sen;
			this->sentinel = sen;
//			this->root = NULL;
			this->root = sentinel;
		}
		~BSTree();
/*
		BSTree& operator=(const BSTree& o)
		{
//			std::cout << "operator=" << std::endl;
//			node*	sen = n_alloc.allocate(1);
//			this->clear();
			this->_size = o.size();
//			this->root = o.root;
//			this->sentinel = o.getSentinel();
//			insert(o.begin(), o.end());
			const_iterator it;

			for (it = o.begin(); it != o.end(); it++)
			{
				insert(*it);
			}
			this->root = sentinel->right;
			
			return (*this);

		}
*/		

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

		size_t	max_size() const {return (node_allocator().max_size());};
//		size_t	max_size() const {return (pair_allocator().max_size());};
		void	swap(tree& other)
		{
			node*			sw;
			node*			sentinel_swp;
			node_allocator	alloc_swp;
			size_t	size_sw;

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

			/*
			if (sentinel)
			{
//				delete sentinel;
				n_alloc.destroy(sentinel);
				n_alloc.deallocate(sentinel, 1);
				sentinel = NULL;
			}
			*/
			this->root = sentinel;	
			this->_size = 0;
		}
		size_t	size() const;


		pointer	getHighestNodeFrom(node *node)
		{
			Node<T>* aux = NULL;

			aux = node;
			while (aux && aux->right && aux->right!= sentinel)
				aux = aux->right;
			return (aux);
		}

		const_pointer getHighestNodeFrom(node *node) const
		{
			Node<T>* aux = NULL;

			aux = node;
			while (aux && aux->right && aux->right!= sentinel)
				aux = aux->right;
			return (aux);
		}

		pointer getLowestNodeFrom(node* node) 
		{
			Node<T>* aux = NULL;

			aux = node;
			while (aux && aux->left && aux->left != sentinel)
				aux = aux->left;
			return (aux);
		};

		const_pointer getLowestNodeFrom(node* node) const
		{
			const Node<T>* aux = NULL;

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

		node*	base() { return root; };
		node_allocator	getAllocator() { return n_alloc; }

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
		node			*findNode(typename value_type::first_type key) const;


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


		/*
		 * red-black tree properties:
		 *  1. every node is either red or black
		 *  2. root is black
		 *  3. every leaf (sentinel, in this case) is black
		 *  4. if a node is red, then bot its children are black
		 *  5. for each node, all simple paths from the node to descendant leaves
		 *     contain the same number of black nodes
		 */

		void printorder(node *node)
		{
			if (node == sentinel)
				return ;
			printorder(node->left);
			if (node == root)
//				std::cout << "root : ";
//			std::cout << "." << node->content->first << "," << node->color << "," << node->parent->content->first << std::endl;

			printorder(node->right);
		}

	public:
		void	printtree()
		{
			printorder(root);
		}

	private:

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
					y = z->parent->parent->right;
					if (y->color == 'r')
					{
						z->parent->color = 'b';
						y->color = 'b';
						z->parent->parent->color = 'r';
						z = z->parent->parent;
					}
					else
					{
						if (z == z->parent->right && z->parent != sentinel)
						{
							z = z->parent;
							leftRotate(z);
						}
						z->parent->color = 'b';
						z->parent->parent->color = 'r';
						rightRotate(z->parent->parent);
						
					}

				}
				else if (z->parent == z->parent->parent->right)
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
						if (z == z->parent->left)
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
			sentinel->right = root;
//			std::cout << "fixup" << std::endl;
//			std::cout << "fixup" << std::endl;
		}


		//currently unused:
		size_t			count_nodes(const Node<T> *root) const;
};

template <class T, class Alloc, class Comp>
void	BSTree<T, Alloc, Comp>::del(typename T::first_type key)
{
	Node<T>* found;

	found = this->_find(key);
	if (found && found != sentinel)
		this->deleteKeyFrom(found);
}

//template <class T>
template <class T, class Alloc, class Comp>
typename BSTree<T, Alloc, Comp>::pointer	BSTree<T, Alloc, Comp>::_find(typename T::first_type key)
{
	return (this->findNode(key));
}

template <class T, class Alloc, class Comp>
typename BSTree<T, Alloc, Comp>::const_pointer	BSTree<T, Alloc, Comp>::_find(typename T::first_type key) const
{
	return (this->findNode(key));
}

//template <class T>
template <class T, class Alloc, class Comp>
bool	BSTree<T, Alloc, Comp>::deleteKeyFrom(node *node)
{
	size_t	old_size;

	old_size = this->_size;
	del(node);
	return (old_size - _size);
}

//template <class T>
template <class T, class Alloc, class Comp>
void	BSTree<T, Alloc, Comp>::transplant(node* u, node *v)
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
template <class T, class Alloc, class Comp>
void	BSTree<T, Alloc, Comp>::del(node *node)
{
	Node<T>*	y;
	Node<T>*	old_node;

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
	
	n_alloc.destroy(old_node);
	n_alloc.deallocate(old_node, 1);
//	delete old_node;
	this->_size--;
	if (this->_size == 0)
	{
		this->root = sentinel;
		this->sentinel->right = this->root;
	}
}

template <class T, class Alloc, class Comp>
typename BSTree<T, Alloc, Comp>::node*	BSTree<T, Alloc, Comp>::getMaxNode(Node<T> *node)
{
	Node<T>* aux;

	aux = node;
	while (aux->right && aux->right != sentinel)
		aux = aux->right;
	return (aux);
}


template <class T, class Alloc, class Comp>
typename BSTree<T, Alloc, Comp>::node*	BSTree<T, Alloc, Comp>::getMinNode(Node<T> *node)
{
	Node<T>* aux;

	aux = node;
	while (aux->left && aux->left != sentinel)
		aux = aux->left;
	return (aux);
}

template <class T, class Alloc, class Comp>
typename BSTree<T, Alloc, Comp>::node*	BSTree<T, Alloc, Comp>::findNode(typename T::first_type key) const
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
size_t	BSTree<T, Alloc, Comp>::count_nodes(const Node<T> *root) const
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

template <class T, class Alloc, class Comp>
size_t	BSTree<T, Alloc, Comp>::size() const
{
	return (this->_size);
}

template <class T, class Alloc, class Comp>
BSTree<T, Alloc, Comp>::~BSTree()
{
//	std::cout << "chaoo" << std::endl;
	if (this->root && this->root != sentinel)
	{		
		this->freeTree(this->root);
		this->root = NULL;
	}

	if (sentinel)
	{
		n_alloc.destroy(sentinel);
		n_alloc.deallocate(sentinel, 1);
//		delete sentinel;
		sentinel = NULL;
	}
	
}

template <class T, class Alloc, class Comp>
void BSTree<T, Alloc, Comp>::freeTree(node *r)
{
//	std::cout << "free tree" << std::endl;
//	return; 
	if (!r || r == sentinel)
		return;
	if (r->left && r->left != sentinel)
		freeTree(r->left);
	if (r->right && r->right != sentinel)
		freeTree(r->right);
//	if (r != sentinel)
//	{
	n_alloc.destroy(r);
	n_alloc.deallocate(r, 1);
	_size--;
//	}
	r = NULL;
}

template <class T, class Alloc, class Comp>
typename BSTree<T, Alloc, Comp>::pointer	BSTree<T, Alloc, Comp>::insert(const typename BSTree<T, Alloc, Comp>::value_type &p)
{
	return (this->insertFromNode(p, &(this->root)));
}

template <class T, class Alloc, class Comp>
typename BSTree<T, Alloc, Comp>::node*	BSTree<T, Alloc, Comp>::insertFromNode(const typename BSTree<T, Alloc, Comp>::value_type &p, Node<T> **r)
{
//	std::cout << "inserting" << std::endl;
	key_compare comp = Comp();
	Node<T>	*y = sentinel;
	Node<T>	*x = *r;

	Node<T>	*insert = n_alloc.allocate(1);
//	n_alloc.construct(insert, node(new value_type(p), sentinel));
	n_alloc.construct(insert, node(p, sentinel));

//	insert->content = new value_type(p);
	insert->color = 'r';
	insert->right = sentinel;
	insert->left = sentinel;

//	this->sentinel = sen;
//	this->root = sentinel;

//	Node<T>	*insert = new Node<T>(new value_type(p), sentinel);

	while (x != sentinel)
	{
		y = x;
		if (comp(insert->getContent()->first, x->getContent()->first))
			x = x->left;
		else if (insert->getContent()->first == x->getContent()->first)
		{
			n_alloc.destroy(insert);
			n_alloc.deallocate(insert, 1);
//			delete insert;
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
	else if (comp(insert->getContent()->first, y->getContent()->first))
		y->left = insert;
	else
		y->right = insert;
	this->_size++;
	insertFixup(insert);
//	std::cout << "insert " << insert->content->first  << ", color " << insert->color << std::endl;
//	insert-fixup(insert);
	return (insert);
}

}//end of ft namespace

#endif
