#include "tests.hpp"
#include "map.hpp"
#include <string>
#include <map>

void	map_constructor()
{
	std::map<int,int> map;
	ft::map<int,int> map1;
	
	check(map.size() == map1.size());
	check(map.empty() == map1.empty());
	
	map.insert( std::pair<int, int>(8, 8) );
	map1.insert( ft::pair<int, int>(8, 8) );
	check(map.size() == map1.size());
	check(map.empty() == map1.empty());

	map.insert( std::pair<int, int>(5, 5) );
	map1.insert( ft::pair<int, int>(5, 5) );
	check(map.size() == map1.size());

	map.insert( std::pair<int, int>(11, 11) );
	map1.insert( ft::pair<int, int>(11, 11) );
	check(map.size() == map1.size());

	map.insert( std::pair<int, int>(-2, -2) );
	map1.insert( ft::pair<int, int>(-2, -2) );
	check(map.size() == map1.size());

	map.insert( std::pair<int, int>(7, 7) );
	map1.insert( ft::pair<int, int>(7, 7) );
	check(map.size() == map1.size());

	map.insert( std::pair<int, int>(10, 10) );
	map1.insert( ft::pair<int, int>(10, 10) );
	check(map.size() == map1.size());
	

/*	map.insert(10, 10);
	map.insert(9, 9);
	map.insert(4, 4);
	map.insert(1, 1);
	map.insert(-1, -1);	
	map.insert(6, 6);
	map.insert(12, 12);	
	map.insert(-7, -7); 
*/

	/*
	map1.insert(3, 3);
	map1.insert(11, 11);
	map1.insert(-2, -2);
	map1.insert(7, 7);
	map1.insert(10, 10);
	map1.insert(9, 9);
	map1.insert(4, 4);	
	map1.insert(1, 1);
	map1.insert(-1, -1);
	map1.insert(6, 6);
	map1.insert(12, 12);
	map1.insert(-7, -7);
	*/

	
//	std::cout << "size: " << map.size() << std::endl;

}

ft::map<int, int> create_map()
{
	ft::map<int,int> map1;
	map1.insert( ft::pair<int, int>(8, 8) );
	map1.insert( ft::pair<int, int>(5, 5) );
	map1.insert( ft::pair<int, int>(11, 11) );
	map1.insert( ft::pair<int, int>(-2, -2) );
	map1.insert( ft::pair<int, int>(6, 6) );
	map1.insert( ft::pair<int, int>(10, 10) );
	map1.insert( ft::pair<int, int>(9, 9) );
	map1.insert( ft::pair<int, int>(-10, -10) );
	map1.insert( ft::pair<int, int>(1, 1) );
	map1.insert( ft::pair<int, int>(4, 4) );
	return (map1);
}

std::map<int, int> create_std_map()
{
	std::map<int,int> map1;
	map1.insert( std::pair<int, int>(8, 8) );
	map1.insert( std::pair<int, int>(5, 5) );
	map1.insert( std::pair<int, int>(11, 11) );
	map1.insert( std::pair<int, int>(-2, -2) );
	map1.insert( std::pair<int, int>(6, 6) );
	map1.insert( std::pair<int, int>(10, 10) );
	map1.insert( std::pair<int, int>(9, 9) );
	map1.insert( std::pair<int, int>(-10, -10) );
	map1.insert( std::pair<int, int>(1, 1) );
	map1.insert( std::pair<int, int>(4, 4) );
	return (map1);
}

void	map_constructor2()
{
	std::map<int, int> map = create_std_map();
	ft::map<int, int> map1 = create_map();
	std::map<int, int>::iterator it;
	ft::map<int, int>::iterator it1;
	std::map<int, int>::iterator it_end;
	ft::map<int, int>::iterator it1_end;

	it = map.begin();
	it1 = map1.begin();
	it++;
	it++;
	it1++;
	it1++;
	
	it_end = it;	
	it1_end = it1;
	check((*it_end).first == (*it1_end).first);

	for (int i = 0; i < 4; i++)
	{
		it_end++;
		it1_end++;
	}

	std::map<int,int> map2(it, it_end);
	ft::map<int,int> map3(it1, it1_end);

	check(map2.size() == map3.size());

	it = map2.begin();
	it1 = map3.begin();
	for (; it1 != map3.end(); it1++)
	{
		check((*it).first == (*it1).first);
		it++;
	}
}

