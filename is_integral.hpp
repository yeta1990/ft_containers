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
