#ifndef TREE_ITERATOR
# define TREE_ITERATOR

#include "iterator_traits.hpp"

namespace ft{
	//map uses node*
	template <class N, class B>
	class tree_iterator
	{

		public:
		//			iterator_category; //bidirectional
//			typedef typename ft::iterator_traits<T>::value_type	value_type;
			typedef B	value_type;
//			typedef	typename ft::iterator_traits<N>::value_type	self_type;
//			typedef	typename self_type::value_type				value_type;
			typedef typename ft::iterator_traits<N>::pointer npointer;
//			typedef	T*				pointer;
			typedef typename ft::iterator_traits<N>::reference nreference;
//			typedef typename ft::iterator_traits<B>::pointer pointer;
//			typedef typename ft::iterator_traits<B>::reference reference;
			typedef	value_type*		pointer;
			typedef	value_type&		reference;
			typedef std::bidirectional_iterator_tag iterator_category;
			typedef std::ptrdiff_t			difference_type;
//			typedef	value_type&				reference;
//			typedef typename ft::iterator_traits<typename T::value_type>::difference_type difference_type;
//			typedef size_t difference_type;
//			typedef typename ft::iterator_traits<T>::pointer pointer;
//			reference;

			tree_iterator() : p() {}
			explicit tree_iterator(npointer ptr) : p(ptr) {}

//			explicit tree_iterator(const tree_iterator& it) : p(it.getNode()) {}

			template<typename C, typename D>
			tree_iterator(const tree_iterator<C, D> &it) : p(it.getNode()) {}

//			template<typename C>
			tree_iterator& operator=(const tree_iterator &it)
			{
				p = it.getNode();
				return *this;
			}

			reference operator*() const { return *(p->content); }
			pointer operator->() const { return p->content; }
			npointer*	base() { return (&p) ;}
			npointer		getNode() const { return (p) ;}
//			pointer		getNode() { return (p) ;}
			tree_iterator& operator++() {
				npointer n;
				n = p;
				n = n->getNextElement(); 
				p = n;
				return *this; 
			}
			tree_iterator& operator--() { 
				npointer n;
				n = p;
				n = n->getPrevElement(); 
				p = n;
				return *this; 
			}

			tree_iterator operator++(int) { 
				tree_iterator copy(*this);
				++(*this);
				return (copy); }
			tree_iterator operator--(int) { 
				tree_iterator	copy(*this);
				--(*this);
				return (copy);
			}

			//this isn't necessary for a bidirectional iterator
		/*	tree_iterator operator-(difference_type i) const { 
				pointer n;
				n = p;

				for (difference_type j = 0; j < i; j++)
					n = n->getPrevElement();
				return (tree_iterator(n)); 
			};
			*/

		private:
			npointer p;
	};

template <typename N1, typename B1, typename N2, typename B2>
bool operator!=(const ft::tree_iterator<N1, B1> &a, const ft::tree_iterator<N2, B2> &b){
				return (a.getNode() != b.getNode());	}

template <typename N1, typename B1, typename N2, typename B2>
bool operator==(const ft::tree_iterator<N1, B1> &a, const ft::tree_iterator<N2, B2> &b){
				return (a.getNode() == b.getNode());	}

}


#endif
