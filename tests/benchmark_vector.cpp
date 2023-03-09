#include "tests.hpp"
#include <limits>
#include "benchmarks.hpp"

class timer;

//_ratio = 100;

void	vec_b_insert()
{
	ft::vector<int> vector;
	std::vector<int> vector2;
	std::vector<int> v;
	std::vector<int> tmp;

	tmp.assign(2600 * _ratio, 1);
	vector.assign(4200 * _ratio, 7);

	std::cout << "inserting " << tmp.size() << " elements from a std vector in a ft vector of size " << vector.size() << std::endl;
    t = timer();
	vector.insert(vector.begin(), tmp.begin(), tmp.end());
	std::cout << "ft: " << t.get_time();

	for (size_t i = 0; i < tmp.size(); ++i) {
		v.push_back(vector[i]);
	}
	v.push_back(vector.size());
	v.push_back(vector.capacity());

    t = timer();
	vector2.assign(4200 * _ratio, 7);
	vector2.insert(vector2.begin(), tmp.begin(), tmp.end());
	std::cout << " vs std: " << t.get_time();

	for (size_t i = 0; i < tmp.size(); ++i) {
		v.push_back(vector2[i]);
	}
	v.push_back(vector2.size());
	v.push_back(vector2.capacity());

}

void	vec_b_erase()
{
	ft::vector<int> vector;
	std::vector<int> vector1;
    std::vector<int> v;
    std::vector<int> v1;

    for (unsigned long i = 0; i < 9900 * _ratio; ++i)
    {
        vector.push_back(i);
    }
	std::cout << "erasing the element " << (8 * _ratio) << "in a vector of size " << vector.size() << std::endl;

    t = timer();
    v.push_back(*(vector.erase(vector.begin() + 8 * _ratio)));
	std::cout << "ft: " << t.get_time();
    v.push_back(*(vector.begin() + 82 * _ratio));
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    

    for (unsigned long i = 0; i < 9900 * _ratio; ++i)
        vector1.push_back(i);
    t = timer();
    v1.push_back(*(vector1.erase(vector1.begin() + 8 * _ratio)));
	std::cout << "std: " << t.get_time();
    v1.push_back(*(vector1.begin() + 82 * _ratio));
    v1.push_back(vector1.size());
    v1.push_back(vector1.capacity());

//    check_size_capacity(

}


void	vec_b_insert_heavy()
{
    t = timer();
    for (int i = 0; i < 2; ++i) {
        ft::vector<int> v;

        for (std::size_t i = 0; i < MAXSIZE / 3; ++i) {
            v.insert(v.end(), rand());
        }
    }
	std::cout << "ft: " << t.get_time();

    t = timer();
    for (int i = 0; i < 2; ++i) {
        std::vector<int> v;

        for (std::size_t i = 0; i < MAXSIZE / 3; ++i) {
            v.insert(v.end(), rand());
        }
    }
	std::cout << "std: " << t.get_time();
}

void	vec_b_erase_value()
{
	ft::vector<int> vector;
	std::vector<int> vector1;
    std::vector<int> v;
   
	std::cout << "eooo" << std::endl;
    for (unsigned int i = 0; i < 4000 * _ratio; ++i)
    {
        vector.push_back(i);
        v.push_back(i);
    }

    t = timer();
	for (unsigned int i = 0; i < 400; i++)
	{
		if (i % 2 == 0)
			vector.erase(vector.begin() + i);
		else 
			vector.erase(vector.end() - i);
	}
	vector.insert(vector.begin() + 1000 * _ratio, v.begin() + 2000 * _ratio, v.begin() + 3500 * _ratio);
	std::cout << "ft: " << t.get_time();

    for (unsigned int i = 0; i < 4000 * _ratio; ++i)
        vector1.push_back(i);

    t = timer();
	for (unsigned int i = 0; i < 400; i++)
	{
		if (i % 2 == 0)
			vector1.erase(vector1.begin() + 1);
		else 
			vector1.erase(vector1.end() - 1);
	}
	vector1.insert(vector1.begin() + 1000 * _ratio, v.begin() + 2000 * _ratio, v.begin() + 3500 * _ratio);

	std::cout << "std: " << t.get_time();
}


void	vector_benchmark()
{
	test_case("vector: benchmark insert std iterators->", &vec_b_insert);
	test_case("vector: benchmark erase->", &vec_b_erase);
	test_case("vector: benchmark insert heavy->", &vec_b_insert_heavy);
	test_case("vector: benchmark erase value->", &vec_b_erase_value);

}
