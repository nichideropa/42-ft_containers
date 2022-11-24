#ifndef STACK_HPP
# define STACK_HPP

// instead of define possible
// #pragma once

// using std::vector as default container for now
// must be replaced by ft::vector
#include <vector>
// #include "vector.hpp"

namespace ft {

	template <typename T, typename Container=std::deque<T> >
	class stack
	{
		protected:
			Container		c;
		public:
			/* typename specifier to differentiate between value, type and template */
			typedef Container									container_type;
			typedef typename container_type::value_type			value_type;
			typedef typename container_type::size_type			size_type;
			// typedef typename container_type::reference			reference;				// c++11?
			// typedef typename container_type::const_reference	const_reference;		// c++11?


			stack() : c()
			{}

			stack(const stack &other) : c(other.c)
			{}

			~stack()
			{}

			stack	&operator=(const stack &other)
			{
				c = other.c;
				return (*this);
			}

			/* don't mention the internal implementation of the functions
			you will use your own implemented container as the default underlying of stack */
			/* sort it to make its appearance look good, ugly now */
			bool empty()		const	{ return c.empty(); }

			size_type size()	const	{ return c.size(); }

			// reference top()					{ return c.back(); }
			value_type &top()				{ return c.back(); }

			// const_reference top const		{ return c.back(); }
			const value_type &top() const	{ return c.back(); }

			void push(const value_type &value)	{ c.push_back(value); }

			void pop()	{ c.pop_back(); }
	};

}


/*** features of c++11 that might be useful ***/

/* the initial implementation of reference and const reference typedef
typedef typename value_type&			reference;
typedef typename const value_type&		const_reference;
*/

/* specific to stack
typedef typename container_type::reference			reference;
typedef typename container_type::const_reference	const_reference;
*/

#endif // STACK_HPP
