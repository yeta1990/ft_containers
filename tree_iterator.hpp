#ifndef TREE_ITERATOR
# define TREE_ITERATOR

#include "iterator_traits.hpp"
#include <cstddef>
#include <iterator>
namespace ft{
	// map uses node*
	// N usually will be node*, B will be a pair<T, Y>
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
			typedef typename ft::iterator_traits<N>::difference_type difference_type;
//			typedef std::ptrdiff_t			difference_type;

			tree_iterator() : p(NULL), sentinel(NULL) {}
//			explicit tree_iterator(npointer ptr) : p(ptr), sentinel(ptr.getSen) {}
			explicit tree_iterator(npointer ptr, npointer sentinel) : p(ptr), sentinel(sentinel) {}


//			template<typename C, typename D>
//			tree_iterator(C ptr, D sentinel) : p(ptr), sentinel(sentinel) {}

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
			

//			reference operator*() const { return *(p->content); }
//			pointer operator->() const { return p->content; }
			reference operator*() const { return *(p->getContent()); }
			pointer operator->() const { return p->getContent(); }
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

			npointer getHighestNode() const
			{
				npointer aux = NULL;

				aux = p;
				while (aux && aux->parent && aux->parent != sentinel)
					aux = aux->parent;
				return (getHighestNodeFrom(aux));
			}

			npointer getHighestNodeFrom(npointer node) const
			{
				npointer aux = NULL;

				aux = node;
				while (aux && aux->right && aux->right != sentinel)
					aux = aux->right;
				return (aux);
			}

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

			npointer	getPrevElement() const
			{
				npointer	parent;
				npointer	node;

				node = p;
				if (p == sentinel)
				{
					return (getHighestNode());
				}
				if (node->left && node->left != sentinel)
					return (getHighestNodeFrom(node->left));
				parent = node->parent;
				while (parent && node == parent->left && parent != sentinel)
				{
					node = parent;
					parent = parent->parent;
				}
				return (parent);
			}

			tree_iterator& operator++() {
				p = getNextElement();
				return *this; 
			}

			tree_iterator& operator--() { 
				p = getPrevElement();
				return *this; 
			}

			tree_iterator operator++(int) { 
				tree_iterator copy(getNode(), getSentinel());
				++(*this);
				return (copy); 
			}

			tree_iterator operator--(int) { 
				tree_iterator copy(getNode(), getSentinel());
				--(*this);
				return (copy);
			}

		protected:
			npointer 	p;
			npointer	sentinel;
	};

	template <class N, class B>
	class set_iterator : public tree_iterator<N,B>
	{
		public:
			typedef B	value_type;
			typedef typename ft::iterator_traits<N>::pointer npointer;
			typedef typename ft::iterator_traits<N>::reference nreference;
			typedef	const typename value_type::second_type*		pointer;
			typedef	const typename value_type::second_type&		reference;
			typedef std::bidirectional_iterator_tag iterator_category;
			typedef typename ft::iterator_traits<N>::difference_type difference_type;

			set_iterator() : tree_iterator<N, B>(){};

			explicit set_iterator(npointer ptr, npointer sentinel) : tree_iterator<N,B>(ptr, sentinel) {}

			template<typename C, typename D>
			set_iterator(const set_iterator<C, D> &it)
			{
				this->p = it.getNode();
//				this->p = it.p;
				this->sentinel = it.getSentinel();
//				this->sentinel = it.end();
			}

			template<typename C, typename D>
			set_iterator& operator=(const set_iterator<C, D> &it)
//			set_iterator& operator=(const set_iterator &it)
			{
//				this->p = it.p;
				this->p = it.getNode();
				this->sentinel = it.getSentinel();
				return *this;
			}

			npointer		getNode() const { return (this->p) ;}
			npointer		getSentinel() const { return (this->sentinel) ;}

			reference operator*() const { 
				return (this->p->getContent()->first);
			}
			pointer operator->() const { return &(this->p->getContent()->first); }

			set_iterator& operator++() {
				this->p = this->getNextElement();
				return *this; 
			}

			set_iterator& operator--() { 
				this->p = this->getPrevElement();
				return *this; 
			}

			set_iterator operator++(int) { 
				set_iterator copy(this->getNode(), this->getSentinel());
				++(*this);
				return (copy); 
			}

			set_iterator operator--(int) { 
				set_iterator copy(this->getNode(), this->getSentinel());
				--(*this);
				return (copy);
			}

	};

template <typename N1, typename B1, typename N2, typename B2>
bool operator!=(const ft::tree_iterator<N1, B1> &a, const ft::tree_iterator<N2, B2> &b){
				return (a.getNode() != b.getNode());	}

template <typename N1, typename B1, typename N2, typename B2>
bool operator==(const ft::tree_iterator<N1, B1> &a, const ft::tree_iterator<N2, B2> &b){
				return (a.getNode() == b.getNode());	}

}


#endif
