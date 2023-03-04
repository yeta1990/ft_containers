#ifndef PAIR_HPP
# define PAIR_HPP

namespace ft{
template <class T1, class T2> 
struct pair
{
	typedef T1	first_type;
	typedef T2	second_type;

	first_type 	first;
	second_type	second;

	pair() : first(first_type()), second(second_type()) {};

	template<class U, class V>
	pair (const ft::pair<U,V>& pr) : first(pr.first), second(pr.second)	{ }

	pair (const first_type& a, const second_type& b) : first(a), second(b) {}

	template<class U, class V>
	pair& operator= (const ft::pair<U, V>& pr)
	{
		this->first = pr.first;
		this->second = pr.second;
		return (*this);
	}


//	void swap (pair& pr) noexcept ( noexcept(swap(first,pr.first)) && noexcept(swap(second,pr.second)) )
//	{
//		swap(first,pr.first);
//  		swap(second,pr.second);
//	}

//	template <size_t I, class T1, class T2>  
//	typename std::tuple_element< I, pair<T1,T2> >::type&  get (pair<T1,T2>&  pr) noexcept;

//	template <size_t I, class T1, class T2>  
//	typename std::tuple_element< I, pair<T1,T2> >::type&& get (pair<T1,T2>&& pr) noexcept;

//	template <size_t I, class T1, class T2>  
//	const typename std::tuple_element< I, pair<T1,T2> >::type& get (const pair<T1,T2>& pr) noexcept;



};

template <class T1, class T2>  
bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
{ return lhs.first==rhs.first && lhs.second==rhs.second; }

template <class T1, class T2>  
bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
{ return !(lhs==rhs); }

template <class T1, class T2>  
bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
{ return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second); }

template <class T1, class T2>  
bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
{ return !(rhs<lhs); }

template <class T1, class T2>  
bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
{ return rhs<lhs; }

template <class T1, class T2>  
bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
{ return !(lhs<rhs); }


}

#endif
