#include <iostream>

namespace ft{

class Node;

class Node{
	public:
		int value;
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

		void	insertFromRoot(int value, Node **root);
		Node	*del(int value, Node *root);
		void	freeTree(Node *root);
		Node	*root;
//		Node*	getNextLowestNode(Node *node);
		Node*	getMaxNode(Node *node);
		Node*	findNode(int value, Node *node);
};

void	BSTree::del(int value)
{
	this->del(value, root);
}

Node	*BSTree::del(int value, Node *root)
{
	Node	*maxNode;
	Node	*aux;
	Node	*child;

	child = NULL;
	aux = NULL;
	maxNode = NULL;
	if (root == NULL)
		return (root);
	else if (value < root->value)
		root->left = del(value, root->left);
	else if (value > root->value)
		root->right = del(value, root->right);
	else //found
	{
		std::cout << "found node: " << root->value << std::endl;
		if (!root->hasAnyChild())
		{
			std::cout << "hasnt any child" << std::endl;
			delete root;
			root = NULL;
		}
		else if ((child = root->hasOneChild())) // go left
		{
			std::cout << "has one child" << std::endl;
			aux = root;
			root = child;
			delete aux;
		}
		else if (root->hasTwoChildren())
		{
			maxNode = this->getMaxNode(root->right);
			root->value = maxNode->value;
			root->right = del(maxNode->value, root->right);
			delete maxNode;
		}
		return (root);

	}
	return (root);
/*
	found = findNode(value, this->root);
	maxNode = NULL;
	child = NULL;
	if (!found)
		return ;

	std::cout << "found node: " << found->value << std::endl;
	std::cout << "max next node is: " << getMaxNode(found)->value << std::endl;
	if (!found->hasAnyChild()) //if hasn't children-> delete and = NULL
	{
		std::cout << "hasnt any child" << std::endl;
//		delete found;
		found = NULL;
	}
	else if ((child = found->hasOneChild()))
	{
		std::cout << "has one child" << std::endl;
		found->value = child->value;
		delete child;
		child = NULL;
	}
	else if (found->hasTwoChildren())
	{
		std::cout << "has two children" << std::endl;
		maxNode = getMaxNode(found);
		found->value = maxNode->value;
		delete maxNode;
		maxNode = NULL;
	}

	//if has one child -> copy child and delete child
	//if has two children -> find max value, copy and delete
//	next = getNextLowestNode(found);
*/
}

Node*	BSTree::getMaxNode(Node *node)
{
	if (node->right)
		return (getMaxNode(node->right));
	return (node);
}

Node*	BSTree::findNode(int value, Node *node)
{
	if (node->value == value)
		return (node);
	else if (node->left && value <= node->value)
		return (findNode(value, node->left));
	else if (node->right && value >= node->value)
		return (findNode(value, node->right));
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
	tree->insert(-7);
	
//	tree->del(-1);
//	tree->del(1);
	tree->del(3);
	tree->del(2);
//	tree->del(6);
//	tree->del(12);
//	tree->del(9);
//	tree->del(-1);
//	tree->del(8);

	delete tree;

}
