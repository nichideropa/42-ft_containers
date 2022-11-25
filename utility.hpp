#ifndef UTILITY_HPP
# define UTILITY_HPP

#include <utility>

namespace ft {

	// everything in a struct is public
	template <typename T1, typename T2>
	struct pair
	{
		/* types */
		typedef T1			first_type;
		typedef T2			second_type;

		/* attributes */
		T1			first;
		T2			second;

		/* methods */
		// cplusplus
		pair()
			: first(), second()
		{}

		pair(const first_type &_a, const second_type &_b)
			: first(a), second(b)
		{}

		template <typename U, typename V>
		pair(const pair<U,V> &_p) : first(p.first), second(p.second)
		{}

		pair	&operator=(const pair &_p)

		/* copy constructor
			is defaulted (until C++11 it's implicitly declared */
		// pair(const pair &p) : first(p.first), second(p.second)
		// {}
	};

} // namespace ft

/* doesn't throw exceptions unless one of specified options throws
	e.G. constructor of an element (no-throw guarantee)

	construction with move semantics may leave explicit copy constructor
	in invalid state (no guarantees)
*/

#endif