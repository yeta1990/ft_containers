#ifndef MAP_HPP
# define MAP_HPP

#include "iterator_traits.hpp"
#include "random_iterator.hpp"
#include "reverse_iterator.hpp"
#include "pair.hpp"

#include <memory>

namespace ft{
	template< class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > > class map
	{
		public:

		typedef Key											key_type;
		typedef T											mapped_type;
		typedef pair<const key_type, mapped_type>			value_type;
		typedef std::less<key_type> 						key_compare;
		//value_compare
		typedef std::allocator<value_type> 					allocator_type;
		typedef typename allocator_type::reference 			reference;
		typedef typename allocator_type::const_reference 	const_reference;
		typedef typename allocator_type::pointer 			pointer;
		typedef typename allocator_type::const_pointer 		const_pointer;

		//random iterator or bidirectional iterator?
		typedef random_iterator<pointer> iterator;
		typedef random_iterator<const_pointer> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef typename iterator_traits<iterator>::difference_type difference_type;
		typedef size_t size_type;

		explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
		{
			std::cout << "map created " << std::endl;
			this->_allocator = alloc;
			this->_comp = comp;
		}

//		template <class InputIterator>
//		map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());
//
//		map (const map& x);

		private:
			Allocator			_allocator;
			key_compare		_comp;

	};

}

#endif
