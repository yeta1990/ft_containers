#ifndef STACK_HPP
# define STACK_HPP

#include "vector.hpp"

namespace ft{

	template <class T, class Container = ft::vector<T> > class stack
	{
		public:
			typedef T						value_type;
			typedef Container 				container_type;
			typedef size_t					size_type;
			typedef typename Container::reference 	reference;
			typedef typename Container::const_reference const_reference;

			explicit stack (const container_type& ctnr = container_type()) : c(ctnr) {};

			void push (const value_type& val)
			{
				c.push_back(val);
			}

			bool empty() const
			{
				return (!c.size());
			}

			size_type size() const
			{
				return (c.size());
			}

			value_type& top()
			{
				return (c.back());
			}

			const value_type& top() const
			{
				return (c.back());
			}

			void pop()
			{
				return (c.pop_back());
			}


		protected:
			container_type c;


//		template< class T, class Container >
		friend bool operator==( const ft::stack<T, Container>& lhs,
			const ft::stack<T, Container>& rhs )
		{
			return (lhs.c == rhs.c);
		}

	friend bool operator!=( const ft::stack<T, Container>& lhs,
		const ft::stack<T, Container>& rhs )
	{
		return (lhs.c != rhs.c);
	}





//	template< class T, class Container >

		
	
//	template< class T, class Container >
	friend bool operator< ( const ft::stack<T, Container>& lhs,
                 const ft::stack<T, Container>& rhs )
	{
		return (lhs.c < rhs.c);
	}

//	template< class T, class Container >
	friend bool operator<=( const ft::stack<T, Container>& lhs,
		const ft::stack<T, Container>& rhs )
	{
		return (lhs.c <= rhs.c);
	}

//	template< class T, class Container >
	friend bool operator> ( const ft::stack<T, Container>& lhs,
		const ft::stack<T, Container>& rhs )
	{
		return (lhs.c > rhs.c);
	}

//	template< class T, class Container >
	friend bool operator>=( const ft::stack<T, Container>& lhs,
		const ft::stack<T, Container>& rhs )
	{
		return (lhs.c >= rhs.c);
	}

	};


}

#endif
