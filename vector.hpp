#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <memory>
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include "iterator_traits.hpp"
#include "enable_if.hpp"
#include "is_integral.hpp"
#include "reverse_iterator.hpp"

//#include "is_iterator.hpp"

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

			random_iterator() : p(0) {}	
			random_iterator(pointer ptr) : p(ptr) {}

			template<class C>
			random_iterator(const random_iterator<C> &it) : p(&(*it)) {}

			//if isn't constant
			//random_iterator(random_iterator const &it) : p(it.p) {}
			//random_iterator(random_iterator<const pointer> &it) : p(it.p) {}

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
			typedef ft::reverse_iterator<iterator> reverse_iterator;
			typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
			typedef typename iterator_traits<iterator>::difference_type difference_type;

			//member functions
			
			//constructors
			//default constructor
			explicit vector (const allocator_type& alloc = allocator_type())
			{
				this->_allocator = alloc;
				this->_capacity = 0;
				this->_size = 0;
				this->_data = 0;
				this->_usedValues = 0;
				_firstElement = _data;
				_lastElement = _data;
			};

			//fill constructor
			explicit vector (size_type n, const value_type& val = value_type(),                 const allocator_type& alloc = allocator_type())
			{
				this->_allocator = alloc;
				this->_capacity = 0;
				this->_size = 0;
				this->_data = 0;
				this->_usedValues = 0;
				_firstElement = _data;
				_lastElement = _data;
				this->resize(n, val);
			};

			//range constructor			
			template <class InputIterator>
			vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename ft::enable_if<!is_integral<InputIterator>::value >::type* = 0){
				InputIterator 	it;
				size_t			distance;
				size_t			i;

				i = 0;
				this->_allocator = alloc;
				distance = 0;
				for (it = first; it != last; it++)
					distance++;
				this->_size = distance;
				this->_capacity = this->_size;
				this->_data = this->_allocator.allocate(this->_size);
				for (it = first; it != last; it++)
				{
					this->_allocator.construct(&_data[i], *it);
					i++;
				}
			}

			//copy constructor
			vector (const vector& x)
			{
				*this = x;
			}

			reference operator=( T& o)
			{
				*this = o;
				return (*this);
			}

			vector& operator=( const vector& other )
			{
				ft::vector<int>::iterator it;
				it = other.begin();

				this->_size = other.size();
				this->_capacity = this->_size;
				this->_usedValues = this->_size;
				this->_data = this->_allocator.allocate(this->_size);

				for (size_type i = 0; i < this->_size; i++)
				{
					this->_allocator.construct(&_data[i], *it);
					it++;
				}
				return (*this);
			}

			~vector(void) {
				destroy_and_deallocate();
//				this->_allocator.deallocate(this->_data, this->_size);
			};

			/*vector(const vector& x);
			vector(const vector&, const Allocator&);

			template <class InputIterator>         
			vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());


			*/


			//iterators	
			iterator begin() { return iterator(&this->_data[0]); }
			iterator end() { return iterator(&this->_data[this->_size]); }
			const_iterator begin() const { return const_iterator(&this->_data[0]); }
			const_iterator end() const { return const_iterator(&this->_data[this->_size]); }
            reverse_iterator rbegin() { return reverse_iterator(this->_data + this->_size); }
            reverse_iterator rend() { return reverse_iterator(this->_data);}
            const_reverse_iterator rbegin() const { return const_reverse_iterator(this->_data + this->_size); }
            const_reverse_iterator rend() const { return const_reverse_iterator(this->_data);}

			//element access

			reference at(size_type pos);

			const_reference at(size_type n) const;

			reference operator[](size_type pos)
			{
				return (this->_data[pos]);
			};

			const_reference operator[](size_type pos) const
			{
				return (this->_data[pos]);
			};

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


			void	assign (size_type n, const value_type& val);

