#ifndef BSTREE_HPP
# define BSTREE_HPP

#include <iostream>
#include "tree_iterator.hpp"

namespace ft{

template <class T>
class BSTree;

template <class P>
class Node
{
	public:
//		typedef pair<const T1, T2>	value_type;
		typedef P	value_type;

		Node() : content(NULL), left(NULL), right(NULL), parent(NULL), my_tree(NULL), sentinel(NULL) { }
//		Node() : content(), key(content->first), value(content.second), left(NULL), right(NULL), parent(NULL), my_tree(NULL), sentinel(NULL) { }
		Node(value_type *p, Node* parent, ft::BSTree<P> *tree, Node* sentinel) : content(p), left(NULL), right(NULL), parent(parent), my_tree(tree), sentinel(sentinel) {	};
//		Node(ft::pair<T1,T2> p, Node* parent, ft::BSTree<T1, T2> *tree, Node* sentinel) : content(p), key(content->first), value(content.second), left(NULL), right(NULL), parent(parent), my_tree(tree), sentinel(sentinel) {	};
		~Node()
		{
			delete content;
		}
		value_type		*content;
//		const T1&		key;
//		T2&				value;
		Node			*left;
		Node			*right;
		Node			*parent;
		BSTree<P>		*my_tree;
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
			*this = o;
			return (*this);
		}

