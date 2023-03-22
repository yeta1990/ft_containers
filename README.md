# ft_containers
### Description
My own implementation of some containers from STL:
- Vector, map, stack and set.
- Includes const and non-const iterators, reverse iterators and a red-black tree.
- Stress tests perform similar to STL.
- Unit tests: clone and type `make && ./tests_containers`

### Usage of the 4 containers:
Include needed header (i.e.: #include "map.hpp") and use it in namespace ft, for instance:

    ft::map<int, int> map;
    ft::map<int, int>::iterator it;

Although implementation may differ (and indeed most times it will), all member functions, member types and non-member functions behave like C++ STL 98. Check [cppreference](https://en.cppreference.com/w/cpp/container) or [cplusplus](https://cplusplus.com/reference/stl/) documentation.

### Usage of red-black tree
This is the red-black tree I've implemented to work behind the map and the set. 
`#include "RBTree.hpp"`

    template <class T, class Alloc, class Comp >
    class RBTree;

The tree stores nodes of `T = ft::pair::<const key_type, value_type>`
#### Main member functions of RBTree:
|Function| Description |
|---------------|--|
| RBTree(); | Constructor |
| pointer insert(const value_type& p); | Insert pair<key, value>, returns iterator pointing to the inserted node |
| void	del(typename value_type::first_type key); | Remove the element with key 'key' |
| iterator find(typename value_type::first_type key); <br /> const_iterator find(typename value_type::first_type key) const; | Find a node with key 'key'. Returns iterator to the found node, otherwise returns iterator to the sentinel |
| void	swap(tree& other); | Swap content of 2 trees |
| void clear(); | Remove all elements from the tree |
| iterator	begin(); <br/> const_iterator	begin() const; | Get an iterator of the node with the lowest key from the tree |
| const_iterator	end() const; <br />iterator	end(); | Get an iterator of the "end" of the tree (the sentinel node) |
| const_iterator	end() const; <br />iterator	end(); | Get an iterator of the "end" of the tree (the sentinel node) |
| const_iterator	end() const; <br />iterator	end(); | Get an iterator of the "end" of the tree (the sentinel node) |

#### Main functions of the RBtree iterator:
|Function| Description |
|---------------|--|
| reference operator*() | Returns a reference to the pair<key, value> stored in the node pointed from the iterator |
| pointer operator->() | Returns a pointer to the pair<key, value> stored in the node pointed from the iterator |
| tree_iterator& operator++ <br /> tree_iterator operator++(int) | Incremental operators |
| tree_iterator& operator++ <br /> tree_iterator operator--(int) | Decrement operators |

### Performance tests:

<summary>
    summary
  </summary>

