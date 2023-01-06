#ifndef ITERATOR_TRAITS_HPP
# define ITERATOR_TRAITS_HPP

//#include <iterator>

namespace ft
{
	template< class T >
	struct iterator_traits
	{
		typedef typename T::value_type			value_type;
		typedef typename T::difference_type		difference_type;
		typedef typename T::pointer				pointer;
		typedef typename T::reference			reference;
		typedef typename T::iterator_category	iterator_category;
	};

	template< class Iter >
	struct iterator_traits<Iter*>
	{
		typedef Iter						value_type;
		typedef std::ptrdiff_t					difference_type;
		typedef Iter*						pointer;
		typedef Iter&						reference;
		typedef std::random_access_iterator_tag iterator_category;
	};

	template< class Iter >
	struct iterator_traits<const Iter*>
	{
		typedef Iter							value_type;
		typedef ptrdiff_t					 	difference_type;
		typedef const Iter * 					pointer;
		typedef const Iter & 					reference;
		typedef std::random_access_iterator_tag	iterator_category;
	};

}
#endif
