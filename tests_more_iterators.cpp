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

template <class T, class Alloc>
void	cmp(const std::vector<T, Alloc> &lhs, const std::vector<T, Alloc> &rhs)
{
	static int i = 0;

	std::cout << "############### [" << i++ << "] ###############"  << std::endl;
	std::cout << "eq: " << (lhs == rhs) << " | ne: " << (lhs != rhs) << std::endl;
	std::cout << "lt: " << (lhs <  rhs) << " | le: " << (lhs <= rhs) << std::endl;
	std::cout << "gt: " << (lhs >  rhs) << " | ge: " << (lhs >= rhs) << std::endl;
}

template <class T, class Alloc>
void	cmp1(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs)
{
	static int i = 0;

	std::cout << "############### [" << i++ << "] ###############"  << std::endl;
	std::cout << "eq: " << (lhs == rhs) << " | ne: " << (lhs != rhs) << std::endl;
	std::cout << "lt: " << (lhs <  rhs) << " | le: " << (lhs <= rhs) << std::endl;
	std::cout << "gt: " << (lhs >  rhs) << " | ge: " << (lhs >= rhs) << std::endl;
}

void	comparision_operators()
{
	std::vector<int>	vct(4);
	std::vector<int>	vct2(4);
	ft::vector<int>		vctt(4);
	ft::vector<int>		vctt2(4);

//	std::cout << (vctt == vctt) << std::endl;
//	std::cout << a << std::endl;

	cmp(vct, vct);
	cmp1(vctt, vctt);
	std::cout << "===========" << std::endl;

	std::vector<int>::iterator	it;
	std::vector<int>::iterator	it1;
	ft::vector<int>::iterator	it2;
	ft::vector<int>::iterator	it3;



	std::cout << "===========" << std::endl;
	std::cout << "===========" << std::endl;
	vct2.resize(10);
	vctt2.resize(10);
	cmp(vct, vct2);
	cmp1(vctt, vctt2);

	it = vct.begin();
	it1 = vct2.begin();
	it2 = vctt.begin();
	it3 = vctt2.begin();
//		std::cout << vct[0] << std::endl;
	for (size_t i = 0; i < 4; i++)
	{
//		std::cout << vct[i] << std::endl;
		std::cout << *it++ << "," << *it1++ << "," << *it2++ << "," << *it3++ << std::endl;


	}


//	cmp(vct, vct2);	

}

void	more_iterators()
{
	test_case("vector: more iterators", &ite_arrow);
	test_case("vector: more more iterators", &ite_vector);
	test_case("vector: comparision operators", &comparision_operators);
}

#endif
