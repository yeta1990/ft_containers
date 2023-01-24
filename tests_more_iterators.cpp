#ifndef TESTS_MORE_ITERATORS
# define TESTS_MORE_ITERATORS

#include "tests.hpp"
#include <vector>
#include "vector.hpp"
#include "containers_test/srcs/base.hpp"

void	ite_arrow()
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

//	check(it->m() == it1->m());
//	check(ite->m() == ite1->m());

}

void	ite_vector()
{
	std::vector<int>	vct(5);
//	std::vector<int>::iterator	it = vct.begin();
	ft::vector<int>		vct1(5);
//	ft::vector<int>::iterator	it1 = vct.begin();
			

	std::vector<int>::iterator	it = vct.begin();
	std::vector<int>::iterator	it_tmp;
	ft::vector<int>::iterator	it1 = vct1.begin();
	ft::vector<int>::iterator	it1_tmp;

	it_tmp = ++it;
	it1_tmp = ++it1;
	check(*it_tmp == *it1_tmp);
	check(*it == *it1);
	it_tmp = --it;
	it1_tmp = --it1;
	check(*it_tmp == *it1_tmp);
	check(*it == *it1);
	it_tmp = it++;
	it1_tmp = it1++;
	check(*it_tmp == *it1_tmp);
	check(*it == *it1);
	it_tmp = it++;
	it1_tmp = it1--;
	check(*it_tmp == *it1_tmp);
	check(*it == *it1);

	std::vector<int>::iterator itt = vct.begin();
//	std::vector<int>::const_iterator itte = vct.begin();
	ft::vector<int>::iterator itt1 = vct1.begin();
//	ft::vector<int>::const_iterator itte1 = vct1.begin();

	for (int i = 0; i < 5; ++i)
	{
		itt[i] = (5 - i) * 5;
		itt1[i] = (5 - i) * 5;
	}

	itt = itt + 5;
	itt = 1 + itt;
	itt = itt - 4;
	itt1 = itt1 + 5;
	itt1 = 1 + itt1;
	itt1 = itt1 - 4;
	check(*(itt += 2) == *(itt1 += 2));

}

void	more_iterators()
{
	test_case("vector: more iterators", &ite_arrow);
	test_case("vector: more more iterators", &ite_vector);
}

#endif
