#ifndef STACK_HPP
# define STACK_HPP

// pragma once

#include <deque>
// std deque must be replaced by our own vector
// #include "vector.hpp"

namespace ft {

	template <typename T, typename _Container=std::deque<T> >
	class stack
	{
		public:
			/* typename specifier because container_type::value_type could be
				expanded to a value, whereas T is known to be a type */
			typedef _Container									container_type;
			typedef typename container_type::value_type			value_type;
			typedef typename container_type::size_type			size_type;

		protected:
			_Container		c;

		public:

			/* explicit keyword disallows implicit conversion */
			explicit stack(const _Container &_c = _Container()) : c(_c)
			{}

			/* don't mention the internal implementation of the functions
			you will use your own implemented container as the default underlying of stack */
			/* sort it to make its appearance look good, ugly now */
			bool empty() const
			{ return c.empty(); }

			size_type size() const
			{ return c.size(); }

			value_type &top()
			{ return c.back(); }

			const value_type &top() const
			{ return c.back(); }

			void push(const value_type &value)
			{ c.push_back(value); }

			void pop()
			{ c.pop_back(); }

			template <typename T1, typename _Con1>
			friend bool
			operator==(const stack<T1, _Con1> &, const stack<T1, _Con1> &);

			template <typename T1, typename _Con1>
			friend bool
			operator<(const stack<T1, _Con1> &, const stack<T1, _Con1> &);
	};

	/* comparison functions originally are inlined */
	template <typename T, typename _Con>
	bool	operator==(const stack<T, _Con> &lhs, const stack<T, _Con> &rhs)
	{
		return (lhs.c == rhs.c);
	}

	/* usually lexicographical_compare() is used for determination */
	template <typename T, typename _Con>
	bool	operator<(const stack<T, _Con> &lhs, const stack<T, _Con> &rhs)
	{
		return (lhs.c < rhs.c);
	}

	/* comparison operators can be implemented using other
		comparison operators to minimize comparative redundancy */
	template <typename T, typename _Con>
	bool	operator!=(const stack<T, _Con> &lhs, const stack<T, _Con> &rhs)
	{
		return !(lhs == rhs)
	}

	template <typename T, typename _Con>
	bool	operator>(const stack<T, _Con> &lhs, const stack<T, _Con> &rhs)
	{
		return (rhs < lhs);
	}

	template <typename T, typename _Con>
	bool	operator<=(const stack<T, _Con> &lhs, const stack<T, _Con> &rhs)
	{
		return !(rhs < lhs);
	}

	template <typename T, typename _Con>
	bool	operator>=(const stack<T, _Con> &lhs, const stack<T, _Con> &rhs)
	{
		return !(lhs < rhs);
	}

} // namespace ft


/* some additional not required for C++98 
	typedef typename container_type::reference			reference
	typedef typename container_type::const_reference	const_reference
	
	methods with new typedef:
	reference top() { return c.back(); }
	const_reference top() const { return c.back(); }
*/

#endif // STACK_HPP
