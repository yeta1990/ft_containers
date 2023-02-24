#ifndef EQUAL_HPP
# define EQUAL_HPP

namespace ft{

template< class InputIt1, class InputIt2 >
bool equal( InputIt1 first1, InputIt1 last1,
            InputIt2 first2 )
{
	InputIt1	it;
	InputIt2	it2;
	for(it = first1, it2 = first2; it != last1; it++, it2++)
	{
		if (*it != *it2)
			return (false);
	}
	return (true);
}

}

#endif
