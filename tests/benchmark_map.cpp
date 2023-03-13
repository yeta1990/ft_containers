#include "tests.hpp"
#include <limits>
#include "benchmarks.hpp"
#include "pair.hpp"
#include "map.hpp"
#include <map>

class timer;

void	map_b_equal_range()
{
    ft::map<int, int> data1;
    std::map<int, int> data;
    ft::map<int, int>::iterator it1;
    std::map<int, int>::iterator it;

    for (std::size_t i = 0; i < MAXSIZE_MAP / 2; ++i) {
        data.insert(std::make_pair(rand(), rand()));
        data1.insert(ft::make_pair(rand(), rand()));
    }

	it1 = data1.begin();
	it = data.begin();
	
    t = timer();
    while (it != data.end())
    {
    	it++;
    }
	std::cout << "std: " << t.get_time();

    t = timer();
    while (it1 != data1.end())
    {
    	it1++;
    }
	std::cout << ", ft: " << t.get_time();

	it1 = data1.begin();
	it = data.begin();
	
    t = timer();
    while (it != data.end())
    {
    	it++;
    }
	std::cout << "std: " << t.get_time();

    t = timer();
    while (it1 != data1.end())
    {
    	it1++;
    }
	std::cout << ", ft: " << t.get_time();


    for (int i = 0; i < 10000000; ++i) {
    	
        ft::pair<ft::map<int, int>::iterator, ft::map<int, int>::iterator> eq =
            data1.equal_range(rand());
        if (eq.first != data1.end()) {
            eq.second->second = 64;
        }
    }
}


void	map_benchmark()
{
	test_case("map: equal range", &map_b_equal_range);

}