void	map_copy_constructor()
{
	std::map<int, int> map = create_std_map();
	ft::map<int, int> map1 = create_map();
	std::map<int, int> mapc(map);
	ft::map<int, int> map1c(map1);



}

void	operator_access()
{
	std::map<int,int> map;
	ft::map<int,int> map1;
	
	for (size_t i = 0; i < 12; i++)
	{
		map.insert( std::pair<int, int>(i, i) );
		map1.insert( ft::pair<int, int>(i, i) );
	}
	for (size_t i = 0; i < 12; i++)
		check(map[i] == map1[i]);
//	check(map[111] == map1[111]);
//	std::cout << map1[1] << std::endl;

}

void	map_at()
{
	std::map<int,int> map;
	ft::map<int,int> map1;
	
	for (size_t i = 0; i < 12; i++)
	{
		map.insert( std::pair<int, int>(i, i) );
		map1.insert( ft::pair<int, int>(i, i) );
	}
	for (size_t i = 0; i < 12; i++)
		check(map.at(i) == map1.at(i));
	bool	ex1 = false;
	bool 	ex2 = false;

	try
	{
		map.at(101);
	}
	catch (std::exception &e)
	{
		ex1 = true;
	}
	try
	{
		map1.at(101);
	}
	catch (std::exception &e)
	{
		ex2 = true;
	}
	check(ex1 == ex2);
}

void	map_const_at()
{
	std::map<const int,int> map;
	ft::map<const int,int> map1;
	
	for (size_t i = 0; i < 12; i++)
	{
		map.insert( std::pair<int, int>(i, i) );
		map1.insert( ft::pair<int, int>(i, i) );
	}
	for (size_t i = 0; i < 12; i++)
		check(map.at(i) == map1.at(i));
	bool	ex1 = false;
	bool 	ex2 = false;

	try
	{
		map.at(101);
	}
	catch (std::exception &e)
	{
		ex1 = true;
	}
	try
	{
		map1.at(101);
	}
	catch (std::exception &e)
	{
		ex2 = true;
	}
//	std::cout << ex1 << "," << ex2 << std::endl;
	check(ex1 == ex2);
}

void	map_insert()
{
	std::map<char,int> map;
	ft::map<char,int> map1;
	std::pair<std::map<char,int>::iterator,bool> ret;
	ft::pair<ft::map<char,int>::iterator,bool> ret1;

	ret = map.insert( std::pair<int, int>('c', 1) );
	ret1 = map1.insert( ft::pair<char, int>('c', 1) );
	check (ret.second == ret1.second);

	ret = map.insert( std::pair<int, int>('c', 1) );
	ret1 = map1.insert( ft::pair<char, int>('c', 1) );
	check (ret.second == ret1.second);
//	std::cout << ret.second << "," << ret1.second << std::endl;

}

void	map_insert_iterator()
{
	std::map<char,int> map;
	std::pair<std::map<char,int>::iterator,bool> ret;
	ret = map.insert( std::make_pair('c', 2) );
	map.insert( std::make_pair('d', 2) );
	map.insert( std::make_pair('a', 2) );
	map.insert( std::make_pair('x', 2) );

	ft::map<char,int> map1;
	ft::pair<ft::map<char,int>::iterator,bool> ret1;
	ret1 = map1.insert( ft::make_pair('c', 2) );

	std::map<char,int>::iterator it1(ret.first);

	ft::map<char,int>::iterator it2(ret1.first);
//	std::cout << (*it2).first << std::endl;
	check((*it1).first == (*it2).first);
//	ft::Node<char, int> n(*it2);
//	std::cout << n.key << std::endl;
//	std::cout << (*it2).first << std::endl;
//	std::cout << (*(ret.first)).first << std::endl;
	check((*(ret.first)).first == (*(ret1.first)).first);

	ret = map.insert( std::make_pair('d', 2) );
	ret1 = map1.insert( ft::make_pair('d', 2) );
	check((*(ret.first)).first == (*(ret1.first)).first);
}

