#ifndef ITERATOR_HPP
# define ITERATOR_HPP

#include <iterator>
#include <cstddef>	// ptrdiff_t
#include "type_traits.hpp"

/* "Abstractions for uniform iterating through various underlying types." */

namespace ft {

	/* iterator tags (empty types for distinguishing iterators)
		distincion is made by what they are, not what they contain.
		inheritance implies the support for a superset of operations
		of base class */
	// struct input_iterator_tag { };
	// struct output_iterator_tag { };
	// struct forward_iterator_tag : public input_iterator_tag { };
	// struct bidirectional_iterator_tag : public forward_iterator_tag { };
	// struct random_access_iterator_tag : public bidirectional_iterator_tag { };


	
	typedef std::input_iterator_tag					input_iterator_tag;
	typedef std::output_iterator_tag				output_iterator_tag;
	typedef std::forward_iterator_tag				forward_iterator_tag;
	typedef std::bidirectional_iterator_tag			bidirectional_iterator_tag;
	typedef std::random_access_iterator_tag			random_access_iterator_tag;


	/* allows for a uniform way of getting information about iterators */
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


	template<typename Category, typename T, typename Distance = ptrdiff_t,
								typename Pointer = T*, typename Reference = T&>
	struct iterator
	{
		typedef Category		iterator_category;
		typedef T				value_type;
		typedef Distance		difference_type;
		typedef Pointer			pointer;
		typedef Reference		reference;

		/* the developers intention was to separate data (container)
			from operation (algorithm). As one needs information of the other,
			iterators bridge them. the reason why the default iterator class
			doesn't hold any member. */
	};


	/* this function is mentioned as "syntactic sugar for internal use"
		and is used to determine the category an iterator belongs too
		(easier to determine the type and optimise algorithms) */
	template <typename Iterator>
	inline
	typename iterator_traits<Iterator>::iterator_category
	iterator_category(const Iterator &)
	{
		return typename iterator_traits<Iterator>::iterator_category();
	}


	/* reverse_iterator is an iterator adaptor reversing an iterators direction
		(needs at least a bidirectional iterator) */
	template <typename Iterator>
	class reverse_iterator : public iterator<typename iterator_traits<Iterator>::iterator_category,
	 											typename iterator_traits<Iterator>::value_type,
	 											typename iterator_traits<Iterator>::distance_type,
	 											typename iterator_traits<Iterator>::pointer,
	 											typename iterator_traits<Iterator>::reference>
	{
		public:
			typedef Iterator												iterator_type;
			typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename iterator_traits<Iterator>::value_type			value_type;
			typedef typename iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename iterator_traits<Iterator>::pointer				pointer;
			typedef typename iterator_traits<Iterator>::reference			reference;

		protected:
			iterator_type		current_;

			// typedef iterator_traits<Iterator>		traits_type;

		public:

			reverse_iterator() : current_()
			{}

			explicit reverse_iterator(iterator_type _iter) : current_(_iter)
			{}

			/* not belonging to C++98 but the copy constructor would be */
			// reverse_iterator(const reverse_iterator &_r_iter)
			// 	: current_(_r_iter.current)
			// {}

			/* copy constructor for reverse iterator of other type if the
				underlying iterator can be converted to current */
			template <typename Iter>
			reverse_iterator(const reverse_iterator<Iter> &_other)
			: current_(_other.base())
			{}

			template <typename Iter>
			reverse_iterator	&operator=(const reverse_iterator<Iter> &_other)
			{
				current_ = _other.base();
				return (*this);
			}

			iterator_type
			base() const
			{ return current_; }

			/* returns reference or pointer to element previous to current */
			reference	operator*() const
			{
				iterator_type	tmp = current_;
				return (*(--tmp));
			}

			pointer		operator->() const
			{
				return (&(operator*()));
			}

			reverse_iterator	&operator++()
			{
				--current_;
				return (*this);
			}

			reverse_iterator	operator++(int)
			{
				reverse_iterator	tmp = *this;
				--current_;
				// ++(*this); // call to pre-increment
				return (tmp);
			}

			reverse_iterator	&operator--()
			{
				++current_;
				return (*this);
			}

			reverse_iterator	operator--(int)
			{
				reverse_iterator	tmp(*this);
				++current_;
				// --(*this); // call to pre-drecement
				return (tmp);
			}

			/* require random-access iterator as base iterator */
			reverse_iterator	operator+(difference_type n) const
			{
				return (reverse_iterator(current_ - n));
			}

			reverse_iterator	operator-(difference_type n) const
			{
				return (reverse_iterator(current_ + n));
			}

			reverse_iterator	&operator+=(difference_type n)
			{
				current_ -= n;
				return (*this);
			}

			reverse_iterator	&operator-=(difference_type n)
			{
				current_ += n;
				return (*this);
			}

			reference	operator[](difference_type n) const
			{
				return (*(*this + n));
				// return (base()[-n - 1]);
			}

			/* no friends because relational operators can access base function */

			/* some additional functions I saw in the implementation
				(function to return pointer to value) */
			// template <typename T>
			// static T* _to_pointer(T *ptr)
			// {
			// 	return (ptr);
			// }

			// /* if operator-> overloaded, it's used instead */
			// template <typename T>
			// static pointer _to_pointer(T val)
			// {
			// 	return (val.operator->());
			// }
	};

