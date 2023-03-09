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
//				std::cout << "eeeeo" << std::endl;
				this->_capacity = 0;
				this->_size = 0;
				this->_data = 0;
				this->_usedValues = 0;
				_firstElement = _data;
				_lastElement = _data;
				this->resize(n, val);
				_lastElement = _data + n;
			};

			//range constructor			
			template <class InputIterator>
			vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename ft::enable_if<!is_integral<InputIterator>::value >::type* = 0) : _allocator(alloc) { 

				typedef typename ft::iterator_traits<InputIterator>::iterator_category iter_category;
				vector_constructor_range(first, last, iter_category());
				this->_lastElement = this->_data + this->_size;
			}



			//copy constructor
			vector (const vector& x)
			{
				this->_capacity = 0;
				this->_size = 0;
				this->_data = 0;
				this->_usedValues = 0;
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

				this->_usedValues = this->_size;
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
//				std::cout << this->_size << "destructor" << this->_capacity << std::endl;
				destroy_and_deallocate();
			};


			//iterators	
			iterator begin() { return iterator(&this->_data[0]); }
			iterator end() { return iterator(this->_lastElement); }
//			iterator end() { return iterator(&this->_data[this->_size]); }
			const_iterator begin() const { return const_iterator(&this->_data[0]); }
			const_iterator end() const { return const_iterator(this->_lastElement); }
//			const_iterator end() const { return const_iterator(&this->_data[this->_size]); }
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

			//create template to handle input iterators...?
			//https://stackoverflow.com/questions/61889111/own-vector-assign-implementation
			//https://gcc.gnu.org/onlinedocs/libstdc++/libstdc++-html-USERS-4.1/stl__vector_8h-source.html#l00315
			template <class InputIterator> 
			void 	assign(InputIterator first, InputIterator last, typename ft::enable_if<!is_integral<InputIterator>::value >::type* = 0)
			{
				typedef typename ft::iterator_traits<InputIterator>::iterator_category iter_category;

				assign_work(first, last, iter_category());
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
			//this needs a huge refactor: is it necessary to allocate always?
			void insert (iterator pos, size_type n, const value_type& value)
			{
				value_type*	_newData;
				iterator	it;
				size_type	_newSize;
				size_type	i;
				size_t new_capacity;

				if (n <= 0)
					return ;
				_newSize = this->_size + n;
//				if (_newSize <= this->_capacity)
//					new_capacity = _newSize;
//				else
				new_capacity = std::max(this->_capacity * 2, this->_size + n);

				if (pos == end())
				{
					for (size_type i = 0; i < n; i++)
					{
						push_back_with_custom_capacity(value, new_capacity);
					}
					return ;
				}
//				std::cout << "new size: " << _newSize << "new capacity " << new_capacity;
				try
				{
					if (_newSize > 0 && _newSize > this->_capacity)
					{
						_newData = this->_allocator.allocate(new_capacity);
//						this->_capacity = new_capacity;
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
				this->_usedValues = this->_size;
				this->_lastElement = this->_data + this->_size;
			}

			//iterator range
			template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!is_integral<InputIterator>::value >::type* = 0)
			{

				typedef typename ft::iterator_traits<InputIterator>::iterator_category iter_category;

				insert_iterator(position, first, last, iter_category());
				this->_lastElement = this->_data + this->_size;
			}

			template <class InputIterator>
			void insert_iterator(iterator position, InputIterator first, InputIterator last,std::input_iterator_tag) 
			{
//				std::cout << "----->inserting here" << std::endl;
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

//				std::cout << "inserting here" << std::endl;
				diff = std::distance(first, last);

/*
				pointer res;
				res = this->_allocator.allocate(diff);

				InputIterator iter;	
				bool valid;
				valid = true;	
				difference_type j = 0;

				for (iter = first; iter != last; iter++)
				{
					try { res[j] = *iter; }
					catch(...) { valid = false; break ;}
					j++;
				}
				this->_allocator.deallocate(res, diff);
*/
//				if (!valid)
//					throw std::exception();

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
				this->_usedValues = this->_size;
				this->_capacity = _newCapacity;
				this->_data = _newData;
				this->_lastElement = this->_data + this->_size - 1;
			}

			//erase
			iterator erase( iterator pos )
			{
//				value_type*			_element;

//				_element = &this->_data[std::distance(begin(), pos) - 1];

				iterator it = this->end();
				
				if ( pos != it && pos + 1 != it)
				{
//					std::memmove(pos.getData(), (pos + 1).getData(), std::distance(pos + 1, end()));
					std::copy(pos + 1, it, pos);
				}
				if (this->_size)
					this->_lastElement--;
				this->_allocator.destroy(&this->_data[this->_size - 1]);
//				this->_allocator.destroy(_element);
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

			void		push_back(const value_type& val);

			void		pop_back()
			{
				this->_allocator.destroy(&*(this->end() - 1));
				this->_size--;
				this->_usedValues--;
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
			void	push_back_with_custom_capacity(const T& val, size_type custom_capacity);

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

			template <typename InputIterator>
			void	vector_constructor_range(InputIterator first, InputIterator last, std::input_iterator_tag)
			{
				InputIterator 	it;
				this->_size = 0;
				this->_capacity = 0;

				for (it = first; it != last; it++)
				{
					this->push_back(*it);
//					this->_lastElement++;
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

			template <typename InputIterator>
			void	assign_work(InputIterator first, InputIterator last, std::input_iterator_tag)
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
//					this->_lastElement++;
				}

			}

			template <typename InputIterator>
			void	assign_work(InputIterator first, InputIterator last, std::forward_iterator_tag)
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
