#ifndef ITERATOR_HPP
# define ITERATOR_HPP

#include <iterator>
#include <cstddef>	// ptrdiff_t

/* iterators are a generalization of pointers, providing a standard
	interface for the access to elements of the stl containers
	where you don't have to worry about the implementation of the container 
	(abstracts away the details, while keeping behavioural limits) */

/* five main types of iterators (hierarchical)
	1. input iterator (istream &is) 
	2. output iterator (ostrema &os)
	3. forward iterator (std::forward_list::iterator or std::unordered_map::iterator)
	4. bidirectional iterator (std::list::iterator)
	5. random access iterator (pointer to C array, std::vector::iterator or std::deque::iterator)

	This categorization is the way algorithms specify which iterator can be used.
	Until C++20 they do this implicitly by using operations supported only by this
	iterator and all in higher rank. From C++20 on using concepts.
*/

/* CPLUSPLUS says: "There is not a single type of bidirectional iterator. Each
	container may define its own specific iterator type able to iterator 
	though it and access its elements" */

/* input iterators are read-only once 
	probably implemented by incrementing when dereferencing a value */

/* quote from gnu implementation: "Abstractions for uniform iterating
	through various underlying types." */

namespace ft {

	/* iterator tags */
	/* empty types for distinguishing iterators.
		Distincion is made by what they are, not what they contain) */
	struct input_iterator_tag { };
	struct output_iterator_tag { };
	/* support superset of input iterator operations */
	struct foward_iterator_tag : public input_iterator_tag { };
	/* suport a superset of forward iterator operations */
	struct bidirectional_iterator_tag : public forward_iterator_tag { };
	/* support a superset of bidirectional iterator operations */
	struct random_access_iterator_tag : public bidirectional_iterator_tag { };

	/* it seems that the std iterator tags need to be used to work properly */
	typedef std::input_iterator_tag					input_iterator_tag;
	typedef std::output_iterator_tag				output_iterator_tag;
	typedef std::forward_iterator_tag				forward_iterator_tag;
	typedef std::bidirectional_iterator_tag			bidirectional_iterator_tag;
	typedef std::random_access_iterator_tag			random_access_iterator_tag;


	/* common interface to work with iterators
		gnu sorts: iterator_category, value_type, difference_type, pointer, reference */
	template <typename Iter>
	struct iterator_traits
	{
		typedef typename Iter::difference_type		difference_type;
		typedef typename Iter::value_type 			value_type;
		typedef typename Iter::pointer 				pointer;
		typedef typename Iter::reference 			reference;
		typedef typename Iter::iterator_category 	iterator_category;
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
		typedef T*				pointer;
		typedef T&				reference;

		/* I would've thought it has a protected member with the values */
		/* An article says that the developers chose a design
			where data and operation are separated. The data being held by
			the container, while the operations are done using algorithms.
			Bridging them both are iterators */
	};

	/* not a struct but a class is necessary */
	/* the iterator you can get from scope resolution
		of the container is only a typedef of the iterator
		implementation */
	/* somehow the iterators need to have access to the containers
		elements even though they are separated. As iterators are connected
		to the container, the container can reference itself in the iterator */
	/* iterator type of std::vector<T> is implementation defined. It does not 
		need to be a nested class template, it might be simply an alias for a pointer
		to the value type T*. */
	template <typename T, typename _Container>
	class input_iterator : public iterator<input_iterator_tag, T>
	{
	};

} // namespace ft

#endif // ITERATOR_HPP