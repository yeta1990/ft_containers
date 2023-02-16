#ifndef VECTOR_TPP
# define VECTOR_TPP
#include "vector.hpp"
namespace ft{

template <class T, class Allocator>
void	vector<T, Allocator>::expandCapacity(size_type requiredCapacity)
{
	size_type new_capacity = std::max(this->_capacity * 2, requiredCapacity);
	expansor(new_capacity);
}

template <class T, class Allocator>
void	vector<T, Allocator>::destroy_and_deallocate(void)
{
//	std::cout << this->_data << "," << this->_size << "," << this->_capacity << std::endl;
	if (this->_data && this->_capacity)
	{
		for (size_t i = 0; i < this->_size; i++)
			this->_allocator.destroy(&this->_data[i]);
		this->_allocator.deallocate(this->_data, this->_capacity);
	}
}

template <class T, class Allocator>
void	vector<T, Allocator>::expansor(size_type new_capacity)
{
	value_type*		_newData;

//	std::cout << "old capacity is " << this->_capacity << "new capacity is " << new_capacity << std::endl;
	_newData = this->_allocator.allocate(new_capacity);
	copyDataToOtherObject(_newData);
	if (this->_size > 0)
		destroy_and_deallocate();
	_firstElement = _data;
	setLastElement();
	this->_data = _newData;
	this->_capacity = new_capacity;

}

template <class T, class Allocator>
void	vector<T, Allocator>::push_back(const T& val)
{
	if (this->_size >= this->_capacity)
		expandCapacity(_size + 1);
	_size++;
	this->_usedValues++;
	this->_allocator.construct(&this->_data[this->_size - 1], val);
	this->_lastElement++;
}

template <class T, class Allocator>
void	vector<T, Allocator>::resize(size_type n, value_type val)
{
//	std::cout << "------resizing to " << n << std::endl;
//	resize when there is content in the vector fails, why?
//
	if (n < this->_size)
	{
		//remove and destroy elements beyond n
		for (size_t i = n; i < this->_size; i++)
			this->_allocator.destroy(&this->_data[i]);
		this->_size = n;
		this->_usedValues = n;
		//destroy_and_deallocate();
	}
	else if (n > this->_size)
	{
		if (n > this->_capacity)
		{
			size_t new_capacity = std::max(this->_size * 2, n);
			expansor(new_capacity);
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
//		this->_capacity = n;
		expansor(n);
	}
}

template <class T, class Allocator>
void	vector<T, Allocator>::assign(size_type n, const value_type& val)
{
	if (n == 0)
		return ;
//	if (n > this->_capacity)
//	{
		destroy_and_deallocate();
		this->_size = n;
	if (n > this->_capacity)
		this->_capacity = n;
//	}
//	else
//	{
//		this->_allocator.deallocate(this->_data, this->_size);
//		this->_size = n;
//		this->_usedValues = this->_size;
//		this->_capacity = n;
//	}
	this->_data = this->_allocator.allocate(this->_size);
	for (size_type i = 0; i < n; i++)
		this->_allocator.construct(&_data[i], val);
	this->_usedValues = this->_size;
}
	

template <class T, class Allocator>
void	vector<T, Allocator>::clear()
{
	this->_size = 0;
}



template <class T, class Allocator>
T& vector<T, Allocator>::at(size_type pos)
{
	if (!(pos < this->_size))
		throw (std::out_of_range("vector"));
	return (this->_data[pos]);
}

/*
template <class T, class Allocator>
typename ft::vector<T>::const_reference vector<T, Allocator>::at(size_type n) const
{
	if (!(n < this->_size))
		throw (std::out_of_range("vector"));
	return (this->_data[n]);
}
*/
template <class T, class Allocator>
T& vector<T, Allocator>::front()
{
	return (this->_data[0]);
}

/*
template <class T, class Allocator>
typename std::allocator<T>::const_reference vector<T, Allocator>::front() const
{
	return (this->_data[0]);
}
*/
template <class T, class Allocator>
T& vector<T, Allocator>::back()
{
	if (this->_size == 0)
		return (this->_data[0]);
	return (this->_data[this->_size - 1]);
}

/*
template <class T, class Allocator>
typename std::allocator<T>::const_reference vector<T, Allocator>::back() const
{
	if (this->_size == 0)
		return (this->_data[0]);
	return (this->_data[this->_size - 1]);
}
*/
/*
template <class T, class Allocator>
typename std::allocator<T>::pointer vector<T, Allocator>::data()
{
	return (this->_data);
}
*/
/*
template <class T, class Allocator>
typename std::allocator<T>::const_pointer vector<T, Allocator>::data() const
{
	return (this->_data);
}
*/
}
#endif
