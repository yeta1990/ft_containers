#include "tests.hpp"
#include "map.hpp"
#include <string>
#include <map>

void	map_constructor()
{
	std::map<int,int> map;
	ft::map<int,int> map1;
	
	check(map.size() == map1.size());
	check(map.empty() == map1.empty());
	
	map.insert( std::pair<int, int>(8, 8) );
	map1.insert( ft::pair<int, int>(8, 8) );
	check(map.size() == map1.size());
	check(map.empty() == map1.empty());

	map.insert( std::pair<int, int>(5, 5) );
	map1.insert( ft::pair<int, int>(5, 5) );
	check(map.size() == map1.size());

	map.insert( std::pair<int, int>(11, 11) );
	map1.insert( ft::pair<int, int>(11, 11) );
	check(map.size() == map1.size());

	map.insert( std::pair<int, int>(-2, -2) );
	map1.insert( ft::pair<int, int>(-2, -2) );
	check(map.size() == map1.size());

	map.insert( std::pair<int, int>(7, 7) );
	map1.insert( ft::pair<int, int>(7, 7) );
	check(map.size() == map1.size());

	map.insert( std::pair<int, int>(10, 10) );
	map1.insert( ft::pair<int, int>(10, 10) );
	check(map.size() == map1.size());
	

/*	map.insert(10, 10);
	map.insert(9, 9);
	map.insert(4, 4);
	map.insert(1, 1);
	map.insert(-1, -1);	
	map.insert(6, 6);
	map.insert(12, 12);	
	map.insert(-7, -7); 
*/

	/*
	map1.insert(3, 3);
	map1.insert(11, 11);
	map1.insert(-2, -2);
	map1.insert(7, 7);
	map1.insert(10, 10);
	map1.insert(9, 9);
	map1.insert(4, 4);	
	map1.insert(1, 1);
	map1.insert(-1, -1);
	map1.insert(6, 6);
	map1.insert(12, 12);
	map1.insert(-7, -7);
	*/

	
//	std::cout << "size: " << map.size() << std::endl;

}

void	operator_access()
{
	std::map<int,int> map;
	ft::map<int,int> map1;
	
	for (size_t i = 0; i < 12; i++)
	{
		map.insert( std::pair<int, int>(i, i) );
		map1.insert( ft::pair<int, int>(i, i) );
	}
	for (size_t i = 0; i < 1; i++)
		check(map[i] == map1[i]);
//	check(map[111] == map1[111]);

//	std::cout << map1[1] << std::endl;

}

void	map_at()
{
	std::map<int,int> map;
	ft::map<int,int> map1;
	
	for (size_t i = 0; i < 12; i++)
	{
		map.insert( std::pair<int, int>(i, i) );
		map1.insert( ft::pair<int, int>(i, i) );
	}
	for (size_t i = 0; i < 12; i++)
		check(map.at(i) == map1.at(i));
	bool	ex1 = false;
	bool 	ex2 = false;

	try
	{
		map.at(101);
	}
	catch (std::exception &e)
	{
		ex1 = true;
	}
	try
	{
		map1.at(101);
	}
	catch (std::exception &e)
	{
		ex2 = true;
	}
	check(ex1 == ex2);
}

void	map_const_at()
{
	std::map<const int,int> map;
	ft::map<const int,int> map1;
	
	for (size_t i = 0; i < 12; i++)
	{
		map.insert( std::pair<int, int>(i, i) );
		map1.insert( ft::pair<int, int>(i, i) );
	}
	for (size_t i = 0; i < 12; i++)
		check(map.at(i) == map1.at(i));
	bool	ex1 = false;
	bool 	ex2 = false;

	try
	{
		map.at(101);
	}
	catch (std::exception &e)
	{
		ex1 = true;
	}
	try
	{
		map1.at(101);
	}
	catch (std::exception &e)
	{
		ex2 = true;
	}
//	std::cout << ex1 << "," << ex2 << std::endl;
	check(ex1 == ex2);
}

