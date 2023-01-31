#include "tests.hpp"
#include "map.hpp"
#include <string>
#include <map>

void	map_constructor()
{
	std::map<int,int> map;
	ft::map<int,int> map1;

	map.insert( std::pair<int, int>(8, 8) );
	map1.insert(8, 8);
	check(map.size() == map1.size());
	std::cout << "size: " << map.size() << ", " << map1.size() << std::endl;

	map.insert( std::pair<int, int>(5, 5) );
	map1.insert(5, 5);
	check(map.size() == map1.size());
	std::cout << "size: " << map.size() << ", " << map1.size() << std::endl;

	map.insert( std::pair<int, int>(11, 11) );
	map1.insert(11, 11);
	check(map.size() == map1.size());
	std::cout << "size: " << map.size() << ", " << map1.size() << std::endl;

	map.insert( std::pair<int, int>(-2, -2) );
	map1.insert(-2, -2);
	check(map.size() == map1.size());
	std::cout << "size: " << map.size() << ", " << map1.size() << std::endl;
//	map.insert(5, 5);
//	map.insert(3, 3);
/*	map.insert(11, 11);
	map.insert(-2, -2);
	map.insert(7, 7);	
	map.insert(10, 10);
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

void map_tests()
{
	test_case("map_constructors", &map_constructor);
}

