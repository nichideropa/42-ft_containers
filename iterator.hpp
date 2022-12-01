#ifndef ITERATOR_HPP
# define ITERATOR_HPP

#include <iterator>
#include <cstddef>	// ptrdiff_t

namespace ft {

	/* iterator tags */
	struct input_iterator_tag {};
	struct output_iterator_tag{};
	struct foward_iterator_tag : public input_iterator_tag {};
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};


	/* explanation and maybe implementation of the iterator_traits concept */
	template <typename Iter>
	struct iterator_traits;

	/* partial specializations */
	template <typename T>
	struct iterator_traits<T*>;

	template <typename T>
	struct iterator_traits<const T*>;


	// template<
	// 	typename Category,
	// 	typename T,
	// 	typename Distance = std::ptrdiff_t,
	// 	typename Pointer = T*,
	// 	typename Reference = T&
	// >
	// struct iterator;

	template <typename T>
	struct iterator
	{
		typedef T			value_type;

		private:
			value_type		*value;
	}

} // namespace ft

#endif // ITERATOR_HPP