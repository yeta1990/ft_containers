#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <memory>
#include <iostream>
#include <algorithm>
#include <stdexcept>
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
			//typedef typename allocator_type::reference reference;
			typedef value_type& reference;
			typedef typename allocator_type::const_reference const_reference;
			typedef typename allocator_type::pointer pointer;
			typedef typename allocator_type::const_pointer const_pointer;
			typedef ptrdiff_t difference_type;
			typedef size_t size_type;

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
			
			//element access
			reference operator[](size_type pos)
			{
				return (this->_data[pos]);
			};

			const_reference operator[](size_type pos) const
			{
				return (this->_data[pos]);
			};

			//capacity/
			size_type 	size() const {return (this->_size);};
			size_type 	max_size() const {return (this->_allocator.max_size());};
			void		resize(size_type n, value_type val = value_type());
			size_type 	capacity() const {return (this->_capacity);};
			bool 		empty() const {return (this->_size == 0 ? true : false);};
			void 		reserve (size_type n);
			void 		shrink_to_fit(); //TBD
			void		push_back(const value_type& val);

			//modifiers


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
