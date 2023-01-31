#include "BSTree.hpp"

int main()
{
	ft::BSTree *tree;

	tree = new ft::BSTree();
	tree->insert(8);	
	tree->insert(5);	
	tree->insert(3);	
	tree->insert(11);	
	tree->insert(-2);
	tree->insert(7);	
	tree->insert(10);	
	tree->insert(9);	
	tree->insert(4);	
	tree->insert(1);	
	tree->insert(-1);	
	tree->insert(6);	
	tree->insert(12);	
	tree->insert(-7);
//	tree->del(-1);
//	tree->del(1);
//	tree->del(3);
	//tree->del(-2);
//	tree->del(6);
//	tree->del(12);
//	tree->del(9);
//	tree->del(5);
//	tree->del(-1);
	tree->del(8);
//	tree->del(3);

	delete tree;

}
