#include <vector>
#include <iostream>

int main(void)
{
	std::vector<int>			v1;	
	std::vector<int>::iterator	it;

	v1.push_back(42);
	v1.push_back(43);
	v1.push_back(44);
	v1.push_back(45);
	it = v1.begin();

	it++;
	it++;
	it++;
	it--;
	std::cout << *it << std::endl;
	it -= 2;
	std::cout << *it << std::endl;
	for (int i = 0; i < 100; i++)
	{
		*it = 1;
		std::cout << *it << std::endl;
		it++;
	}

	it--;
	std::cout << *it << std::endl;
	it--;
	std::cout << *it << std::endl;
	std::cout << v1.size() << std::endl;

	std::cout << it[5] << std::endl;
	std::cout << v1[5] << std::endl;


	
}
