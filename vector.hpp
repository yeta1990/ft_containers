#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <memory>
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include "iterator_traits.hpp"

//VECTOR
//https://www.geeksforgeeks.org/vector-in-cpp-stl/?ref=leftbar-rightbar
//https://towardsdatascience.com/c-basics-array-data-structure-c25b8ad4d32c
//https://cplusplus.com/reference/vector/vector/

//ALLOCATOR
//https://stackoverflow.com/questions/39273469/c-memory-allocation-upon-resizing-of-reserved-stdvector
//https://www.geeksforgeeks.org/stdallocator-in-cpp-with-examples/
//https://en.cppreference.com/w/cpp/memory/allocator
//

//vector && allocator
//https://stackoverflow.com/questions/17299951/c-vector-what-happens-whenever-it-expands-reallocate-on-stack
//https://lokiastari.com/blog/2016/02/27/vector/index.html
//https://en.cppreference.com/w/cpp/named_req/RandomAccessIterator
//https://codereview.stackexchange.com/questions/202157/basic-iterator-supporting-vector-implementation

//iterators
//https://leimao.github.io/blog/CPP-Const-Iterator/#Implementation-Without-Code-Duplication


//resize:

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

			random_iterator() : p(nullptr) {}	
			random_iterator(pointer ptr) : p(ptr) {}
			//if isn't constant
			random_iterator(random_iterator const &it) : p(it.p) {}

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

			//random_iterator& operator=(const random_iterator &i) { this->p = i.p; return *this; }

			value_type& operator[](difference_type n) { return *(p + n);}
			friend bool operator<(const random_iterator &a, const random_iterator &b) { return (a.p < b.p); }
			friend bool operator>(const random_iterator &a, const random_iterator &b) { return b.p < a.p; }
			friend bool operator<=(const random_iterator &a, const random_iterator &b) { return (a.p <= b.p); }
			friend bool operator>=(const random_iterator &a, const random_iterator &b) { return b.p <= a.p; }
			friend bool operator==(const random_iterator &a, const random_iterator &b){
				return a.p == b.p; }
			friend bool operator!=(const random_iterator &a, const random_iterator &b){
				return a.p != b.p;
			}

		private:
			pointer p;

	};

	template <class T, class Allocator = std::allocator<T> > 
	class vector
	{
		public:
			typedef T value_type;
			typedef std::allocator<value_type> allocator_type;
			typedef value_type& reference;
			typedef typename allocator_type::const_reference const_reference;
			typedef typename allocator_type::pointer pointer;
			typedef typename allocator_type::const_pointer const_pointer;
			typedef size_t size_type;
			typedef random_iterator<pointer> iterator;
			typedef random_iterator<const_pointer> const_iterator;
			typedef typename ft::iterator_traits<iterator>::difference_type difference_type;


			vector(void) 
			{
				this->_capacity = 0;
				this->_size = 0;
				this->_data = nullptr;
				this->_usedValues = 0;
				_firstElement = _data;
				_lastElement = _data;

			};

			~vector(void) {};

			//iterators	
			iterator begin() { return iterator(&this->_data[0]); }
			iterator end() { return iterator(&this->_data[this->_size]); }
			const_iterator begin() const { return const_iterator(&this->_data[0]); }
			const_iterator end() const { return const_iterator(&this->_data[this->_size]); }

			//element access
			reference operator[](size_type pos)
			{
				return (this->_data[pos]);
			};

			const_reference operator[](size_type pos) const
			{
				return (this->_data[pos]);
			};

			reference at(size_type n);
			const_reference at(size_type n) const;
			reference front();
 			const_reference front() const;
			reference back();
			const_reference back() const;
			pointer data();
			const_pointer data() const;

			//capacity/
			size_type 	size() const {return (this->_size);};
			size_type 	max_size() const {return (this->_allocator.max_size());};
			void		resize(size_type n, value_type val = value_type());
			size_type 	capacity() const {return (this->_capacity);};
			bool 		empty() const {return (this->_size == 0 ? true : false);};
			void 		reserve (size_type n);
			void 		shrink_to_fit(); //TBD

			//modifiers
			void 		clear();
			//insert
			iterator insert( const_iterator pos, const T& value );
			iterator insert( const_iterator pos, size_type count, const T& value );
			template< class InputIt >
			iterator insert( const_iterator pos, InputIt first, InputIt last );

			//erase
			void		push_back(const value_type& val);
			//pop_back
			//resize
			//swap



			value_type	usedValues(void)
			{
				return (this->_usedValues);
			};
			//allocator

			allocator_type get_allocator(void) const { return (this->_allocator);};

		private:
			Allocator			_allocator;
			value_type*			_data;
			value_type*			_firstElement;
			value_type*			_lastElement;
			size_type			_capacity;
			size_type			_size;
			size_type			_usedValues;


			void	copyDataToOtherObject(value_type* _newData)
			{
				//std::cout << "used values: " << this->_usedValues << std::endl;
				for (size_type i = 0; i < this->_usedValues; i++)
					this->_allocator.construct(&_newData[i], this->_data[i]);
			};

			void			setLastElement(void)
			{
				for (size_type i = 0; i < this->_size - 1; i++)
					this->_lastElement = &this->_data[i];
			};

			void				expansor(void);
			void	expandCapacity(size_type requiredCapacity);

	};
}

#include "vector.tpp"

#endif
