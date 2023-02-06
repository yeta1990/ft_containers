#ifndef TREE_ITERATOR
# define TREE_ITERATOR

#include "iterator_traits.hpp"

namespace ft{
	//map uses node*
	template <class T>
	class tree_iterator
	{

		public:
		//			iterator_category; //bidirectional
//			typedef typename ft::iterator_traits<T>::value_type	value_type;
			typedef	typename ft::iterator_traits<T>::value_type	self_type;
			typedef	typename self_type::value_type				value_type;
			typedef typename ft::iterator_traits<T>::pointer pointer;
//			typedef	self_type*				pointer;
			typedef	value_type&				reference;
//			typedef typename ft::iterator_traits<T>::pointer pointer;
//			reference;
//
			tree_iterator() : p() {}
			tree_iterator(pointer ptr) : p(ptr) {}
			value_type operator*() const { return p->content; }
			pointer*	base() { return (&p) ;}
			tree_iterator& operator++(int) { p = p->getNextElement(); return *this; }

		private:
			pointer p;
	};

}


#endif