void	map_insert_iterator2()
{
//	std::map<int,int> map;
//	std::pair<std::map<int,int>::iterator,bool> ret;
//	ret = map.insert( std::make_pair(, 2) );
//	map.insert( std::make_pair('d', 2) );
//	map.insert( std::make_pair('a', 2) );
//	map.insert( std::make_pair('x', 2) );

	ft::map<int,int> map1;
	ft::pair<ft::map<int,int>::iterator,bool> ret1;
	map1.insert( ft::make_pair(15, 2) );
	map1.insert( ft::make_pair(7, 2) );
	map1.insert( ft::make_pair(30, 2) );
	map1.insert( ft::make_pair(1, 2) );
	map1.insert( ft::make_pair(11, 2) );
	ret1 = map1.insert( ft::make_pair(5, 2) );
//	map1.insert( ft::make_pair(6, 2) );
	ft::pair<ft::map<int,int>::iterator,bool> ret3;
//	ret3 = map1.insert( ft::make_pair(3, 2) );
	map1.insert( ft::make_pair(20, 2) );
	map1.insert( ft::make_pair(17, 2) );
//	map1.insert( ft::make_pair(5, 2) );

//	ret1 = map1.insert( ft::make_pair('x', 2) );
	ft::pair<ft::map<int,int>::iterator,bool> ret2;

	map1.insert(ret1.first, ft::make_pair(25, 2));
	map1.insert(ret1.first, ft::make_pair(6, 2));
	ret2 = map1.insert( ft::make_pair(24, 2) );
	map1.insert(ret1.first, ft::make_pair(-3, 2));
	
	
}



void	map_parent_navigation()
{
	ft::map<int,int> map1 = create_map();
	ft::pair<ft::map<int,int>::iterator,bool> ret1;
	
	ret1 = map1.insert( ft::pair<const int, int>(3, 3) );

	ft::BSTree<ft::pair<const int, int> >::node *n1;
	ft::BSTree<ft::pair<const int, int> >::node *aux;

	n1 = *(ret1.first.base());
	aux = n1;
	check(aux->content->first == 3);
	aux = aux->parent;
	check(aux->content->first == 4);
	aux = aux->parent;
	check(aux->content->first == 1);
	aux = aux->parent;
	check(aux->content->first == -2);
	aux = aux->parent;
	check(aux->content->first == 5);
	aux = aux->parent;
	check(aux->content->first == 8);

}


// 3 insert with hint tests, inserting:
// -3 in node 4
// ¿-1 in node 4?
// 0 in node 1
// 7 in node 4
// 12 in node 10

void	map_insert_hint1()
{
	ft::map<int,int> map1; // = new ft::map<int,int>();
	ft::pair<ft::map<int,int>::iterator,bool> ret1;

	map1.insert( ft::pair<int, int>(8, 8) );
	map1.insert( ft::pair<int, int>(5, 5) );
	map1.insert( ft::pair<int, int>(11, 11) );
	map1.insert( ft::pair<int, int>(-2, -2) );
	map1.insert( ft::pair<int, int>(6, 6) );
	map1.insert( ft::pair<int, int>(10, 10) );
	map1.insert( ft::pair<int, int>(9, 9) );
	map1.insert( ft::pair<int, int>(-10, -10) );
	map1.insert( ft::pair<int, int>(1, 1) );
	ret1 = map1.insert( ft::pair<int, int>(4, 4) );

	ft::map<int,int>::iterator it1;
	it1 = map1.insert(ret1.first, ft::make_pair(-3, -3));

	ft::BSTree<ft::pair<const int, int> >::node *n1;
	ft::BSTree<ft::pair<const int, int> >::node *aux;

	n1 = *it1.base();
	aux = n1;
	check(aux->content->first == -3);
	aux = aux->parent;
	check(aux->content->first == -10);
	
//	std::cout << aux->key << std::endl;
}


