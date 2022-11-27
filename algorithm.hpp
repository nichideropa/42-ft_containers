#ifndef ALGORITHM_HPP
# define ALGORITHM_HPP


#include <algorithm>

namespace ft {

	template <typename InputIt1, typename InputIt2>
	bool	equal(InputIt1 first1, InputIt1 last1, InputIt2 first2)
	{
		while (first1 != last1)
		{
			/* using because reference mentiones operator==
				as the main way of comparison */
			if (!(*first1 == *first2))
				return (false);
			/* pre increment is without overhead */
			++first1;
			++first2;
		}
		return (true);
	}

	/* BinaryPredicate should be a function for comparison 
		change name of BinaryPredicate paramter to reflect more on its purpose */
	template <typename InputIt1, typename InputIt2, typename BinaryPredicate>
	bool	equal(InputIt1 first1, InputIt1 last1, InputIt2 first2,
					BinaryPredicate _binary_pred)
	{
		while (first1 != last1)
		{
			if (!_binary_pred(*first1, *first2))
				return (false);
			++first1;
			++first2;
		}
		return (true);
	}

	template <typename InputIt1, typename InputIt2>
	bool	lexicographical_compare(InputIt1 first1, InputIt1 last1,
					InputIt2 first2, InputIt2 last2)
	{

	}

	/* change name of last parameter to make it clearer it denotes
		a comparison function */
	template <typename InputIt1, typename InputIt2, typename Compare>
	bool	lexicographical_compare(InputIt1 first1, InputIt1 last1,
					InputIt2 first2, InputIt2 last2, Compare comp)
	{

	}

} // namespace ft


#endif // ALGORITHM_HPP