void	map_insert()
{
	std::map<char,int> map;
	ft::map<char,int> map1;
	std::pair<std::map<char,int>::iterator,bool> ret;
	ft::pair<ft::map<char,int>::iterator,bool> ret1;

	ret = map.insert( std::pair<int, int>('c', 1) );
	ret1 = map1.insert( ft::pair<char, int>('c', 1) );
	check (ret.second == ret1.second);

	ret = map.insert( std::pair<int, int>('c', 1) );
	ret1 = map1.insert( ft::pair<char, int>('c', 1) );
	check (ret.second == ret1.second);
//	std::cout << ret.second << "," << ret1.second << std::endl;

}

void	map_insert_iterator()
{
	std::map<char,int> map;
	std::pair<std::map<char,int>::iterator,bool> ret;
	ret = map.insert( std::make_pair('c', 2) );
	map.insert( std::make_pair('d', 2) );
	map.insert( std::make_pair('a', 2) );
	map.insert( std::make_pair('x', 2) );

	ft::map<char,int> map1;
	ft::pair<ft::map<char,int>::iterator,bool> ret1;
	ret1 = map1.insert( ft::make_pair('c', 2) );

	std::map<char,int>::iterator it1(ret.first);

	ft::map<char,int>::iterator it2(ret1.first);
//	std::cout << (*it2).first << std::endl;
	check((*it1).first == (*it2).first);
//	ft::Node<char, int> n(*it2);
//	std::cout << n.key << std::endl;
//	std::cout << (*it2).first << std::endl;
//	std::cout << (*(ret.first)).first << std::endl;
	check((*(ret.first)).first == (*(ret1.first)).first);

	ret = map.insert( std::make_pair('d', 2) );
	ret1 = map1.insert( ft::make_pair('d', 2) );
	check((*(ret.first)).first == (*(ret1.first)).first);
}

void	map_insert_iterator2()
{
//	std::map<int,int> map;
//	std::pair<std::map<int,int>::iterator,bool> ret;
//	ret = map.insert( std::make_pair(, 2) );
//	map.insert( std::make_pair('d', 2) );
//	map.insert( std::make_pair('a', 2) );
//	map.insert( std::make_pair('x', 2) );

	ft::map<int,int> map1;
	ft::pair<ft::map<int,int>::iterator,bool> ret1;
	map1.insert( ft::make_pair(15, 2) );
	map1.insert( ft::make_pair(7, 2) );
	map1.insert( ft::make_pair(30, 2) );
	map1.insert( ft::make_pair(1, 2) );
	map1.insert( ft::make_pair(11, 2) );
	ret1 = map1.insert( ft::make_pair(5, 2) );
//	map1.insert( ft::make_pair(6, 2) );
	ft::pair<ft::map<int,int>::iterator,bool> ret3;
//	ret3 = map1.insert( ft::make_pair(3, 2) );
	map1.insert( ft::make_pair(20, 2) );
	map1.insert( ft::make_pair(17, 2) );
//	map1.insert( ft::make_pair(5, 2) );

//	ret1 = map1.insert( ft::make_pair('x', 2) );
	ft::pair<ft::map<int,int>::iterator,bool> ret2;

	map1.insert(ret1.first, ft::make_pair(25, 2));
	map1.insert(ret1.first, ft::make_pair(6, 2));
	ret2 = map1.insert( ft::make_pair(24, 2) );
	map1.insert(ret1.first, ft::make_pair(-3, 2));
	
	
}

ft::map<int, int> create_map()
{
	ft::map<int,int> map1;
	map1.insert( ft::pair<int, int>(8, 8) );
	map1.insert( ft::pair<int, int>(5, 5) );
	map1.insert( ft::pair<int, int>(11, 11) );
	map1.insert( ft::pair<int, int>(-2, -2) );
	map1.insert( ft::pair<int, int>(6, 6) );
	map1.insert( ft::pair<int, int>(10, 10) );
	map1.insert( ft::pair<int, int>(9, 9) );
	map1.insert( ft::pair<int, int>(-10, -10) );
	map1.insert( ft::pair<int, int>(1, 1) );
	map1.insert( ft::pair<int, int>(4, 4) );
	return (map1);
}