void	map_insert_hint2()
{
	ft::map<int,int> map1; // = new ft::map<int,int>();
	ft::pair<ft::map<int,int>::iterator,bool> ret1;
	ft::pair<ft::map<int,int>::iterator,bool> ret2;
	ft::pair<ft::map<int,int>::iterator,bool> ret3;

	map1.insert( ft::pair<int, int>(8, 8) );
	map1.insert( ft::pair<int, int>(5, 5) );
	map1.insert( ft::pair<int, int>(11, 11) );
	map1.insert( ft::pair<int, int>(-2, -2) );
	map1.insert( ft::pair<int, int>(6, 6) );
	map1.insert( ft::pair<int, int>(10, 10) );
	map1.insert( ft::pair<int, int>(9, 9) );
	ret2 = map1.insert( ft::pair<int, int>(-10, -10) );
	map1.insert( ft::pair<int, int>(1, 1) );
	ret1 = map1.insert( ft::pair<int, int>(4, 4) );

	ft::BSTree<ft::pair<const int, int> >::node *n1;
	ft::BSTree<ft::pair<const int, int> >::node *aux;
	ft::map<int,int>::iterator it1;

	it1 = map1.insert(ret1.first, ft::make_pair(7, 7));
	n1 = *it1.base();
	aux = n1;
	check(aux->content->first == 7);
	aux = aux->parent;
	check(aux->content->first == 6);

	it1 = map1.insert(ret1.first, ft::make_pair(-3, -3));
	n1 = *it1.base();
	aux = n1;
	check(aux->content->first == -3);
	aux = aux->parent;
	check(aux->content->first == -10);

	it1 = map1.insert(ret2.first, ft::make_pair(12, 12));
	n1 = *it1.base();
	aux = n1;
	check(aux->content->first == 12);
	aux = aux->parent;
	check(aux->content->first == 11);
}


void	map_insert_iterator3()
{
	std::map<int, int> map = create_std_map();
	ft::map<int, int> map1 = create_map();
	std::map<int, int>::iterator it;
	ft::map<int, int>::iterator it1;
	std::map<int, int>::iterator it_end;
	ft::map<int, int>::iterator it1_end;

	it = map.begin();
	it1 = map1.begin();
	it++;
	it++;
	it1++;
	it1++;
	
	it_end = it;	
	it1_end = it1;
	check((*it_end).first == (*it1_end).first);

	for (int i = 0; i < 4; i++)
	{
		it_end++;
		it1_end++;
	}

	std::map<int,int> map2;

	ft::map<int,int> map3;
	check(map2.size() == map3.size());
	map2.insert(it, it_end);
	map3.insert(it1, it1_end);

	check(map2.size() == map3.size());
	it = map2.begin();
	it1 = map3.begin();
	for (; it1 != map3.end(); it1++)
	{
		check((*it).first == (*it1).first);
		it++;
	}
}



void	map_operator_pp()
{
	std::map<int, int> map = create_std_map();
	std::map<int, int>::iterator it;
	ft::map<int, int> map1 = create_map();
	ft::map<int, int>::iterator it1;

	it = map.begin();
	it1 = map1.begin();
	check((*it).first == (*it1).first);
	map.insert( std::pair<int, int>(12, 12) );
	map1.insert( ft::pair<int, int>(12, 12) );

	for (it1 = map1.begin(); it1 != map1.end(); it1++)
	{
		check((*it).first == (*it1).first);
		it++;
	}

	it = map.begin();
	it1 = map1.begin();
	for (; it1 != map1.end(); ++it1)
	{
		check((*it).first == (*it1).first);
		++it;
	}

}

void	map_operator_ll()
{
	std::map<int, int> map = create_std_map();
	std::map<int, int>::iterator it;
	ft::map<int, int> map1 = create_map();
	ft::map<int, int>::iterator it1;

	it = map.end();
	it1 = map1.end();
	it--;
	it1--;


	for (; it1 != map1.begin(); it1--)
	{
		check((*it).first == (*it1).first);
		it--;
	}

	it = map.end();
	it1 = map1.end();
	--it;
	--it1;
	for (; it1 != map1.begin(); it1--)
	{
		check((*it).first == (*it1).first);
		it--;
	}

}

void	map_iterator_const()
{
	std::map<int, int> map = create_std_map();
	std::map<int, int>::iterator it;
	ft::map<int, int> map1 = create_map();
	ft::map<int, int>::const_iterator it1;

	it = map.begin();
	it1 = map1.begin();
	std::map<int, int>::const_iterator	it2(it);
	ft::map<int, int>::const_iterator	it3(it1);

	check(it->first == it1->first);
	it2++;
	it3++;
	check(it2->first == it3->first);
	it2--;
	it3--;
	check(it2->first == it3->first);
}

void	map_iterator_const_2()
{
	std::map<int, int> map = create_std_map();
	std::map<int, int>::const_iterator it;
	ft::map<int, int> map1 = create_map();
	ft::map<int, int>::const_iterator it1;

	it = map.begin();
	it1 = map1.begin();
	std::map<int, int>::const_iterator	it2(it);
	ft::map<int, int>::const_iterator	it3(it1);

	check(it->first == it1->first);
	it2++;
	it3++;
	check(it2->first == it3->first);
	it2--;
	it3--;
	check(it2->first == it3->first);
}

