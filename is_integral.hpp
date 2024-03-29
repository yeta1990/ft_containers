#ifndef IS_INTEGRAL_HPP
# define IS_INTEGRAL_HPP
//https://cplusplus.com/reference/type_traits/is_integral/

namespace ft{

template <typename T>
struct is_integral {
	static const bool value = false;
};

template <>
struct is_integral<bool>{
	static const bool value = true;
};

template <>
struct is_integral<char>{
	static const bool value = true;
};

template <>
struct is_integral<signed char>{
	static const bool value = true;
};

template <>
struct is_integral<short int>{
	static const bool value = true;
};

template <>
struct is_integral<int>{
	static const bool value = true;
};

template <>
struct is_integral<long int>{
	static const bool value = true;
};

template <>
struct is_integral<unsigned char>{
	static const bool value = true;
};
template <>
struct is_integral<unsigned short int>{
	static const bool value = true;
};

template <>
struct is_integral<unsigned int>{
	static const bool value = true;
};

template <>
struct is_integral<unsigned long int>{
	static const bool value = true;
};

//const
template <>
struct is_integral<const bool>{
	static const bool value = true;
};

template <>
struct is_integral<const char>{
	static const bool value = true;
};

template <>
struct is_integral<const signed char>{
	static const bool value = true;
};

template <>
struct is_integral<const short int>{
	static const bool value = true;
};

template <>
struct is_integral<const int>{
	static const bool value = true;
};

template <>
struct is_integral<const long int>{
	static const bool value = true;
};

template <>
struct is_integral<const unsigned char>{
	static const bool value = true;
};
template <>
struct is_integral<const unsigned short int>{
	static const bool value = true;
};

template <>
struct is_integral<const unsigned int>{
	static const bool value = true;
};

template <>
struct is_integral<const unsigned long int>{
	static const bool value = true;
};

//volatile
template <>
struct is_integral<volatile bool>{
	static const bool value = true;
};

template <>
struct is_integral<volatile char>{
	static const bool value = true;
};

template <>
struct is_integral<volatile signed char>{
	static const bool value = true;
};

template <>
struct is_integral<volatile short int>{
	static const bool value = true;
};

template <>
struct is_integral<volatile int>{
	static const bool value = true;
};

template <>
struct is_integral<volatile long int>{
	static const bool value = true;
};

template <>
struct is_integral<volatile unsigned char>{
	static const bool value = true;
};
template <>
struct is_integral<volatile unsigned short int>{
	static const bool value = true;
};

template <>
struct is_integral<volatile unsigned int>{
	static const bool value = true;
};

template <>
struct is_integral<volatile unsigned long int>{
	static const bool value = true;
};

//const volatile
template <>
struct is_integral<const volatile bool>{
	static const bool value = true;
};

template <>
struct is_integral<const volatile char>{
	static const bool value = true;
};

template <>
struct is_integral<const volatile signed char>{
	static const bool value = true;
};

template <>
struct is_integral<const volatile short int>{
	static const bool value = true;
};

template <>
struct is_integral<const volatile int>{
	static const bool value = true;
};

template <>
struct is_integral<const volatile long int>{
	static const bool value = true;
};

template <>
struct is_integral<const volatile unsigned char>{
	static const bool value = true;
};
template <>
struct is_integral<const volatile unsigned short int>{
	static const bool value = true;
};

template <>
struct is_integral<const volatile unsigned int>{
	static const bool value = true;
};

template <>
struct is_integral<const volatile unsigned long int>{
	static const bool value = true;
};

}
#endif