std::map<int, int> create_std_map()
{
	std::map<int,int> map1;
	map1.insert( std::pair<int, int>(8, 8) );
	map1.insert( std::pair<int, int>(5, 5) );
	map1.insert( std::pair<int, int>(11, 11) );
	map1.insert( std::pair<int, int>(-2, -2) );
	map1.insert( std::pair<int, int>(6, 6) );
	map1.insert( std::pair<int, int>(10, 10) );
	map1.insert( std::pair<int, int>(9, 9) );
	map1.insert( std::pair<int, int>(-10, -10) );
	map1.insert( std::pair<int, int>(1, 1) );
	map1.insert( std::pair<int, int>(4, 4) );
	return (map1);
}

void	map_parent_navigation()
{
	ft::map<int,int> map1 = create_map();
	ft::pair<ft::map<int,int>::iterator,bool> ret1;
	
	ret1 = map1.insert( ft::pair<int, int>(3, 3) );

	ft::BSTree<int, int>::node *n1;
	ft::BSTree<int, int>::node *aux;

	n1 = *(ret1.first.base());
	aux = n1;
	check(aux->key == 3);
	aux = aux->parent;
	check(aux->key == 4);
	aux = aux->parent;
	check(aux->key == 1);
	aux = aux->parent;
	check(aux->key == -2);
	aux = aux->parent;
	check(aux->key == 5);
	aux = aux->parent;
	check(aux->key == 8);

}

// 3 insert with hint tests, inserting:
// -3 in node 4
// ¿-1 in node 4?
// 0 in node 1
// 7 in node 4
// 12 in node 10

void	map_insert_hint1()
{
	ft::map<int,int> map1; // = new ft::map<int,int>();
	ft::pair<ft::map<int,int>::iterator,bool> ret1;

	map1.insert( ft::pair<int, int>(8, 8) );
	map1.insert( ft::pair<int, int>(5, 5) );
	map1.insert( ft::pair<int, int>(11, 11) );
	map1.insert( ft::pair<int, int>(-2, -2) );
	map1.insert( ft::pair<int, int>(6, 6) );
	map1.insert( ft::pair<int, int>(10, 10) );
	map1.insert( ft::pair<int, int>(9, 9) );
	map1.insert( ft::pair<int, int>(-10, -10) );
	map1.insert( ft::pair<int, int>(1, 1) );
	ret1 = map1.insert( ft::pair<int, int>(4, 4) );

	ft::map<int,int>::iterator it1;
	it1 = map1.insert(ret1.first, ft::make_pair(-3, -3));

	ft::BSTree<int, int>::node *n1;
	ft::BSTree<int, int>::node *aux;

	n1 = *it1.base();
	aux = n1;
	check(aux->key == -3);
	aux = aux->parent;
	check(aux->key == -10);
//	std::cout << aux->key << std::endl;
}


