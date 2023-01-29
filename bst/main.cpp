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
		void insert(int value);
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
};

BSTree::~BSTree()
{
	//this->freeTree(this->root);
}

void BSTree::freeTree(Node *root)
{
	//std::cout << "eooo" << std::endl;
	if (root)
		std::cout << root->value << std::endl;
	if (root->left)
	{
		freeTree(root->left);
		root->left = NULL;
	}
	if (root->right)
	{
		freeTree(root->right);	
		root->right = NULL;
	}
	delete root;
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
	tree->insert(2);
	tree->insert(3);	
	tree->insert(7);	
	tree->insert(10);	
	tree->insert(9);	
	

	delete tree;

}
