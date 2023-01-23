#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

//using namespace ft;
namespace ft{

//	template <class T>
//	class random_iterator;
//
//	template <class T, class Allocator = std::allocator<T> >
//	class vector;

	template< class Iter >
	class reverse_iterator{

		public:

			typedef Iter iterator_type ;
			typedef typename iterator_traits<Iter>::iterator_category iterator_category;

			reverse_iterator() : current() {} ;
			explicit reverse_iterator (iterator_type it)
			{
				current = it;
			}

		protected:
			iterator_type	current;


	};
}
#endif
