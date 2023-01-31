#ifndef MAKE_PAIR_HPP
# define MAKE_PAIR_HPP

# include "pair.hpp"

namespace ft {
template< class T1, class T2 >
pair<T1, T2> make_pair( T1 t, T2 u )
{
	return ( pair<T1,T2>(t, u) );	
}

}
#endif