void	map_insert_hint2()
{
	ft::map<int,int> map1; // = new ft::map<int,int>();
	ft::pair<ft::map<int,int>::iterator,bool> ret1;
	ft::pair<ft::map<int,int>::iterator,bool> ret2;
	ft::pair<ft::map<int,int>::iterator,bool> ret3;

	map1.insert( ft::pair<int, int>(8, 8) );
	map1.insert( ft::pair<int, int>(5, 5) );
	map1.insert( ft::pair<int, int>(11, 11) );
	map1.insert( ft::pair<int, int>(-2, -2) );
	map1.insert( ft::pair<int, int>(6, 6) );
	map1.insert( ft::pair<int, int>(10, 10) );
	map1.insert( ft::pair<int, int>(9, 9) );
	ret2 = map1.insert( ft::pair<int, int>(-10, -10) );
	map1.insert( ft::pair<int, int>(1, 1) );
	ret1 = map1.insert( ft::pair<int, int>(4, 4) );

	ft::BSTree<int, int>::node *n1;
	ft::BSTree<int, int>::node *aux;
	ft::map<int,int>::iterator it1;

	it1 = map1.insert(ret1.first, ft::make_pair(7, 7));
	n1 = *it1.base();
	aux = n1;
	check(aux->key == 7);
	aux = aux->parent;
	check(aux->key == 6);

	it1 = map1.insert(ret1.first, ft::make_pair(-3, -3));
	n1 = *it1.base();
	aux = n1;
	check(aux->key == -3);
	aux = aux->parent;
	check(aux->key == -10);

	it1 = map1.insert(ret2.first, ft::make_pair(12, 12));
	n1 = *it1.base();
	aux = n1;
	check(aux->key == 12);
	aux = aux->parent;
	check(aux->key == 11);
}

/*
void	map_insert_playground()
{
//	std::map<char,int> map;
//	ft::map<char,int> map1;

//	std::pair<std::map<char,int>::iterator,bool> ret1;
//	std::pair<std::map<char,int>::iterator,bool> ret2;


//	ret1 = map.insert( std::make_pair('d', 1) );
//	ret2 = map.insert( std::make_pair('c', 1) );

//	content = *(ret.first);

	std::cout << std::endl;

	std::map<char,int> map;
	std::pair<std::map<char,int>::iterator,bool> ret;
	ret = map.insert( std::make_pair('c', 2) );
	map.insert( std::make_pair('d', 2) );
	map.insert( std::make_pair('a', 2) );
	map.insert( std::make_pair('x', 2) );

	std::map<char,int>::iterator it = ret.first;
	std::pair<char,int> content = *it;

	std::cout << content.first << std::endl;
	it++;
	content = *it;
	std::cout << content.first << std::endl;
	it++;
	content = *it;
	std::cout << content.first << std::endl;
//	ret1 = map1.insert( ft::<char, int>('c', 1) );

}
*/

void	map_operator_pp()
{
	std::map<int, int> map = create_std_map();
	std::map<int, int>::iterator it;
	ft::map<int, int> map1 = create_map();
	ft::map<int, int>::iterator it1;

	it = map.begin();
	it1 = map1.begin();
	check((*it).first == (*it1).first);
	std::cout << (*it).first << "," << (*it1).first << std::endl;
	it++;
	it1++;
	check((*it).first == (*it1).first);
	std::cout << (*it).first << "," << (*it1).first << std::endl;
	for (size_t i = 0; i < 7; i++)
	{
		it++;
		it1++;
//		std::cout << (*it).first << std::endl;
		check((*it).first == (*it1).first);
		std::cout << (*it).first << "," << (*it1).first << std::endl;
	}
		
//	map.insert(std::make_pair(27, 27));
	std::map<int, int>::iterator it7 = map.end();
//	it7++;
//	it7++;
	std::cout << &*it7 << std::endl << std::endl;

	for (it = map.begin(); it != map.end(); it++)
	{
//		std::cout << &it.ase() << std::endl << std::endl;
		std::cout << (*it).first << std::endl;
	}

//	std::cout << "lowest is " << (*it1).first << std::endl;	

}

void map_tests()
{
	test_case("map_constructors", &map_constructor);
	test_case("operator[]", &operator_access);
	test_case("map at", &map_at);
	test_case("map at const", &map_const_at);
	test_case("map insert", &map_insert);
	test_case("map insert iterator", &map_insert_iterator);
	test_case("map insert iterator2", &map_insert_iterator2);
	test_case("map parent navigation", &map_parent_navigation);
	test_case("map insert hint1", &map_insert_hint1);
	test_case("map insert hint2", &map_insert_hint2);
	test_case("map operator ++", &map_operator_pp);
//	test_case("map insert playground", &map_insert_playground);
}

