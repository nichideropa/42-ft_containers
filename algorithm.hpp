#ifndef ALGORITHM_HPP
# define ALGORITHM_HPP


#include <algorithm>

namespace ft {

	/* non-mutating algorithms: do not modify objects passes to them */
	template <typename InputIter1, typename InputIter2>
	bool	equal(InputIter1 first1, InputIter1 last1, InputIter2 first2)
	{
		while (first1 != last1)
		{
			if (!(*first1 == *first2))
				return (false);
			/* pre increment is without overhead */
			++first1;
			++first2;
		}
		return (true);
	}


	/* binary_pred must accept two arguments of any type and return
		a value  convertible to bool which determines if elements match */
	template <typename InputIter1, typename InputIter2, typename BinaryPredicate>
	bool	equal(InputIter1 first1, InputIter1 last1, InputIter2 first2,
					BinaryPredicate binary_pred)
	{
		/* gnu implementation */
		for (; first1 != last1; ++first1, ++first2)
		{
			if (!binary_pred(*first1, *first2))
				return (false);
		}
		return (true);
	}

	/* compares if range [first1, last1] is lexicographically 
		less than range [first2, last2], mismatch prioritized */
	template <typename InputIter1, typename InputIter2>
	bool	lexicographical_compare(InputIter1 first1, InputIter1 last1,
					InputIter2 first2, InputIter2 last2)
	{
		while (first1 != last1 && first2 != last2)
		{
			if (*first1 < *first2)
				return (true);
			else if (*first2 < first1)
				return (false);
		}
		return (first1 == last1 && first2 != last2);
	}

	/* comp denotes a comparison function taking two arguments
		and returning a value convertible to bool */
	template <typename InputIter1, typename InputIter2, typename Compare>
	bool	lexicographical_compare(InputIter1 first1, InputIter1 last1,
					InputIter2 first2, InputIter2 last2, Compare comp)
	{
		for (; first1 != last1 && first2 != last2, ++first1, ++first2)
		{
			if (comp(*f1, *f2))
				return (true);
			/* negation of comp is not enough, fires when
				elements are equal */
			else if (comp(*f2, *f1))
				return (false);
		}
		return (first1 == last1 && first2 != last2)
	}

	/* ^ throw if element comparisons or function throws */

} // namespace ft

/* different algorithm for lexicographical compare
	bool	lexicographical_compare(InputIter1 first1, InputIter1 last1,
				InputIter2 first2, InputIter2 last2)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || *first2 < *first1)
				return (false);
			else if (*first1 < *first2)
				return (true);
			++first1;
			++first2;
		}
		return (first2 != last2);
	}
*/

#endif // ALGORITHM_HPP