void	map_maxsize()
{
	std::map<int, int> map;
	ft::map<int, int> map1;

	check(map.max_size() == map1.max_size());
//	std::cout << map.max_size() << "," << map1.max_size() << std::endl;
}

void	map_find()
{
	std::map<int, int> map = create_std_map();
	ft::map<int, int> map1 = create_map();

	std::map<int, int>::iterator it;
	ft::map<int, int>::iterator it1;

	it = map.find(-10);
	it1 = map1.find(-10);

	check((*it).first == (*it1).first);
	it = map.find(0);
	it1 = map1.find(0);
	check(it == map.end());
	check(it1 == map1.end());

	std::map<int, int>::iterator itc;
	ft::map<int, int>::iterator it1c;
	itc = map.find(-10);
	it1c = map1.find(-10);

	check((*itc).first == (*it1c).first);
	itc = map.find(0);
	it1c = map1.find(0);
	check(itc == map.end());
	check(it1c == map1.end());

	map.insert(std::make_pair<int,int>(-10,-10));
	map1.insert(ft::make_pair<int,int>(-10,-10));
	check(map.count(-10) == map1.count(-10));	
	check(map.count(0) == map1.count(0));	
	map.insert(std::make_pair<int,int>(0,0));
	map1.insert(ft::make_pair<int,int>(0,0));
	check(map.count(0) == map1.count(0));	

}

void	map_lower_bound()
{
	std::map<int, int> map = create_std_map();
	ft::map<int, int> map1 = create_map();
	std::map<int, int>::iterator it;
	ft::map<int, int>::iterator it1;

	it = map.lower_bound(7);
	it1 = map1.lower_bound(7);
	check((*it).first == (*it1).first);

	it = map.lower_bound(-10);
	it1 = map1.lower_bound(-10);
	check((*it).first == (*it1).first);

	it1 = map1.lower_bound(200);
	check(it1 == map1.end());

	std::map<int, int>::const_iterator itc;
	ft::map<int, int>::const_iterator it1c;

	itc = map.lower_bound(7);
	it1c = map1.lower_bound(7);
	check((*itc).first == (*it1c).first);

	itc = map.lower_bound(-10);
	it1c = map1.lower_bound(-10);
	check((*itc).first == (*it1c).first);

	it1c = map1.lower_bound(200);
	check(it1c == map1.end());
}

void	map_upper_bound()
{
	std::map<int, int> map = create_std_map();
	ft::map<int, int> map1 = create_map();
	std::map<int, int>::iterator it;
	ft::map<int, int>::iterator it1;

	it = map.upper_bound(7);
	it1 = map1.upper_bound(7);
	check((*it).first == (*it1).first);

	it = map.upper_bound(-10);
	it1 = map1.upper_bound(-10);
	check((*it).first == (*it1).first);

	it1 = map1.upper_bound(200);
	check(it1 == map1.end());

	std::map<int, int>::const_iterator itc;
	ft::map<int, int>::const_iterator it1c;

	itc = map.upper_bound(7);
	it1c = map1.upper_bound(7);
	check((*itc).first == (*it1c).first);

	itc = map.upper_bound(-10);
	it1c = map1.upper_bound(-10);
	check((*itc).first == (*it1c).first);

	it1c = map1.upper_bound(200);
	check(it1c == map1.end());
}

void	map_equal_range()
{
	std::map<int, int> map = create_std_map();
	ft::map<int, int> map1 = create_map();
//	std::map<int, int>::iterator it;
//	ft::map<int, int>::iterator it1;

	std::pair<std::map<int,int>::iterator, std::map<int,int>::iterator> p;
	ft::pair<ft::map<int,int>::iterator, ft::map<int,int>::iterator> p1;

	p = map.equal_range(1);
	p1 = map1.equal_range(1);
	check((*p.first).first == (*p1.first).first);
	check((*p.second).first == (*p1.second).first);

//	std::map<int, int> map2;
//	ft::map<int, int> map3;
	p = map.equal_range(150);
	p1 = map1.equal_range(150);
	check(p.first == map.end());
	check(p1.first == map1.end());

	std::map<int, int> const map2(map);
	ft::map<int, int> const map3(map1);
	std::pair<std::map<int,int>::const_iterator, std::map<int,int>::const_iterator> p2;
	ft::pair<ft::map<int,int>::const_iterator, ft::map<int,int>::const_iterator> p3;
	p2 = map2.equal_range(1);
	p3 = map3.equal_range(1);
	check((*p2.first).first == (*p3.first).first);
	check((*p2.second).first == (*p3.second).first);

//	ft::map<int, int> map3 = create_map();

}

