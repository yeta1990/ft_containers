#include "tests.hpp"
#include "stack.hpp"
#include <stack>

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
}

void	stack_tests()
{
	test_case("stack tests", &stack_all_tests);
}
