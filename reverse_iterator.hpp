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
			typedef typename iterator_traits<Iter>::value_type value_type;
 			typedef typename iterator_traits<Iter>::difference_type difference_type;
			typedef typename iterator_traits<Iter>::pointer pointer;
			typedef typename iterator_traits<Iter>::reference reference;

			reverse_iterator() : current() {} ;
			explicit reverse_iterator (iterator_type it)
			{
				current = it;
				p = it - 1;
			}

//			template <class Iter>
//			reverse_iterator (const reverse_iterator<Iter>& rev_it);

			template< class U >
			reverse_iterator& operator=( const reverse_iterator<U>& other )
			{
				this->current = other.current;
				this->p = other.p;
				return (*this);
			}

			iterator_type base() const
			{
				return (this->current);
			}

			reference operator*() const
			{
				Iter tmp = current;
				return *--tmp;
			}

			pointer operator->() const
			{
				return &(operator*());
			}

			reverse_iterator& operator--()
			{
				p = p - 1;
				return (p);
			}


		protected:
			iterator_type	current;
			iterator_type	p;

	};
}
#endif
