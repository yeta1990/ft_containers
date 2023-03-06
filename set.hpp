#ifndef SET_HPP
# define SET_HPP

#include "iterator_traits.hpp"
#include "random_iterator.hpp"
#include "reverse_iterator.hpp"
#include "pair.hpp"
#include "make_pair.hpp"
#include "BSTree.hpp"
#include <memory>
#include <cstddef>
#include <limits>
#include "tree_iterator.hpp"
#include "equal.hpp"

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
		typedef ft::BSTree<pair_type, Allocator, key_compare>	tree;
		typedef Allocator				 					allocator_type;

	private:
		typedef typename Allocator::template 				rebind<node>::other	node_allocator;
		typedef typename node_allocator::pointer			node_pointer;
		typedef typename node_allocator::const_pointer		const_node_pointer;
	public:
		typedef set_iterator<node_pointer, pair_type>	iterator;
		typedef set_iterator<const_node_pointer, const pair_type>	const_iterator;
//		typedef typename tree::iterator						iterator;
//		typedef typename tree::const_iterator				const_iterator;
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

		ft::pair<iterator, bool> insert( const value_type& value )
		{
			node		*new_inserted;
			size_type	old_size;

			old_size = this->size();
			new_inserted = _tree.insert(ft::make_pair<key_type, value_type>(value, value));
			return (ft::make_pair<iterator, bool> (iterator(new_inserted, this->_tree.getSentinel()), (old_size < this->size())));
//			return (_tree.insert(value));
		}

		size_type	size() const { return (this->_tree.size());};

		/*

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

		~set() { 
			
////			std::cout << "map destructor" << std::endl;
//			this->_tree->clear(); 
//			tree_alloc c;
//			c.destroy(_tree);
//			c.deallocate(_tree, 1);
			
//			delete this->_tree; 
//			this->_tree = NULL;
		}

		//capacity
		bool empty() const { return (!this->size());};
		size_type	size() const { return (this->_tree.size());};
		size_type 	max_size() const {return (this->_tree.max_size());};
//		size_type	max_size() const {
//			return (std::numeric_limits<map::size_type>::max() / sizeof(T));
//		}

		//element access
		mapped_type& operator[] (const key_type& k)
		{

			pair<iterator, bool> p = insert(ft::make_pair<key_type, mapped_type>(k, mapped_type()));
			return ((*p.first).second);
		}

		mapped_type& at (const key_type& k)
		{
			node *found;

			found = this->_tree._find(k);
			if (found == _tree.getSentinel())
				throw (std::out_of_range("set::at"));
			return (found->getContent()->second);
		}

		const mapped_type& at (const key_type& k) const
		{
			const_node *found;

			found = this->_tree._find(k);
			if (found == _tree.getSentinel())
				throw (std::out_of_range("map::at"));
			return (found->getContent()->second);
		}

		//modifiers
		pair<iterator,bool>	insert(const value_type& p)
		{
			node	*new_inserted;
			size_type	old_size;

			old_size = this->size();
			new_inserted = _tree.insert(p);
			return (ft::make_pair<iterator, bool> (iterator(new_inserted, this->_tree.getSentinel()), (old_size < this->size())));
		}

		//insert with hint
		iterator insert (iterator position, const value_type& val)
		{
			node	*new_inserted;

			if (position == this->end())
				new_inserted = _tree.insert(this->begin(), val);
			else
				new_inserted = _tree.insert(position, val);
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
			_tree.deleteKeyFrom(*position.base());
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
			return (this->_tree.find(k));
		}

		const_iterator find (const key_type& k) const
		{
			return (this->_tree.find(k));
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

//		key_comp(element_key,k) would return false
		iterator lower_bound (const key_type& k)
		{
			iterator	it;
			key_compare comp = this->key_comp();

			for (it = this->begin(); it != this->end(); it++)
			{
				if (!comp(it->first, k))
					return (it);
			}
			return (it);
		}

		const_iterator lower_bound (const key_type& k) const
		{
			const_iterator	it;
			key_compare comp = this->key_comp();

			for (it = this->begin(); it != this->end(); it++)
			{
				if (!comp(it->first, k))
					return (it);
			}
			return (it);
//			return (const_iterator(lower_bound(k)));
		}


		//key_comp(k,element_key) would return true.
		iterator upper_bound (const key_type& k)
		{
			iterator	it;
			key_compare comp = this->key_comp();

			for (it = this->begin(); it != this->end(); it++)
			{
				if (comp(k, it->first))
					return (it);
			}
			return (it);

		}

		const_iterator upper_bound (const key_type& k) const
		{
			const_iterator	it;
			key_compare comp = this->key_comp();

			for (it = this->begin(); it != this->end(); it++)
			{
				if (comp(k, it->first))
					return (it);
			}
			return (it);
		}

		ft::pair<const_iterator,const_iterator> equal_range (const key_type& k) const
		{
			return (ft::make_pair(lower_bound(k), upper_bound(k)));
		}

		ft::pair<iterator,iterator> equal_range (const key_type& k)
		{
			return (ft::make_pair(lower_bound(k), upper_bound(k)));
		}

		//iterators
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

	 	 //remove before evaluation!!
	 	 void	printmap()
	 	 {
	 	 	 this->_tree.printtree();
	 	 }

		private:
			Allocator			_allocator;
			key_compare			_comp;
			BSTree<value_type, Allocator, key_compare>	_tree;
			*/
		private:
			Allocator			_allocator;
			key_compare			_comp;
			BSTree<pair_type, Allocator, key_compare>	_tree;
	};
/*

template <class Key, class Compare, class Alloc>  
void swap (set<Key,T,Compare,Alloc>& x, set<Key,T,Compare,Alloc>& y)
{
	x.swap(y);
}

template< class Key, class Compare, class Alloc >
bool operator==( const ft::set<Key, T, Compare, Alloc>& lhs,
                 const ft::set<Key, T, Compare, Alloc>& rhs )
{
	if (lhs.size() != rhs.size())
		return (false);
	return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}


template< class Key, class Compare, class Alloc >
bool operator!=( const ft::set<Key, T, Compare, Alloc>& lhs,
                 const ft::set<Key, T, Compare, Alloc>& rhs )
{
	if (lhs.size() != rhs.size())
		return (true);
	return (!ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}


template< class Key, class Compare, class Alloc >
bool operator<( const ft::set<Key, T, Compare, Alloc>& lhs,
                const ft::set<Key, T, Compare, Alloc>& rhs )
{
	typename ft::set<Key, T, Compare, Alloc>::const_iterator it;
	typename ft::set<Key, T, Compare, Alloc>::const_iterator it2;

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

template< class Key, class Compare, class Alloc >
bool operator<=( const ft::set<Key, T, Compare, Alloc>& lhs,
                 const ft::set<Key, T, Compare, Alloc>& rhs )
{
	return ((lhs < rhs) || (lhs == rhs));
}

template< class Key, class Compare, class Alloc >

bool operator>=( const ft::set<Key, T, Compare, Alloc>& lhs,
                 const ft::set<Key, T, Compare, Alloc>& rhs )
{
	return ((lhs > rhs) || (lhs == rhs));
}

template< class Key, class Compare, class Alloc >
bool operator>( const ft::set<Key, T, Compare, Alloc>& lhs,
                const ft::set<Key, T, Compare, Alloc>& rhs )
{
	typename ft::set<Key, T, Compare, Alloc>::const_iterator it;
	typename ft::set<Key, T, Compare, Alloc>::const_iterator it2;

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
*/




}













#endif
