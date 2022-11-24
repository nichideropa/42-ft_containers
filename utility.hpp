#ifndef UTILITY_HPP
# define UTILITY_HPP

#include <utility>

// everything in a struct is public
template <typename T1, typename T2>
struct pair
{
	// why is there no need for the typename specifier?
	/* types */
	typedef T1			first_type;
	typedef T2			second_type;

	/* attributes */
	T1			first;
	T2			second;

	/* methods */
	pair();
	template <typename U, typename V>
	pair(const pair<U,V> &p);
	pair(const first_type &x, const second_type &y);

	// only in cppreference mentioned
	pair(const pair &p);
}

#endif