		Node& operator=( const Node& other )
		{
			this->right = other.right();
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

template <class T>
class BSTree{

	public:
		typedef Node<T>			node;
		typedef BSTree<T>			tree;
		typedef T				value_type;
//		typedef pair<const T1, T2>		value_type;
		typedef tree_iterator<node*>	iterator;

		BSTree() : sentinel(new Node<T>(new value_type(), NULL, this, NULL)), root(NULL), _size(0) { sentinel->sentinel = sentinel; };
		~BSTree();
		node	*insert(value_type p);

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
			if (!root)
				return (insertFromRoot(val, position.base(), NULL));
			if (insert_has_good_hint(position, val))
			{
				if (val.first > (*position).first)
					return (this->insertFromRoot(val, &((*position.base())->right), *(position.base())));
				return (this->insertFromRoot(val, &((*position.base())->left), *(position.base())));
			}
			return (insertFromRoot(val, &root, NULL));
		}

		void	del(typename value_type::first_type key);
		bool	deleteKeyFrom(typename value_type::first_type key, node *node);
		size_t	size() const;
		node	*find(typename value_type::first_type key);

		node	*getHighestNodeFrom(node *node)
		{
			Node<T>* aux = NULL;

			aux = node;
			while (aux && aux->right && aux->right!= sentinel)
				aux = aux->right;
			return (aux);
		}

		node	*getLowestNodeFrom(node* node)
		{
			Node<T>* aux = NULL;

			aux = node;
			while (aux && aux->left && aux->left != sentinel)
				aux = aux->left;
			return (aux);
		};

		node	*getHighestNode()
		{
			return (getHighestNodeFrom(root));
		}
		node	*getLowestNode()
		{
			return (getLowestNodeFrom(root));
		}

		node	*getSentinel()
		{
			return (sentinel);
		}
		
//		node	*get

		//remove it before evaluation
//		node*	base() { return root; };

	private:
		node			*sentinel;
		node			*root;
		size_t			_size;

		node			*insertFromRoot(value_type p, Node<T> **r, Node<T> *parent);
		node			*del(typename value_type::first_type key, node *root);
		void			freeTree(node *root);
		node			*getMaxNode(node *node);
		node			*findNode(typename value_type::first_type key, node *node);

		bool insert_has_good_hint(iterator position, const value_type& val)
		{
			node*	parent;
			node*	current;
			
			current = *position.base();
			parent = current->parent;
			while (parent)
			{
				if (parent->content->first < current->content->first && parent->content->first > val.first)
					return (false);
				else if (parent->content->first > current->content->first && parent->content->first < val.first)
					return (false);
				current = parent;
				parent = parent->parent;
			}
			return (true);
		}

		//currently unused:
		size_t			count_nodes(const Node<T> *root) const;
};

template <class T>
void	BSTree<T>::del(typename T::first_type key)
{
	this->del(key, root);
}

template <class T>
typename BSTree<T>::node*	BSTree<T>::find(typename T::first_type key)
{
	return (this->findNode(key, this->root));
}

template <class T>
bool	BSTree<T>::deleteKeyFrom(typename T::first_type key, node *node)
{
	size_t	old_size;

	old_size = this->_size;
	del(key, node);
	return (old_size - _size);
}

template <class T>
typename BSTree<T>::node*	BSTree<T>::del(typename T::first_type key, node *node)
{
	typedef typename BSTree<T>::node n;
	n	*maxNode;
//	node	*aux;
	n	*child;

	child = NULL;
//	aux = NULL;
	maxNode = NULL;
	if (node == NULL)
		return (node);
	else if (key < node->content->first && node != sentinel)
		node->left = del(key, node->left);
	else if (key > node->content->first && node != sentinel)
		node->right = del(key, node->right);
	else if (key == node->content->first)//found
	{
		std::cout << "found node: " << node->content->first << std::endl;
//		std::cout << node->right << std::endl;
		if (node->left == sentinel && node->right == sentinel)
//		if (!node->hasAnyChild() || (node->left == sentinel && node->right == sentinel))
		{
			std::cout << "hasnt any child, " << node->content->first << std::endl;
			this->_size--;
		/*	if (node == root)
				node->parent->right = NULL;
			else if (node == node->parent->left)
				node->parent->left = sentinel;
			else
				node->parent->right = sentinel;
			if (node == root)
				root = NULL;
//			if (node != sentinel) //doesn't seem necessary at all
				delete node; 
//			node = NULL;
			if (root)
				node = sentinel;
				*/
			delete node;
			node = NULL;
		}
		else if (node->hasTwoChildren() && node->left != sentinel && node->right != sentinel)
		{
			std::cout << "has two children " << node->content->first << std::endl;
//			std::cout << node->left->content->first << "," << node->right->content->first << std::endl;
//			n*	copy_max_node;
//			n*	old_node;
			value_type	*old_content;	
//			old_node = node;
			maxNode = this->getMaxNode(node->left);
			old_content = node->content;
			node->content = maxNode->content;
			delete old_content;
//			copy_max_node = new Node<T>(new value_type(*maxNode->content), node->parent, this, sentinel);
//			copy_max_node->left = node->left;
//			copy_max_node->right = node->right;
//			if (node == node->parent->left)
//				node->parent->left = copy_max_node;
//			else
//				node->parent->right = copy_max_node;

//			node->content = maxNode->content;
			node->left = del(maxNode->content->first, node->left);
//			delete old_node;
//			if (node == root)
//				root = copy_max_node;
//			delete node;
		}
		else if ((child = node->hasOneChild())) // go left
		{
			n*	aux;

			std::cout << "has one child" << std::endl;
			aux = node;
			node = child;
			/*
			if (node == node->parent->left)
				node->parent->left = child;
			else
				node->parent->right = child;
			child->parent = node->parent;
			if (node == root)
				root = child;
			delete node;
			node = child;
			*/
			
			this->_size--;
			delete aux;
		}
		return (node);
	}
	return (node);
}



template <class T>
typename BSTree<T>::node*	BSTree<T>::getMaxNode(Node<T> *node)
{
	if (node->right && node->right != sentinel)
		return (getMaxNode(node->right));
	return (node);
}

template <class T>
typename BSTree<T>::node*	BSTree<T>::findNode(typename T::first_type key, Node<T> *node)
{
	if (node && node->content->first == key)
	{
//		std::cout << "found " << key << std::endl;
		return (node);
	}
	else if (node && node->left && node->left != sentinel && key <= node->content->first)
		return (findNode(key, node->left));
	else if (node && node->right && node->right != sentinel && key >= node->content->first)
		return (findNode(key, node->right));
	return (sentinel);
}

template <class T>
size_t	BSTree<T>::count_nodes(const Node<T> *root) const
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

template <class T>
size_t	BSTree<T>::size() const
{
	return (this->_size);
}

template <class T>
BSTree<T>::~BSTree()
{
	this->freeTree(this->root);
	delete sentinel;
}

template <class T>
void BSTree<T>::freeTree(node *root)
{
	if (!root)
		return;
	if (root->left && root->left != sentinel)
		freeTree(root->left);
	if (root->right && root->right != sentinel)
		freeTree(root->right);	
//	std::cout << root->key << std::endl;
	delete root;
	root = NULL;
}

template <class T>
typename BSTree<T>::node*	BSTree<T>::insert(typename BSTree<T>::value_type p)
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

template <class T>
typename BSTree<T>::node*	BSTree<T>::insertFromRoot(typename BSTree<T>::value_type p, Node<T> **r, Node<T> *parent)
{
	if (*r == NULL || *r == sentinel)
	{
		if (!parent)
		{
			sentinel->right = *r;
			parent = sentinel;
		}
		*r = new Node<T>(new value_type(p), parent, this, sentinel);
		(*r)->left = sentinel;
		(*r)->right = sentinel;
//		std::cout << "adding node" << std::endl;
		this->_size++;
		return (*r);
	}
	else if (p.first < (*r)->content->first)
		return (this->insertFromRoot(p, &(*r)->left, *r));
	else if (p.first == (*r)->content->first)
		return (*r);
	return (this->insertFromRoot(p, &(*r)->right, *r));
}

}//end of ft namespace

#endif
