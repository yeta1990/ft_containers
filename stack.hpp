#ifndef STACK_HPP
# define STACK_HPP

#include "vector.hpp"

namespace ft{

	template <class T, class Container = ft::vector<T> > class stack
	{
		public:
			typedef T			value_type;
			typedef Container 	container_type;
			typedef size_t		size_type;

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
				return (c.at(0));
			}

			const value_type& top() const
			{
				return (c.at(0));
			}


		private:
			container_type c;


	};


}

#endif
