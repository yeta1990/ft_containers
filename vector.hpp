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
//https://lokiastari.com/blog/2016/02/27/vector/index.html
//https://en.cppreference.com/w/cpp/named_req/RandomAccessIterator
//https://codereview.stackexchange.com/questions/202157/basic-iterator-supporting-vector-implementation
//


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
				this->_capacity = 0;
				this->_size = 0;
				this->_data = this->_allocator.allocate(this->_capacity);
				_firstElement = _data;
				_lastElement = _data;

				std::cout << this->_allocator.max_size() << std::endl;
			};
			~vector(void) {};

			//iterators
			
			//capacity/
			bool empty() const
			{
				if (this->_size == 0)
					return (true);
				return (false);
			};
			size_type 	size() const {return (this->_size);};
			size_type 	max_size() const {return (this->_allocator.max_size());};
			size_type 	capacity() const {return (this->_capacity);};

			void		resize(size_type n, value_type val = value_type())
			{
			/*	
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

					*/
			};

			//element access
			
			//modifiers
			void	push_back(const value_type& val)
			{
				this->_size++;
				if (!isCapacityEnough())
					expandCapacity();
				this->_data[this->_size - 1] = val;
				this->_lastElement++;
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

			bool				isCapacityEnough(void)
			{
				if (this->_size == 1 && this->_capacity == 0)
					return (false);
				else if (this->_size == 2 && this->_capacity == 1)
					return (false);
				else if (this->_size == this->_capacity + 1)
					return (false);
				return (true);
			};

			void				copyDataToOtherObject(value_type* _newData)
			{
				for (size_type i = 0; i < this->_size - 1; i++)
					this->_data[i] = _newData[i];
			};
			
			void			setLastElement(void)
			{
				for (size_type i = 0; i < this->_size - 1; i++)
					this->_lastElement = &this->_data[i];
			};

			void				expandCapacity(void)
			{
			//	std::cout << "expanding capacity" << std::endl;
				value_type*		_newData;

				if (this->_capacity == 0)
					this->_capacity = 1;
				else
					this->_capacity *= 2;
				this->_data = this->_allocator.allocate(this->_capacity);
				copyDataToOtherObject(_newData);
				this->_allocator.deallocate(this->_data, this->_size - 1);
				_firstElement = _data;
				setLastElement();
				this->_data = _newData;
			};
	};
}
#endif
