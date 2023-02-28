#ifndef BSTREE_HPP
# define BSTREE_HPP

#include <iostream>
#include "tree_iterator.hpp"

namespace ft{

//template <class T>
template <class T, class Comp>
class BSTree;

template <class P, class Comp>
class Node
{
	public:
//		typedef pair<const T1, T2>	value_type;
		typedef P	value_type;

		Node() : content(NULL), left(NULL), right(NULL), parent(NULL), my_tree(NULL), sentinel(NULL) { }
//		Node() : content(), key(content->first), value(content.second), left(NULL), right(NULL), parent(NULL), my_tree(NULL), sentinel(NULL) { }
		Node(value_type *p, Node* parent, ft::BSTree<P, Comp> *tree, Node* sentinel) : content(p), left(NULL), right(NULL), parent(parent), my_tree(tree), sentinel(sentinel) {	};
//		Node(ft::pair<T1,T2> p, Node* parent, ft::BSTree<T1, T2> *tree, Node* sentinel) : content(p), key(content->first), value(content.second), left(NULL), right(NULL), parent(parent), my_tree(tree), sentinel(sentinel) {	};
		~Node()
		{
			if (content)
			{
				delete content;
				content = NULL;
			}
		}
		value_type		*content;
//		const T1&		key;
//		T2&				value;
		Node			*left;
		Node			*right;
		Node			*parent;
		BSTree<P, Comp>		*my_tree;
		Node			*sentinel;

		value_type&	getContent() const
		{
			return (content);
		}
		bool	hasAnyChild()
		{
			return (left || right);
		}

		Node	*hasOneChild()
		{
			if (left && left != sentinel)
				return (left);
			else if (right && right != sentinel)
				return (right);
			return (NULL);
		}

		bool	hasTwoChildren()
		{
			return (left && right);
		}


		Node& operator= (Node& o)
		{
			this->content = o.getContent();
			this->parent= o.parent;
			this->sentinel = o.sentinel;
			this->left= o.left;
			this->right = o.right;
			this->my_tree = o.my_tree;
			return (*this);
		}

		Node& operator=( const Node& o )
		{
			this->content = o.getContent();
			this->parent= o.parent;
			this->sentinel = o.sentinel;
			this->left= o.left;
			this->right = o.right;
			this->my_tree = o.my_tree;
			return (*this);
		}
		//find inorder successor
		//https://www.techiedelight.com/find-inorder-successor-given-key-bst/
		//https://www.scaler.com/topics/inorder-successor/
		Node*	getNextElement() const
		{
			Node *parent;
			Node const	*node;

			node = this;
			if (node->right && node->right != sentinel)
				return (this->my_tree->getLowestNodeFrom(node->right));
			parent = node->parent;
			while (parent && node == parent->right && parent != sentinel)
			{
				node = parent;
				parent = parent->parent;
			}
			return (parent);
		}

		Node*	getPrevElement() const
		{
			Node 	*parent;
			Node const	*node;

			node = this;
			if (this == sentinel)
				return (this->my_tree->getHighestNode());
			if (node->left && node->left != sentinel)
				return (this->my_tree->getHighestNodeFrom(node->left));
			parent = node->parent;
			while (parent && node == parent->left && parent != sentinel)
			{
				node = parent;
				parent = parent->parent;
			}
			return (parent);
		}

};

template <class T, class Comp = std::less<typename T::first_type> >
class BSTree{

	public:
		typedef Node<T, Comp>			node;
//		typedef Node<const T>	cnode;
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

		BSTree() : sentinel(new Node<T, Comp>(new value_type(), NULL, this, NULL)), root(NULL), _size(0) { sentinel->sentinel = sentinel; };
		~BSTree();

		pointer insert(const value_type& p);

		pointer _find(typename value_type::first_type key);
		const_pointer _find(typename value_type::first_type key) const;

		/* Insert with hint. As this is a BSTree, to insert with hint
		 * we must ensure the the hint is good
		 * 
		 * Bad hint:
		 * if parent < current && parent > key to insert
		 *  || parent > current && parent < key to insert
	 	 *
		 * Otherwise, the hint is good
		 */

