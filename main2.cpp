#include "vector.hpp"
#include <vector>

void	vectorSizeVsCapacityTest(void)
{
	std::vector<int> v;
	ft::vector<int> v1;

	std::cout << "size: " << v.size() << ", " << v1.size() << std::endl;
	std::cout << "capacity: " << v.capacity() << ", " << v1.capacity() << std::endl << std::endl;
	for (size_t i = 0; i < 100; i++)
	{
		v.push_back(42);
		v1.push_back(42);
		std::cout << "size: " << v.size() << ", " << v1.size() << std::endl;
		std::cout << "capacity: " << v.capacity() << ", " << v1.capacity() << std::endl << std::endl;
	}

}

void	vectorResizeTest(void)
{
	std::vector<int> v;
	ft::vector<int> v1;

	std::cout << "size: " << v.size() << ", " << v1.size() << std::endl;
	std::cout << "capacity: " << v.capacity() << ", " << v1.capacity() << std::endl << std::endl;
	v.push_back(3);
	v.push_back(3);
	v.push_back(3);
	std::cout << "size: " << v.size() << ", " << v1.size() << std::endl;
	std::cout << "capacity: " << v.capacity() << ", " << v1.capacity() << std::endl << std::endl;
	v.resize(2);
	std::cout << "size: " << v.size() << ", " << v1.size() << std::endl;
	std::cout << "capacity: " << v.capacity() << ", " << v1.capacity() << std::endl << std::endl;



}

int	main(void)
{

	//vectorSizeVsCapacityTest();
	vectorResizeTest();
	//system("leaks a.out");
}
