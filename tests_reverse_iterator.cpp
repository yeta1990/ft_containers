
#include "tests.hpp"
//#include "reverse_iterator.hpp"
#include <vector>
#include "vector.hpp"
#include <list>

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

void	rev_it_constructor2()
{
	std::vector<int>					v(42,42);
	std::vector<int>::iterator 			it;
	ft::vector<int>						v1(42,42);
	ft::vector<int>::iterator			it1;

	it = v.begin() + 5;
	it1 = v1.begin() + 5;

	for (size_t i = 0; i < 10; i++)
	{
		v[i] = i;
		v1[i] = i;
	}
	std::vector<int>::reverse_iterator	rit(it);
	ft::vector<int>::reverse_iterator	rit1(it1);

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

void	rev_it_dereference()
{
	std::vector<int>	v;
	ft::vector<int>	v1;

	for (size_t i = 0; i < 100; i++)
	{
		v.push_back(i);
		v1.push_back(i);
	}

	std::vector<int>::reverse_iterator rit = v.rbegin();
	ft::vector<int>::reverse_iterator rit1 = v1.rbegin();
	std::vector<int>::pointer p = rit.operator->();
	ft::vector<int>::pointer p1 = rit1.operator->();
	check(*p == *p1);
//	std::cout << *p << std::endl;
//	std::cout << *p << std::endl;

//	check(t.base() == it);

}

void	rev_it_operators()
{
	std::vector<int>					v(42);
	std::vector<int>::iterator 			it;
	ft::vector<int>						v1(42);
	ft::vector<int>::iterator			it1;

	for (size_t i = 0; i < 42; i++)
	{
		v[i] = i;
		v1[i] = i;
	}
	std::vector<int>::reverse_iterator	rit = v.rbegin();
	ft::vector<int>::reverse_iterator	rit1 = v1.rbegin();
	check(*rit == *rit1);

	rit = ++rit;	
	rit1 = ++rit1;	
	check(*rit == *rit1);
	
	rit = --rit;	
	rit1 = --rit1;	
	check(*rit == *rit1);

	rit++;
	rit1++;
	check(*rit == *rit1);

	rit--;
	rit1--;
	check(*rit == *rit1);

	rit = rit + 5;
	rit1 = rit1 + 5;
	check(*rit == *rit1);

	rit = rit - 5;
	rit1 = rit1 - 5;
	check(*rit == *rit1);

	rit += 3;
	rit1 += 3;
	check(*rit == *rit1);

	rit -= 2;
	rit1 -= 2;
	check(*rit == *rit1);

	check(rit[17] == rit1[17]);
}

void	rev_it_rend()
{
	std::vector<int>					v(42);
	std::vector<int>::iterator 			it;
	ft::vector<int>						v1(42);
	ft::vector<int>::iterator			it1;

	for (size_t i = 0; i < 42; i++)
	{
		v[i] = i;
		v1[i] = i;
	}
	std::vector<int>::reverse_iterator	rit;
	rit = v.rend() - 1;
	ft::vector<int>::reverse_iterator	rit1;
	rit1 = v1.rend() - 1;
	check(*rit == *rit1);

}

void	rev_it_2()
{
	std::list<int> lst;
	std::list<int>::iterator lst_it;
//	ft::list<int> lst1;
//	ft::list<int>::iterator lst_it1;
	for (int i = 1; i < 5; ++i)
		lst.push_back(i * 3);
	std::vector<int> vct(lst.begin(), lst.end());
	ft::vector<int> vct1(lst.begin(), lst.end());
	lst_it = lst.begin();

	for (int i = 1; lst_it != lst.end(); ++i)
		*lst_it++ = i * 5;
	vct.assign(lst.begin(), lst.end());
	vct1.assign(lst.begin(), lst.end());
	lst_it = lst.begin();
	check_size_capacity(vct, vct1);
	for (ft::vector<int>::size_type i = 0; i < vct.size(); i++)
		check(vct[i] == vct1[i]);

	vct.insert(vct.end(), lst.rbegin(), lst.rend());
	vct1.insert(vct1.end(), lst.rbegin(), lst.rend());

}

void	reverse_iterator_tests()
{
	test_case("vector: reverse iterator constructor", &rev_it_constructor);
	test_case("vector: reverse iterator constructor2", &rev_it_constructor2);
	test_case("vector: reverse iterator base", &rev_it_base);
	test_case("vecto: reverse iterator dereference", &rev_it_dereference);
	test_case("vector: reverse iterator operator", &rev_it_operators);
	test_case("vector: rend", &rev_it_rend);
	test_case("vector: reverse iterator 2", &rev_it_2);
//	test_case("", &);
//	test_case("vector: bidirect iterator", &bidirect_iterator);
//	test_case("", &);


}
