#include "tests.hpp"
#include "stack.hpp"
#include <stack>
#include <list>

void	stack_all_tests()
{
	std::stack<int> t;
	ft::stack<int> stck;

	check(t.empty() == stck.empty());
	check(t.size() == stck.size());
	stck.push(41);
	stck.push(29);
	stck.push(10);
	stck.push(42);
	t.push(41);
	t.push(29);
	t.push(10);
	t.push(42);
	check(t.empty() == stck.empty());
	check(t.size() == stck.size());
	check(t.top() == stck.top());
	t.pop();
	stck.pop();
	check(t.top() == stck.top());

	ft::stack<int> s;
	int myints[] = {16,2,77,29};
  	std::list<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

//  	std::cout << "The contents of fifth are: ";
  	for (std::list<int>::iterator it = fifth.begin(); it != fifth.end(); it++)
  	{
		s.push(*it);
  	}
  	check(s.top() == 29);
  	s.pop();
  	check(s.top() == 77);
  	s.pop();
  	check(s.size() == 2);

}

void	stack_tests()
{
	test_case("stack tests", &stack_all_tests);
}
