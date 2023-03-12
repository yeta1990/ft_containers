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

namespace ft{

	// To be as faithful as possible to the implementation of the STL, 
	// the capacity (the allocated memory) increases as long as new elements
	// are inserted. If size is specified or can be deduced, that will be the 
	// allocated capacity. In some cases, the vector will allocate the bigger
	// number between the double of the current capacity and the given size.
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

			vector(void) : _allocator(Allocator())
			{
				this->_capacity = 0;
				this->_size = 0;
				this->_data = 0;
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
				_firstElement = _data;
				_lastElement = _data;
				this->resize(n, val);
				_lastElement = _data + n;
			};

			//about dispatchers:
			// the constructor, assign and insert methods, all with iterators, can 
			// lead to substitution issues during compilation. i.e. in vector<int, int>(1,2)
			// compilator will choose the vector iterator constructor. To prevent this,
			// we have the dispatchers, responsible for enable or disable, thanks to SFINAE,
			// the proper method

			//range constructor			
			template <class InputIterator>
			vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()) : _allocator(alloc) { 
				vector_range_dispatch(first, last);
			}
			

			//copy constructor
			vector (const vector& x)
			{
				this->_capacity = 0;
				this->_size = 0;
				this->_data = 0;
				this->_lastElement = 0;
				*this = x;
			}

			reference operator=( T& o)
			{
				*this = o;
				return (*this);
			}

			vector& operator=( const vector& other )
			{
				typename vector::const_iterator it;
				it = other.begin();

				destroy_and_deallocate();
				this->_size = other.size();
				this->_capacity = this->_size;

				this->_allocator = vector::allocator_type();
				if (this->_capacity > 0)
					this->_data = this->_allocator.allocate(this->_capacity);
				for (size_type i = 0; i < this->_size; i++)
				{
					this->_allocator.construct(&_data[i], *it);
					it++;
				}
				this->_lastElement = this->_data + this->_size;
				return (*this);
			}

			~vector(void) {
				destroy_and_deallocate();
			};

			//iterators	
			iterator begin() { return iterator(&this->_data[0]); }
			iterator end() { return iterator(this->_lastElement); }
			const_iterator begin() const { return const_iterator(&this->_data[0]); }
			const_iterator end() const { return const_iterator(this->_lastElement); }
            reverse_iterator rbegin() { return reverse_iterator(this->_data + this->_size); }
            reverse_iterator rend() { return reverse_iterator(this->_data);}
            const_reverse_iterator rbegin() const { return const_reverse_iterator(this->_data + this->_size); }
            const_reverse_iterator rend() const { return const_reverse_iterator(this->_data);}

			//element access
			reference at(size_type pos)
			{
				if (!(pos < this->_size))
					throw (std::out_of_range("vector"));
				return (this->_data[pos]);
			}

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

			reference front()
			{
				return (this->_data[0]);
			}

 			const_reference front() const
 			{
				return (this->_data[0]);
 			}

			reference back()
			{
				if (this->_size == 0)
					return (this->_data[0]);
				return (this->_data[this->_size - 1]);
			}

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

			//capacity
			size_type 	size() const {return (this->_size);};
			size_type 	max_size() const {return (this->_allocator.max_size());};

			void		resize(size_type n, value_type val = value_type())
			{
				if (n < this->_size)
				{
					erase(this->begin() + n, end());
				}
				else if (n > 0)
				{
					size_type old_size = this->_size;
					for (size_type i = 0; i < n - old_size; i++)
						push_back_with_custom_capacity(val, n);
				}
			}

			size_type 	capacity() const {return (this->_capacity);};
			bool 		empty() const {return (this->_size == 0 ? true : false);};
			void 		reserve (size_type n)
			{
				if (n == 0)
					return ;
				if (n > this->max_size())
					throw (std::length_error("'n' exceeds maximum supported size"));
				if (n > this->_capacity)
				{
					expansor(n);
				}
			}

			//modifiers
			void	assign (size_type n, const value_type& val)
			{
				assign_work_simple(n, val);
			}

			template <class InputIterator> 
			void 	assign(InputIterator first, InputIterator last)
			{
				assign_dispatch(first, last);
			}

			void 		clear()
			{
				for (size_t i = 0; i < this->_size; i++)
					this->_allocator.destroy(&this->_data[i]);
				this->_size = 0;
				this->_lastElement = this->_data;
			}

			//insert
			//insert single
			iterator insert (iterator pos, const value_type& value)
			{
				iterator 	it;
				size_type 	i;

				i = 0;
				for (it = this->begin(); it != pos; it++)
					i++;
				if (pos == end())
				{
					push_back(value);
					return (this->end() - 1);
				}
				insert(pos, 1, value);
				it = this->begin() + i;
				return (it);
			}

			//insert fill
			void insert (iterator pos, size_type n, const value_type& value)
			{
				insert_fill(pos, n, value);
			}

			//iterator range
			template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last)
			{
				insert_iterator_dispatch(position, first, last);
			}


			//erase
			iterator erase( iterator pos )
			{
				iterator it = this->end();
				
				if ( pos != it && pos + 1 != it)
				{
					std::copy(pos + 1, it, pos);
				}
				if (this->_size)
					this->_lastElement--;
				this->_allocator.destroy(&this->_data[this->_size - 1]);
				this->_size--;
				return (pos);
			}

			iterator erase( iterator first, iterator last )
			{
				iterator return_iterator;
				difference_type diff;

				diff = last - first;
				return_iterator = first;

				iterator end = this->end();
				if ( last != end)
				{
					std::copy(last, end, first);
				}
				for (difference_type i = 0; i < diff; i++)
					this->_allocator.destroy(&this->_data[this->_size - i - 1]);
				this->_size -= diff;
				this->_lastElement -= diff;
				return (first);
			}

			void		push_back(const value_type& val)
			{
				if (this->_size >= this->_capacity)
					expandCapacity(_size + 1);
				_size++;
				this->_allocator.construct(&this->_data[this->_size - 1], val);
				this->_lastElement++;
			}

			void		pop_back()
			{
				this->_allocator.destroy(&*(this->end() - 1));
				this->_size--;
				this->_lastElement--;
			}

			//swap
			void	swap (vector& x)
			{
				value_type*	dataSwap;
				value_type*	lastElementSwap;
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

				lastElementSwap = this->_lastElement;
				this->_lastElement = x._lastElement;
				x._lastElement = lastElementSwap;

			}

			//allocator
			allocator_type get_allocator(void) const { return (this->_allocator);};

		private:
			Allocator			_allocator;
			value_type*			_data;
			value_type*			_firstElement;
			value_type*			_lastElement;
			size_type			_capacity;
			size_type			_size;

			void	copyDataToOtherObject(value_type* _newData)
			{
				for (size_type i = 0; i < this->_size; i++)
					this->_allocator.construct(&_newData[i], this->_data[i]);
			};

			void	push_back_with_custom_capacity(const T& val, size_type custom_capacity)
			{
				if (custom_capacity > this->_capacity)
					expandCapacity(custom_capacity);
				_size++;
				this->_allocator.construct(&this->_data[this->_size - 1], val);
				this->_lastElement++;
			}

			void	setLastElement(void)
			{
				if (this->_size <= 0)
					return ;
				for (size_type i = 0; i < this->_size - 1; i++)
					this->_lastElement = &this->_data[i];
			};

			void	expansor(size_type new_capacity)
			{
				value_type*		_newData;

				try	
				{
					_newData = this->_allocator.allocate(new_capacity);
				}
				catch (std::bad_alloc &e)
				{
					throw (std::length_error("vector exceeds maximum supported size"));
				}
				copyDataToOtherObject(_newData);
				destroy_and_deallocate();
				this->_data = _newData;
				this->_capacity = new_capacity;
				this->_lastElement = this->_data + this->_size;
			}

			void	expandCapacity(size_type requiredCapacity)
			{
					size_type new_capacity = std::max(this->_capacity * 2, requiredCapacity);
					expansor(new_capacity);
			}

			void	destroy_and_deallocate(void)
			{
				if (this->_data && this->_capacity)
				{
					for (size_t i = 0; i < this->_size; i++)
						this->_allocator.destroy(&this->_data[i]);
					this->_allocator.deallocate(this->_data, this->_capacity);
				}
			}

			// enable_if is a way to use a conditional in a function prototype, among
			//other cases. This class is used in all dispatchers to check if the
			//parameters are iterators o integral types
			template <class Input>
			void	vector_range_dispatch(Input n, Input val, typename ft::enable_if<ft::is_integral<Input>::value >::type* = 0)
			{
				this->_capacity = 0;
				this->_size = 0;
				this->_data = 0;
				_firstElement = _data;
				_lastElement = _data;
				this->resize(n, val);
				_lastElement = _data + n;
			}

			// in this case enable_if is used also to choose the most efficient way to
			// construct the vector depending on the type of iterator. continue in
			// the next function
			template <class InputIterator>
			void	vector_range_dispatch(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0)
			{
				typedef typename ft::iterator_traits<InputIterator>::iterator_category iter_category;
				vector_constructor_range(first, last, iter_category());
				this->_lastElement = this->_data + this->_size;

			}

			// if the iterator is only able to be read once, we can't calculate the distance
			// between first and last, so push_back is used. it's inefficient,
			// compared to the next function, with more sophisticated iterators, but it's
			// the only way
			template <typename InputIterator>
			void	vector_constructor_range(InputIterator first, InputIterator last, std::input_iterator_tag)
			{
				InputIterator 	it;
				this->_size = 0;
				this->_capacity = 0;
				for (it = first; it != last; it++)
				{
					this->push_back(*it);
				}
			}

			template <typename InputIterator>
			void	vector_constructor_range(InputIterator first, InputIterator last, std::forward_iterator_tag)
			{
				InputIterator 	it;
				size_t			distance;
				size_t			i;

				i = 0;
				distance = std::distance(first, last);
				this->_size = distance;
				this->_capacity = this->_size;
				if (distance > 0)
					this->_data = this->_allocator.allocate(this->_size);
				else
					this->_data = 0;
				for (it = first; it != last; it++)
				{
					this->_allocator.construct(&_data[i], *it);
					i++;
				}
				this->_lastElement = this->_data + this->_size;
			}

			void insert_fill(iterator pos, size_type n, const value_type& value)
			{
				value_type*	_newData;
				iterator	it;
				size_type	_newSize;
				size_type	i;
				size_t new_capacity;

				if (n <= 0)
					return ;
				_newSize = this->_size + n;
				//if the given position is at the end(), the insert
				//is done via push_back
				if (pos == end() && this->_size + n < this->max_size())
				{
					for (size_type i = 0; i < n; i++)
					{
						push_back_with_custom_capacity(value, this->_size + n);
					}
					return ;
				}
				new_capacity = std::max(this->_capacity * 2, this->_size + n);
				
				try
				{
					if (_newSize > 0 && _newSize > this->_capacity)
					{
						_newData = this->_allocator.allocate(new_capacity);
					}
					else
					{
						_newData = this->_allocator.allocate(this->_capacity);
						new_capacity = this->_capacity;
					}
				}
				catch (std::bad_alloc &e)
				{
					throw (std::length_error("vector exceeds maximum supported size"));
				}
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
				this->_capacity = new_capacity;
				this->_data = _newData;
				this->_lastElement = this->_data + this->_size;
			}

			template <class InputIterator> 
			void 	assign_dispatch(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0)
			{
				typedef typename ft::iterator_traits<InputIterator>::iterator_category iter_category;
				assign_work_iterators(first, last, iter_category());
			}

			template <class Input> 
			void 	assign_dispatch(Input n, Input val, typename ft::enable_if<ft::is_integral<Input>::value >::type* = 0)
			{
				assign_work_simple(n, val);
			}

			void	assign_work_simple(size_type n, const value_type& val)
			{
				if (n == 0)
				{
					return ;
				}
				destroy_and_deallocate();
				this->_size = n;
				if (n > this->_capacity)
					this->_capacity = n;
				try	
				{
					this->_data = this->_allocator.allocate(this->_capacity);
				}
				catch (std::bad_alloc &e)
				{
					throw (std::length_error("vector exceeds maximum supported size"));
				}
				for (size_type i = 0; i < n; i++)
					this->_allocator.construct(&_data[i], val);
				this->_lastElement = this->_data + this->_size;

			}

			template <typename InputIterator>
			void	assign_work_iterators(InputIterator first, InputIterator last, std::input_iterator_tag)
			{
				InputIterator 	it;
				destroy_and_deallocate();
				value_type		*new_data;
				new_data = 0;
				this->_size = 0;
				this->_capacity = 0;
				this->_data = new_data;

				for (it = first; it != last; it++)
				{
					this->push_back(*it);
				}

			}

			template <typename InputIterator>
			void	assign_work_iterators(InputIterator first, InputIterator last, std::forward_iterator_tag)
			{
				InputIterator 	it;
				size_t			i;
				size_t			distance;
				size_t			new_capacity;
				value_type		*new_data;

				it = first;
				distance = std::distance(first, last);
				if (distance > this->_capacity)
					new_capacity = distance;
				else
					new_capacity = this->_capacity;
				if (distance > 0)
					new_data = this->_allocator.allocate(new_capacity);
				else
				{
					for (size_t i = 0; i < this->_size; i++)
						this->_allocator.destroy(&this->_data[i]);
					this->_size = 0;
					this->_lastElement = this->_data;
					return ;
				}
				i = 0;
				for (it = first; it != last; it++)
				{
					this->_allocator.construct(&new_data[i], *it);
					i++;
				}
				destroy_and_deallocate();
				this->_size = distance;
				this->_capacity = new_capacity;
				this->_data = new_data;
				this->_lastElement = this->_data + this->_size;
			}

			template <class InputIterator>
			void insert_iterator_dispatch(iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0)
			{

				typedef typename ft::iterator_traits<InputIterator>::iterator_category iter_category;
				insert_iterator(position, first, last, iter_category());
				this->_lastElement = this->_data + this->_size;
			}

			template <class Input>
			void insert_iterator_dispatch(iterator pos, Input n, Input value, typename ft::enable_if<ft::is_integral<Input>::value >::type* = 0)
			{

				insert_fill(pos, n, value);
			}

			template <class InputIterator>
			void insert_iterator(iterator position, InputIterator first, InputIterator last,std::input_iterator_tag) 
			{
				vector	v(begin(), position);
				InputIterator it;
				for (it = first; it != last; it++)
				{
					v.push_back(*it);
				}
				if (position != end())
					v.insert(v.end(), position, end());
				*this = v;
			}

			template <class InputIterator>
			void insert_iterator(iterator position, InputIterator first, InputIterator last, std::forward_iterator_tag)
			{
				difference_type diff;
				value_type*	_newData;
				iterator	it;	
				size_type	_newSize;
				size_type	_newCapacity ;
				size_type	i;

				diff = std::distance(first, last);
				_newSize = this->_size + diff;
				_newCapacity = std::max(this->_capacity * 2, _newSize);
				try	
				{
					if (_newCapacity > 0)
						_newData = this->_allocator.allocate(_newCapacity);
					else
						return ;
				}
				catch (std::bad_alloc &e)
				{
					throw (std::length_error("vector exceeds maximum supported size"));
				}

				i = 0;
				//copy elements before 'pos'
				for (it = this->begin(); it != position; it++)
				{
					this->_allocator.construct(&_newData[i], this->_data[i]);
					i++;
				}
					
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
				this->_capacity = _newCapacity;
				this->_data = _newData;
				this->_lastElement = this->_data + this->_size - 1;
			}
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


#endif
