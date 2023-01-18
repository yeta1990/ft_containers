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

template <class T>
void check_size_capacity(std::vector<T> v, ft::vector<T> v1)
{
	if (v.size() == v1.size())
		std::cout << "\x1B[32m✓\x1B[0m";
	else
	{
		std::cout << "\x1B[31mx\x1B[0m";
		std::cout << std::endl << "Expected size: " << v.size()
				<< ", but is " << v1.size() << std::endl;
	}
	if (v.capacity() == v1.capacity())
		std::cout << "\x1B[32m✓\x1B[0m";
	else
	{
		std::cout << "\x1B[31mx\x1B[0m";
		std::cout << std::endl << "Expected capacity: " << v.size()
				<< ", but is " << v1.size() << std::endl;
	}
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

void vector_constructors_2()
{
	std::vector<int> v(42, 42);	
	std::vector<int>::iterator it;
	std::vector<int>::iterator it2;

	it = v.begin();
	it2 = v.end() - 5;
	ft::vector<int> v2(42, 42);	
	ft::vector<int>::iterator it3;
	ft::vector<int>::iterator it4;

	it3 = v2.begin();
	it4 = v2.end() - 5;

	std::vector<int> vit(it, it2);
	ft::vector<int> vit1(it3, it4);
	check_size_capacity(vit, vit1);
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

void	vector_iterator_substr(){
	std::vector<int> v(42, 42);	
	std::vector<int>::iterator it;
	std::vector<int>::iterator it2;

	it = v.begin();
	it2 = v.end() - 5;
	ft::vector<int> v2(42, 42);	
	ft::vector<int>::iterator it3;
	ft::vector<int>::iterator it4;

	it3 = v2.begin();
	it4 = v2.end() - 5;
	check(it2 - it == it4 - it3);

}

void vector_eq_operator()
{
	std::vector<int> v(5,10);
	ft::vector<int> v1(5,10);
	std::vector<int> v2;
	ft::vector<int> v3;
	std::vector<int>::iterator it;
	ft::vector<int>::iterator it2;
	
	check(v2.empty() == v3.empty());
	v2 = v;
	v3 = v1;	
	check(v2.empty() == v3.empty());
	check(v2.capacity() == v3.capacity());
	check(v2.size() == v3.size());
	it = v2.begin();
	it2 = v3.begin();
	for (int i = 0; i < 5; i++)
		check(*it == *it2);
}

void	vector_at()
{
	std::vector<int> v(5,10);
	ft::vector<int> v1(5,10);

	check(v[1] == v1[1]);
	std::string m1;
	std::string m2;

	bool except1 = false;
	bool except2 = false;
	try
	{
		std::cout << v.at(6) << std::endl;
	}
	catch (std::out_of_range &e)
	{
		m1 = e.what();
		except1 = true;
	}

	try
	{
		std::cout << v1.at(6) << std::endl;
	}
	catch (std::out_of_range &e)
	{
		m2 = e.what();
		except2 = true;
	}
//	this test has different behaviour in mac and linux
//	std::cout << m1 << "," << m2 << std::endl;
//	check(m1.compare(m2) == 0);
	check(except1 == except2);
	v.at(1) = 7;
	v1.at(1) = 7;
	check(v.at(1) == v1.at(1));
}

void	vector_at2()
{
	std::vector<int> v(5,10);
	ft::vector<int> v1(5,10);
	std::vector<int> const v2(v);
	ft::vector<int> const v3(v1);
	ft::vector<int> const v4(v3);
	check (&(v3.at(3)) != &(v1.at(3)));
}

void vector_assign()
{
	std::vector<int> v(5, 11);
	ft::vector<int> v1(5, 11);

	check(v.size() == v1.size());
	check(v.capacity() == v1.capacity());
	v.assign(3, 2);
	v1.assign(3, 2);
	check(v.size() == v1.size());
//	std::cout << v.size() << "," << v1.size() << std::endl;
	check(v.capacity() == v1.capacity());
//	check(v[4] == v1[4]);

	v.assign(6, 20);
	v1.assign(6, 20);
	check_size_capacity(v, v1);
	check(v[4] == v1[4]);
	v.assign(61, 42);
	v1.assign(61, 42);
	check_size_capacity(v, v1);
	check(v[4] == v1[4]);
	check(v[58] == v1[58]);

}

void	vector_assign_iterator()
{
	std::vector<int> v(42,42);
	ft::vector<int> v1(42,42);
	std::vector<int> v2(1,1);
	ft::vector<int> v3(1,1);
	std::vector<int>::iterator it;
	std::vector<int>::iterator it1;
	ft::vector<int>::iterator it2;
	ft::vector<int>::iterator it3;

	it = v.begin();
	it1 = v.end();
	it2 = v1.begin();
	it3 = v1.end();

	check_size_capacity(v2, v3);
	v2.assign(it, it1);
	v3.assign(it2, it3);
	check_size_capacity(v2, v3);

}

void	vector_assign_iterator2()
{
	std::vector<int> v;
	ft::vector<int> v1;
	std::vector<int> v2;
	ft::vector<int> v3;

	for (size_t i = 0; i < 100; i += 3)
	{
		v.push_back(i);
		v1.push_back(i);
	}
	v2.assign(v.begin(), v.end());
	v3.assign(v.begin(), v.end());
	check_size_capacity(v2, v3);
	check(v2[3] == v3[3]);

	v2.assign(1000, 420);
	v3.assign(1000, 420);
	check_size_capacity(v2, v3);
	check(v2[3] == v3[3]);
	v2.assign(v.begin(), v.end());
	v3.assign(v.begin(), v.end());
	check_size_capacity(v2, v3);
	check(v2[3] == v3[3]);
}

void	vector_assign_iterator3()
{
	std::vector<int> vct(7);
	std::vector<int> vct2(4);
	ft::vector<int> vct3(7);
	ft::vector<int> vct4(4);

	for (size_t i = 0; i < vct.size(); ++i)
		vct[i] = (vct.size() - i) * 3;
	for (size_t i = 0; i < vct2.size(); ++i)
		vct2[i] = (vct2.size() - i) * 5;
	for (size_t i = 0; i < vct3.size(); ++i)
		vct3[i] = (vct3.size() - i) * 3;
	for (size_t i = 0; i < vct4.size(); ++i)
		vct4[i] = (vct4.size() - i) * 5;
	check_size_capacity(vct, vct3);
	check_size_capacity(vct2, vct4);

	std::vector<int> vct5;
	std::vector<int> vct6;
	ft::vector<int> vct7;
	ft::vector<int> vct8;

	vct5.assign(vct.begin(), vct.end());
	vct.assign(vct2.begin(), vct2.end());
	vct2.assign(2, 42);
	vct6.assign(4,21);	

	vct7.assign(vct3.begin(), vct3.end());
	vct3.assign(vct4.begin(), vct4.end());
	vct4.assign(2, 42);
	vct8.assign(4,21);	

	check_size_capacity(vct, vct3);
	check_size_capacity(vct2, vct4);
	check_size_capacity(vct5, vct7);
	check_size_capacity(vct6, vct8);

	vct.assign(vct5.begin(), vct5.begin() + 2);
	vct3.assign(vct5.begin(), vct5.begin() + 2);
	check_size_capacity(vct, vct3);
	vct.assign(vct5.end() - 3, vct5.end());
	vct3.assign(vct7.end() - 3, vct7.end());
	check_size_capacity(vct, vct3);

}

void vector_erase()
{
	std::vector<int> v(42,42);
	ft::vector<int> v1(42,42);
	std::vector<int>::iterator it;
	ft::vector<int>::iterator	it1;

	it = v.end() - 1;
	it = v.erase(it);
	it1 = v1.end() - 1;
	it1 = v1.erase(it1);
	check(it == v.end());
	check(it1 == v1.end());
	check_size_capacity(v, v1);
	check(it1 == v1.end());
	check(v[40] == v1[40]);
	for (size_t i = 0; i < 41; i++)
	{
		v[i] = i;
		v1[i] = i;
	}
	it = v.begin() + 10;
	it1 = v1.begin() + 10;
	it = v.erase(it);
	it1 = v1.erase(it1);
	check_size_capacity(v, v1);
	check(v[9] == v1[9]);
	check(v[10] == v1[10]);
}

void vector_erase2()
{
	std::vector<int> v(1);
	ft::vector<int> v1(1);
	std::vector<int>::iterator it;
	ft::vector<int>::iterator	it1;

	it = v.begin();
	it = v.erase(it);
	it1 = v1.begin();
	it1 = v1.erase(it1);
	check_size_capacity(v, v1);
}

void vector_erase_iterator()
{

}

void all_tests()
{
	test_case("vector_constructors", &vector_constructors);
	test_case("vector_constructors2", &vector_constructors_2);
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
	test_case("vector: iterator substr", &vector_iterator_substr);
	test_case("vector: eq operations", &vector_iterator_operations);
	test_case("vector: at", &vector_at);
	test_case("vector: at2", &vector_at2);
	test_case("vector: at2", &vector_at2);
	test_case("vector: assign", &vector_assign);
	test_case("vector: assign iterator", &vector_assign_iterator);
	test_case("vector: assign iterator2", &vector_assign_iterator2);
	test_case("vector: assign iterator3", &vector_assign_iterator3);
	test_case("vector: erase", &vector_erase);
	test_case("vector: erase2", &vector_erase2);
	test_case("vector: erase iterator", &vector_erase_iterator);
//	test_case("vector: erase iterator", &vector_erase_iterator);
}

int main(void)
{
	all_tests();
}
