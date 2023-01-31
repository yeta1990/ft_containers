#include "tests.hpp"
#include "map.hpp"
#include <string>

void	map_constructor()
{
	ft::map<int,int> map;

	map.insert(8, 8);
	map.insert(5, 5);
	map.insert(3, 3);
	map.insert(11, 11);
	map.insert(-2, -2);
//	map->insert(7);	
//	map->insert(10);	
//	map->insert(9);	
//	map->insert(4);	
//	map->insert(1);	
//	map->insert(-1);	
//	map->insert(6);	
//	map->insert(12);	
//	map->insert(-7);
//	std::cout << "eeo" << std::endl;
}

void map_tests()
{
	test_case("map_constructors", &map_constructor);
}

