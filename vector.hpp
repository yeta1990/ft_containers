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
			bool empty() const
			{
				if (this->_size == 0)
					return (true);
				return (false);
			};
			size_type 	size() const {return (this->_size);};
			size_type 	max_size() const {return (this->_allocator.max_size());};
			size_type 	capacity() const {return (this->_capacity);};



			//modifiers
			void	push_back(const value_type& val);
			void	resize(size_type n, value_type val = value_type());

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


			bool				isCapacityEnough(void)
			{
				if (this->_usedValues == this->_capacity)
					return (false);
				return (true);
			};

			void				copyDataToOtherObject(value_type* _newData)
			{
				std::cout << "used values: " << this->_usedValues << std::endl;
				//if (this->_usedValues == 0)
				//	return ;
				for (size_type i = 0; i < this->_usedValues; i++)
					this->_allocator.construct(&_newData[i], this->_data[i]);
			};
			
			void			setLastElement(void)
			{
				for (size_type i = 0; i < this->_size - 1; i++)
					this->_lastElement = &this->_data[i];
			};

			void				expansor(void)
			{
				value_type*		_newData;

				std::cout << "allocating " << this->_capacity << std::endl;
				_newData = this->_allocator.allocate(this->_capacity);
				copyDataToOtherObject(_newData);
				if (this->_usedValues > 0)
					this->_allocator.deallocate(this->_data, this->_capacity);
				_firstElement = _data;
				setLastElement();
				this->_data = _newData;
			};

			void				expandCapacity(void)
			{
				//value_type*		_newData;

				if (this->_capacity == 0)
					this->_capacity = 1;
				else
					this->_capacity *= 2;
				expansor();
			};

			void	expandCapacity(size_type capacity)
			{
				//value_type*		_newData;
				std::cout << "expanding to " << capacity << std::endl;
				this->_capacity = capacity;
				expansor();
			};

	};

}

#include "vector.tpp"

#endif
