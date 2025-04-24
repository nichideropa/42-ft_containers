#ifndef ALGORITHM_HPP
# define ALGORITHM_HPP


namespace ft {

	/* non-mutating algorithms: do not modify objects passed to them */

	/* comparisons are only done in the range of the first object */
	template <typename InputIter1, typename InputIter2>
	bool	equal(InputIter1 first1, InputIter1 last1, InputIter2 first2)
	{
		while (first1 != last1)
		{
			if (!(*first1 == *first2))
				return (false);
			++first1;
			++first2;
		}
		return (true);
	}

	/* binary_pred must accept two arguments of any type and return
		a value convertible to bool which determines if elements match */
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
			else if (*first2 < *first1)
				return (false);
			++first1;
			++first2;
		}
		return (first1 == last1 && first2 != last2);
	}

	/* comp denotes a comparison function taking two arguments
		and returning a value convertible to bool */
	template <typename InputIter1, typename InputIter2, typename Compare>
	bool	lexicographical_compare(InputIter1 first1, InputIter1 last1,
					InputIter2 first2, InputIter2 last2, Compare comp)
	{
		for (; first1 != last1 && first2 != last2; ++first1, ++first2)
		{
			if (comp(*first1, *first2))
				return (true);
			/* negation of comp is not enough, fires when
				elements are equal */
			else if (comp(*first2, *first1))
				return (false);
		}
		return (first1 == last1 && first2 != last2);
	}

	/* ^ throw if element comparisons or function throws */




	/* Helper */

	template <typename T>
	void swap(T& a, T& b)
	{
		T tmp = a;
		a = b;
		b = tmp;
	}

	template <typename T>
	const T& min(const T& a, const T& b)
	{
		return a < b ? a : b;
	}

	template <typename T>
	const T& max(const T& a, const T& b)
	{
		return a > b ? a : b;
	}

	template <typename ForwardIterator, typename T>
	void fill(ForwardIterator first, ForwardIterator last, const T& val)
	{
		while (first != last)
		{
			*first = val;
			++first;
		}
	}

	template <typename OutputIterator, typename Size, typename T>
	void fill_n(OutputIterator first, Size n, const T& val)
	{
		while (n > 0)
		{
			*first = val;
			++first;
			--n;
		}
	}

	template <typename InputIterator, typename OutputIterator>
	OutputIterator copy(InputIterator first, InputIterator last,
						OutputIterator d_first)
	{
		while (first != last)
		{
			*d_first = *first;
			++first;
			++d_first;
		}

		return d_first;
	}

	template <typename BidirIterator1, typename BidirIterator2>
	BidirIterator2 copy_backward(BidirIterator1 first, BidirIterator1 last,
								BidirIterator2 d_last)
	{
		while (last != first)
		{
			--last;
			--d_last;
			*d_last = *last;
		}

		return d_last;
	}

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
	-> returns lexicographically not less results faster
*/

#endif // ALGORITHM_HPP