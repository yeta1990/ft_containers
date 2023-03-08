
#include "tests.hpp"
#include <ctime>
#include <sys/time.h>
class timer
{
public:
    timer();

public:
    long get_time();
    void reset();

private:
    struct timeval stamp;
};

timer::timer()
{
    reset();
}

long timer::get_time()
{
    struct timeval now;
    struct timeval diff;

    gettimeofday(&now, NULL);
    timersub(&now, &stamp, &diff);

    return diff.tv_sec * 1000 + diff.tv_usec / 1000;
}

void timer::reset()
{
    gettimeofday(&stamp, NULL);
}

timer	t;

//unsigned long _ratio = 300000;
unsigned long _ratio = 300;

void	vec_b_insert()
{
	ft::vector<int> vector;
	std::vector<int> vector2;
	std::vector<int> v;
	std::vector<int> tmp;

	tmp.assign(2600 * _ratio, 1);
	vector.assign(4200 * _ratio, 7);

	std::cout << "inserting " << tmp.size() << " elements in a vector of size " << vector.size() << std::endl;
    t = timer();
	vector.insert(vector.begin(), tmp.begin(), tmp.end());
	std::cout << "ft: " << t.get_time();

	for (size_t i = 0; i < tmp.size(); ++i) {
		v.push_back(vector[i]);
	}
	v.push_back(vector.size());
	v.push_back(vector.capacity());

//	tmp.assign(2600 * _ratio, 1);
    t = timer();
	vector2.assign(4200 * _ratio, 7);
	vector2.insert(vector2.begin(), tmp.begin(), tmp.end());
	std::cout << " vs std: " << t.get_time();

	for (size_t i = 0; i < tmp.size(); ++i) {
		v.push_back(vector2[i]);
	}
	v.push_back(vector2.size());
	v.push_back(vector2.capacity());

//	return v;

}

void	vec_b_erase()
{
	ft::vector<int> vector;
	std::vector<int> vector1;
    std::vector<int> v;
    std::vector<int> v1;

    for (unsigned long i = 0; i < 9900 * _ratio; ++i)
        vector.push_back(i);
    t = timer();
    
//    vector.erase(vector.begin() + 8 * _ratio);
    v.push_back(*(vector.erase(vector.begin() + 8 * _ratio)));
    
	std::cout << "ft: " << t.get_time();
//    g_end2 = timer();
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

#define MAXRAM (std::numeric_limits<int>::max())
#define MAXSIZE ((std::size_t)MAXRAM / sizeof(int))

void	vec_b_insert_heavy()
{

    for (int i = 0; i < 2; ++i) {
        ft::vector<int> v;

        for (std::size_t i = 0; i < MAXSIZE / 2; ++i) {
            v.insert(v.end(), rand());
            if (i % 100000 == 0)
            	std::cout << i << std::endl;
        }
//        BLOCK_OPTIMIZATION(v);
    }
}

void	vector_benchmark()
{
//	test_case("vector: benchmark insert std iterators->", &vec_b_insert);
//	test_case("vector: benchmark insert std iterators->", &vec_b_erase);
	test_case("vector: benchmark insert std iterators->", &vec_b_insert_heavy);

}
