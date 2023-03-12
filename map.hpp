#ifndef MAP_HPP
# define MAP_HPP

#include "iterator_traits.hpp"
#include "reverse_iterator.hpp"
#include "pair.hpp"
#include "make_pair.hpp"
#include "RBTree.hpp"
#include <memory>
#include <cstddef>
#include "tree_iterator.hpp"
#include "equal.hpp"

namespace ft{
	template< class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > > class map
	{
		public:

		typedef Key											key_type;
		typedef T											mapped_type;
		typedef ft::pair<const key_type, mapped_type>			value_type;
		typedef Compare				 						key_compare;
		typedef	ft::Node<value_type>						node;
		typedef	const node									const_node;
		typedef ft::RBTree<value_type, Allocator, key_compare>	tree;
		typedef Allocator				 					allocator_type;
		typedef typename tree::iterator						iterator;
		typedef typename tree::const_iterator				const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef std::ptrdiff_t								difference_type;
		typedef size_t size_type;
		typedef typename allocator_type::pointer						pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef value_type&									reference;
		typedef const value_type&							const_reference;

		class value_compare : std::binary_function<value_type,value_type,bool> {
			// Since constructor is required to be protected, map is defined as friend class to be
			// able to be called from value_comp() of map
			friend class map; 
							  
			public:
				bool		result_type;
				value_type	first_argument_type;
				value_type	second_argument_type;
				bool operator()( const value_type& lhs, const value_type& rhs ) const { return comp(lhs.first, rhs.first); }

			protected:
				Compare	comp;
				value_compare( Compare c ) : comp(c) {};

		};

		// an explicit constructor requires the use of the constructor name when creating an object of the class
		// in this case, to prevent things like  ft::map<int, int> map = std::less<int>();
		explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
		{
			this->_allocator = alloc;
			this->_comp = comp;
		}

		template <class InputIterator>
		map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) 
		{
			InputIterator it;

			this->_allocator = alloc;
			this->_comp = comp;
			it = first;
			while (it != last)
			{
				insert(*it);
				it++;
			}
		}

		//copy constructor
		map (const map& other)
		{
			*this = other;
		}

		map& operator= (const map& other)
		{
			this->_allocator = other.get_allocator();
			this->_comp = key_compare();
			this->_tree.clear();
			insert(other.begin(), other.end());
			return (*this);
		}

		allocator_type get_allocator() const
		{
			return (this->_allocator);
		}

		~map() { 
			
		}

		//capacity
		bool empty() const { return (!this->size());};
		size_type	size() const { return (this->_tree.size());};
		size_type 	max_size() const {return (this->_tree.max_size());};

		//element access
		mapped_type& operator[] (const key_type& k)
		{
			ft::pair<iterator, bool> p = insert(ft::make_pair<key_type, mapped_type>(k, mapped_type()));
			return ((*p.first).second);
		}

		mapped_type& at (const key_type& k)
		{
			node *found;

			found = this->_tree._find(k);
			if (found == this->_tree.getSentinel())
				throw (std::out_of_range("map::at"));
			return (found->getContent()->second);
		}

		const mapped_type& at (const key_type& k) const
		{
			const_node *found;

			found = this->_tree._find(k);
			if (found == this->_tree.getSentinel())
				throw (std::out_of_range("map::at"));
			return (found->getContent()->second);
		}

		//modifiers
		ft::pair<iterator,bool>	insert(const value_type& p)
		{
			node	*new_inserted;
			size_type	old_size;

			old_size = this->size();
			new_inserted = this->_tree.insert(p);
			return (ft::make_pair<iterator, bool> (iterator(new_inserted, this->_tree.getSentinel()), (old_size < this->size())));
		}

		//insert with hint
		iterator insert (iterator position, const value_type& val)
		{
			node	*new_inserted;

			new_inserted = this->_tree.insert(position, val);
			return (iterator(new_inserted, this->_tree.getSentinel()));
		}

		template <class InputIterator>
		void insert (InputIterator first, InputIterator last)
		{
			InputIterator it;

			it = first;
			while (it != last)
			{
				insert(*it);
				it++;	
			}
		}

		void erase (iterator position)
		{
			this->_tree.deleteKeyFrom(*position.base());
		}

		size_type erase (const key_type& k)
		{
			size_type	old_size;

			old_size = this->size();
			this->_tree.del(k);
			return (old_size - this->size());
		}

		void erase (iterator first, iterator last)
		{
			iterator	it;

			it = first;
			while (it != end() && it->first != last->first)
			{
				first++;
				erase(it);
				it = first;
			}
		}

		void swap (map& x)
		{
			Allocator sw;

			sw = x.get_allocator();
			x._allocator = this->_allocator;
			this->_allocator = sw;
			this->_tree.swap(x._tree);
		}

		void clear()
		{
			this->_tree.clear();
		}

		//observers
		key_compare key_comp() const
		{
			return (this->_comp);
		}

		value_compare value_comp() const
		{
			return (value_compare(this->_comp));
		}

		//operations
		iterator find (const key_type& k)
		{
			return (this->_tree.find(k));
		}

		const_iterator find (const key_type& k) const
		{
			return (this->_tree.find(k));
		}
		
		size_type count (const key_type& k) const
		{
			const_iterator	it;

			it = this->find(k);
			if (it == this->end())
				return (0);
			return (1);
		}

