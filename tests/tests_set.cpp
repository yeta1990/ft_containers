
#include "tests.hpp"
#include "set.hpp"
#include <set>



void	set_all_tests()
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

	std::set<int> first; 

  	int myints[]= {10,20,30,40,50};
  	std::set<int> second (myints,myints+5); 
  	std::set<int> third (second);   
  	std::set<int> fourth (second.begin(), second.end());

	ft::set<int> first1;
  	ft::set<int> second1 (myints,myints+5);        
  	ft::set<int> third1 (second1);     
  	ft::set<int> fourth1 (second1.begin(), second1.end()); 

	check(first.size() == first1.size());
	check(second.size() == second1.size());
	check(third.size() == third1.size());
	check(fourth.size() == fourth1.size());
	check(*(fourth.lower_bound(20)) == *(fourth1.lower_bound(20)));
	check(*fourth.upper_bound(20) == *fourth1.upper_bound(20));
	check(*(fourth.find(30)) == *(fourth1.find(30)));

	fourth1.insert(10);
	fourth.insert(10);
	check(fourth.size() == fourth1.size());



}

void	set_tests()
{
	test_case("set tests", &set_all_tests);
}
