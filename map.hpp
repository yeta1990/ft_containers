#ifndef MAP_HPP
# define MAP_HPP

# if __linux__
#  define MAX_SIZE_DIVISOR 12
# else
#  define MAX_SIZE_DIVISOR 10
# endif

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
	template< class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > > class map
	{
		public:

		typedef Key											key_type;
		typedef T											mapped_type;
		typedef pair<const key_type, mapped_type>			value_type;
		typedef Compare				 						key_compare;
		//value_compare
		typedef Allocator				 					allocator_type;
		typedef typename Allocator::template 				rebind<value_type>::other	alloc_pair;

		typedef typename alloc_pair::reference 				reference;
		typedef typename alloc_pair::const_reference 		const_reference;
		typedef typename alloc_pair::pointer 				pointer;
		typedef typename alloc_pair::const_pointer 			const_pointer;

		typedef BSTree<value_type, key_compare>							tree;
		typedef typename tree::iterator						iterator;
		typedef typename tree::const_iterator				const_iterator;
		typedef	ft::Node<value_type, key_compare>						node;
		typedef	ft::Node<value_type, key_compare>					const_node;
		//bidirectional iterator?
		//this must be chaged to a custom iterator for node*
//		typedef tree_iterator<node *>	iterator;
//		typedef tree_iterator<node *>	const_iterator;
//		typedef random_iterator<pointer> iterator;
//		typedef random_iterator<const_pointer> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef std::ptrdiff_t			difference_type;
		typedef size_t size_type;

		class value_compare : std::binary_function<value_type,value_type,bool> {
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

		
		explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
		{
//			std::cout << "map created " << std::endl;
			this->_allocator = alloc;
			this->_comp = comp;
			this->_root = new BSTree<value_type, key_compare>();
		}

		template <class InputIterator>
		map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) 
		{
			InputIterator it;

			this->_allocator = alloc;
			this->_comp = comp;
			this->_root = new BSTree<value_type, key_compare>();
//			insert(first, last);
//			std::cout << "yeee" << std::endl;
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
			this->_root = NULL;
			*this = other;
//			return (*this);
			/*
			this->_allocator = other.get_allocator();
			this->_comp = key_compare();
			this->_root = new BSTree<value_type>();

			const_iterator	it;
			for (it = other.begin(); it != other.end(); it++)
			{
				insert(*it);
			}
			*/
		}

		map& operator= (const map& other)
		{
//			std::cout << "yee" << std::endl;
			this->_allocator = other.get_allocator();
			this->_comp = key_compare();
			if (this->_root)
			{
				this->_root->clear();
				delete this->_root;
				this->_root = NULL;
			}
			this->_root = new BSTree<value_type, key_compare>();

			if (other.size() == 0)
				return (*this);
//			const_iterator	it;
//			std::cout << std::endl;
//			for (it = other.begin(); it != other.end(); it++)
//			{
			insert(other.begin(), other.end());
//				std::cout << "inserting " << (*it).first << std::endl;
//			}
//			std::cout << "operator =" << std::endl;
			return (*this);
		}

		allocator_type get_allocator() const
		{
			return (this->_allocator);
		}

		~map() { this->_root->clear(); delete this->_root; this->_root = NULL;}

		//capacity
		bool empty() const { return (!this->size());};
		size_type	size() const { return (this->_root->size());};
		size_type 	max_size() const {return (alloc_pair().max_size());};
//		size_type	max_size() const {
//			return (std::numeric_limits<map::size_type>::max() / sizeof(T));
//		}

		//element access
		mapped_type& operator[] (const key_type& k)
		{
//			int j = 7;
			typename BSTree<value_type, key_compare>::node	*found;

			if (this->size() == 0)
			{
				this->_root->insert(ft::make_pair<key_type, mapped_type>(k, mapped_type()));
				return ((*this)[k]);
			}
			found = this->_root->_find(k);
			if (found == _root->getSentinel())
			{
				this->_root->insert(ft::make_pair<key_type, mapped_type>(k, mapped_type()));
				return (this->operator[](k));
			}
			return (found->content->second);

		}

		mapped_type& at (const key_type& k)
		{
			typename BSTree<value_type, key_compare>::node	*found;

			found = this->_root->_find(k);
			if (found == _root->getSentinel())
				throw (std::out_of_range("map::at"));
			return (found->content->second);
		}

		const mapped_type& at (const key_type& k) const
		{
			typename BSTree<value_type, key_compare>::node	*found;

			found = this->_root->_find(k);
			if (found == _root->getSentinel())
				throw (std::out_of_range("map::at"));
			return (found->value);
		}

		//modifiers
		pair<iterator,bool>	insert(const value_type& p)
		{
			typename BSTree<value_type, key_compare>::node	*new_inserted;
			size_type	old_size;

			old_size = this->size();
			new_inserted = _root->insert(p);
			return (ft::make_pair<iterator, bool> (iterator(new_inserted), (old_size < this->size())));
		}

		//insert with hint
		iterator insert (iterator position, const value_type& val)
		{
			typename BSTree<value_type, key_compare>::node	*new_inserted;

			if (position == this->end())
				new_inserted = _root->insert(this->begin(), val);
			else
				new_inserted = _root->insert(position, val);
			return (iterator(new_inserted));
		}

		template <class InputIterator>
		void insert (InputIterator first, InputIterator last)
		{
			InputIterator it;

			it = first;
			while (it != last)
			{
//				std::cout << "yee" << std::endl;
				insert(*it);
				it++;	
			}
		}

		void erase (iterator position)
		{
//			if (*position)
			_root->deleteKeyFrom(*position.base());
//				_root->deleteKeyFrom((*position).first, *position.base());
		}

		size_type erase (const key_type& k)
		{
			size_type	old_size;

			old_size = this->size();
			this->_root->del(k);
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
			BSTree<value_type, key_compare> *sw;

			sw = this->_root;
			this->_root = x._root;
			x._root = sw;

		}
		void clear()
		{
			_root->clear();
			delete _root;
			this->_root = new BSTree<value_type, key_compare>();
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
//			node*	found;

//			found = this->_root->find(k);
//			return (iterator(found));
			return (this->_root->find(k));
		}

		const_iterator find (const key_type& k) const
		{
//			cnode*	found;

//			found = this->_root->find(k);
//			return (const_iterator(found));
			return (this->_root->find(k));
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
//			return (const_iterator(upper_bound(k)));
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
			node*	found;
			found = this->_root->getLowestNode();

			return (iterator(found));
		}

		iterator end()
		{
			node*	found;
			found = this->_root->getSentinel();

			return (iterator(found));
		}

		const_iterator begin() const
		{
//			const node*	found;
//			found = this->_root->getLowestNode();

//			return (const_iterator(found));
			return (this->_root->begin());
		}

		const_iterator end() const
		{
//			node*	found;
//			found = this->_root->getSentinel();

//			return (const_iterator(found));
			return (this->_root->end());
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

		private:
			Allocator			_allocator;
			key_compare			_comp;
			BSTree<value_type, key_compare>	*_root;
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
		if (it->second < it2->second)
			return (true);
		else if (it->second > it2->second)
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
		if (it->second > it2->second)
			return (true);
		else if (it->second < it2->second)
			return (false);
	}
	return (lhs.size() > rhs.size());
//	return (it == lhs.end() && (it2 != rhs.end()));
}





}













#endif
