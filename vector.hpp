#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <memory>
#include <iostream>
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

//resize:

namespace ft{
	template <class T, class Allocator = std::allocator<T> > 
	class vector
	{
		public:
			typedef T value_type;
			typedef std::allocator<value_type> allocator_type;
			typedef typename allocator_type::reference reference;
			typedef typename allocator_type::const_reference const_reference;
			typedef typename allocator_type::pointer pointer;
			typedef typename allocator_type::const_pointer const_pointer;
			typedef ptrdiff_t difference_type;	
			typedef size_t size_type;

			vector(void) 
			{
				this->_capacity = 3;
				this->_size = 0;
				this->_data = this->_allocator.allocate(this->_capacity);
				_firstElement = _data;
				_lastElement = _data;

				std::cout << this->_allocator.max_size() << std::endl;
			};
			~vector(void) {};

			//iterators
			
			//capacity
			size_type 	size() const {return (this->_size);};
			size_type 	max_size() const {return (this->_allocator.max_size());};
			size_type 	capacity() const {return (this->_capacity);};
		/*	void		resize(size_type n, value_type val = value_type())
			{
				if (n < this->_size)
				{
					// reduce to n first elements, remove and destroy the rest
					this->_size = n;
				}
				else if (n > this->_size && val)
				{
					// insert as many elements as needed to reach a size of n
					
				}
				else if (n > this->_size)
				{
				
				}
				if (n > this->_capacity)
					// content reallocation

			};
*/
			//element access
			
			//modifiers
			void	push_back(const value_type& val)
			{
				this->_size++;
				//if size || capacity == 0
				//else
				if (this->_size > this->_capacity)
				{
					//reallocation
					this->_capacity++;
				}
				this->_lastElement++;
				*_lastElement = val;
				std::cout << "added " << *_lastElement << std::endl;
			};

			//allocator
	
			allocator_type get_allocator(void) const { return (this->_allocator);};

		private:
			Allocator			_allocator;
			value_type*			_data;
			value_type*			_firstElement;
			value_type*			_lastElement;
			size_type	_capacity;
			size_type	_size;
	};
}
#endif
