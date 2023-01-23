#ifndef TESTS_MORE_ITERATORS
# define TESTS_MORE_ITERATORS

#include "tests.hpp"
#include <vector>
#include "vector.hpp"
#include "containers_test/srcs/base.hpp"

void ite_arrow()
{
	std::vector<foo<int> > vct(5);
	std::vector<foo<int> >::iterator it(vct.begin());
	std::vector<foo<int> >::const_iterator ite(vct.end());
	ft::vector<foo<int> > vct1(5);
	ft::vector<foo<int> >::iterator it1(vct1.begin());
	ft::vector<foo<int> >::const_iterator ite1(vct1.end());

	for (int i = 1; it != ite; ++i)
		*it++ = i;
	for (int i = 1; it1 != ite1; ++i)
		*it1++ = i;

	it = vct.begin();
	it1 = vct1.begin();
	for (int i = 1; it1 != ite1; ++i)
	{
		check(*it == *it1);
		*it++ = i;
		*it1++ = i;
	}
	it = vct.begin();
	ite = vct.begin();
	it1 = vct1.begin();
	ite1 = vct1.begin();

	check(*(++ite) == *(++ite1));
	check(*(ite++) == *(ite1++));
	check(*ite++ == *ite1++);
	check(*++ite == *++ite1);

	it->m();
	ite->m();
	it1->m();
	ite1->m();

}

void	more_iterators()
{
	test_case("vector: more iterators", &ite_arrow);
}

#endif
