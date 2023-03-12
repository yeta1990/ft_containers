#ifndef IS_INTEGRAL_HPP
# define IS_INTEGRAL_HPP
//https://cplusplus.com/reference/type_traits/is_integral/

namespace ft{

template <typename T>
struct is_integral {
	static const bool value = false;
};

template <>
struct is_integral<int>{
	static const bool value = true;
};

template <>
struct is_integral<unsigned int>{
	static const bool value = true;
};

template <>
struct is_integral<char>{
	static const bool value = true;
};

template <>
struct is_integral<unsigned long>{
	static const bool value = true;
};


template <>
struct is_integral<bool>{
	static const bool value = true;
};

}
#endif
