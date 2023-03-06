
#include "tests.hpp"
#include "set.hpp"
#include <set>

void	set_tests()
{
	std::set<int> s;	
	std::set<int>::iterator it;	

	it = s.insert(1).first;
//	std::cout << *it << std::endl;

	ft::set<int> s1;	
	ft::set<int>::iterator it1;	
	it1 = s1.insert(1).first;
	check(*it == *it1);
//	std::cout << *it1 << std::endl;

	for (size_t i = 0; i < 10; i++)
	{
		s.insert(i*2);
		s1.insert(i*2);
	}

	for (it1 = s1.begin(), it = s.begin(); it1 != s1.end(); it1++)
	{
		check(*it == *it1);
		it++;
	}

	check(s.size() == s1.size());

	ft::set<int>::iterator it3 = s1.begin(), ite = s1.end();
	ft::set<int> st_range(it3, --(--ite));


}
