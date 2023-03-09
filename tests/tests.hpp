#ifndef TESTS_HPP
# define TESTS_HPP

#include <string>
#include "vector.hpp"
#include <vector>

void check(bool test);



template <class T>
void check_size_capacity(std::vector<T>& v, ft::vector<T>& v1);

void test_case(std::string name, void (*test)());
void	reverse_iterator_tests();
void	more_iterators();
void	map_tests();
void	stack_tests();
void	set_tests();
void	map_constructor();
void	vector_benchmark();
void	map_benchmark();

/*
std::string s_string[32] = {                                                                   \
        "QExoqp0nICr0sXsHqty2", "naax9QcpJhvaL7DezsNQ", "25ZTtB6wbptfbxM8AvHB",                    \
        "tShYNtc0MkdjqLrOatgz", "7Z3kf1Qec0NnsLSEpbOt", "WhkSNrKJC966fvjZ2Or1",                    \
        "8vlxlFRRgW7yYj4GO7dt", "5sq1aoT8zP0HaHj3nFOK", "61Dv31GYZhkgjKCErpng",                    \
        "l0IIcWWHhOcPzoxEamQM", "bE1RYclskwXlhCm46YFs", "kXeoi5qz94JYPqSDTs79",                    \
        "TFsQP1dz8VVos9KzUpY0", "b3wYQR7An193gjgYuRj3", "xSmyNsnSJ47jLqrvbpyr",                    \
        "guAIP2Wq43Gf8VhHsyu5", "yT6c2loPebHovnq9BQog", "3qvU1xcVm2g1DKFDlqh4",                    \
        "L0q8RR9P41VD4sVjdnWl", "YdjESsIZM4b1oGQPjpBe", "l1ZVQbWKw7brHUSimJgq",                    \
        "xdn0cf4vqRzpfXWtl10G", "lYnZvpqaV0s8DowMZwzV", "8P1cyKrwJNLoJyvLjYqO",                    \
        "4MhOXNbAX23CEijO5cRT", "tHe3miAwCOVQbuoLaEP2", "l6uNLsc8fiLl3eWoG6j6",                    \
        "477xt6l0lph9ALQdr4HX", "D9UJNe4s8YF02LhrwOdl", "dLCisBNOdE8yugntu6cj",                    \
        "YvY4aQFHgAuagn4dFLO1", "eGR6Dtv7LW75qlV5Fkik"                                             \
    };                                                                                             \

*/
#endif
