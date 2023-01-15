https://stackoverflow.com/questions/4335962/how-to-check-if-a-template-parameter-is-an-iterator-type-or-not
template <class T, class = void>
struct is_iterator : std::false_type { };

template <class T>
struct is_iterator<T, typename std::iterator_traits<T>::iterator_category > : std::true_type { };

