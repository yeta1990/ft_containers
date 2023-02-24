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
			}

			template <class Iter1>
			reverse_iterator (const reverse_iterator<Iter1>& rev_it)
			{
				*this = rev_it;
			}

			template< class U >
			reverse_iterator& operator=( const reverse_iterator<U>& other )
			{
				this->current = other.base();
				return (*this);
			}

			iterator_type base() const
			{
				return (this->current);
			}

			reference operator*() const
			{
				Iter tmp = current;
				return *(--tmp);
//				return *--tmp;
			}

			pointer operator->() const
			{
				return &(operator*());
			}
			reference operator[] (difference_type n) const { return (base()[-n-1]);	}
			reverse_iterator& operator++() { current = current - 1; return (*this); }
			reverse_iterator& operator--() { current = current + 1; return (*this);	}
			reverse_iterator operator++( int ) { iterator_type tmp = current;
					--current; return(reverse_iterator(tmp));	}
			reverse_iterator operator--( int ) { iterator_type tmp = current;
					++current; return(reverse_iterator(tmp));	}
			reverse_iterator operator+( difference_type n ) const {	return (reverse_iterator(current - n));	}
			reverse_iterator operator-( difference_type n ) const {	return (reverse_iterator(current + n));	}
			reverse_iterator& operator+=( difference_type n ) { current -= n; return (*this); }
			reverse_iterator& operator-=( difference_type n ) { current += n; return (*this); }

		protected:
			iterator_type	current;

	};

template< class Iterator1, class Iterator2 >
bool operator==( const ft::reverse_iterator<Iterator1>& lhs,
                 const ft::reverse_iterator<Iterator2>& rhs )
{ return (lhs.base() == rhs.base()); }

template< class Iterator1, class Iterator2 >
bool operator!=( const ft::reverse_iterator<Iterator1>& lhs,
                 const ft::reverse_iterator<Iterator2>& rhs )
{ return (lhs.base() != rhs.base()); }

template< class Iterator1, class Iterator2 >
bool operator<( const ft::reverse_iterator<Iterator1>& lhs,
                const ft::reverse_iterator<Iterator2>& rhs )
{ return (lhs.base() > rhs.base()); }

template< class Iterator1, class Iterator2 >
bool operator<=( const ft::reverse_iterator<Iterator1>& lhs,
                 const ft::reverse_iterator<Iterator2>& rhs )
{ return (lhs.base() >= rhs.base()); }

template< class Iterator1, class Iterator2 >
bool operator>( const ft::reverse_iterator<Iterator1>& lhs,
                const ft::reverse_iterator<Iterator2>& rhs )
{ return (lhs.base() < rhs.base()); }

template< class Iterator1, class Iterator2 >
bool operator>=( const ft::reverse_iterator<Iterator1>& lhs,
                 const ft::reverse_iterator<Iterator2>& rhs )
{ return (lhs.base() <= rhs.base()); }

template <class T>
typename ft::reverse_iterator<T> operator+(int n, const ft::reverse_iterator<T> &a)
{
	return (a.operator+(n));
}

template <class T, typename U>
typename ft::reverse_iterator<T>::difference_type operator-(const ft::reverse_iterator<T> &a, const ft::reverse_iterator<U> &b) { return (b.base() - a.base()); }


}
#endif
