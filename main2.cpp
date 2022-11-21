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

	v.push_back(31);
	v.push_back(32);
	v.push_back(33);
	v.push_back(34);
	v1.push_back(31);
	v1.push_back(32);
	v1.push_back(33);
	v1.push_back(34);
	std::cout << "size: " << v.size() << ", " << v1.size() << std::endl;
	std::cout << "capacity: " << v.capacity() << ", " << v1.capacity() << std::endl << std::endl;
	std::cout << "used values: " << v1.usedValues() << std::endl << std::endl;

	for (size_t i = 0; i < 4; i++)
	{
		std::cout << v[i] << std::endl;
		std::cout << v1[i] << std::endl;
	}

	v.resize(3);
	v1.resize(3);
	std::cout << "size: " << v.size() << ", " << v1.size() << std::endl;
	std::cout << "capacity: " << v.capacity() << ", " << v1.capacity() << std::endl;
	std::cout << "used values: " << v1.usedValues() << std::endl << std::endl;
	for (size_t i = 0; i < v1.size(); i++)
	{
		std::cout << v[i] << std::endl;
		std::cout << v1[i] << std::endl;
	}
	std::cout << std::endl;	
	
	v.resize(5,1);
	v1.resize(5,1);
	std::cout << "size: " << v.size() << ", " << v1.size() << std::endl;
	std::cout << "capacity: " << v.capacity() << ", " << v1.capacity() << std::endl;
	std::cout << "used values: " << v1.usedValues() << std::endl << std::endl;
	
	for (size_t i = 0; i < 5; i++)
	{
		std::cout << v[i] << std::endl;
		std::cout << v1[i] << std::endl;
	}

	v.resize(9);
	v1.resize(9);
	std::cout << "size: " << v.size() << ", " << v1.size() << std::endl;
	std::cout << "capacity: " << v.capacity() << ", " << v1.capacity() << std::endl;
	std::cout << "used values: " << v1.usedValues() << std::endl << std::endl;

	for (size_t i = 0; i < 9; i++)
	{
		std::cout << v[i] << std::endl;
		std::cout << v1[i] << std::endl;
	}
	
	v.resize(100);
	v1.resize(100);
	std::cout << "size: " << v.size() << ", " << v1.size() << std::endl;
	std::cout << "capacity: " << v.capacity() << ", " << v1.capacity() << std::endl;
	std::cout << "used values: " << v1.usedValues() << std::endl << std::endl;

//	std::vector<int>::iterator it;

	//for(it = v.begin(); it != v.end(); it++)
	//	std::cout << *it << std::endl;
}

int	main(void)
{

//	vectorSizeVsCapacityTest();
	vectorResizeTest();
	//system("leaks a.out");
}
