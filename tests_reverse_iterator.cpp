
#include "tests.hpp"
//#include "reverse_iterator.hpp"
#include <vector>
#include "vector.hpp"

void	rev_it_constructor()
{
	std::vector<int>	v(5);
	std::vector<int>::reverse_iterator rit;
	ft::vector<int>	v1(5);
	ft::vector<int>::reverse_iterator rit1;


}

void	reverse_iterator_tests()
{
	test_case("vector: reverse iterator constructor", &rev_it_constructor);
//	test_case("vector: bidirect iterator", &bidirect_iterator);
//	test_case("", &);


}
