#include "tests.hpp"
#include "map.hpp"
#include <string>

void	map_constructor()
{
	ft::map<int,int> map;
//	std::cout << "eeo" << std::endl;
}

void map_tests()
{
	test_case("map_constructors", &map_constructor);
}

