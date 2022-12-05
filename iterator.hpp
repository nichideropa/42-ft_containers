#ifndef ITERATOR_HPP
# define ITERATOR_HPP

#include <iterator>
#include <cstddef>	// ptrdiff_t

/* "Abstractions for uniform iterating through various underlying types." */

namespace ft {

	/* iterator tags (empty types for distinguishing iterators)
		distincion is made by what they are, not what they contain.
		inheritance implies the support for a superset of operations
		of base class */
	struct input_iterator_tag { };
	struct output_iterator_tag { };
	struct foward_iterator_tag : public input_iterator_tag { };
	struct bidirectional_iterator_tag : public forward_iterator_tag { };
	struct random_access_iterator_tag : public bidirectional_iterator_tag { };

	// typedef std::input_iterator_tag					input_iterator_tag;
	// typedef std::output_iterator_tag				output_iterator_tag;
	// typedef std::forward_iterator_tag				forward_iterator_tag;
	// typedef std::bidirectional_iterator_tag			bidirectional_iterator_tag;
	// typedef std::random_access_iterator_tag			random_access_iterator_tag;


	template <typename Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::value_type 			value_type;
		typedef typename Iterator::pointer 				pointer;
		typedef typename Iterator::reference 			reference;
		typedef typename Iterator::iterator_category 	iterator_category;
	};

	/* pointer specialization to allow pointers to be used with
		iterator based algorithms */
	template <typename T>
	struct iterator_traits<T*>
	{
		typedef std::ptrdiff_t					difference_type;
		typedef T 								value_type;
		typedef T* 								pointer;
		typedef T& 								reference;
		typedef random_access_iterator_tag		iterator_category;
	};

	template <typename T>
	struct iterator_traits<const T*>
	{
		typedef std::ptrdiff_t					difference_type;
		typedef T								value_type;
		typedef const T*						pointer;
		typedef const T&						reference;
		typedef random_access_iterator_tag		iterator_category;
	};


	template<typename Category, typename T, typename Distance = std::ptrdiff_t,
								typename Pointer = T*, typename Reference = T&>
	struct iterator
	{
		typedef Category		iterator_category;
		typedef T				value_type;
		typedef Distance		difference_type;
		typedef Pointer			pointer;
		typedef Reference		reference;

		/* the developers intention was to separate data (container)
			from operation (algorithm). As one needs information of the other
			iterators bridge them. the reason why the default iterator class
			doesn't hold any member. */
	};


	/* reverse_iterator is an iterator adaptor reversing an iterators direction
		(needs at least a bidirectional iterator) */
	template <typename Iterator>
	class reverse_iterator : iterator<iterator_traits<Iterator>::iter_category,
										iterator_traits<Iterator>::value_type,
										iterator_traits<Iterator>::distance_type,
										iterator_traits<Iterator>::pointer,
										iterator_traits<Iterator>::reference>
	{
		public:
			typedef Iterator										iterator_type;
			typedef iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef iterator_traits<Iterator>::value_type			value_type;
			typedef iterator_traits<Iterator>::difference_type		difference_type;
			typedef iterator_traits<Iterator>::pointer				pointer;
			typedef iterator_traits<Iterator>::reference			reference;

		protected:
			iterator_type		current;

		public:

			reverse_iterator() : current()
			{}

			explicit reverse_iterator(iterator_type _iter) : current(_iter)
			{}

			/* copy constructor for reverse iterator of other type if the
				underlying iterator can be converted to current */
			template <typename Iter>
			reverse_iterator(const reverse_iterator<Iter> &_other)
			: current(_other.base())
			{}

			template <typename Iter>
			reverse_iterator	&operator=(const reverse_iterator<Iter> &_other)
			{
				current = _other.base();
				return (*this);
			}

			/* one reference says base iter returned as copy
				-> return () */
			iterator_type
			base() const
			{ return current; }

			/* returns reference or pointer to element previous to current */
			reference	operator*() const
			{
				iterator_type	tmp = current;
				return (*--tmp);
			}

			/* add parenthesis if necessary */
			pointer		operator->() const
			{
				return (&operator*());
			}

			reference	operator[](difference_type n) const;
			{
				return (*(*this + n));
				// return (*(current - 1 - n));
				// return (base()[-n - 1]);
			}

			reverse_iterator	&operator++()
			{
				--current;
				return (*this);
			}

			/* you can use define pre increment operator on 'this' pointer */
			reverse_iterator	operator++(int)
			{
				reverse_iterator	tmp = *this;
				--current;
				// ++(*this);
				return (tmp);
			}

			reverse_iterator	&operator--()
			{
				++current;
				return (*this);
			}

			/* you can use copy constructor for tmp too */
			reverse_iterator	operator--(int)
			{
				reverse_iterator	tmp(*this);
				++current;
				return (tmp);
			}

			/* require random-access iterator as base iterator */
			reverse_iterator	&operator+(difference_type n) const
			{
				return (reverse_iterator(current - n));
			}

			reverse_iterator	&operator-(difference_type n) const
			{
				return (reverse_iterator(current + n));
			}

			reverse_iterator	&operator+=(difference_type n)
			{
				current -= n;
				return (*this);
			}

			reverse_iterator	&operator-=(difference_type n)
			{
				current += n;
				return (*this);
			}


			/* don't need to befriend comparisons as they use public base function */
	};

	/* compares the underlying base iterators to one another, using inverse
		comparison operators for lexicographical comparison */
	template <typename Iterator>
	bool	operator==(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() == rhs.base());
	}

	/* actually lhs > rhs */
	template <typename Iterator>
	bool	operator<(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
	{
		return (rhs.base() < lhs.base());
	}

	template <typename Iterator>
	bool	operator!=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
	{
		return !(lhs == rhs);
	}

	/* actually lhs < rhs */
	template <typename Iterator>
	bool	operator>(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
	{
		return (rhs < lhs);
	}

	/* actually lhs >= rhs */
	template <typename Iterator>
	bool	operator<=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
	{
		return !(rhs < lhs);
	}

	/* actually lhs <= rhs */
	template <typename Iterator>
	bool	operator>=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
	{
		return !(lhs < rhs);
	}

	/* C++98 initially could only compare reverse iterators with the same
		underlying type. a fix was applied retroactive to allow comparisons
		of different types.
		(implies that only const and non-const iterators coming from the same
		object can be safely compared) */
	template <typename Iterator1, typename Iterator2>
	bool	operator==(const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <typename Iterator1, typename Iterator2>
	bool	operator<(const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs)
	{
		return (rhs.base() < lhs.base());
	}

	template <typename Iterator1, typename Iterator2>
	bool	operator!=(const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs)
	{
		return !(lhs == rhs);
	}

	template <typename Iterator1, typename Iterator2>
	bool	operator>(const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs)
	{
		return (rhs < lhs);
	}

	template <typename Iterator1, typename Iterator2>
	bool	operator<=(const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs)
	{
		return !(rhs < lhs);
	}

	template <typename Iterator1, typename Iterator2>
	bool	operator>=(const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs)
	{
		return !(lhs < rhs);
	}

	template <typename Iterator>
	reverse_iterator<Iterator>
	operator+(typename reverse_iterator<Iterator>::difference_type n,
									const reverse_iterator<Iterator> &rev_it)
	{
		return (reverse_iterator<Iterator>(rev_it.base() - n));
		// return (rev_it + n);
	}

	/* same goes here as for relational operator fix applied retroactively */
	template <typename Iterator>
	typename reverse_iterator<Iterator>::difference_type
	operator-(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
	{
		return (rhs.base() - lhs.base());
	}

	
	template <typename Iterator1, typename Iterator2>
	typename reverse_iterator<Iterator1>::difference_type
	operator-(const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs)
	{
		return (rhs.base() - lhs.base());
	}

	/* somehow the iterators need to have access to the containers
		elements even though they are separated. As iterators are connected
		to the container, the container can reference itself in the iterator */
	/* iterator type of std::vector<T> is implementation defined. It does not 
		need to be a nested class template, it might be simply an alias for a pointer
		to the value type T*. */

} // namespace ft

#endif // ITERATOR_HPP
