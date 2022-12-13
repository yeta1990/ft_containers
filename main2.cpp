#include "vector.hpp"
#include <vector>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

TEST_CASE("Vector constructors")
{
	std::vector<int> 	v1(20,20);
	ft::vector<int>		v2(20,20);

	CHECK(v1.size() == v2.size());
	CHECK(v1.capacity() == v2.capacity());

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

TEST_CASE("Vector reserve")
{
	std::vector<int> v;
	ft::vector<int> v1;

	for (size_t i = 0; i < 4; i++)
	{
		v.push_back(42);
		v1.push_back(42);
	}
	CHECK(v.capacity() == v1.capacity());
	v.reserve(5);
	v1.reserve(5);
	CHECK(v.capacity() == v1.capacity());
	v.reserve(99);
	v1.reserve(99);
	CHECK(v.capacity() == v1.capacity());
	CHECK_THROWS_AS(v1.reserve(v.max_size() + 1), std::length_error);
}

TEST_CASE("Vector shrink to fit")
{
	std::vector<int> myvector (100);
	CHECK(myvector.capacity() == 100);
	myvector.resize(10);	
	CHECK(myvector.capacity() == 100);
	myvector.shrink_to_fit();
	CHECK(myvector.capacity() == 10);
}

TEST_CASE("Iterator")
{
	std::vector<int> 			v;
	std::vector<int>::iterator	it;
	std::vector<int>::const_iterator	itc;
	ft::vector<int>				v1;
	ft::vector<int>::iterator	it1;
	ft::vector<int>::const_iterator	it1c;
	ft::vector<int> const				v2;

	it = v.begin();
	v1.push_back(42);
	it1 = v1.begin();
	CHECK(*it1 == 42);
	*it1 = 43;
	CHECK(*it1 == 43);
	CHECK(*it1 == v1[0]);
}

TEST_CASE("Iterator begin and end")
{
	std::vector<int> 			v;
	std::vector<int>::iterator	it;
	ft::vector<int>				v1;
	ft::vector<int>::iterator	it1;
	size_t num1 = 0;
	size_t num2 = 0;

	it = v.begin();
	it1 = v1.begin();
	for (size_t i = 0; i < 9; i++)
	{
		v.push_back(42 + i);
		v1.push_back(42 + i);
	}
	it = v.begin();
	it1 = v1.begin();
	for (it = v.begin(); it != v.end(); it++)
		num1++;
	for (it1 = v1.begin(); it1 != v1.end(); it1++)
		num2++;
	CHECK(num1 == num2);
	v.resize(100);
	v1.resize(100);
	v.push_back(1);
	v1.push_back(1);
	num1 = 0;
	num2 = 0;
	for (it = v.begin(); it != v.end(); it++)
		num1++;
	for (it1 = v1.begin(); it1 != v1.end(); it1++)
		num2++;
	CHECK(num1 == num2);
}

TEST_CASE("Iterator front and back")
{
	std::vector<int> 			v;
	std::vector<int>::iterator	it;
	ft::vector<int>				v1;
	ft::vector<int>::iterator	it1;

	int n1;
	int n2;
	for (size_t i = 0; i < 9; i++)
	{
		v.push_back(42 + i);
		v1.push_back(42 + i);
	}
	n1 = v.front();
	n2 = v1.front();
	CHECK(n1 == n2);
	v.resize(100);
	v1.resize(100);
	v.push_back(1);
	v1.push_back(1);

	n1 = v.back();
	n2 = v1.back();
	CHECK(n1 == n2);
	
}

TEST_CASE("Iterator operations")
{
	std::vector<int>			v1;	
	std::vector<int>::iterator	it;
	ft::vector<int>				v2;	
	ft::vector<int>::iterator	it2;

	v1.push_back(42);
	v1.push_back(43);
	v1.push_back(44);
	v1.push_back(45);
	it = v1.begin();
	v2.push_back(42);
	v2.push_back(43);
	v2.push_back(44);
	v2.push_back(45);
	it2 = v2.begin();

	it++;
	it++;
	it++;
	it--;
	it2++;
	it2++;
	it2++;
	it2--;

	CHECK(*it == *it2);
	it -= 2;
	it2 -= 2;
	CHECK(*it == *it2);
	CHECK(it[2] == it2[2]);

	std::vector<int>::iterator	itt;
	ft::vector<int>::iterator	itt2;
	itt = v1.begin();
	itt2 = v2.begin();
	CHECK((itt < it) == (itt2 < it2));
	CHECK((itt > it) == (itt2 > it2));
	CHECK(itt2 == it2);
	itt++;
	itt2++;
	CHECK((itt < it) == (itt2 < it2));
	CHECK((itt > it) == (itt2 > it2));
	CHECK(itt2 != it2);
}

/*
int	main(void)
{

//	vectorSizeVsCapacityTest();
	vectorResizeTest();
	//system("leaks a.out");
}
*/
