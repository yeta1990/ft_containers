#ifndef BSTREE_HPP
# define BSTREE_HPP

#include <iostream>
#include "tree_iterator.hpp"

namespace ft{

template <class T1, class T2>
class BSTree;

template <class T1, class T2>
class Node
{
	public:
		typedef pair<const T1, T2>	value_type;

		Node() : content(), key(content.first), value(content.second), left(NULL), right(NULL), parent(NULL), my_tree(NULL), sentinel(NULL) { }
		Node(ft::pair<T1,T2> p, Node* parent, ft::BSTree<T1, T2> *tree, Node* sentinel) : content(p), key(content.first), value(content.second), left(NULL), right(NULL), parent(parent), my_tree(tree), sentinel(sentinel) {	};

		value_type	content;
		const T1&		key;
		T2&				value;
		Node			*left;
		Node			*right;
		Node			*parent;
		BSTree<T1, T2>	*my_tree;
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

template <class T1, class T2>
class BSTree{

	public:
		typedef Node<T1, T2>			node;
		typedef BSTree<T1, T2>			tree;
		typedef pair<const T1, T2>		value_type;
		typedef tree_iterator<node*>	iterator;

		BSTree() : sentinel(new Node<T1, T2>(value_type(), NULL, this, NULL)), root(NULL), _size(0) { sentinel->sentinel = sentinel; };
		~BSTree();
		node	*insert(ft::pair<T1,T2> p);

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

		void	del(T1 key);
		size_t	size() const;
		node	*find(T1 key);

		node	*getHighestNodeFrom(node *node)
		{
			Node<T1, T2>* aux = NULL;

			aux = node;
			while (aux && aux->right && aux->right!= sentinel)
				aux = aux->right;
			return (aux);
		}

		node	*getLowestNodeFrom(node* node)
		{
			Node<T1, T2>* aux = NULL;

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

		node			*insertFromRoot(ft::pair<T1, T2> p, Node<T1, T2> **r, Node<T1, T2> *parent);
		node			*del(T1 key, node *root);
		void			freeTree(node *root);
		node			*getMaxNode(node *node);
		node			*findNode(T1 key, node *node);

		bool insert_has_good_hint(iterator position, const value_type& val)
		{
			node*	parent;
			node*	current;
			
			current = *position.base();
			parent = current->parent;
			while (parent)
			{
				if (parent->key < current->key && parent->key > val.first)
					return (false);
				else if (parent->key > current->key && parent->key < val.first)
					return (false);
				current = parent;
				parent = parent->parent;
			}
			return (true);
		}

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
}


template <class T1, class T2>
BSTree<T1, T2>::~BSTree()
{
	this->freeTree(this->root);
	delete sentinel;
}

template <class T1, class T2>
void BSTree<T1, T2>::freeTree(node *root)
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

template <class T1, class T2>
typename BSTree<T1, T2>::node*	BSTree<T1, T2>::insert(ft::pair<T1,T2> p)
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

template <class T1, class T2>
typename BSTree<T1, T2>::node*	BSTree<T1, T2>::insertFromRoot(ft::pair<T1, T2> p, Node<T1, T2> **r, Node<T1, T2> *parent)
{
	/*
	 * if (*r == NULL && !parent)
	{
		*r = new Node<T1, T2>(p, sentinel, this);
		sentinel->right = *r;
//		std::cout << "adding sentinel" << std::endl;
		this->_size++;
		return (*r);
	}
	*/
	if (*r == NULL || *r == sentinel)
	{
		if (!parent)
		{
			sentinel->right = *r;
			parent = sentinel;
		}
		*r = new Node<T1, T2>(p, parent, this, sentinel);
		(*r)->left = sentinel;
		(*r)->right = sentinel;
//		std::cout << "adding node" << std::endl;
		this->_size++;
		return (*r);
	}
	else if (p.first < (*r)->key)
		return (this->insertFromRoot(p, &(*r)->left, *r));
	else if (p.first == (*r)->key)
		return (*r);
	return (this->insertFromRoot(p, &(*r)->right, *r));
}

}//end of ft namespace

#endif
