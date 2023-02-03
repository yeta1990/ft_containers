#ifndef BSTREE_HPP
# define BSTREE_HPP

#include <iostream>
#include "tree_iterator.hpp"

namespace ft{

template <class T1, class T2>
class Node{
	public:
		typedef pair<const T1, T2>	value_type;

		Node() : content(), key(content.first), value(content.second), left(NULL), right(NULL)	{	}
		Node(ft::pair<T1,T2> p) : content(p), key(content.first), value(content.second), left(NULL), right(NULL)	
		{
//			key = p.first;
//			value = p.second;
//			left = NULL;
//			right = NULL;
		};
		value_type	content;
		const T1&		key;
		T2&		value;
		Node	*left;
		Node	*right;

		bool	hasAnyChild()
		{
			return (left || right);
		}
		Node	*hasOneChild()
		{
			if (left)
				return (left);
			else if (right)
				return (right);
			return (NULL);
		}
		bool	hasTwoChildren()
		{
			return (left && right);
		}
};

template <class T1, class T2>
class BSTree{

	public:
		typedef Node<T1, T2>		node;
		typedef BSTree<T1, T2>		tree;
		typedef pair<const T1, T2>	value_type;
		typedef tree_iterator<node*>	iterator;

		BSTree() : root(NULL), _size(0) { }
		~BSTree();
		node	*insert(ft::pair<T1,T2> p);

		node	*insert(iterator position, const value_type& val)
		{
//			std::cout << "inserting after " << (*position).first << "," <<
//				val.first << std::endl;
//			std::cout << "inserting " << (*position).first << std::endl;
//			return new node;
		
	if (!root)
		return (insertFromRoot(val, &root));
	else if ((*position).first < root->key && val.first > root->key)
	{
		std::cout << "no" << std::endl;
		return (insertFromRoot(val, &root));
	}
	else if ((*position).first > root->key && val.first < root->key)
	{
		std::cout << "no2" << std::endl;
		return (insertFromRoot(val, &root));
	}
//	node** n = position.base();
	std::cout << "yes" << std::endl;
	return (insertFromRoot(val, position.base()));
//	return new node;
		}
		void	del(T1 key);
		size_t	size() const;
		node	*find(T1 key);

	private:
		node			*root;
		size_t			_size;

		node			*insertFromRoot(ft::pair<T1, T2> p, Node<T1, T2> **r);
		node			*del(T1 key, node *root);
		void			freeTree(node *root);
		node			*getMaxNode(node *node);
		node			*findNode(T1 key, node *node);

		//currently unused:
		size_t			count_nodes(const Node<T1, T2> *root) const;
};

template <class T1, class T2>
void	BSTree<T1, T2>::del(T1 key)
{
	this->del(key, root);
}

template <class T1, class T2>
typename BSTree<T1, T2>::node*	BSTree<T1, T2>::find(T1 key)
{
	return (this->findNode(key, this->root));
}

template <class T1, class T2>
typename BSTree<T1, T2>::node*	BSTree<T1, T2>::del(T1 key, node *root)
{
	typedef typename BSTree<T1, T2>::node node;
	node	*maxNode;
	node	*aux;
	node	*child;

	child = NULL;
	aux = NULL;
	maxNode = NULL;
	if (root == NULL)
		return (root);
	else if (key < root->key)
		root->left = del(key, root->left);
	else if (key > root->key)
		root->right = del(key, root->right);
	else //found
	{
//		std::cout << "found node: " << root->value << std::endl;
		if (!root->hasAnyChild())
		{
//			std::cout << "hasnt any child" << std::endl;
			this->_size--;
			delete root;
			root = NULL;
		}
		else if (root->hasTwoChildren())
		{
//			std::cout << "has two children" << std::endl;
			maxNode = this->getMaxNode(root->left);
			root->key = maxNode->key;
			root->left = del(maxNode->key, root->left);
		}
		else if ((child = root->hasOneChild())) // go left
		{
//			std::cout << "has one child" << std::endl;
			aux = root;
			root = child;
			this->_size--;
			delete aux;
		}
		return (root);
	}
	return (root);
}


template <class T1, class T2>
typename BSTree<T1, T2>::node*	BSTree<T1, T2>::getMaxNode(Node<T1, T2> *node)
{
	if (node->right)
		return (getMaxNode(node->right));
	return (node);
}

template <class T1, class T2>
typename BSTree<T1, T2>::node*	BSTree<T1, T2>::findNode(T1 key, Node<T1, T2> *node)
{
	if (node && node->key == key)
		return (node);
	else if (node && node->left && key <= node->key)
		return (findNode(key, node->left));
	else if (node && node->right && key >= node->key)
		return (findNode(key, node->right));
	return (NULL);
}

template <class T1, class T2>
size_t	BSTree<T1, T2>::count_nodes(const Node<T1, T2> *root) const
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

template <class T1, class T2>
size_t	BSTree<T1, T2>::size() const
{
	return (this->_size);
//	if (!root)
//		return (0);
//	return (count_nodes(root));
}


template <class T1, class T2>
BSTree<T1, T2>::~BSTree()
{
	this->freeTree(this->root);
}

template <class T1, class T2>
void BSTree<T1, T2>::freeTree(node *root)
{
	if (!root)
		return;
	if (root->left)
		freeTree(root->left);
	if (root->right)
		freeTree(root->right);	
	std::cout << root->key << std::endl;
	delete root;
	root = NULL;
}

template <class T1, class T2>
typename BSTree<T1, T2>::node*	BSTree<T1, T2>::insert(ft::pair<T1,T2> p)
{
//	std::cout << "inserting " << p.second << " in " << p.first << std::endl;
	return (this->insertFromRoot(p, &(this->root)));
//	std::cout << node->value << std::endl;
}
/*
template <class T1, class T2>
typename BSTree<T1, T2>::node*	BSTree<T1, T2>::insert(tree_iterator<typename BSTree<T1, T2>::node* >::iterator position, const ft::pair<T1, T2>& val)
{
	//if position < root && new > root -> wrong position given -> normal insert instead
	// position > root && new < root ->wrong position
	if (!root || !(*root) || !position || *position)
		return (insertFromRoot(val, &root));
	else if (*position->first < (*root).key && val.first > (*root).key)
		return (insertFromRoot(val, &root));
	else if (*position->first > (*root).key && val.first < (*root).key)
		return (insertFromRoot(val, &root));
	return (insertFromRoot(val, *position));
}
*/
template <class T1, class T2>
typename BSTree<T1, T2>::node*	BSTree<T1, T2>::insertFromRoot(ft::pair<T1, T2> p, Node<T1, T2> **r)
{
	if (*r == NULL)
	{
		*r = new Node<T1, T2>(p);
		this->_size++;
		return (*r);
	}
	else if (p.first < (*r)->key)
		return (this->insertFromRoot(p, &(*r)->left));
	else if (p.first == (*r)->key)
		return (*r);
	return (this->insertFromRoot(p, &((*r)->right)));
}

}//end of ft namespace

#endif