//			https://www.internalpointers.com/post/quick-primer-type-traits-modern-cpp
//			template <class iterator >

			template <class InputIterator> 
			void 	assign(InputIterator first, InputIterator last, typename ft::enable_if<!is_integral<InputIterator>::value >::type* = 0)
			{
				InputIterator 	it;
				size_t			i;

				it = first;
				i = 0;
				destroy_and_deallocate();

				size_t			distance;

				distance = 0;
				for (it = first; it != last; it++)
					distance++;
				this->_size = distance;
				this->_capacity = this->_size;
				this->_data = this->_allocator.allocate(this->_size);
				for (it = first; it != last; it++)
				{
					this->_allocator.construct(&_data[i], *it);
					i++;
				}
			}

			void 		clear();
			//insert
			//insert single
			iterator insert (iterator pos, const value_type& value)
			{
				iterator 	it;
				size_type 	i;

				i = 0;
				for (it = this->begin(); it != pos; it++)
					i++;
				insert(pos, 1, value);
				it = this->begin() + i;
				return (it);
			}

			//insert fill
			void insert (iterator pos, size_type n, const value_type& value)
			{
				value_type*	_newData;
				iterator	it;
				size_type	_newSize;
				value_type	i;

				_newSize = this->_size + n;
				_newData = this->_allocator.allocate(_newSize);
				i = 0;
				//copy elements before 'pos'
				for (it = this->begin(); it != pos; it++)
				{
					this->_allocator.construct(&_newData[i], this->_data[i]);
					i++;
				}
				//insert new elements
				for (size_type j = 0; j < n; j++)
				{
					this->_allocator.construct(&_newData[i], value);
					i++;
				}
				//copy the rest of the elements
				for (it = pos; it != this->end(); it++)
				{
					this->_allocator.construct(&_newData[i], this->_data[i - n]);
					i++;
				}
				destroy_and_deallocate();
				this->_size = _newSize;
				this->_capacity = this->_size;
				this->_data = _newData;
				this->_usedValues = this->_size;
			}

			//iterator range
			template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!is_integral<InputIterator>::value >::type* = 0)
			{
				size_type diff;
				value_type*	_newData;
				iterator	it;	
				size_type	_newSize;
				size_type	i;

				diff = last - first;
				_newSize = this->_size + diff;
				_newData = this->_allocator.allocate(_newSize);
				i = 0;
				//copy elements before 'pos'
				for (it = this->begin(); it != position; it++)
				{
					this->_allocator.construct(&_newData[i], this->_data[i]);
					i++;
				}
				//insert new elements
				for (size_type j = 0; j < diff; j++)
				{
					this->_allocator.construct(&_newData[i], *(first + j));
					i++;
				}
				//copy the rest of the elements
				for (it = position; it != this->end(); it++)
				{
					this->_allocator.construct(&_newData[i], this->_data[i - diff]);
					i++;
				}
				if (this->_size > 0)
					destroy_and_deallocate();
				this->_size = _newSize;
				this->_usedValues = this->_size;
				this->_capacity = this->_size;
				this->_data = _newData;

			}

			//erase
			iterator erase( iterator pos )
			{
				value_type*	_newData;
				iterator	it;	
				size_type	_newSize;

				_newSize = 0;
				_newData = this->_allocator.allocate(this->_capacity - 1);
				for (it = this->begin(); it != pos; it++)
				{
					this->_allocator.construct(&_newData[_newSize], this->_data[_newSize]);
					_newSize++;
				}
				iterator	return_iterator(_newData);
				return_iterator += _newSize;
				for (it = pos + 1; it != this->end(); it++)
				{
					this->_allocator.construct(&_newData[_newSize], this->_data[_newSize + 1]);
					_newSize++;
				}

				if (this->_size > 0)
					destroy_and_deallocate();
				this->_size = _newSize;
				this->_usedValues = this->_size;
				this->_data = _newData;
				return (return_iterator);
			}

			iterator erase( iterator first, iterator last )
			{
				iterator return_iterator;
				difference_type diff;

				diff = last - first;
				return_iterator = first;
				for (difference_type i = 0; i < diff; i++)
					return_iterator = erase(return_iterator);
				return (return_iterator);
			}
			
			void		push_back(const value_type& val);

			void		pop_back()
			{

				this->_allocator.destroy(&*(this->end() - 1));
				this->_size--;
				this->_usedValues--;
			}

			//swap
			void	swap (vector& x)
			{
				value_type*	dataSwap;
				size_type	capacitySwap;
				size_type	sizeSwap;
				
				dataSwap = this->_data;
				this->_data = x._data;
				x._data = dataSwap;
				capacitySwap = this->_capacity;
				this->_capacity = x._capacity;
				x._capacity = capacitySwap;
				sizeSwap = this->_size;
				this->_size = x._size;
				x._size = sizeSwap;
				this->_usedValues = this->_size;
				x._usedValues = x._size;
			}

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
				if (this->_size <= 0)
					return ;
				for (size_type i = 0; i < this->_size - 1; i++)
					this->_lastElement = &this->_data[i];
			};

			void				expansor(void);
			void	expandCapacity(size_type requiredCapacity);
			void	destroy_and_deallocate(void);

	};

}

template <class T, class Alloc>  
void swap (ft::vector<T,Alloc>& x, ft::vector<T,Alloc>& y)
{
		x.swap(y);
}

namespace ft{
template <class T, typename U>
bool operator==(const ft::random_iterator<T> &a, const ft::random_iterator<U> &b){
		return a.getData() == b.getData(); }

template <class T, typename U>
typename ft::random_iterator<T>::difference_type operator-(const ft::random_iterator<T> &a, const ft::random_iterator<U> &b) { return (a.getData() - b.getData()); }

template <class T, typename U>
bool operator<(const ft::random_iterator<T> &a, const ft::random_iterator<U> &b) { return (a.getData() < b.getData()); }

template <class T, typename U>
bool operator>(const ft::random_iterator<T> &a, const ft::random_iterator<U> &b) { return b.getData() < a.getData(); }

template <class T, typename U>
bool operator<=(const ft::random_iterator<T> &a, const ft::random_iterator<U> &b) { return (a.getData() <= b.getData()); }

template <class T, typename U>
bool operator>=(const ft::random_iterator<T> &a, const ft::random_iterator<U> &b) { return b.getData() <= a.getData(); }

template <class T, typename U>
bool operator!=(const ft::random_iterator<T> &a, const ft::random_iterator<U> &b){
				return a.getData() != b.getData();
			}
}
#include "vector.tpp"


#endif
