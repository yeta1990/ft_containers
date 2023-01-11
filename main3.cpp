
#include "vector.hpp"
#include <vector>


int main(void)
{
	std::vector<int> v(7,20);
	ft::vector<int> v1(7,20);

	std::vector<int>::iterator it = v.begin();
	ft::vector<int>::iterator it2 = v1.begin();

	int start_size = 7;
	for (int i = 2; i < start_size; ++i)
		it[i] = (start_size - i) * 3;

	start_size = 7;
	for (int i = 2; i < start_size; ++i)
		it2[i] = (start_size - i) * 3;

	it = v.begin();
	it2 = v1.begin();

	for (int i = 0; i < 7; i++)
	{
		std::cout << "- " << *it << std::endl;
		it++;
	}
	std::cout << std::endl;
	
	for (int i = 0; i < 7; i++)
	{
		std::cout << "- " << *it2 << std::endl;
		it2++;
	}
	std::cout << "capacity: " << v.capacity() << "," << v1.capacity() << std::endl;
	std::cout << "size: " << v.size() << "," << v1.size() << std::endl;

	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "resize 10, 42" << std::endl;

	v.resize(11, 42);
	v1.resize(11, 42);
	it = v.begin();
	it2 = v1.begin();
	for (int i = 0; i < 11; i++)
	{
		std::cout << "- " << *it << std::endl;
		it++;
	}
	std::cout << std::endl;
	for (int i = 0; i < 11; i++)
	{
		std::cout << "- " << *it2 << std::endl;
		it2++;
	}
	std::cout << "capacity: " << v.capacity() << "," << v1.capacity() << std::endl;
	std::cout << "size: " << v.size() << "," << v1.size() << std::endl;

	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << "resize 18, 43" << std::endl;
	v.resize(18, 43);
	v1.resize(18, 43);
	it = v.begin();
	it2 = v1.begin();

	for (int i = 0; i < 18; i++)
	{
		std::cout << "- " << *it << std::endl;
		it++;
	}
	std::cout << std::endl;
	for (int i = 0; i < 18; i++)
	{
		std::cout << "- " << *it2 << std::endl;
		it2++;
	}
	std::cout << "capacity: " << v.capacity() << "," << v1.capacity() << std::endl;
	std::cout << "size: " << v.size() << "," << v1.size() << std::endl;


	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "resize 10" << std::endl;
	v.resize(10);
	v1.resize(10);
	it = v.begin();
	it2 = v1.begin();

	for (int i = 0; i < 10; i++)
	{
		std::cout << "- " << *it << std::endl;
		it++;
	}
	std::cout << std::endl;
	for (int i = 0; i < 10; i++)
	{
		std::cout << "- " << *it2 << std::endl;
		it2++;
	}
	std::cout << "capacity: " << v.capacity() << "," << v1.capacity() << std::endl;
	std::cout << "size: " << v.size() << "," << v1.size() << std::endl;

	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "resize 23, 44" << std::endl;
	v.resize(23, 44);
	v1.resize(23, 44);
	it = v.begin();
	it2 = v1.begin();

	for (int i = 0; i < 23; i++)
	{
		std::cout << "- " << *it << std::endl;
		it++;
	}
	std::cout << std::endl;
	for (int i = 0; i < 23; i++)
	{
		std::cout << "- " << *it2 << std::endl;
		it2++;
	}
	std::cout << "capacity: " << v.capacity() << "," << v1.capacity() << std::endl;
	std::cout << "size: " << v.size() << "," << v1.size() << std::endl;


	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "resize 5" << std::endl;
	v.resize(5);
	v1.resize(5);
	it = v.begin();
	it2 = v1.begin();

	for (int i = 0; i < 5; i++)
	{
		std::cout << "- " << *it << std::endl;
		it++;
	}
	std::cout << std::endl;
	for (int i = 0; i < 5; i++)
	{
		std::cout << "- " << *it2 << std::endl;
		it2++;
	}
	std::cout << "capacity: " << v.capacity() << "," << v1.capacity() << std::endl;
	std::cout << "size: " << v.size() << "," << v1.size() << std::endl;


	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "reserve 5" << std::endl;
	v.reserve(5);
	v1.reserve(5);
	it = v.begin();
	it2 = v1.begin();

	for (int i = 0; i < 5; i++)
	{
		std::cout << "- " << *it << std::endl;
		it++;
	}
	std::cout << std::endl;
	for (int i = 0; i < 5; i++)
	{
		std::cout << "- " << *it2 << std::endl;
		it2++;
	}
	std::cout << "capacity: " << v.capacity() << "," << v1.capacity() << std::endl;
	std::cout << "size: " << v.size() << "," << v1.size() << std::endl;


	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "reserve 3" << std::endl;
	v.reserve(5);
	v1.reserve(5);
	it = v.begin();
	it2 = v1.begin();

	for (int i = 0; i < 3; i++)
	{
		std::cout << "- " << *it << std::endl;
		it++;
	}
	std::cout << std::endl;
	for (int i = 0; i < 3; i++)
	{
		std::cout << "- " << *it2 << std::endl;
		it2++;
	}
	std::cout << "capacity: " << v.capacity() << "," << v1.capacity() << std::endl;
	std::cout << "size: " << v.size() << "," << v1.size() << std::endl;
	

	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "resize 87" << std::endl;
	v.resize(87);
	v1.resize(87);
	it = v.begin();
	it2 = v1.begin();

	for (int i = 0; i < 6; i++)
	{
		std::cout << "- " << *it << std::endl;
		it++;
	}
	std::cout << std::endl;
	for (int i = 0; i < 6; i++)
	{
		std::cout << "- " << *it2 << std::endl;
		it2++;
	}
	std::cout << "capacity: " << v.capacity() << "," << v1.capacity() << std::endl;
	std::cout << "size: " << v.size() << "," << v1.size() << std::endl;


	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "resize 5" << std::endl;
	v.resize(5);
	v1.resize(5);
	it = v.begin();
	it2 = v1.begin();

	for (int i = 0; i < 5; i++)
	{
		std::cout << "- " << *it << std::endl;
		it++;
	}
	std::cout << std::endl;
	for (int i = 0; i < 5; i++)
	{
		std::cout << "- " << *it2 << std::endl;
		it2++;
	}
	std::cout << "capacity: " << v.capacity() << "," << v1.capacity() << std::endl;
	std::cout << "size: " << v.size() << "," << v1.size() << std::endl;

	std::vector<int> v2;
	ft::vector<int> v3;

	std::cout << "empty: " << v2.empty() << "," << v3.empty() << std::endl;		
	std::cout << "operator= " << std::endl;
	v2 = v;
	v3 = v1;	
	std::cout << "empty: " << v2.empty() << "," << v3.empty() << std::endl;		

	it = v2.begin();
	it2 = v3.begin();
	std::cout << std::endl;
	for (int i = 0; i < 5; i++)
	{
		std::cout << "- " << *it << std::endl;
		it++;
	}
	std::cout << std::endl;
	for (int i = 0; i < 5; i++)
	{
		std::cout << "- " << *it2 << std::endl;
		it2++;
	}
	std::cout << "capacity: " << v2.capacity() << "," << v3.capacity() << std::endl;
	std::cout << "size: " << v2.size() << "," << v3.size() << std::endl;

}

/*
int	main(void)
{
	//asigning const_iterator to non-const vector -> compiles

	std::vector<int> vv;
	std::vector<int const>::const_iterator itit;

	itit = vv.begin();

	// but custom vector doesn't compile yet
	ft::vector<int>	v;
	ft::vector<int>::iterator it;

	v.push_back(42);
	it = v.begin();
	std::cout << *it << std::endl;
	
	ft::vector<int>	vc;
	ft::vector<int const>::const_iterator ci;

	ci = vc.begin();
	
	ft::vector<int>		v2(20,20);

	std::cout << v2.size() << std::endl;
}
*/