		node	*insert(iterator position, const value_type& val)
		{
			key_compare comp = Comp();

			if (this->_size == 0)
				return (insertFromRoot(val, &root, NULL));
			else if (insert_has_good_hint(position, val))
			{

				if (comp((*position).first, val.first))
					return (this->insertFromRoot(val, &((*position.base())->right), *(position.base())));
				return (this->insertFromRoot(val, &((*position.base())->left), *(position.base())));
			}
			return (insertFromRoot(val, &root, NULL));
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

//		cnode	*getSentinel() const
//		{
//			return (sentinel);
//		}
		
//		node	*get

		node*	base() { return root; };

		/*void swap (BSTree* x)
		{
			node*	x_sentinel;	
			node*	x_root;	
			size_t	x_size;

			x_sentinel = x->getSentinel();
			x_root = x->base();
			x_size = x->_size;
			x->sentinel = this->sentinel;
			x->root = this->root;
			x->_size = this->_size;
			this->sentinel = x_sentinel;
			this->root = x_root;
			this->_size = x_size;
		}
		*/
	private:
		node			*sentinel;
		node			*root;
		size_t			_size;

		node			*insertFromRoot(const value_type &p, Node<T, Comp> **r, Node<T, Comp> *parent);
		void			del(node *root);
		void			freeTree(node *root);
		node			*getMaxNode(node *node);
		node			*getMinNode(node *node);

		node			*findNode(typename value_type::first_type key, node *node);

		bool insert_has_good_hint(iterator position, const value_type& val)
		{
			node*	parent;
			node*	current;
			key_compare comp = Comp();
			
			current = *position.base();
			parent = current->parent;
			while (parent)
			{
				if (comp(parent->content->first, current->content->first) && comp(val.first, parent->content->first))
					return (false);
				else if (comp(current->content->first, parent->content->first) && comp(parent->content->first, val.first))
					return (false);
				current = parent;
				parent = parent->parent;
			}
			return (true);
		}

		//currently unused:
		size_t			count_nodes(const Node<T, Comp> *root) const;
};

//template <class T>
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
	return (this->findNode(key, this->root));
}

//template <class T>
template <class T, class Comp>
typename BSTree<T, Comp>::const_pointer	BSTree<T, Comp>::_find(typename T::first_type key) const
{
	return (this->findNode(key, this->root));
}

//template <class T>
template <class T, class Comp>
bool	BSTree<T, Comp>::deleteKeyFrom(node *node)
{
	size_t	old_size;

	old_size = this->_size;
//	std::cout << "deleting " << key << std::endl;
	del(node);
//	del(key, node);
	return (old_size - _size);
}

//template <class T>
template <class T, class Comp>
void	BSTree<T, Comp>::transplant(node* u, node *v)
{
	if (u->parent == sentinel)
		this->root = v;
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
	else 
	{
		y = getMinNode(node->right);
//		std::cout << "y is " << y->content->first << std::endl;
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
		this->root = NULL;
		this->sentinel->right = NULL;
	}
}

//template <class T>
template <class T, class Comp>
typename BSTree<T, Comp>::node*	BSTree<T, Comp>::getMaxNode(Node<T, Comp> *node)
{
	Node<T, Comp>* aux;

	aux = node;
	while (aux->right && aux->right != sentinel)
		aux = aux->right;
//	if (node->right && node->right != sentinel)
//		return (getMaxNode(node->right));
	return (aux);
}


//template <class T>
template <class T, class Comp>
typename BSTree<T, Comp>::node*	BSTree<T, Comp>::getMinNode(Node<T, Comp> *node)
{
	Node<T, Comp>* aux;

	aux = node;
	while (aux->left && aux->left != sentinel)
		aux = aux->left;
//	if (node->right && node->right != sentinel)
//		return (getMaxNode(node->right));
	return (aux);
//	if (node->left && node->left != sentinel)
//		return (getMinNode(node->left));
//	return (node);
}

template <class T, class Comp>
typename BSTree<T, Comp>::node*	BSTree<T, Comp>::findNode(typename T::first_type key, Node<T, Comp> *node)
{
	key_compare comp = Comp(); 

	if (node && node->content->first == key)
	{
		return (node);
	}
	else if (node && node->left && node->left != sentinel && comp(key, node->content->first))
		return (findNode(key, node->left));
	else if (node && node->right && node->right != sentinel && comp(node->content->first, key))
		return (findNode(key, node->right));
	return (sentinel);
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
//	std::cout << "deleting " << root->content->first << std::endl;
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
//	std::cout << "inserting " << p.second << " in " << p.first << std::endl;
	return (this->insertFromRoot(p, &(this->root), NULL));
//	std::cout << node->value << std::endl;
}

/*
template <class T1, class T2>
typename BSTree<T1, T2>::node*	BSTree<T1, T2>::insert(tree_iterator<typename BSTree<T1, T2>::node* >::iterator position, const ft::pair<T1, T2>& val)
{
}
*/

/*
template <class T, class Comp>
typename BSTree<T, Comp>::node*	BSTree<T, Comp>::insertFromRoot(typename BSTree<T, Comp>::value_type p, Node<T, Comp> **r, Node<T, Comp> *parent)
{
	key_compare comp = Comp();


	if (*r == NULL || *r == sentinel)
	{
		if (!parent)
		{
			sentinel->right = *r;
			parent = sentinel;
		}
		*r = new Node<T, Comp>(new value_type(p), parent, this, sentinel);
		(*r)->left = sentinel;
		(*r)->right = sentinel;
//		std::cout << "adding node" << std::endl;
		this->_size++;
		return (*r);
	}
	else if (comp(p.first, (*r)->content->first))
//	else if (p.first < (*r)->content->first)
		return (this->insertFromRoot(p, &(*r)->left, *r));
	else if (p.first == (*r)->content->first)
		return (*r);
	return (this->insertFromRoot(p, &(*r)->right, *r));
}
*/


template <class T, class Comp>
typename BSTree<T, Comp>::node*	BSTree<T, Comp>::insertFromRoot(const typename BSTree<T, Comp>::value_type &p, Node<T, Comp> **r, Node<T, Comp> *parent)
{
	key_compare comp = Comp();
	Node<T, Comp>	**start;
	Node<T, Comp>	*par;

	start = &(*r);
	par = parent;
	while (*start != NULL && *start != sentinel)
	{
//		std::cout << "eeeooo" << std::endl;
		par = *start;
		if (comp(p.first, (*start)->content->first))
			start = &(*start)->left;
		else if (p.first == (*start)->content->first)
			return (*start);
		else
			start = &(*start)->right;
	}

//	if (*r == NULL || *r == sentinel)
//	{
		if (!par)
		{
			sentinel->right = *start;
			par = sentinel;
		}
		*start = new Node<T, Comp>(new value_type(p), par, this, sentinel);
		(*start)->left = sentinel;
		(*start)->right = sentinel;
//		std::cout << "adding node" << std::endl;
		this->_size++;
		return (*start);
//	}
/*	else if (comp(p.first, (*r)->content->first))
//	else if (p.first < (*r)->content->first)
		return (this->insertFromRoot(p, &(*r)->left, *r));
	else if (p.first == (*r)->content->first)
		return (*r);
	return (this->insertFromRoot(p, &(*r)->right, *r));
	*/
}

}//end of ft namespace

#endif
