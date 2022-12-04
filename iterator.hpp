#ifndef ITERATOR_HPP
# define ITERATOR_HPP

#include <iterator>
#include <cstddef>	// ptrdiff_t

/* "Abstractions for uniform iterating through various underlying types." */

namespace ft {

	/* iterator tags */
	/* empty types for distinguishing iterators.
		distincion is made by what they are, not what they contain */
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


	/* reverse_iterator is an iterator adaptor, that reverses the direction
		of an iterator. it needs at least a bidirectional iterator because
		it has the necessary operations to make this work */
	/* a copy of the initial (base) iterator is kept internally as a protected
		member to reflect the options */
	/* to me it seems that the base iterator is used with the operations
		just reversed (incrementing -> decrementing base iterator) */
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
			/* think about naming the parameters in a good way*/
			reverse_iterator() : current()
			{}

			explicit reverse_iterator(iterator_type _it) : current(_it)
			{}

			template <typename Iter>
			reverse_iterator(const reverse_iterator<Iter> &rev_it)
			

	};

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
