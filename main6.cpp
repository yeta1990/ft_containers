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
	check(v[9] == v1[9]);
}

void vector_resize6()
{
	std::vector<int> v;
	ft::vector<int> v1;

	v.push_back(31);
	v1.push_back(31);
	v.resize(9);
	v1.resize(9);
	check(v.size() == v1.size());
	check(v.capacity() == v1.capacity());
	v.resize(0);
	v1.resize(0);
	check(v.size() == v1.size());
	check(v.capacity() == v1.capacity());
}

void vector_empty()
{
	ft::vector<int> v1;
	check(v1.empty() == true);
	v1.push_back(42);
	check(v1.empty() == false);
}

void vector_reserve()
{
	std::vector<int> v;
	ft::vector<int> v1;

	for (size_t i = 0; i < 4; i++)
	{
		v.push_back(42);
		v1.push_back(42);
	}
	check(v.capacity() == v1.capacity());
	v.reserve(5);
	v1.reserve(5);
	check(v.capacity() == v1.capacity());
	v.reserve(99);
	v1.reserve(99);
	check(v.capacity() == v1.capacity());
//	check_THROWS_AS(v1.reserve(v.max_size() + 1), std::length_error);

}

void vector_iterator()
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
	check(*it1 == 42);
	*it1 = 43;
	check(*it1 == 43);
	check(*it1 == v1[0]);
}

void vector_iterator_begin_end()
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
	check(num1 == num2);
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
	check(num1 == num2);


}

void vector_iterator_front_back()
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
	check(n1 == n2);
	v.resize(100);
	v1.resize(100);
	v.push_back(1);
	v1.push_back(1);

	n1 = v.back();
	n2 = v1.back();
	check(n1 == n2);

}

void vector_iterator_operations()
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

	check(*it == *it2);
	it -= 2;
	it2 -= 2;
	check(*it == *it2);
	check(it[2] == it2[2]);

	std::vector<int>::iterator	itt;
	ft::vector<int>::iterator	itt2;
	itt = v1.begin();
	itt2 = v2.begin();
	check((itt < it) == (itt2 < it2));
	check((itt > it) == (itt2 > it2));
	check(itt2 == it2);
	itt++;
	itt2++;
	check((itt < it) == (itt2 < it2));
	check((itt > it) == (itt2 > it2));
	check(itt2 != it2);

}

void all_tests()
{
	test_case("vector_constructors", &vector_constructors);
	test_case("vector push back", &vector_push_back);
	test_case("vector resize: initial values: check capacity and size", &vector_resize1);
	test_case("vector resize: expanding: check capacity and size", &vector_resize2);
	test_case("vector resize: expanding: check values with default value", &vector_resize3);
	test_case("expanding: check values with custom value", &vector_resize4);
	test_case("expanding, push_back and reducing", &vector_resize5);
	test_case("reducing", &vector_resize6);
	test_case("vector: empty", &vector_empty);
	test_case("vector: reserve", &vector_reserve);
	test_case("vector: iterator", &vector_iterator);
	test_case("vector: iterator begin and end", &vector_iterator_begin_end);
	test_case("vector: iterator front and back", &vector_iterator_front_back);
	test_case("vector: iterator operations", &vector_iterator_operations);
	


//	vector_constructors();
	//std::cout << str << std::endl;
}

int main(void)
{
//	std::string res = all_tests();
	all_tests();


		
}
