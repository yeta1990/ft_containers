#include "vector.hpp"
#include <vector>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

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
	SUBCASE("reducing")
	{
		v.resize(9);
		v1.resize(9);
		CHECK(v.size() == v1.size());
		CHECK(v.capacity() == v1.capacity());
		v.resize(0);
		v1.resize(0);
		CHECK(v.size() == v1.size());
		CHECK(v.capacity() == v1.capacity());

	}
}

TEST_CASE("Vector: empty()")
{
	ft::vector<int> v1;
	CHECK(v1.empty() == true);
	v1.push_back(42);
	CHECK(v1.empty() == false);
}

/*
int	main(void)
{

//	vectorSizeVsCapacityTest();
	vectorResizeTest();
	//system("leaks a.out");
}
*/
