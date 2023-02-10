#ifndef MAP_HPP
# define MAP_HPP

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

namespace ft{
	template< class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > > class map
	{
		public:

		typedef Key											key_type;
		typedef T											mapped_type;
		typedef pair<const key_type, mapped_type>			value_type;
		typedef Compare				 						key_compare;
		//value_compare
		typedef std::allocator<value_type> 					allocator_type;
		typedef typename allocator_type::reference 			reference;
		typedef typename allocator_type::const_reference 	const_reference;
		typedef typename allocator_type::pointer 			pointer;
		typedef typename allocator_type::const_pointer 		const_pointer;
		typedef	ft::Node<value_type>						node;
		//bidirectional iterator?
		//this must be chaged to a custom iterator for node*
		typedef tree_iterator<node *>	iterator;
		typedef tree_iterator<node *>	const_iterator;
//		typedef random_iterator<pointer> iterator;
//		typedef random_iterator<const_pointer> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef std::ptrdiff_t			difference_type;
		typedef size_t size_type;

		class value_compare {
			public:
				bool		result_type;
				value_type	first_argument_type;
				value_type	second_argument_type;

			protected:
				Compare	comp;
				value_compare( Compare c ) : comp(c) {};
				bool operator()( const value_type& lhs, const value_type& rhs ) const { return comp(lhs.first, rhs.first); }



		};

		/*
		map() {
			this->_allocator = NULL;
			this->_comp = NULL;
			this->_root = new BSTree<value_type>();
		};
		*/

		explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
		{
//			std::cout << "map created " << std::endl;
			this->_allocator = alloc;
			this->_comp = comp;
			this->_root = new BSTree<value_type>();
		}

		template <class InputIterator>
		map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) 
		{
			InputIterator it;

			this->_allocator = alloc;
			this->_comp = comp;
			this->_root = new BSTree<value_type>();
			it = first;
			while (it != last)
			{
				insert(*it);
				it++;	
			}

		}
//
		map (const map& other)
		{
//			*this = map(
			this->_allocator = other.get_allocator();
			this->_comp = key_compare();
			this->_root = new BSTree<value_type>();

			const_iterator	it;
			for (it = other.begin(); it != other.end(); it++)
			{
				insert(*it);
			}
		}

		allocator_type get_allocator() const
		{
			return (this->_allocator);
		}

		~map() { delete this->_root; this->_root = NULL;}

		//capacity
		bool empty() const { return (!this->size());};
		size_type	size() const { return (this->_root->size());};
//		size_type 	max_size() const {return (this->_allocator.max_size());};
		size_type	max_size() const {
			return (std::numeric_limits<map::size_type>::max() / sizeof(T) / 10);
		}

		//element access
		mapped_type& operator[] (const key_type& k)
		{
//			int j = 7;
			typename BSTree<value_type>::node	*found;

			if (this->size() == 0)
			{
				this->_root->insert(ft::make_pair<key_type, mapped_type>(k, mapped_type()));
				return ((*this)[k]);
			}
			found = this->_root->find(k);
			if (!found)
			{
				this->_root->insert(ft::make_pair<key_type, mapped_type>(k, mapped_type()));
				return (this->operator[](k));
			}
			return (found->content.second);

		}

		mapped_type& at (const key_type& k)
		{
			typename BSTree<value_type>::node	*found;

			found = this->_root->find(k);
			if (!found)
				throw (std::out_of_range("map::at"));
			return (found->content.second);
		}

		const mapped_type& at (const key_type& k) const
		{
			typename BSTree<value_type>::node	*found;

			found = this->_root->find(k);
			if (!found)
				throw (std::out_of_range("map::at"));
			return (found->value);
		}

		//modifiers
		pair<iterator,bool>	insert(const value_type& p)
		{
			typename BSTree<value_type>::node	*new_inserted;
			size_type	old_size;

			old_size = this->size();
			new_inserted = _root->insert(p);
			return (make_pair<iterator, bool> (iterator(new_inserted), (old_size < this->size())));
		}

		iterator insert (iterator position, const value_type& val)
		{
			typename BSTree<value_type>::node	*new_inserted;

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
				insert(*it);
				it++;	
			}
		}

		//void erase (iterator position);
		//size_type erase (const key_type& k);
		//void erase (iterator first, iterator last);
		//void swap (map& x);
		//void clear();

		
		//observers
		key_compare key_comp() const
		{
			return (this->_comp);
		}
		//value_compare value_comp() const;
		

		//operations
		iterator find (const key_type& k)
		{
			node*	found;

			found = this->_root->find(k);
			return (iterator(found));
		}
		const_iterator find (const key_type& k) const
		{
			node*	found;

			found = this->_root->find(k);
			return (const_iterator(found));
		}
		//
		size_type count (const key_type& k) const
		{
			iterator	it;

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
			return (const_iterator(lower_bound(k)));
		}


//
//		iterator upper_bound (const key_type& k);const_iterator upper_bound (const key_type& k) const;
//
//		pair<const_iterator,const_iterator> equal_range (const key_type& k) const;pair<iterator,iterator>             equal_range (const key_type& k);


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
			node*	found;
			found = this->_root->getLowestNode();

			return (const_iterator(found));
		}

		const_iterator end() const
		{
			node*	found;
			found = this->_root->getSentinel();

			return (const_iterator(found));
		}

		private:
			Allocator			_allocator;
			key_compare			_comp;
			BSTree<value_type>	*_root;
	};

}

#endif
