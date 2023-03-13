#ifndef RANDOM_ITERATOR_HPP
# define RANDOM_ITERATOR_HPP

#include "iterator_traits.hpp"

//iterators
//https://leimao.github.io/blog/CPP-Const-Iterator/#Implementation-Without-Code-Duplication
namespace ft{
	// iterator used by vector
	template <class T>
	class random_iterator
	{
		public:
			typedef typename ft::iterator_traits<T>::iterator_category iterator_category;
			typedef typename ft::iterator_traits<T>::difference_type difference_type;
			typedef typename ft::iterator_traits<T>::value_type	value_type;
			typedef typename ft::iterator_traits<T>::pointer pointer;
			typedef typename ft::iterator_traits<T>::reference reference;

			random_iterator() : p(0) {}	
			random_iterator(pointer ptr) : p(ptr) {}

			//conversion from non-const C to const T
			template<class C>
			random_iterator(const random_iterator<C> &it) : p(&(*it)) {}

			random_iterator(random_iterator<const pointer> &it) : p(it.p) {}

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

			reference operator[](difference_type n) const { return (p[n]);}

			pointer getData(void) const { return p; };

		private:
			pointer p;

	};

//T and U
template <class T, class U>
bool operator==(const random_iterator<T> &a, const random_iterator<U> &b){
		return a.getData() == b.getData(); }

template <class T, class U>
typename ft::random_iterator<T>::difference_type operator-(const ft::random_iterator<T> &a, const ft::random_iterator<U> &b) { return (a.getData() - b.getData()); }

template <class T, class U>
bool operator<(const ft::random_iterator<T> &a, const ft::random_iterator<U> &b) { return (a.getData() < b.getData()); }

template <class T, class U>
bool operator>(const ft::random_iterator<T> &a, const ft::random_iterator<U> &b) { return b.getData() < a.getData(); }

template <class T, class U>
bool operator<=(const ft::random_iterator<T> &a, const ft::random_iterator<U> &b) { return (a.getData() <= b.getData()); }

template <class T, class U>
bool operator>=(const ft::random_iterator<T> &a, const ft::random_iterator<U> &b) { return b.getData() <= a.getData(); }

template <class T, class U>
bool operator!=(const ft::random_iterator<T> &a, const ft::random_iterator<U> &b){
				return a.getData() != b.getData();	}

template <class T>
typename ft::random_iterator<T> operator+(typename ft::random_iterator<T>::difference_type n, const ft::random_iterator<T> &a) {
	return (a.operator+(n));
}

template <class T>
typename ft::random_iterator<T> operator-(typename ft::random_iterator<T>::difference_type n, const ft::random_iterator<T> &a) {
	return (a.operator-(n));
}

}

#endif
