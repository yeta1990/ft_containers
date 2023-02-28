#ifndef TREE_ITERATOR
# define TREE_ITERATOR

#include "iterator_traits.hpp"

namespace ft{
	//map uses node*
	template <class N, class B>
	class tree_iterator
	{

		public:
			typedef B	value_type;
			typedef typename ft::iterator_traits<N>::pointer npointer;
			typedef typename ft::iterator_traits<N>::reference nreference;
			typedef	value_type*		pointer;
			typedef	value_type&		reference;
			typedef std::bidirectional_iterator_tag iterator_category;
			typedef std::ptrdiff_t			difference_type;

			tree_iterator() : p(NULL), sentinel(NULL) {}
//			explicit tree_iterator(npointer ptr) : p(ptr), sentinel(ptr.getSentinel()) {}
			explicit tree_iterator(npointer ptr, npointer sentinel) : p(ptr), sentinel(sentinel) {}

			template<typename C, typename D>
			tree_iterator(const tree_iterator<C, D> &it)
			{
				p = it.getNode();
				sentinel = it.getSentinel();
			}

			template<typename C, typename D>
			tree_iterator& operator=(const tree_iterator<C, D> &it)
			{
				p = it.getNode();
				sentinel = it.getSentinel();
				return *this;
			}
			

			reference operator*() const { return *(p->content); }
			pointer operator->() const { return p->content; }
			npointer*	base() { return (&p) ;}
			npointer		getNode() const { return (p) ;}
			npointer		getSentinel() const { return (sentinel) ;}

			npointer getLowestNodeFrom(npointer node) const
			{
				npointer aux = NULL;

				aux = node;
				while (aux && aux->left && aux->left != sentinel)
					aux = aux->left;
				return (aux);
			};

			npointer	getNextElement() const
			{
				npointer parent;
				npointer node;

				node = p;
				if (node && node->right && node->right != sentinel)
					return (getLowestNodeFrom(node->right));
				parent = node->parent;
				while (parent && node == parent->right && parent != sentinel)
				{
					node = parent;
					parent = parent->parent;
				}
				return (parent);
			}

			tree_iterator& operator++() {
//				npointer n;
//				n = p;
//				n = n->getNextElement(); 
				p = getNextElement();
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
//				tree_iterator copy(*this);
				tree_iterator copy(getNode(), getSentinel());
				++(*this);
				return (copy); 
			}

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
			npointer 	p;
			npointer	sentinel;
	};

template <typename N1, typename B1, typename N2, typename B2>
bool operator!=(const ft::tree_iterator<N1, B1> &a, const ft::tree_iterator<N2, B2> &b){
				return (a.getNode() != b.getNode());	}

template <typename N1, typename B1, typename N2, typename B2>
bool operator==(const ft::tree_iterator<N1, B1> &a, const ft::tree_iterator<N2, B2> &b){
				return (a.getNode() == b.getNode());	}

}


#endif
