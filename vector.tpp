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
//		this->_size = 0;
//		this->_capacity = 0;
//		this->_data = 0;
	}
}


template <class T, class Allocator>
void	vector<T, Allocator>::expansor(size_type new_capacity)
{
	value_type*		_newData;

//	std::cout << "old capacity is " << this->_capacity << "new capacity is " << new_capacity << std::endl;
	try	
	{
	_newData = this->_allocator.allocate(new_capacity);
	}
	catch (std::bad_alloc &e)
//	catch (std::exception &e)
	{
		throw (std::length_error("vector exceeds maximum supported size"));
	}


	copyDataToOtherObject(_newData);
	destroy_and_deallocate();
//	_firstElement = _data;
//	setLastElement();
	this->_data = _newData;
	this->_capacity = new_capacity;
	this->_lastElement = this->_data + this->_size;

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
//
	if (n < this->_size)
	{
		erase(this->begin() + n, end());
	}
	else
	{
		insert(end(), n - this->_size, val);
	}

}

template <class T, class Allocator>
void 	vector<T, Allocator>::reserve (size_type n)
{
	if (n == 0)
		return ;
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
	{
		return ;
	}
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
	try	
	{
		this->_data = this->_allocator.allocate(this->_capacity);
	}
	catch (std::bad_alloc &e)
//	catch (std::exception &e)
	{
		throw (std::length_error("vector exceeds maximum supported size"));
	}

//	this->_data = this->_allocator.allocate(this->_capacity);
	for (size_type i = 0; i < n; i++)
		this->_allocator.construct(&_data[i], val);
	this->_usedValues = this->_size;
	this->_lastElement = this->_data + this->_size;
}
	

template <class T, class Allocator>
void	vector<T, Allocator>::clear()
{
	for (size_t i = 0; i < this->_size; i++)
		this->_allocator.destroy(&this->_data[i]);
	this->_size = 0;
	this->_lastElement = this->_data;
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
