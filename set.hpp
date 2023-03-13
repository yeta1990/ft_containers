#ifndef SET_HPP
# define SET_HPP

#include "iterator_traits.hpp"
#include "random_iterator.hpp"
#include "reverse_iterator.hpp"
#include "pair.hpp"
#include "make_pair.hpp"
#include "RBTree.hpp"
#include <memory>
#include <cstddef>
#include <limits>
#include "tree_iterator.hpp"
#include "equal.hpp"
#include "lexicographical_compare.hpp"

namespace ft{

	template< class Key, class Compare = std::less<Key>, class Allocator = std::allocator<Key> > class set
	{
	public:

		typedef Key											key_type;
		typedef Key											value_type;
		typedef Compare				 						key_compare;
		typedef Compare				 						value_compare;
		typedef	ft::pair<key_type, value_type>				pair_type;
		typedef	ft::Node<pair_type>							node;
		typedef	const node									const_node;
		typedef ft::RBTree<pair_type, Allocator, key_compare>	tree;
		typedef Allocator				 					allocator_type;

	private:
		typedef typename Allocator::template 				rebind<node>::other	node_allocator;
		typedef typename node_allocator::pointer			node_pointer;
		typedef typename node_allocator::const_pointer		const_node_pointer;
	public:
		typedef set_iterator<const_node_pointer, pair_type>	iterator;
		typedef set_iterator<const_node_pointer, pair_type>	const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef std::ptrdiff_t								difference_type;
		typedef size_t size_type;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef value_type&									reference;
		typedef const value_type&							const_reference;


		explicit set (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
		{
			this->_allocator = alloc;
			this->_comp = comp;
		}

		template <class InputIterator>  
		set (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
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
		set (const set& other)
		{
			*this = other;
		}

		set& operator= (const set& other)
		{
			this->_allocator = other.get_allocator();
			this->_comp = key_compare();
			_tree.clear();
			insert(other.begin(), other.end());
			return (*this);
		}

		allocator_type get_allocator() const
		{
			return (this->_allocator);
		}

		~set() {};

		ft::pair<iterator, bool> insert( const value_type& value )
		{
			node		*new_inserted;
			size_type	old_size;

			old_size = this->size();
			new_inserted = _tree.insert(ft::make_pair<key_type, value_type>(value, value));
			return (ft::make_pair<iterator, bool> (iterator(new_inserted, this->_tree.getSentinel()), (old_size < this->size())));
		}

		iterator insert (iterator position, const value_type& val)
		{
			(void) position;
			node	*new_inserted;

			new_inserted = _tree.insert(ft::make_pair<key_type, value_type>(val, val));
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

		iterator begin()
		{
			return (iterator(this->_tree.begin().getNode(),
						this->_tree.getSentinel()));
		}

		iterator end()
		{
			return (iterator(this->_tree.getSentinel(), 
						this->_tree.getSentinel()));
		}

		const_iterator begin() const
		{
			return (const_iterator(this->_tree.begin().getNode(), 
						this->_tree.getSentinel()));
		}

		const_iterator end() const
		{
			return (const_iterator(this->_tree.getSentinel(), 
						this->_tree.getSentinel()));
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
     	
		size_type	size() const { return (this->_tree.size());};
		size_type 	max_size() const {return (this->_tree.max_size());};

		//capacity
		bool empty() const { return (!this->size());};

		void erase (iterator position)
		{
			erase(*position);
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
			while (it != end() && *it != *last)
			{
				first++;
				erase(it);
				it = first;
			}
		}

		void swap (set& x)
		{
			Allocator sw;

			sw = x.get_allocator();
			x._allocator = this->_allocator;
			this->_allocator = sw;
			this->_tree.swap(x._tree);
		}

		void clear()
		{
			_tree.clear();
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
			return (iterator(this->_tree._find(k), this->_tree.getSentinel()));
		}

		const_iterator find (const key_type& k) const
		{
			return (const_iterator(this->_tree._find(k), this->_tree.getSentinel()));
		}
		
		//
		size_type count (const key_type& k) const
		{
			const_iterator	it;

			it = this->find(k);
			if (it == this->end())
				return (0);
			return (1);
		}
		
		iterator lower_bound (const key_type& k)
		{
			return(iterator(this->_tree.findLowerBoundNode(k), this->_tree.getSentinel()));
		}

		const_iterator lower_bound (const key_type& k) const
		{
			return(const_iterator(this->_tree.findLowerBoundNode(k), this->_tree.getSentinel()));
		}

		iterator upper_bound (const key_type& k)
		{
			return(iterator(this->_tree.findUpperBoundNode(k), this->_tree.getSentinel()));

		}

		const_iterator upper_bound (const key_type& k) const
		{
			return(const_iterator(this->_tree.findUpperBoundNode(k), this->_tree.getSentinel()));
		}

		ft::pair<const_iterator,const_iterator> equal_range (const key_type& k) const
		{
			return (ft::make_pair(lower_bound(k), upper_bound(k)));
		}

		ft::pair<iterator,iterator> equal_range (const key_type& k)
		{
			return (ft::make_pair(lower_bound(k), upper_bound(k)));
		}

		private:
			Allocator			_allocator;
			key_compare			_comp;
			RBTree<pair_type, Allocator, key_compare>	_tree;
	};


template <class Key, class Compare, class Alloc>  
void swap (set<Key,Compare,Alloc>& x, set<Key,Compare,Alloc>& y)
{
	x.swap(y);
}

template< class Key, class Compare, class Alloc >
bool operator==( const ft::set<Key, Compare, Alloc>& lhs,
                 const ft::set<Key, Compare, Alloc>& rhs )
{
	if (lhs.size() != rhs.size())
		return (false);
	return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}


template< class Key, class Compare, class Alloc >
bool operator!=( const ft::set<Key, Compare, Alloc>& lhs,
                 const ft::set<Key, Compare, Alloc>& rhs )
{
	if (lhs.size() != rhs.size())
		return (true);
	return (!ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}


template< class Key, class Compare, class Alloc >
bool operator<( const ft::set<Key, Compare, Alloc>& lhs,
                const ft::set<Key, Compare, Alloc>& rhs )
{
	return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
}

template< class Key, class Compare, class Alloc >
bool operator<=( const ft::set<Key, Compare, Alloc>& lhs,
                 const ft::set<Key, Compare, Alloc>& rhs )
{
	return ((lhs < rhs) || (lhs == rhs));
}

template< class Key, class Compare, class Alloc >

bool operator>=( const ft::set<Key, Compare, Alloc>& lhs,
                 const ft::set<Key, Compare, Alloc>& rhs )
{
	return ((lhs > rhs) || (lhs == rhs));
}

template< class Key, class Compare, class Alloc >
bool operator>( const ft::set<Key, Compare, Alloc>& lhs,
                const ft::set<Key, Compare, Alloc>& rhs )
{
	return (rhs < lhs);
}

}

#endif
