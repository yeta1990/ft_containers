#ifndef TESTS_HPP
# define TESTS_HPP

#include <string>
#include "vector.hpp"
#include <vector>

void check(bool test);
template <class T>
void check_size_capacity(std::vector<T> v, ft::vector<T> v1);
void test_case(std::string name, void (*test)());
void	reverse_iterator_tests();
void	more_iterators();

#endif
