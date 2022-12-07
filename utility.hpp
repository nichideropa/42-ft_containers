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
		pair()
			: first(), second()
		{}

		pair(const first_type &_a, const second_type &_b)
		: first(_a), second(_b)
		{}

		template <typename U, typename V>
		pair(const pair<U,V> &_p) : first(_p.first), second(_p.second)
		{}

		/* ill formed if either attributes const qualified , reference
			with inaccessible copy assignment operator */
		pair	&operator=(const pair &_p)
		{
			/* gnu implementation doesn't check */
			if (this != &_p)
			{
				first = _p.first;
				second = _p.second;
			}
			return (*this);
		}

		/* copy constructor
			is defaulted (until C++11 it's implicitly declared)a */
		// pair(const pair &p) : first(p.first), second(p.second)
		// {}
	};

	/* originally inlined */
	/* no need for friend because attributes of a struct are public */
	template <typename T1, typename T2>
	bool	operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return (lhs.first == rhs.first && lhs.second == rhs.second);
	}

	/* only if first of lhs and rhs are equal compare second */
	template <typename T1, typename T2>
	bool	operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		/* follows the order and conditions mentioned by the reference*/
		return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second));
	}

	template <typename T1, typename T2>
	bool	operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return !(lhs == rhs);
	}

	template <typename T1, typename T2>
	bool	operator>(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return (rhs < lhs);
	}

	template <typename T1, typename T2>
	bool	operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return !(rhs < lhs);
	}

	template <typename T1, typename T2>
	bool	operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return !(lhs < rhs);
	}

	/* originally inlined */
	template <typename T1, typename T2>
	pair<T1, T2> make_pair(T1 _f, T2 _s)
	{
		return (pair<T1, T2>(_f, _s));
	}

} // namespace ft

/* 
	exceptions:
	doesn't throw exceptions unless one of specified options throws
	e.G. constructor of an element (no-throw guarantee)
	construction with move semantics may leave explicit copy constructor
	in invalid state (no guarantees)
	otherwise strong guarantee.

	copy assignment operator guarantees that both objects end up in
	a valid state in case of an exception (basic guarantee)


	from C++11 the copy assignment operator is defined as deleted if
	std::is_copy_assignable<T>::value of either type returns false
*/

#endif // UTILITY_HPP