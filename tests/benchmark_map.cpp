#include "tests.hpp"
#include <limits>
#include "benchmarks.hpp"
#include "pair.hpp"
#include "map.hpp"
#include <map>

class timer;

void	map_b_equal_range()
{
    std::map<int, int> data;

    t = timer();

    for (std::size_t i = 0; i < MAXSIZE_MAP / 2; ++i) {
        data.insert(std::make_pair(rand(), rand()));
    }


    for (int i = 0; i < 10000000; ++i) {
    	if (i % 10 == 0)
    		std::cout << i << std::endl;
        std::pair<std::map<int, int>::iterator, std::map<int, int>::iterator> eq =
            data.equal_range(rand());
        if (eq.first != data.end()) {
            eq.second->second = 64;
        }
    }

	std::cout << "ft: " << t.get_time();

}


//    t = timer();

//	std::cout << "ft: " << t.get_time();

//    t = timer();
//	std::cout << "std: " << t.get_time();
void	map_benchmark()
{
	test_case("vector: resize 7", &map_b_equal_range);

}
