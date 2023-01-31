#ifndef BSTREE_HPP
# define BSTREE_HPP

#include <iostream>

namespace ft{

template <class T1, class T2>
class Node{
	public:
		Node()
		{
			left = NULL;
			right= NULL;
		}
		Node(ft::pair<T1,T2> p) : key(p.first), value(p.second), left(NULL), right(NULL)	{
//			key = p.first;
//			value = p.second;
//			left = NULL;
//			right = NULL;
		};
		T1		key;
		T2		value;
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
		typedef Node<T1, T2> node;
		typedef BSTree<T1, T2> tree;

		BSTree(){ this->root = NULL;}
		~BSTree();
		void	insert(ft::pair<T1,T2> p);
		void	del(T1 key);
		size_t	size() const;
		node	*find(T1 key);

	private:
		void			insertFromRoot(ft::pair<T1, T2> p, Node<T1, T2> **root);
		node			*del(T1 key, node *root);
		void			freeTree(node *root);
		node			*root;
		node			*getMaxNode(node *node);
		node			*findNode(T1 key, node *node);
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
	if (node->key == key)
		return (node);
	else if (node->left && key <= node->key)
		return (findNode(key, node->left));
	else if (node->right && key >= node->key)
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
	if (!root)
		return (0);
	return (count_nodes(root));
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
//	std::cout << root->value << std::endl;
	delete root;
	root = NULL;
}

template <class T1, class T2>
void	BSTree<T1, T2>::insert(ft::pair<T1,T2> p)
{
//	std::cout << "inserting " << p.second << " in " << p.first << std::endl;
	this->insertFromRoot(p, &(this->root));
}

template <class T1, class T2>
void	BSTree<T1, T2>::insertFromRoot(ft::pair<T1, T2> p, Node<T1, T2> **root)
{
	if (*root == NULL)
		*root = new Node<T1, T2>(p);
	else if (p.first<= (*root)->key)
		this->insertFromRoot(p, &((*root)->left));
	else
		this->insertFromRoot(p, &((*root)->right));
}

}//end of ft namespace

#endif
