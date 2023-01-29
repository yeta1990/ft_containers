#include <iostream>

namespace ft{

class Node;

class Node{
	public:
		int value;
		Node *left;
		Node *right;
};

class BSTree{
	public:
		BSTree(){ this->root = NULL;}
		void	insert(int value);
		void	del(int value);
		~BSTree();

	private:
		Node	*createNode(int val)
		{
			Node* n;
			n = new Node();
			n->value = val;
			n->left = NULL;
			n->right= NULL;

			return (n);
		}

		void insertFromRoot(int value, Node **root);
		void freeTree(Node *root);
		Node	*root;
		Node*	getNextLowestNode(Node *node);
		Node*	findNode(int value, Node *prev, Node *parent);
};

void	BSTree::del(int value)
{
	Node	*parent;
	Node	*found;
	Node	*next;

	parent = NULL;
	found = findNode(value, this->root, parent);
	if (!found)
		return ;	
	next = getNextLowestNode(found);
}

Node*	BSTree::getNextLowestNode(Node *node)
{
	if (!node->left && node->right)
		return (node->right);
	else if (node->left && !node->right)
		return (node->left);
	else if (node->left->value < node->right->value)
		return (node->left);
	else if (node->right)
		return (node->right);
	return (NULL);
}

Node*	BSTree::findNode(int value, Node *node, Node *parent)
{
	if (node->left && node->left->value == value)
	{
		parent = node;
		return (node->left);
	}
	else if (node->left && node->right->value == value)
	{
		parent = node;
		return (node->right);
	}
	else if (node->left)
		return (findNode(value, node->left, node));
	else if (node->right)
		return (findNode(value, node->right, node));
	return (NULL);
}

BSTree::~BSTree()
{
	this->freeTree(this->root);
}

void BSTree::freeTree(Node *root)
{
	if (root->left)
		freeTree(root->left);
	if (root->right)
		freeTree(root->right);	
	std::cout << root->value << std::endl;
	delete root;
	root = NULL;
}

void	BSTree::insert(int value)
{
	std::cout << "inserting " << value << std::endl;
	this->insertFromRoot(value, &(this->root));
}

void	BSTree::insertFromRoot(int value, Node **root)
{
	if (*root == NULL)
		*root = createNode(value);
	else if (value <= (*root)->value)
	{
		std::cout << " left " << (*root)->value << std::endl;
		this->insertFromRoot(value, &((*root)->left));
	}
	else
	{
		std::cout << " right " << (*root)->value << std::endl;
		this->insertFromRoot(value, &((*root)->right));
	}
	
}

}//end of ft namespace

int main()
{
	ft::BSTree *tree;

	tree = new ft::BSTree();
	tree->insert(8);	
	tree->insert(5);	
	tree->insert(4);	
	tree->insert(11);	
	tree->insert(-2);
	tree->insert(3);	
	tree->insert(7);	
	tree->insert(10);	
	tree->insert(9);	
	tree->insert(1);	
	tree->insert(-1);	
	tree->insert(6);	
	tree->insert(12);	
	

	delete tree;

}
