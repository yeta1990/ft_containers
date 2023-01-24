#ifndef LEXICOGRAPHICAL_COMPARE
# define LEXICOGRAPHICAL_COMPARE

//https://en.cppreference.com/w/cpp/algorithm/lexicographical_compare
//true if the first range is lexicographically less than the second, otherwise false.

namespace ft{

template< class InputIt1, class InputIt2 >
bool lexicographical_compare( InputIt1 first1, InputIt1 last1,
                              InputIt2 first2, InputIt2 last2 )
{
	for (; first1 != last1 && first2 != last2; first1++, first2++)
	{
		if (*first1 < *first2)
			return (true);
		else if (*first1 > *first2)
			return (false);
	}
	return (first1 == last1) && (first2 != last2);
}
}

#endif