	/* compares the underlying base iterators to one another, using inverse
		comparison operators for lexicographical comparison */
	/* inlined */
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

	/* C++98 initially could only compare reverse iterators with the same underlying type.
		a fix was applied retroactive to allow comparisons of different types. (implies that
		only const and non-const iterators coming from the same object can be safely compared) */
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


	/* wrapper for pointer, to serve as iterator for vector (random-access)
		needs to at least inherit from our base iterator (to make it work
		with the std algorithms, inherit from std base iterator)*/
	/* explain why inherits from std::iterator */
	template <typename Iterator, typename Container>
	class	normal_iterator //:	public iterator<typename iterator_traits<Iterator>::iterator_category,
											// typename iterator_traits<Iterator>::value_type,
											// typename iterator_traits<Iterator>::difference_type,
											// typename iterator_traits<Iterator>::pointer,
											// typename iterator_traits<Iterator>::reference>

								// public std::iterator<typename std::iterator_traits<Iterator>::iterator_category,
								// 				 typename std::iterator_traits<Iterator>::value_type,
								// 				 typename std::iterator_traits<Iterator>::difference_type,
								// 				 typename std::iterator_traits<Iterator>::pointer,
								// 				 typename std::iterator_traits<Iterator>::reference>
	{
		public:
			typedef Iterator														iterator_type;
			typedef typename iterator_traits<iterator_type>::iterator_category		iterator_category;
			typedef typename iterator_traits<iterator_type>::value_type				value_type;
			typedef typename iterator_traits<iterator_type>::difference_type		difference_type;
			typedef typename iterator_traits<iterator_type>::pointer				pointer;
			typedef typename iterator_traits<iterator_type>::reference				reference;

		protected:
			iterator_type		current_;

			// typedef iterator_traits<Iterator>		traits_type;

		public:
			normal_iterator() : current_()
			{}

			/* internally we are executing the copy constructor of the
				underlying object. copy constructors take const parameter */
			explicit normal_iterator(const iterator_type _iter) : current_(_iter)
			{}

			/* allow conversion of iterator to const iterator */
			/* does this already work for implicit conversion */
			template <typename Iter>
			normal_iterator(const normal_iterator<
								Iter, typename ft::enable_if<
								ft::are_same<Iter, typename Container::pointer>::value,
								Container>::type>& it)
			: current_(it.base())
			{}

			// template <typename Iter>
			// normal_iterator	&operator=(const normal_iterator<Iter> &_other)
			// {
			// 	current_ = _other.base();
			// 	return (*this);
			// }

			reference	operator*() const
			{
				return (*current_);
			}

			pointer		operator->() const
			{
				return (current_);
			}

			normal_iterator	&operator++()
			{
				++current_;
				return (*this);
			}

			normal_iterator	operator++(int)
			{
				normal_iterator	tmp = *this;
				++current_;
				return (tmp);
				// return (normal_iterator(current_++));
			}

			/* requirements for bidirectional iterator */

			normal_iterator	&operator--()
			{
				--current_;
				return (*this);
			}

			normal_iterator	operator--(int)
			{
				normal_iterator	tmp = *this;
				--current_;
				return (tmp);
				// return (normal_iterator(current_--));
			}

			/* requirements for random access iterator */

			normal_iterator	&operator+=(difference_type n)
			{
				current_ += n;
				return (*this);
			}

			normal_iterator	&operator-=(difference_type n)
			{
				current_ -= n;
				return (*this);
			}

			normal_iterator	operator+(difference_type n) const
			{
				return (normal_iterator(current_ + n));
			}

			normal_iterator	operator-(difference_type n) const
			{
				return (normal_iterator(current_ - n));
			}

			reference	operator[](difference_type n) const
			{
				return (current_[n]);
			}

			iterator_type base() const
			{
				return (current_);
			}
			
	};

	/* maybe name the template parameters different to make clear to the reader
		that it was meant to work with a pointer (for vector)
		it can equally work with a wrapper that supports same operations */

