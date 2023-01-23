
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

	for (size_t i = 0; i < 100; i++)
	{
		v.push_back(i);
		v1.push_back(i);
	}

	rit = v.rbegin();
	rit1 = v1.rbegin();
	check(*rit == *rit1);
}

void	rev_it_base()
{
	// https://en.cppreference.com/w/cpp/iterator/reverse_iterator/base
	ft::vector<int>	v1(5);
	ft::vector<int>::iterator it;
	ft::vector<int>::reverse_iterator t(it);
	check(t.base() == it);
	check(&*(t.base() - 1) == &*t);

}

void	reverse_iterator_tests()
{
	test_case("vector: reverse iterator constructor", &rev_it_constructor);
	test_case("vector: reverse iterator base", &rev_it_base);
//	test_case("", &);
//	test_case("vector: bidirect iterator", &bidirect_iterator);
//	test_case("", &);


}
