#ifndef RANDOM_ITERATOR
# define RANDOM_ITERATOR

#include "iterator_traits.hpp"
namespace ft{

	template <class T>
	class random_iterator
	{
		public:
			typedef typename ft::iterator_traits<T>::iterator_category iterator_category;
			typedef typename ft::iterator_traits<T>::difference_type difference_type;
			typedef typename ft::iterator_traits<T>::value_type	value_type;
			typedef typename ft::iterator_traits<T>::value_type* pointer;
			typedef typename ft::iterator_traits<T>::value_type& reference;

			random_iterator() : p(0) {}	
			random_iterator(pointer ptr) : p(ptr) {}

			template<class C>
			random_iterator(const random_iterator<C> &it) : p(&(*it)) {}

			//if isn't constant
//			random_iterator(random_iterator const &it) : p(it.p) {}
			random_iterator(random_iterator<const pointer> &it) : p(it.p) {}

			//iterator() {}
			//copy constructor?
			//destructor?
			reference operator*() const { return *this->p; }
			pointer operator->() { return p; }
			random_iterator& operator++() { p++; return *this; }
			random_iterator operator++(int) {
				random_iterator p_cpy = *this;
				++(*this);
				return (p_cpy);
			}
			random_iterator& operator--() { p--; return *this; }
			random_iterator operator--(int) {
				random_iterator p_cpy = *this;
				--(*this);
				return (p_cpy);
			}
			random_iterator& operator+=(difference_type i) { p += i; return (*this); }
			random_iterator& operator-=(difference_type i)	{ p -= i; return (*this); }
			random_iterator operator+(difference_type i) const { pointer p1; p1 = p + i; return (p1);};
			random_iterator operator-(difference_type i) const { pointer p1; p1 = p - i; return (p1);};

//			random_iterator& operator+(difference_type i) { return &p[i]; }
//			random_iterator& operator-(difference_type i)	{ return (this->(p - i)); }

			
//			random_iterator& operator=(const random_iterator<const pointer> &i) { this->p = i.p; return *this; }

			value_type& operator[](difference_type n) { return *(p + n);}
			pointer getData(void) const { return p; };

		private:
			pointer p;

	};

}
#endif
