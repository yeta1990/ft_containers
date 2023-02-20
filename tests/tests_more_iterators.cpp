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

//	cmp(vct, vct2);	

}

void	rev_iterator_constructor()
{
//	std::vector<int> vct;
//	std::vector<int>::iterator it = vct.begin();
//	std::vector<int>::const_iterator cit = vct.begin();
//
//	std::vector<int>::reverse_iterator rit(it);
//
//	std::vector<int>::const_reverse_iterator crit(rit);
////	std::vector<int>::const_reverse_iterator crit_(it); std::vector<int>::const_reverse_iterator crit_2(cit);

	//this should compile
	ft::vector<int> vct;
	ft::vector<int>::iterator it = vct.begin();
	ft::vector<int>::const_iterator cit = vct.begin();

	ft::vector<int>::reverse_iterator rit(it);

	ft::vector<int>::const_reverse_iterator crit(rit);
	ft::vector<int>::const_reverse_iterator crit_(it);
	ft::vector<int>::const_reverse_iterator crit_2(cit);


}

void	rev_ite_2()
{
	const int size = 5;

	std::vector<int> vct(size);
	std::vector<int>::reverse_iterator it = vct.rbegin();
	std::vector<int>::const_reverse_iterator ite = vct.rbegin();

	ft::vector<int> vct1(size);
	ft::vector<int>::reverse_iterator it1 = vct1.rbegin();
	ft::vector<int>::const_reverse_iterator ite1 = vct1.rbegin();

	for (int i = 0; i < size; ++i)
	{
		it[i] = (size - i) * 5;
		it1[i] = (size - i) * 5;
	}

	it = it + 5;
	it = 1 + it;
	it = it - 4;
	it1 = it1 + 5;
	it1 = 1 + it1;
	it1 = it1 - 4;

	check(*(it += 2) == *(it1 += 2));
	check(*(it -= 1) == *(it1 -= 1));
//	std::cout << *(it -= 1) << std::endl;

	*(it -= 2) = 42;
	*(it1 -= 2) = 42;
	check(*it == *it1);
	*(it += 2) = 21;
	*(it1 += 2) = 21;
	check(*it == *it1);

	check(*(ite += 2) == *(ite1 += 2));
	check(*(ite -= 2) == *(ite1 -= 2));

	check((ite == it) == (ite1 == it1));
	check((ite - it) == (ite1 - it1));
	check((ite + 3 == it) == (ite1 + 3 == it1));
}

void	ite_end_begin()
{
	std::vector<int> vct;
	ft::vector<int> vct1;
	std::vector<int>::iterator it;
	ft::vector<int>::iterator it1;

	for (size_t i = 0; i < 42; i++)
	{
		vct.push_back(i);
		vct1.push_back(i);
	}

//	std::cout << vct[41] << "," << vct1[41] << std::endl;
//	std::cout << *(vct.end() - 1) << std::endl;
//	std::cout << *(vct1.end() - 1) << std::endl;

//	it = vct.erase(vct.end() - 1);
//	it1 = vct1.erase(vct1.end() - 1);
//	check(*it == *it1);
//	check(vct.size() == vct1.size());
//	std::cout << *it << std::endl;
//	std::cout << *it1 << std::endl;


//	it = vct.erase(vct.begin());
//	it1 = vct1.erase(vct1.begin());
//	check(*it == *it1);
//	std::cout << *it << std::endl;
//	std::cout << *it1 << std::endl;

	std::vector<int> v(1,4);
	ft::vector<int> v1(1,4);

	it = v.erase(v.begin());
	it1 = v1.erase(v1.begin());
	check(it == v.end());
	check(it1 == v1.end());
	
	it = vct.erase(vct.begin(), vct.begin() + 3);
	it1 = vct1.erase(vct1.begin(), vct1.begin() + 3);

	check(vct.size() == vct1.size());
	for (size_t i = 0; i < vct.size(); i++)
	{
		check(vct[i] == vct1[i]);
	}
	check(it - vct.begin() ==  it1 - vct1.begin());

	it = vct.erase(vct.end() - 3, vct.end() - 1);
	it1 = vct1.erase(vct1.end() - 3, vct1.end() - 1);
	check(vct.size() == vct1.size());
	for (size_t i = 0; i < vct.size(); i++)
	{
		check(vct[i] == vct1[i]);
	}
	check(it - vct.begin() ==  it1 - vct1.begin());

}


void	more_iterators()
{
	test_case("vector: more iterators", &ite_arrow);
	test_case("vector: more more iterators", &ite_vector);
//	test_case("vector: comparision operators", &comparision_operators);
	test_case("vector: reverse iterator constructor", &rev_iterator_constructor);
	test_case("vector: reverse ite", &rev_ite_2);
	test_case("vector: ite end, begin", &ite_end_begin);
	
}

#endif
