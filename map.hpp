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
#include "tree_iterator.hpp"

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
		typedef	Node<key_type, mapped_type>					node;
		//bidirectional iterator?
		//this must be chaged to a custom iterator for node*
		typedef tree_iterator<typename BSTree<Key, T>::node* >	iterator;
//		typedef random_iterator<pointer> iterator;
//		typedef random_iterator<const_pointer> const_iterator;
//		typedef ft::reverse_iterator<iterator> reverse_iterator;
//		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
//		typedef typename iterator_traits<iterator>::difference_type difference_type;
		typedef size_t size_type;

//		map() {};
		explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
		{
//			std::cout << "map created " << std::endl;
			this->_allocator = alloc;
			this->_comp = comp;
			this->_root = new BSTree<key_type, mapped_type>();
		}

//		template <class InputIterator>
//		map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());
//
//		map (const map& other);
		~map() { delete this->_root; this->_root = NULL;}

		//capacity
		bool empty() const { return (!this->size());};
		size_type	size() const { return (this->_root->size());};

		//element access
		mapped_type& operator[] (const key_type& k)
		{
//			int j = 7;
			typename BSTree<key_type, mapped_type>::node	*found;

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
			return (found->value);

		}

		mapped_type& at (const key_type& k)
		{
			typename BSTree<key_type, mapped_type>::node	*found;

			found = this->_root->find(k);
			if (!found)
				throw (std::out_of_range("map::at"));
			return (found->value);
		}

		const mapped_type& at (const key_type& k) const
		{
			typename BSTree<key_type, mapped_type>::node	*found;

			found = this->_root->find(k);
			if (!found)
				throw (std::out_of_range("map::at"));
			return (found->value);
		}

		pair<iterator,bool>	insert(const value_type& p)
		{
			typename BSTree<key_type, mapped_type>::node	*new_inserted;
			size_type	old_size;

			old_size = this->size();
			new_inserted = _root->insert(p);
			return (make_pair<iterator, bool> (iterator(new_inserted), (old_size < this->size())));
		}

		iterator insert (iterator position, const value_type& val)
		{
			typename BSTree<key_type, mapped_type>::node	*new_inserted;

			new_inserted = _root->insert(position, val);
			return (iterator(new_inserted));
		}

//		template <class InputIterator>
//		void insert (InputIterator first, InputIterator last)
//		{
//
//		}


		iterator begin()
		{
			node*	found;
			found = this->_root->getLowestNode();

			return (iterator(found));
		}
//		const_iterator begin() const;


		private:
			Allocator			_allocator;
			key_compare			_comp;
			BSTree<key_type, mapped_type>	*_root;
	};

}

#endif
