#include "vector.hpp"
#include <vector>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

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

TEST_CASE("Vector push back")
{
	std::vector<int> v;
	ft::vector<int> v1;

	SUBCASE("initial values")
	{
		CHECK(v.size() == v1.size());
		CHECK(v.capacity() == v1.capacity());
	}
	SUBCASE("more values")
	{
		for (size_t i = 0; i < 100; i++)
		{
			v.push_back(42);
			v1.push_back(42);
			CHECK(v.size() == v1.size());
			CHECK(v.capacity() == v1.capacity());
		}

	}

}

TEST_CASE("Vector resize") 
{
	std::vector<int> v;
	ft::vector<int> v1;

	v.push_back(31);
	v1.push_back(31);
	SUBCASE("initial values: check capacity and size")
	{

		CHECK(v.size() == v1.size());
		CHECK(v.capacity() == v1.capacity());
	}
	SUBCASE("expanding: check capacity and size")
	{
		for (size_t i = 0; i < 10; i++)
		{
			//std::cout << "------------resize " << i << std::endl;
			v.resize(i);
			v1.resize(i);
			CHECK(v.size() == v1.size());
			CHECK(v.capacity() == v1.capacity());
		}
		v.resize(200);
		v1.resize(200);
		CHECK(v.size() == v1.size());
		CHECK(v.capacity() == v1.capacity());
		v.resize(202);
		v1.resize(202);
		CHECK(v.size() == v1.size());
		CHECK(v.capacity() == v1.capacity());
		v.resize(400);
		v1.resize(400);
		CHECK(v.size() == v1.size());
		CHECK(v.capacity() == v1.capacity());
	}
	SUBCASE("expanding: check values with default value")
	{
		CHECK(v[0] == v1[0]);
		v.resize(100);
		v1.resize(100);
		for (size_t i = 0; i < 100; i++)
		{
			//std::cout << "------------value position " << i << std::endl;
			CHECK(v[i] == v1[i]);
		}
	}
	SUBCASE("expanding: check values with custom value")
	{
		CHECK(v[0] == v1[0]);
		v.resize(100, 1342);
		v1.resize(100, 1342);
		for (size_t i = 0; i < 100; i++)
		{
			//std::cout << "------------value position " << i << std::endl;
			CHECK(v[i] == v1[i]);
		}
		CHECK(v.size() == v1.size());
		CHECK(v.capacity() == v1.capacity());
	}
	SUBCASE("expanding, push_back and reducing")
	{
		v.resize(9);
		v1.resize(9);
		CHECK(v.size() == v1.size());
		CHECK(v.capacity() == v1.capacity());
		v.push_back(42);
		v1.push_back(42);
		CHECK(v.size() == v1.size());
		CHECK(v.capacity() == v1.capacity());
		CHECK(v[10] == v1[10]);

	}
}

/*
void	vectorResizeTest(void)
{
	std::vector<int> v;

	v.push_back(31);
	std::cout << "size: " << v.size() << ", " << v.capacity() << std::endl;
	v.resize(1);
	std::cout << "size: " << v.size() << ", " << v.capacity() << std::endl;
	v.resize(2);
	std::cout << "size: " << v.size() << ", " << v.capacity() << std::endl;
	v.resize(3);
	std::cout << "size: " << v.size() << ", " << v.capacity() << std::endl;
	v.resize(4);
	std::cout << "size: " << v.size() << ", " << v.capacity() << std::endl;
	v.resize(5);
	std::cout << "size: " << v.size() << ", " << v.capacity() << std::endl;
	for (size_t i = 0; i < 100; i++)
	{
		v.resize(i);
		std::cout << "size: " << v.size() << ", " << v.capacity() << std::endl;
	}
	v.resize(101);
	std::cout << "size: " << v.size() << ", " << v.capacity() << std::endl << std::endl;

	std::vector<int> v1;

	v1.push_back(31);
	std::cout << "size: " << v1.size() << ", " << v1.capacity() << std::endl << std::endl;
	v1.resize(2);
	std::cout << "size: " << v1.size() << ", " << v1.capacity() << std::endl << std::endl;
	v1.resize(3);
	std::cout << "size: " << v1.size() << ", " << v1.capacity() << std::endl << std::endl;
	v1.resize(4);
	std::cout << "size: " << v1.size() << ", " << v1.capacity() << std::endl << std::endl;
	v1.resize(5);
	std::cout << "size: " << v1.size() << ", " << v1.capacity() << std::endl << std::endl;
	for (size_t i = 0; i < 100; i++)
	{
		v1.resize(i);
		std::cout << "size: " << v1.size() << ", " << v1.capacity() << std::endl;
	}
	v1.resize(101);
	std::cout << "size: " << v1.size() << ", " << v1.capacity() << std::endl;


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
	v.resize(20,1);
	v1.resize(20,1);
	std::cout << "size: " << v.size() << ", " << v1.size() << std::endl;
	std::cout << "capacity: " << v.capacity() << ", " << v1.capacity() << std::endl;
	std::cout << "used values: " << v1.usedValues() << std::endl << std::endl;
	*/
/*	
	v.resize(100);
	v1.resize(100);
	std::cout << "size: " << v.size() << ", " << v1.size() << std::endl;
	std::cout << "capacity: " << v.capacity() << ", " << v1.capacity() << std::endl;
	std::cout << "used values: " << v1.usedValues() << std::endl << std::endl;
*/
//	std::vector<int>::iterator it;

	//for(it = v.begin(); it != v.end(); it++)
	//	std::cout << *it << std::endl;
//}

/*
int	main(void)
{

//	vectorSizeVsCapacityTest();
	vectorResizeTest();
	//system("leaks a.out");
}
*/
