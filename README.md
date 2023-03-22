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

<img width="608" alt="rbtree" src="https://user-images.githubusercontent.com/65416560/226849840-d341a511-a3c7-4f11-b636-b3e7cc9d124a.png">
 
*Image from Introduction to Algorithms, 3rd Edition(The MIT Press)*
 
- This is the red-black tree I've implemented to work behind the map and the set. 
`#include "RBTree.hpp"`

    >template <class T, class Alloc, class Comp > <br/>
    >class RBTree;

- The tree stores nodes of `T = ft::pair::<const key_type, value_type>`.
- T.nil is the "sentinel" node, which points to the minimum (left) and maximum (right) and to itself (parent).

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
Stress tests results from github.com/Mikastiv/ft_containers-terminator/
Most of them allocate half of RAM from the computer.

[video (1).webm](https://user-images.githubusercontent.com/65416560/226856166-20ef0854-a872-40b7-ba7c-f089fb097eb8.webm)

