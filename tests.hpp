#ifndef TESTS_HPP
# define TESTS_HPP

void check(bool test);

template <class T>
void check_size_capacity(std::vector<T> v, ft::vector<T> v1);

void test_case(std::string name, void (*test)());

#endif
