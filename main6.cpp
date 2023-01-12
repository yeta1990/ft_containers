//#include "tester.h"
#include <string>
#include "vector.hpp"
#include <vector>

void check(bool test)
{
	if (test)
		std::cout << "\x1B[32m✓\x1B[0m";
	else
		std::cout << "\x1B[31mx\x1B[0m";
}

void test_case(std::string name, void (*test)())
{
	std::cout << name << " ";
	test();
	std::cout << std::endl;
}

void vector_constructors()
{
	std::vector<int> 	v1(20,20);
	ft::vector<int>		v2(20,20);

	check(v1.size() == v2.size());
	check(v1.capacity() == v2.capacity());
}

void vector_push_back()
{
	std::vector<int> v;
	ft::vector<int> v1;

	check(v.size() == v1.size());
	check(v.capacity() == v1.capacity());
	for (size_t i = 0; i < 100; i++)
	{
		v.push_back(42);
		v1.push_back(42);
		check(v.size() == v1.size());
		check(v.capacity() == v1.capacity());
	}
}

void vector_resize1()
{
	std::vector<int> v;
	ft::vector<int> v1;
	v.push_back(31);
	v1.push_back(31);
	check(v.size() == v1.size());
	check(v.capacity() == v1.capacity());
}

void vector_resize2()
{
	std::vector<int> v;
	ft::vector<int> v1;
	v.push_back(31);
	v1.push_back(31);
	for (size_t i = 0; i < 10; i++)
	{
		//std::cout << "------------resize " << i << std::endl;
		v.resize(i);
		v1.resize(i);
		check(v.size() == v1.size());
		check(v.capacity() == v1.capacity());
	}
	v.resize(200);
	v1.resize(200);
	check(v.size() == v1.size());
	check(v.capacity() == v1.capacity());
	v.resize(202);
	v1.resize(202);
	check(v.size() == v1.size());
	check(v.capacity() == v1.capacity());
	v.resize(400);
	v1.resize(400);
	check(v.size() == v1.size());
	check(v.capacity() == v1.capacity());
}

void vector_resize3()
{
	std::vector<int> v;
	ft::vector<int> v1;
	v.push_back(31);
	v1.push_back(31);

	check(v[0] == v1[0]);
	v.resize(100);
	v1.resize(100);
	for (size_t i = 0; i < 100; i++)
		check(v[i] == v1[i]);
}

void vector_resize4()
{
	std::vector<int> v;
	ft::vector<int> v1;

	v.push_back(31);
	v1.push_back(31);
	check(v[0] == v1[0]);
	v.resize(100, 1342);
	v1.resize(100, 1342);
	for (size_t i = 0; i < 100; i++)
		check(v[i] == v1[i]);
	check(v.size() == v1.size());
	check(v.capacity() == v1.capacity());
}

void vector_resize5()
{
	std::vector<int> v;
	ft::vector<int> v1;

	v.push_back(31);
	v1.push_back(31);
	v.resize(9);
	v1.resize(9);
	check(v.size() == v1.size());
	check(v.capacity() == v1.capacity());
	v.push_back(42);
	v1.push_back(42);
	check(v.size() == v1.size());
	check(v.capacity() == v1.capacity());
	check(v[10] == v1[10]);
}

void all_tests()
{
	test_case("vector_constructors", &vector_constructors);
	test_case("vector push back", &vector_push_back);
	test_case("vector resize: initial values: check capacity and size", &vector_resize1);
	test_case("vector resize: expanding: check capacity and size", &vector_resize2);
	test_case("vector resize: expanding: check values with default value", &vector_resize3);
	test_case("expanding: check values with custom value", &vector_resize4);
	test_case("expanding, push_back and reducing", &vector_resize4);


//	vector_constructors();
	//std::cout << str << std::endl;
}

int main(void)
{
//	std::string res = all_tests();
	all_tests();


		
}