void	map_erase()
{
	std::map<int, int> map = create_std_map();
	ft::map<int, int> map1 = create_map();
	std::map<int, int>::iterator it;
	ft::map<int, int>::iterator it1;

	it = map.begin();
	it1 = map1.begin();
	for (size_t i = 0; i < 4; i++)
	{
		it++;
		it1++;
	}
//	std::cout << "erase " << it->first << std::endl;
	map.erase(it);
	map1.erase(it1);
	check(map.size() == map1.size());

	
	it = map.find(5);
	it1 = map1.find(5);
	check(it == map.end());
	check(it1 == map1.end());

	it = map.find(4);
	it1 = map1.find(4);
	check(it->first == it1->first);
	check((++it)->first == (++it1)->first);

	it = map.find(4);
	it1 = map1.find(4);
	check((--it)->first == (--it1)->first);

	it = map.find(1);
	it1 = map1.find(1);
//	std::cout << "erase " << it->first << std::endl;
	map.erase(it);
	map1.erase(it1);
	check(map.size() == map1.size());
	it = map.find(1);
	it1 = map1.find(1);
	check(it == map.end());
	check(it1 == map1.end());

	map[3] = 3;	
	map1[3] = 3;	
	check(map.size() == map1.size());
	it = map.find(3);
	it1 = map1.find(3);
	check(it->first == it1->first);
	check((--it)->first == (--it1)->first);
//	std::cout << it->first << "," << it1->first << std::endl;
	check((++it)->first == (++it1)->first);
//	std::cout << it->first << "," << it1->first << std::endl;

	it = map.find(10);
	it1 = map1.find(10);
	map.erase(it);
	map1.erase(it1);
	check(map.size() == map1.size());
//	std::cout << it->first << "," << it1->first << std::endl;
	it = map.find(9);
	it1 = map1.find(9);
//	check(it != map.end());
//	check(it1 1= map1.end());
	check(it->first == it1->first);
	check((--it)->first == (--it1)->first);
//	std::cout << it->first << "," << it1->first << std::endl;
	check((++it)->first == (++it1)->first);
//	std::cout << it->first << "," << it1->first << std::endl;
	it = map.find(10);
	it1 = map1.find(10);
	check(it == map.end());
	check(it1 == map1.end());

}

void	map_erase_2()
{
	std::map<int, int>				map;
	ft::map<int, int>				map1;
	std::map<int, int>::iterator	it;
	ft::map<int, int>::iterator		it2;
	std::map<int, int>::iterator	it3;
	ft::map<int, int>::iterator		it4;
	std::map<int, int>::iterator	it5;
	ft::map<int, int>::iterator		it6;

	it = map.insert(std::make_pair(1,1)).first;
	it2 = map1.insert(ft::make_pair(1,1)).first;
	it3 = map.insert(std::make_pair(2,2)).first;
	it4 = map1.insert(ft::make_pair(2,2)).first;
	it5 = map.insert(std::make_pair(-1,-1)).first;
	it6 = map1.insert(ft::make_pair(-1,-1)).first;
	check(map.size() == map1.size());

	map.erase(it);
	map1.erase(it2);
	check(map.size() == map1.size());
	
	map.erase(it5);
	map1.erase(it6);
	check(map.size() == map1.size());
	
	it4 = map1.find(2);
	map.erase(it3);
//	std::cout << (*it4).first;
	map1.erase(it4);
	check(map.size() == map1.size());
	
	map.insert(std::make_pair(1,1));
	map1.insert(ft::make_pair(1,1));
	check(map.size() == map1.size());
}


