#ifndef VECTOR_TPP
# define VECTOR_TPP

namespace ft{

template <class T, class Allocator>
void	vector<T, Allocator>::expandCapacity(size_type requiredCapacity)
{
	if (this->_capacity == 0)
		this->_capacity = 1;
	else 
		this->_capacity = std::max(this->_capacity * 2, requiredCapacity);
	expansor();
};

template <class T, class Allocator>
void	vector<T, Allocator>::expansor(void)
{
	value_type*		_newData;

	//std::cout << "allocating " << this->_capacity << std::endl;
	_newData = this->_allocator.allocate(this->_capacity);
	copyDataToOtherObject(_newData);
	if (this->_usedValues > 0)
		this->_allocator.deallocate(this->_data, this->_capacity);
	_firstElement = _data;
	setLastElement();
	this->_data = _newData;
};

template <class T, class Allocator>
void	vector<T, Allocator>::push_back(const T& val)
{
	_size++;
	if (this->_size > this->_capacity)
		expandCapacity(_size);
	this->_usedValues++;
	this->_allocator.construct(&this->_data[this->_usedValues - 1], val);
	this->_lastElement++;
};

template <class T, class Allocator>
void	vector<T, Allocator>::resize(size_type n, value_type val)
{
	//std::cout << "------resizing to " << n << std::endl;
	if (n < this->_size)
	{
		this->_size = n;
		this->_usedValues = n;
	}
	else if (n > this->_size)
	{
		if (n > this->_capacity)
			expandCapacity(n);
		for (size_t i = this->_usedValues; i < n; i++)
		{
			this->_allocator.construct(&this->_data[this->_usedValues], val);
			this->_usedValues++;
		}
		this->_size = n;
	}
};

}
#endif
