#include "vector.hpp"
#include <vector>

int	main(void)
{
	ft::vector<int> v;
	std::vector<int> v1;
	std::cout << "size: " << v.size() << ", " << v1.size() << std::endl;
	std::cout << "capacity: " << v.capacity() << ", " << v1.capacity() << std::endl;

	v1.resize(1);

	std::cout << "size: " << v.size() << ", " << v1.size() << std::endl;
	std::cout << "capacity: " << v.capacity() << ", " << v1.capacity() << std::endl;
	v1.push_back(42);
	v.push_back(42);
	std::cout << "size: " << v.size() << ", " << v1.size() << std::endl;
	std::cout << "capacity: " << v.capacity() << ", " << v1.capacity() << std::endl;
	v1.push_back(22);
	std::cout << "size: " << v.size() << ", " << v1.size() << std::endl;
	std::cout << "capacity: " << v.capacity() << ", " << v1.capacity() << std::endl;
}
