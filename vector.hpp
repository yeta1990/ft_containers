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
#include "random_iterator.hpp"
#include "lexicographical_compare.hpp"
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

	template <class T, class Allocator = std::allocator<T> >
	class vector
	{
		public:
			typedef T value_type;
			typedef Allocator allocator_type;
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

			vector(void) : _allocator(Allocator())
			{
				this->_capacity = 0;
				this->_size = 0;
				this->_data = 0;
				this->_usedValues = 0;
				_firstElement = _data;
				_lastElement = _data;
			};

			//constructors
			//default constructor
			explicit vector (const allocator_type& alloc) : _allocator(alloc)
			{
				this->_capacity = 0;
				this->_size = 0;
				this->_data = 0;
				this->_usedValues = 0;
				_firstElement = _data;
				_lastElement = _data;
			};

			//fill constructor
			explicit vector (size_type n, const value_type& val = value_type(),
					const allocator_type& alloc = allocator_type()) : _allocator(alloc)
			{
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
			vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename ft::enable_if<!is_integral<InputIterator>::value >::type* = 0) : _allocator(alloc) { 
				InputIterator 	it;
				size_t			distance;
				size_t			i;

				i = 0;
//				this->_allocator = alloc;
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
				ft::vector<int>::const_iterator it;
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
//				std::cout << this->_size << "destructor" << this->_capacity << std::endl;
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

			const_reference at(size_type n) const
			{
	if (!(n < this->_size))
		throw (std::out_of_range("vector"));
	return (this->_data[n]);

			}

			reference operator[](size_type pos)
			{
				return (this->_data[pos]);
			};

			const_reference operator[](size_type pos) const
			{
				return (this->_data[pos]);
			};

			reference front();
 			const_reference front() const
 			{
				return (this->_data[0]);
 			}
			reference back();
			const_reference back() const
			{
	if (this->_size == 0)
		return (this->_data[0]);
	return (this->_data[this->_size - 1]);

			}
			pointer data()
			{
				return (this->_data);
			}
			const_pointer data() const
			{
				return (this->_data);
			}

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
				size_t			distance;

				it = first;
				i = 0;
				distance = 0;
				if (first == last)
				{
					for (size_t i = 0; i < this->_size; i++)
						this->_allocator.destroy(&this->_data[i]);
					this->_size = 0;
					return ;
				}
				destroy_and_deallocate();
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
				difference_type diff;
				value_type*	_newData;
				iterator	it;	
				size_type	_newSize;
				size_type	i;

				diff = 0;
				InputIterator aux;

				aux = first;
//				std::cout << "eeeooo" << std::endl;
				while (aux!= last)
				{
					diff++;
					aux++;
				}
//				diff = last - first;
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
				for (difference_type j = 0; j < diff; j++)
				{
					this->_allocator.construct(&_newData[i], *first);
					first++;
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
//				if (this->_size > 1)
					_newData = this->_allocator.allocate(this->_capacity - 1);
//				else
//				{
//					this->_size = 0;					
//					return iterator(this->_data);
//				}
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

				if (this->_capacity > 0)
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
				for (size_type i = 0; i < this->_size; i++)
					this->_allocator.construct(&_newData[i], this->_data[i]);
			};

			void			setLastElement(void)
			{
				if (this->_size <= 0)
					return ;
				for (size_type i = 0; i < this->_size - 1; i++)
					this->_lastElement = &this->_data[i];
			};

			void				expansor(size_type new_capacity);
			void	expandCapacity(size_type requiredCapacity);
			void	destroy_and_deallocate(void);

	};


template <class T, class Alloc>  
void swap (ft::vector<T,Alloc>& x, ft::vector<T,Alloc>& y)
{
		x.swap(y);
}

template< class T, class Alloc >
bool operator==( const ft::vector<T,Alloc>& lhs,
                 const ft::vector<T,Alloc>& rhs )
{
	if (lhs.size() != rhs.size())
		return (false);
	for (typename ft::vector<T>::size_type i = 0; i < lhs.size(); i++)
	{
		if (lhs[i] != rhs[i])
			return (false);
	}
	return (true);
}

template< class T, class Alloc >
bool operator!=( const ft::vector<T,Alloc>& lhs,
                 const ft::vector<T,Alloc>& rhs )
{
	if (lhs.size() != rhs.size())
		return (true);
	for (typename ft::vector<T>::size_type i = 0; i < lhs.size(); i++)
	{
		if (lhs[i] != rhs[i])
			return (true);
	}
	return (false);
}

template< class T, class Alloc >
bool operator<( const ft::vector<T,Alloc>& lhs,
                const ft::vector<T,Alloc>& rhs )
{
	return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
}

template< class T, class Alloc >
bool operator>( const ft::vector<T,Alloc>& lhs,
                const ft::vector<T,Alloc>& rhs )
{
	return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));
}

template< class T, class Alloc >
bool operator<=( const ft::vector<T,Alloc>& lhs,
                const ft::vector<T,Alloc>& rhs )
{
	return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())  || (lhs == rhs));
}

template< class T, class Alloc >
bool operator>=( const ft::vector<T,Alloc>& lhs,
                const ft::vector<T,Alloc>& rhs )
{
	return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()) || (lhs == rhs));
}

}
#include "vector.tpp"


#endif
