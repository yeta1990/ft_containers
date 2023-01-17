#ifndef IS_INTEGRAL_HPP
# define IS_INTEGRAL_HPP
//https://cplusplus.com/reference/type_traits/is_integral/

namespace ft{

template <typename T>
struct is_integral {
//	typedef bool value_type;
	static const bool value = false;
//	typedef std::integral_constant<bool, value> type;
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
/*
template <typename T>
struct is_integral<size_t>{
	static const bool value = true;
};

template <typename T>
struct is_integral<bool>{
	static const bool value = true;
};

template <typename T>
struct is_integral<char>{
	static const bool value = true;
};

template <typename T>
struct is_integral<char16_t>{
	static const bool value = true;
};
*/
}
#endif
