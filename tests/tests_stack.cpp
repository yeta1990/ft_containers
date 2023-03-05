
#include "tests.hpp"
#include "stack.hpp"
#include <stack>

void	stack_tests()
{
	std::stack<int> t;
	ft::stack<int> stck;

	std::cout << "empty: " << stck.empty() << std::endl;
	std::cout << "size: " << stck.size() << std::endl;
//	std::cout << "top: " << stck.top() << std::endl;

	stck.push(41);
	stck.push(29);
	stck.push(10);
	stck.push(42);
	std::cout << "empty: " << stck.empty() << std::endl;
	std::cout << "size: " << stck.size() << std::endl;
	std::cout << "top: " << stck.top() << std::endl;
//	test_case("map_constructors", &map_constructor);

}
