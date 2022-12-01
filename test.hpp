#ifndef TEST_HPP
# define TEST_HPP

#include <iostream>


/* for explanation of SFINAE */
// template <typename T>
// struct hasSerialize
// {
// 	typedef char			yes[1];
// 	typedef yes				no[2];

// 	template <typename U, U v>
// 	struct reallyHas;

// 	template <typename V>
// 	static yes	&test(reallyHas<std::string (V::*)(), &V::serialize>* ) { }
// 	static yes	&test(reallyHas<std::string (V::*)() const, &V::serialize>* ) { }

// 	template <typename>
// 	static no	&test(...) { }

// 	static const bool value = sizeof(test<T>(0) == sizeof(yes));
// };

#endif
