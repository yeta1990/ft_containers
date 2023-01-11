#ifndef VECTOR_TPP
# define VECTOR_TPP
#include "vector.hpp"
namespace ft{

template <class T, class Allocator>
void	vector<T, Allocator>::expandCapacity(size_type requiredCapacity)
{
//	if (this->_capacity == 0)
//		this->_capacity = 1;
//	else 

	this->_capacity = std::max(this->_capacity * 2, requiredCapacity);
//	this->_capacity = std::max(this->_size * 2, requiredCapacity);
	expansor();

}

template <class T, class Allocator>
void	vector<T, Allocator>::expansor(void)
{
	value_type*		_newData;

//	std::cout << "allocating " << this->_capacity << std::endl;
	_newData = this->_allocator.allocate(this->_capacity);
	copyDataToOtherObject(_newData);
//	std::cout << "allocating " << this->_capacity << std::endl;
	if (this->_usedValues > 0)
	{
		for (size_t i = 0; i < this->_capacity; i++)
			this->_allocator.destroy(&this->_data[i]);
		this->_allocator.deallocate(this->_data, this->_capacity);
	}
	_firstElement = _data;
	setLastElement();
	this->_data = _newData;
}

template <class T, class Allocator>
void	vector<T, Allocator>::push_back(const T& val)
{
	_size++;
	if (this->_size > this->_capacity)
		expandCapacity(_size);
	this->_usedValues++;
	this->_allocator.construct(&this->_data[this->_usedValues - 1], val);
	this->_lastElement++;
}

template <class T, class Allocator>
void	vector<T, Allocator>::resize(size_type n, value_type val)
{
	//std::cout << "------resizing to " << n << std::endl;
//	resize when there is content in the vector fails, why?
//
	if (n < this->_size)
	{
		this->_size = n;
		this->_usedValues = n;
	}
	else if (n > this->_size)
	{
		if (n > this->_capacity)
		{
			this->_capacity = std::max(this->_size * 2, n);
			expansor();
		//	expandCapacity(n);

//			std::cout << "capacity: " << this->_capacity << std::endl;
//			std::cout << "used values: " << this->_usedValues << std::endl;
//			std::cout << "n: " << n << std::endl;
			}
		for (size_t i = this->_usedValues; i < n; i++)
		{
			//std::cout << "used values: " << this->_usedValues << std::endl;
			this->_allocator.construct(&this->_data[this->_usedValues], val);
			this->_usedValues++;
		}
		this->_size = n;
	}
//	std::cout << "------resizing to " << n << std::endl;
}

template <class T, class Allocator>
void 	vector<T, Allocator>::reserve (size_type n)
{
	if (n > this->max_size())
		throw (std::length_error("'n' exceeds maximum supported size"));
	if (n > this->_capacity)
	{
		this->_capacity = n;
		expansor();
	}
}

template <class T, class Allocator>
void	vector<T, Allocator>::clear()
{
	this->_size = 0;
}

template <class T, class Allocator>
T& vector<T, Allocator>::at(size_type n)
{
	if (n >= this->_size)
		throw (std::out_of_range("out of range error"));
	return (*this[n]);
}

template <class T, class Allocator>
typename std::allocator<T>::const_reference vector<T, Allocator>::at(size_type n) const
{
	if (n >= this->_size)
		throw (std::out_of_range("out of range error"));
	return (*this[n]);
}

template <class T, class Allocator>
T& vector<T, Allocator>::front()
{
	return (this->_data[0]);
}

template <class T, class Allocator>
typename std::allocator<T>::const_reference vector<T, Allocator>::front() const
{
	return (this->_data[0]);
}

template <class T, class Allocator>
T& vector<T, Allocator>::back()
{
	if (this->_size == 0)
		return (this->_data[0]);
	return (this->_data[this->_size - 1]);
}

template <class T, class Allocator>
typename std::allocator<T>::const_reference vector<T, Allocator>::back() const
{
	if (this->_size == 0)
		return (this->_data[0]);
	return (this->_data[this->_size - 1]);
}

template <class T, class Allocator>
typename std::allocator<T>::pointer vector<T, Allocator>::data()
{
	return (this->_data);
}

template <class T, class Allocator>
typename std::allocator<T>::const_pointer vector<T, Allocator>::data() const
{
	return (this->_data);
}

}
#endif