void	map_erase_3()
{
	std::map<int, int> map = create_std_map();
	ft::map<int, int> map1 = create_map();
	std::map<int, int>::iterator it;
	ft::map<int, int>::iterator it1;

//	std::cout << "erase " << it->first << std::endl;
	map.erase(5);
	map1.erase(5);
	check(map.size() == map1.size());

	
	it = map.find(5);
	it1 = map1.find(5);
	check(it == map.end());
	check(it1 == map1.end());

	it = map.find(4);
	it1 = map1.find(4);
	check(it->first == it1->first);
	check((++it)->first == (++it1)->first);

	it = map.find(4);
	it1 = map1.find(4);
	check((--it)->first == (--it1)->first);

//	it = map.find(1);
//	it1 = map1.find(1);
//	std::cout << "erase " << it->first << std::endl;
	map.erase(1);
	map1.erase(1);
	check(map.size() == map1.size());
	it = map.find(1);
	it1 = map1.find(1);
	check(it == map.end());
	check(it1 == map1.end());

	map[3] = 3;	
	map1[3] = 3;	
	check(map.size() == map1.size());
	it = map.find(3);
	it1 = map1.find(3);
	check(it->first == it1->first);
	check((--it)->first == (--it1)->first);
//	std::cout << it->first << "," << it1->first << std::endl;
	check((++it)->first == (++it1)->first);
//	std::cout << it->first << "," << it1->first << std::endl;

//	it = map.find(10);
//	it1 = map1.find(10);
	map.erase(10);
	map1.erase(10);
	check(map.size() == map1.size());
//	std::cout << it->first << "," << it1->first << std::endl;
	it = map.find(9);
	it1 = map1.find(9);
//	check(it != map.end());
//	check(it1 1= map1.end());
	check(it->first == it1->first);
	check((--it)->first == (--it1)->first);
//	std::cout << it->first << "," << it1->first << std::endl;
	check((++it)->first == (++it1)->first);
//	std::cout << it->first << "," << it1->first << std::endl;
	it = map.find(10);
	it1 = map1.find(10);
	check(it == map.end());
	check(it1 == map1.end());

}

void	map_erase_4()
{
	std::map<int, int>				map;
	ft::map<int, int>				map1;
//	std::map<int, int>::iterator	it;
//	ft::map<int, int>::iterator		it2;
//	std::map<int, int>::iterator	it3;
//	ft::map<int, int>::iterator		it4;
//	std::map<int, int>::iterator	it5;
//	ft::map<int, int>::iterator		it6;

	map.insert(std::make_pair(1,1)).first;
	map1.insert(ft::make_pair(1,1)).first;
	map.insert(std::make_pair(2,2)).first;
	map1.insert(ft::make_pair(2,2)).first;
	map.insert(std::make_pair(-1,-1)).first;
	map1.insert(ft::make_pair(-1,-1)).first;
	check(map.size() == map1.size());

	map.erase(1);
	map1.erase(1);
	check(map.size() == map1.size());
	
	map.erase(-1);
	map1.erase(-1);
	check(map.size() == map1.size());
	
//	it4 = map1.find(2);
	map.erase(2);
//	std::cout << (*it4).first;
	map1.erase(2);
	check(map.size() == map1.size());
	
	map.insert(std::make_pair(1,1));
	map1.insert(ft::make_pair(1,1));
	check(map.size() == map1.size());
}

void map_tests()
{
	test_case("map_constructors", &map_constructor);
	test_case("map_constructors2", &map_constructor2);
	test_case("map_copy_constructor", &map_copy_constructor);
	test_case("operator[]", &operator_access);
	test_case("map at", &map_at);
	test_case("map at const", &map_const_at);
	test_case("map insert", &map_insert);
	test_case("map insert iterator", &map_insert_iterator);
	test_case("map insert iterator2", &map_insert_iterator2);
	test_case("map parent navigation", &map_parent_navigation);
	test_case("map insert hint1", &map_insert_hint1);
	test_case("map insert hint2", &map_insert_hint2);
	test_case("map insert iterator3", &map_insert_iterator3);
	test_case("map operator ++", &map_operator_pp);
	test_case("map operator --", &map_operator_ll);
	test_case("map iterator const", &map_iterator_const);
	test_case("map iterator const2", &map_iterator_const_2);
	test_case("map maxsize", &map_maxsize);
	test_case("map find", &map_find);
	test_case("map lower bound", &map_lower_bound);
	test_case("map upper bound", &map_upper_bound);
	test_case("map equal range", &map_equal_range);
	test_case("map erase", &map_erase);
	test_case("map erase2", &map_erase_2);
	test_case("map erase3", &map_erase_3);
	test_case("map erase4", &map_erase_4);
//	test_case("map insert playground", &map_insert_playground);
}