	/* requirements for forward iterator */
	/* inlined */
	template <typename Iterator, typename Container>
	bool	operator==(const normal_iterator<Iterator, Container> &lhs, 
						const normal_iterator<Iterator, Container> &rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <typename Iterator1, typename Iterator2, typename Container>
	bool	operator==(const normal_iterator<Iterator1, Container> &lhs,
						const normal_iterator<Iterator2, Container> &rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <typename Iterator, typename Container>
	bool	operator!=(const normal_iterator<Iterator, Container> &lhs,
						const normal_iterator<Iterator, Container> &rhs)
	{
		return !(lhs == rhs);
	}

	template <typename Iterator1, typename Iterator2, typename Container>
	bool	operator!=(const normal_iterator<Iterator1, Container> &lhs,
						const normal_iterator<Iterator2, Container> &rhs)
	{
		return !(lhs == rhs);
	}

	/* requirements for random access iterator */

	template <typename Iterator, typename Container>
	bool	operator<(const normal_iterator<Iterator, Container> &lhs,
						const normal_iterator<Iterator, Container> &rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <typename Iterator1, typename Iterator2, typename Container>
	bool	operator<(const normal_iterator<Iterator1, Container> &lhs,
						const normal_iterator<Iterator2, Container> &rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <typename Iterator, typename Container>
	bool	operator>(const normal_iterator<Iterator, Container> &lhs,
						const normal_iterator<Iterator, Container> &rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template <typename Iterator1, typename Iterator2, typename Container>
	bool	operator>(const normal_iterator<Iterator1, Container> &lhs,
						const normal_iterator<Iterator2, Container> &rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template <typename Iterator, typename Container>
	bool	operator<=(const normal_iterator<Iterator, Container> &lhs,
						const normal_iterator<Iterator, Container> &rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template <typename Iterator1, typename Iterator2, typename Container>
	bool	operator<=(const normal_iterator<Iterator1, Container> &lhs,
						const normal_iterator<Iterator2, Container> &rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template <typename Iterator, typename Container>
	bool	operator>=(const normal_iterator<Iterator, Container> &lhs,
						const normal_iterator<Iterator, Container> &rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template <typename Iterator1, typename Iterator2, typename Container>
	bool	operator>=(const normal_iterator<Iterator1, Container> &lhs,
						const normal_iterator<Iterator2, Container> &rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	/* non member addition and substraction */
	template <typename Iterator, typename Container>
	normal_iterator<Iterator, Container>
	operator+(typename normal_iterator<Iterator, Container>::difference_type n,
								const normal_iterator<Iterator, Container> &_it)
	{
		return (normal_iterator<Iterator, Container>(_it.base() + n));
		
		// the code for a non-const parameter _it
		// _it += n;
		// return (_it);
	}

	template <typename Iterator, typename Container>
	typename normal_iterator<Iterator, Container>::difference_type
	operator-(const normal_iterator<Iterator, Container> &lhs,
				const normal_iterator<Iterator, Container> &rhs)
	{
		return (lhs.base() - rhs.base());
	}

	template <typename Iterator1, typename Iterator2, typename Container>
	typename normal_iterator<Iterator1, Container>::difference_type
	operator-(const normal_iterator<Iterator1, Container> &lhs,
				const normal_iterator<Iterator2, Container> &rhs)
	{
		return (lhs.base() - rhs.base());
	}



	/* distance functions */

	template <typename Iter>
	typename ft::iterator_traits<Iter>::difference_type
	distance(Iter first, Iter last)
	{
		return (distance(first, last, iterator_category(first)));
	}

	template <typename RandomAccessIterator>
	typename ft::iterator_traits<RandomAccessIterator>::difference_type
	distance(RandomAccessIterator first, RandomAccessIterator last, random_access_iterator_tag)
	{
		return (last - first);
	}

	template <typename InputIterator>
	typename ft::iterator_traits<InputIterator>::difference_type
	distance(InputIterator first, InputIterator last, input_iterator_tag)
	{
		typename iterator_traits<InputIterator>::difference_type	dis(0);

		for (; first != last; ++first)
			++dis;
		return (dis);
	}

} // namespace ft


/* iterator requirements for each type, supporting
	the previous operations by default

	minimum:
		. copy constructible
		. copy assignable
		. destructibe
		. dereferenceable (*it)
		. pre-incrementable (++it)
		
	input/output iterator
		. equality and inequality (it1 [!:=]= it2)
		. post-incrementable (it++)
		
	forward iterator
		. default constructible
		. immutable (const iterator)

	bidirectional iterator
		. pre-decrementable (--it)
		. post-decrementable (it--)

	random access iterator
		. compound addition (+=)
		. compound substraction (-=)
		. addition (+)
		. substraction (-)
		. less and greater (< & >)
		. less-or-equal and greate-or-equal (<= & >=)
	*/

#endif // ITERATOR_HPP
