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
	for (size_t i = 0; i < 12; i++)
		check(map[i] == map1[i]);
	check(map[111] == map1[111]);

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
	ft::Node<char, int> n(*it2);
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
	std::map<char,int> map;
	std::pair<std::map<char,int>::iterator,bool> ret;
	ret = map.insert( std::make_pair('c', 2) );
	map.insert( std::make_pair('d', 2) );
	map.insert( std::make_pair('a', 2) );
	map.insert( std::make_pair('x', 2) );

	ft::map<char,int> map1;
	ft::pair<ft::map<char,int>::iterator,bool> ret1;
	map1.insert( ft::make_pair('c', 2) );
	map1.insert( ft::make_pair('d', 2) );
	map1.insert( ft::make_pair('a', 2) );

	ret1 = map1.insert( ft::make_pair('x', 2) );
	map1.insert(ret1.first, ft::make_pair('y', 2));
	
	
}

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


void map_tests()
{
//	test_case("map_constructors", &map_constructor);
	test_case("operator[]", &operator_access);
//	test_case("map at", &map_at);
//	test_case("map at const", &map_const_at);
//	test_case("map insert", &map_insert);
//	test_case("map insert iterator", &map_insert_iterator);
//	test_case("map insert iterator2", &map_insert_iterator2);
//	test_case("map insert playground", &map_insert_playground);
}

