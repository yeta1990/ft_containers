#ifndef VECTOR_TPP
# define VECTOR_TPP

namespace ft{

template <class T, class Allocator>
void	vector<T, Allocator>::push_back(const T& val)
{
	_size++;
	if (!isCapacityEnough())
		expandCapacity();
	this->_usedValues++;
	this->_allocator.construct(&this->_data[this->_usedValues - 1], val);
	this->_lastElement++;
};

template <class T, class Allocator>
void	vector<T, Allocator>::resize(size_type n, value_type val)
{
	std::cout << "resizing to " << n << std::endl;
	if (n < this->_size)
	{
		this->_size = n;
		this->_usedValues = n;
	}
	else if (n > this->_size)
	{
		size_type oldSize;
		if (!isCapacityEnough())
			expandCapacity();
		else if (n > this->_capacity)
			expandCapacity(n);
		for (size_t i = this->_usedValues; i < n; i++)
			push_back(val);
	}
};

}
#endif
