
#include "vector.hpp"
#include <vector>

int	main(void)
{
	//asigning const_iterator to non-const vector -> compiles
	std::vector<int> vv;
	std::vector<int>::const_iterator itit;

	itit = vv.begin();

	// but custom vector doesn't compile yet
	/*ft::vector<int>	v;
	ft::vector<int>::const_iterator it;

	v.push_back(42);
	it = v.begin();
	std::cout << *it << std::endl;
	*/

	ft::vector<int>	const vc;
	ft::vector<int>::const_iterator ci;

	ci = vc.begin();

}
