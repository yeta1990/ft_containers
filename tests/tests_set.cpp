
#include "tests.hpp"
#include "set.hpp"
#include <set>

void	set_tests()
{
	std::set<int> s;	
	std::set<int>::iterator it;	

	it = s.insert(1).first;
	std::cout << *it << std::endl;

	ft::set<int> s1;	
	ft::set<int>::iterator it1;	
	it1 = s1.insert(1).first;
//	std::cout << *it1 << std::endl;

}
