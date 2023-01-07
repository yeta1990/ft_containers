
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
	std::cout << std::endl;
	std::cout << std::endl;

	v.resize(10, 42);
	v1.resize(10, 42);
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