		//Returns an iterator pointing to the first element in the range [first, last) 
		//that does not satisfy element < value (or comp(element, value) is true
		iterator lower_bound (const key_type& k)
		{
			return(iterator(this->_tree.findLowerBoundNode(k), this->_tree.getSentinel()));
		}

		const_iterator lower_bound (const key_type& k) const
		{
			return(const_iterator(this->_tree.findLowerBoundNode(k), this->_tree.getSentinel()));
		}

		//Returns an iterator pointing to the first element in the range [first, last) 
		//such that value < element (or comp(value, element)) is true
		iterator upper_bound (const key_type& k)
		{
			return(iterator(this->_tree.findUpperBoundNode(k), this->_tree.getSentinel()));
		}

		const_iterator upper_bound (const key_type& k) const
		{
			return(const_iterator(this->_tree.findUpperBoundNode(k), this->_tree.getSentinel()));
		}

		//The range is defined by two iterators, one pointing to the first element that 
		//is not less than key and another pointing to the first element greater than key. 
		ft::pair<const_iterator,const_iterator> equal_range (const key_type& k) const
		{
			return (ft::make_pair(lower_bound(k), upper_bound(k)));
		}

		ft::pair<iterator,iterator> equal_range (const key_type& k)
		{
			return (ft::make_pair(lower_bound(k), upper_bound(k)));
		}

		iterator begin()
		{
			return (this->_tree.begin());
		}

		iterator end()
		{
			return (this->_tree.end());
		}

		const_iterator begin() const
		{
			return (this->_tree.begin());
		}

		const_iterator end() const
		{
			return (this->_tree.end());
		}

      	reverse_iterator rbegin()
      	{
			return (reverse_iterator(this->end()));
		}
		const_reverse_iterator rbegin() const
		{
			return (const_reverse_iterator(this->end()));
     	}

     	reverse_iterator rend()
    	{
	 	 	return (reverse_iterator(this->begin()));
	 	}

     	const_reverse_iterator rend() const
     	{
	 		return (const_reverse_iterator(this->begin()));
     	}

		// used for testing purposes 
		/*
	 	void	printmap()
	 	{
	 		this->_tree.printtree();
	 	}
		*/

		private:
			Allocator			_allocator;
			key_compare			_comp;
			RBTree<value_type, Allocator, key_compare>	_tree;
	};


template <class Key, class T, class Compare, class Alloc>  
void swap (map<Key,T,Compare,Alloc>& x, map<Key,T,Compare,Alloc>& y)
{
	x.swap(y);
}

template< class Key, class T, class Compare, class Alloc >
bool operator==( const ft::map<Key, T, Compare, Alloc>& lhs,
                 const ft::map<Key, T, Compare, Alloc>& rhs )
{
	if (lhs.size() != rhs.size())
		return (false);
	return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}


template< class Key, class T, class Compare, class Alloc >
bool operator!=( const ft::map<Key, T, Compare, Alloc>& lhs,
                 const ft::map<Key, T, Compare, Alloc>& rhs )
{
	if (lhs.size() != rhs.size())
		return (true);
	return (!ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}


template< class Key, class T, class Compare, class Alloc >
bool operator<( const ft::map<Key, T, Compare, Alloc>& lhs,
                const ft::map<Key, T, Compare, Alloc>& rhs )
{
	typename ft::map<Key, T, Compare, Alloc>::const_iterator it;
	typename ft::map<Key, T, Compare, Alloc>::const_iterator it2;

	for (it = lhs.begin(), it2 = rhs.begin(); it != lhs.end() && it2 != rhs.end(); it++, it2++)
	{
		if (it->first <= it2->first && it->second < it2->second)
			return (true);
		else if (it->first < it2->first)
			return (true);
		else if (it->second > it2->second)
			return (false);
		else if (it->first > it2->first)
			return (false);
	}
	return (lhs.size() < rhs.size());
}

template< class Key, class T, class Compare, class Alloc >
bool operator<=( const ft::map<Key, T, Compare, Alloc>& lhs,
                 const ft::map<Key, T, Compare, Alloc>& rhs )
{
	return ((lhs < rhs) || (lhs == rhs));
}

template< class Key, class T, class Compare, class Alloc >

bool operator>=( const ft::map<Key, T, Compare, Alloc>& lhs,
                 const ft::map<Key, T, Compare, Alloc>& rhs )
{
	return ((lhs > rhs) || (lhs == rhs));
}

template< class Key, class T, class Compare, class Alloc >
bool operator>( const ft::map<Key, T, Compare, Alloc>& lhs,
                const ft::map<Key, T, Compare, Alloc>& rhs )
{
	typename ft::map<Key, T, Compare, Alloc>::const_iterator it;
	typename ft::map<Key, T, Compare, Alloc>::const_iterator it2;

	for (it = lhs.begin(), it2 = rhs.begin(); it != lhs.end() && it2 != rhs.end(); it++, it2++)
	{
		if (it->first >= it2->first && it->second > it2->second)
			return (true);
		else if (it->first > it2->first)
			return (true);
		else if (it->second < it2->second)
			return (false);
		else if (it->first < it2->first)
			return (false);
	}
	return (lhs.size() > rhs.size());
}

}

#endif
