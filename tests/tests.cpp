#include <string>
#include "tests.hpp"
#include "benchmarks.hpp"


void check(bool test)
{
	if (test)
		std::cout << "\x1B[32m✓\x1B[0m";
	else
		std::cout << "\x1B[31mx\x1B[0m";
}

template <class T>
void check_size_capacity(std::vector<T>& v, ft::vector<T>& v1)
{
	
	size_t	capacity1 = v.capacity();
	size_t	capacity2 = v1.capacity();
	size_t	size1 = v.size();
	size_t	size2 = v1.size();

	if (size1 == size2)
		std::cout << "\x1B[32m✓\x1B[0m";
	else
	{
		std::cout << "\x1B[31mx\x1B[0m";
		std::cout << std::endl << "Expected size: " << v.size()
				<< ", but is " << v1.size() << std::endl;
	}
	if (capacity1 == capacity2)
		std::cout << "\x1B[32m✓\x1B[0m";
	else
	{
		std::cout << "\x1B[31mx\x1B[0m";
		std::cout << std::endl << "Expected capacity: " << v.capacity()
				<< ", but is " << v1.capacity() << std::endl;
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
//		std::cout << "size " << v.size() << "," << v1.size() << std::endl;
		check(v.capacity() == v1.capacity());
//		std::cout << "capacity " << v.capacity() << "," << v1.capacity() << std::endl;
	}
	v.resize(200);
	v1.resize(200);
	check(v.size() == v1.size());
	check(v.capacity() == v1.capacity());
//		std::cout << "size " << v.size() << "," << v1.size() << std::endl;
//		std::cout << "capacity " << v.capacity() << "," << v1.capacity() << std::endl;

	v.resize(202);
	v1.resize(202);
	check(v.size() == v1.size());
	check(v.capacity() == v1.capacity());
//		std::cout << "size " << v.size() << "," << v1.size() << std::endl;
//		std::cout << "capacity " << v.capacity() << "," << v1.capacity() << std::endl;
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
//	std::cout << v.size() << "," << v1.size() << std::endl;
//	std::cout << v.capacity() << "," << v1.capacity() << std::endl;

	v.resize(9);
	v1.resize(9);
	check(v.size() == v1.size());
	check(v.capacity() == v1.capacity());

	v.resize(2);
	v1.resize(2);
	check(v.size() == v1.size());
	check(v.capacity() == v1.capacity());

	std::vector<int>::iterator	it;
	ft::vector<int>::iterator	it1;

	it = v.begin();
	it1 = v1.begin();

	while (it != v.end())
	{
		check(*it == *it1);
		it++;
		it1++;
	}

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
//	std::cout << v.capacity() << "," << v1.capacity() << std::endl;
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
	
	ft::vector<int>::iterator it;
	size_t i = 0;
	for (it = v1.begin(); it != v1.end(); it++)
	{
		check(v[i] == v1[i]);
		i++;
	}

	v.assign(v.begin(), v.begin() + 30);
	v1.assign(v1.begin(), v1.begin() + 30);
	i = 0;
/*	for (it = v1.begin(); it != v1.end(); it++)
	{
		check(v[i] == v1[i]);
		i++;
	}
	*/
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

void	vector_assign_killer()
{
	int _ratio = 1000;
//	std::vector<int> v(42,42);
//	ft::vector<int> v1(42,42);
//	ft::vector<int> v2(5,1);

//	v.assign(v.);
//	v1.assign(v2.begin(), v2.begin());

    std::vector<int> v;
    ft::vector<int> v1;
    std::vector<int> vector;
    ft::vector<int> vector1;

	std::vector<int> tmp, tmp2;
	ft::vector<int> tmp1, tmp12;


    vector.assign(3, 3);
    vector1.assign(3, 3);

    tmp.assign(4000 * _ratio, 1);
    tmp1.assign(4000 * _ratio, 1);


    tmp2.assign(4 * _ratio, 1);
    tmp12.assign(4 * _ratio, 1);

//    g_start2 = timer();
    vector.assign(tmp.begin(), tmp.end());
    vector1.assign(tmp1.begin(), tmp1.end());

	check_size_capacity(v, v1);
	check_size_capacity(vector, vector1);
	check_size_capacity(tmp, tmp1);
	check_size_capacity(tmp2, tmp12);

    v.push_back(vector[1]);
    v1.push_back(vector1[1]);

    v.push_back(vector.size());
    v1.push_back(vector1.size());

    v.push_back(vector.capacity());
    v1.push_back(vector1.capacity());

    vector.assign(tmp2.begin(), tmp2.end());
    vector1.assign(tmp12.begin(), tmp12.end());
	check_size_capacity(vector, vector1);
	
    ft::vector<int>::iterator it;
    size_t i = 0;
    for (it = vector1.begin(); it != vector1.end(); it++)
    {
		check(vector[i] == vector1[i]);
		i++;
    }

//	std::cout << "v size: " << vector.size() << ", capacity: " << vector.capacity() << std::endl;
//	std::cout << "v size: " << vector1.size() << ", capacity: " << vector1.capacity() << std::endl;
    v.push_back(vector[444]);
    
    v1.push_back(vector1[444]);
	check(vector[*(vector.end() - 1)] == vector1[*(vector1.end() - 1)]);


    v.push_back(vector.size());
    v1.push_back(vector1.size());


    v.push_back(vector.capacity());
    v1.push_back(vector1.capacity());

	check_size_capacity(v, v1);
	check_size_capacity(vector, vector1);
	check_size_capacity(tmp, tmp1);
	check_size_capacity(tmp2, tmp12);


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

//	std::cout << v1.size() << "," << v1.capacity() << std::endl;
	it = v.begin();
	it = v.erase(it);
	it1 = v1.begin();
	it1 = v1.erase(it1);
	check_size_capacity(v, v1);
}

void vector_erase_iterator()
{
	std::vector<int> v(42);
	ft::vector<int> v1(42);
	std::vector<int>::iterator it;
	ft::vector<int>::iterator	it1;

	for (size_t i = 0; i < 42; i++)
	{
		v[i] = i;
		v1[i] = i;
	}

	it = v.erase(v.begin() + 1, v.begin() + 1);
	it1 = v1.erase(v1.begin() + 1, v1.begin() + 1);
	check(v[1] == v1[1]);
	check_size_capacity(v, v1);
	v.push_back(1111);
	v1.push_back(1111);
	check(v[42] == v1[42]);
	check_size_capacity(v, v1);


	it = v.erase(v.begin()+ 1, v.begin() + 2);
	it1 = v1.erase(v1.begin()+ 1, v1.begin() + 2);
	check_size_capacity(v, v1);

	check(v[1] == v1[1]);
	check(v[2] == v1[2]);
	v.push_back(1111);
	v1.push_back(1111);
	check(v[42] == v1[42]);
//	std::cout << v[42] << "," << v1[42] << std::endl;
	check_size_capacity(v, v1);


	it = v.erase(v.begin()+ 10, v.end() - 10);
	it1 = v1.erase(v1.begin() + 10, v1.end() - 10);
	check_size_capacity(v, v1);
	check(v[10] == v1[10]);
	check(v[11] == v1[11]);

}

void	vector_insert()
{
	std::vector<int> v(42);	
	ft::vector<int> v1(42);	
	std::vector<int>::iterator it;
	ft::vector<int>::iterator it1;

	for (size_t i = 0; i < 42; i++)
	{
		v[i] = i;
		v1[i] = i;
	}

	it = v.begin() + 10;
	it1 = v1.begin() + 10;
	v.insert(it, 1, 30);
	v1.insert(it1, 1, 30);
	check(v[9] == v1[9]);
	check(v[10] == v1[10]);
	check(v[11] == v1[11]);
	check_size_capacity(v, v1);

	it = v.begin() + 15;
	it1 = v1.begin() + 15;
	v.insert(it, 5, 30);
	v1.insert(it1, 5, 30);
	check(v[14] == v1[14]);
	check(v[15] == v1[15]);
	check(v[16] == v1[16]);
	check(v[17] == v1[17]);
	check(v[18] == v1[18]);
	check(v[19] == v1[19]);
	check(v[20] == v1[20]);
	check_size_capacity(v, v1);

}

void	vector_insert_single()
{
	std::vector<int> v(42);	
	ft::vector<int> v1(42);	
	std::vector<int>::iterator it;
	ft::vector<int>::iterator it1;

	for (size_t i = 0; i < 42; i++)
	{
		v[i] = i;
		v1[i] = i;
	}
	it = v.begin() + 10;
	it1 = v1.begin() + 10;
	v.insert(it, 30);
	v1.insert(it1, 30);
	check(v[9] == v1[9]);
	check(v[10] == v1[10]);
	check(v[11] == v1[11]);
	check_size_capacity(v, v1);
}

void	vector_insert_range()
{
	std::vector<int> v(42);	
	ft::vector<int> v1(42);	
	std::vector<int>::iterator it;
	ft::vector<int>::iterator it1;
	std::vector<int> vc(9, 3);
	ft::vector<int> vc1(9, 3);

	for (size_t i = 0; i < 42; i++)
	{
		v[i] = i;
		v1[i] = i;
	}
	it = v.begin() + 10;
	it1 = v1.begin() + 10;
//	std::cout << "size: " << v.size() << "," << v1.size() << ". capacity " << v.capacity() << "," << v1.capacity() << std::endl;

//	std::cout << "distance: " << (vc.begin() + 1 - vc.end() - 2) << "," << (vc1.begin() +1 - vc1.end() - 2) << std::endl;
	check_size_capacity(v, v1);
	v.insert(it, vc.begin() + 1, vc.end() - 2);
	v1.insert(it1, vc1.begin() + 1, vc1.end() - 2);
//	check(v[9] == v1[9]);
//	check(v[10] == v1[10]);
//	check(v[11] == v1[11]);
//	std::cout << "size: " << v.size() << "," << v1.size() << ". capacity " << v.capacity() << "," << v1.capacity() << std::endl;
	check_size_capacity(v, v1);

}

void	vector_insert_range2()
{
	size_t _ratio = 1;

    std::vector<int> vector;
    ft::vector<int> vector1;
    std::vector<int> v;
    std::vector<int> tmp;
    ft::vector<int> v1;
    ft::vector<int> tmp1;

    tmp.assign(2600 * _ratio, 1);
    tmp1.assign(2600 * _ratio, 1);
	check_size_capacity(tmp, tmp1);

    vector.assign(4200 * _ratio, 1);
    vector1.assign(4200 * _ratio, 1);
	check_size_capacity(vector, vector1);

    vector.insert(vector.end() - 1000 * _ratio, tmp.begin(), tmp.end());
    vector1.insert(vector1.end() - 1000 * _ratio, tmp1.begin(), tmp1.end());
	check_size_capacity(vector, vector1);

    v.push_back(vector[3]);
    v1.push_back(vector1[3]);
	check_size_capacity(v, v1);

    v.push_back(vector.size());
    v1.push_back(vector1.size());
	check_size_capacity(v, v1);

    v.push_back(vector.capacity());
    v1.push_back(vector1.capacity());
	check_size_capacity(v, v1);

}


void	vector_pop_back()
{
	std::vector<int> v(42);	
	ft::vector<int> v1(42);	

	for (size_t i = 0; i < 42; i++)
	{
		v[i] = i;
		v1[i] = i;
	}
	v.pop_back();
	v1.pop_back();
	check(v[40] == v1[40]);
	check_size_capacity(v, v1);
	v.push_back(1);
	v1.push_back(1);
	check(v[41] == v1[41]);
	check_size_capacity(v, v1);
}

void	vector_pop_back_2()
{
	std::vector<std::string> vct(8);
	std::vector<std::string> vct2;
	std::vector<std::string>::iterator it = vct.begin();

	ft::vector<std::string> vctc(8);
	ft::vector<std::string> vctc2;
	ft::vector<std::string>::iterator it1 = vctc.begin();

	for (unsigned long int i = 0; i < vct.size(); ++i)
	{
		it[i] = std::string((vct.size() - i), i + 65);
		it1[i] = std::string((vctc.size() - i), i + 65);
	}
	vct.push_back("One long string");
	vct2.push_back("Another long string");
	vctc.push_back("One long string");
	vctc2.push_back("Another long string");
	check(vct.size() == vctc.size());
	check(vct2.size() == vctc2.size());
	vct.pop_back();
	vct2.pop_back();
	vctc.pop_back();
	vctc2.pop_back();
	check(vct.size() == vctc.size());
	check(vct2.size() == vctc2.size());

}

void	vector_swap_member()
{
	std::vector<int>	v1(42,42);
	std::vector<int>	v2(1,1);
	ft::vector<int>		v3(42,42);
	ft::vector<int>		v4(1,1);

	v1.swap(v2);
	v3.swap(v4);
	check_size_capacity(v1, v3);
	check_size_capacity(v2, v4);

}

void	vector_swap_member_2()
{
	std::vector<int>	foo(3, 15);
	std::vector<int>	bar(5,42);
	ft::vector<int>		foo1(3,15);
	ft::vector<int>		bar1(5,42);

	std::vector<int>::const_iterator	it_foo = foo.begin();
	std::vector<int>::const_iterator	it_bar = bar.begin();
	ft::vector<int>::const_iterator		it_foo1 = foo1.begin();
	ft::vector<int>::const_iterator		it_bar1 = bar1.begin();

	foo.swap(bar);
	foo1.swap(bar1);
	
	check_size_capacity(foo, foo1);
	check_size_capacity(bar, bar1);

	check(it_foo == bar.begin());
	check(it_bar == foo.begin());
	check(it_foo1 == bar1.begin());
	check(it_bar1 == foo1.begin());
//	std::cout << (it_foo1 == bar1.begin()) << std::endl;
//	std::cout << (it_bar1 == foo1.begin()) << std::endl;
//	v1.swap(v2);
//	v3.swap(v4);
	check_size_capacity(foo, foo1);
	check_size_capacity(bar, bar1);

}

void	vector_swap_no_member()
{
	std::vector<int>	v1(42,42);
	std::vector<int>	v2(1,1);
	ft::vector<int>		v3(42,42);
	ft::vector<int>		v4(1,1);

	swap(v1, v2);
	swap(v3, v4);
	check_size_capacity(v1, v3);
	check_size_capacity(v2, v4);
}

void	vector_resize_7()
{
	int _ratio = 10;
    std::vector<int> vector;
    std::vector<int> v;
    ft::vector<int> vector1;
    ft::vector<int> v1;

    vector.assign(9900 * _ratio, 1);
    vector1.assign(9900 * _ratio, 1);
	check_size_capacity(vector, vector1);

    vector.resize(5000 * _ratio);
    vector1.resize(5000 * _ratio);
	check_size_capacity(vector, vector1);

    vector.reserve(5000 * _ratio);
    vector1.reserve(5000 * _ratio);
	check_size_capacity(vector, vector1);

    v.push_back(vector.size());
    v1.push_back(vector1.size());
	check_size_capacity(v, v1);

    v.push_back(vector.capacity());
    v1.push_back(vector1.capacity());
	check_size_capacity(v, v1);

    vector.resize(7000 * _ratio);
    vector1.resize(7000 * _ratio);
	check_size_capacity(vector, vector1);
//	std::cout << vector.capacity() << "," << vector1.capacity()  << std::endl;;
	
    v.push_back(vector.size());
    v1.push_back(vector1.size());
	check_size_capacity(v, v1);

    v.push_back(vector.capacity());
    v1.push_back(vector1.capacity());

	check_size_capacity(v, v1);
//	std::cout << vector.capacity() << "," << vector1.capacity()  << std::endl;;

    vector.resize(15300 * _ratio, int());
    vector1.resize(15300 * _ratio, int());
	std::cout << std::endl;
	check_size_capacity(vector, vector1);
//	std::cout << vector.capacity() << "," << vector1.capacity()  << std::endl;;
	
    v.push_back(vector.size());
    v1.push_back(vector1.size());

	check_size_capacity(v, v1);
	check (v[v.size() - 1] == v1[v1.size() - 1]);
//	std::cout << v[v.size() - 1] << "," <<  v1[v1.size() - 1] << std::endl;;
//	std::cout << vector.capacity() << "," << vector1.capacity()  << std::endl;;
	
    v.push_back(vector.capacity());
    v1.push_back(vector1.capacity());
	check_size_capacity(v, v1);
	check (v[v.size() - 1] == v1[v1.size() - 1]);
//	std::cout << v[v.size() - 1] << "," <<  v1[v1.size() - 1] << std::endl;;
/*	
    v.push_back(vector[65]);
	*/

}

void vector_tests()
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
	
	test_case("vector: assign killer", &vector_assign_killer);
	
	test_case("vector: erase", &vector_erase);
	
	test_case("vector: erase2", &vector_erase2);
	
	test_case("vector: erase iterator", &vector_erase_iterator);
	
	test_case("vector: insert", &vector_insert);
	test_case("vector: insert single", &vector_insert_single);
	test_case("vector: insert range", &vector_insert_range);
	test_case("vector: insert range2", &vector_insert_range2);
	
	test_case("vector: pop back", &vector_pop_back);
	test_case("vector: pop back 2", &vector_pop_back_2);
	test_case("vector: swap, member function", &vector_swap_member);
	test_case("vector: swap, member function 2", &vector_swap_member_2);
	test_case("vector: swap, no member function", &vector_swap_no_member);
	
	test_case("vector: resize 7", &vector_resize_7);

}

int main(void)
{
	vector_tests();
	map_tests();
	stack_tests();
	set_tests();
	reverse_iterator_tests();
	more_iterators();

	std::cout << std::endl << "Benchmarks" << std::endl;
	vector_benchmark();
	map_benchmark();


}
