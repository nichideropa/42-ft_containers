#include <iostream>
#include <algorithm>
#include <string>
// #include <type_traits>
#include <vector>
#include <list>

#include "test.hpp"

# define GREEN	"\033[32m"
# define RESET	"\033[0m"
# define PRINT(_msg)(std::cout << GREEN << _msg << RESET << std::endl)

/* writing a main for every concept/object implemented
	visualizing the way they work (implementation/principles) 
	e.G. that lexicographical_compare prioritized mismatch
	before length */

// void	printer(int v)
// {
// 	std::cout << "Normal function: " << v << std::endl;
// }

int	main()
{
	/* void causes compile time error, because no void reference */
	// std::vector<int>		v(10);

	// std::vector<int>::iterator i = v.begin();
	// for (; i != v.end(); i++)
	// 	*i = 1;
	
	// if (i == v.end())
	// 	std::cout << "true" << std::endl;
	// std::cout << *i << std::endl;
	// i++;
	// *i = 2;
	// std::cout << *i << std::endl;


	/* test for how the reverse iterator works */

	std::vector<int>			v;

	for (size_t i = 0; i < 10; i++)
		v.push_back(i + 1);

	std::vector<int>::reverse_iterator			r = v.rbegin();
	std::vector<int>::reverse_iterator			s = v.rbegin();
	std::vector<int>::const_reverse_iterator	t = v.rbegin();


	if (r == s)
		std::cout << "r == s" << std::endl;
	if (r == t)
		std::cout << "r == t" << std::endl;
	if (s == t)
		std::cout << "s == t" << std::endl;

	return (0);
}

/*
Non-type parameter is a parameter with predefined type which
	is substituted for a constexpr value passed as argument.
	Following types can be used for non-type parameters:
		-> integral type
		-> enumeration type
		-> pointer or reference to class object, function
			or class member function
		-> std::nullptr_t
		(from C++20 on even floating point)

volatile is a hint to the implementation to avoid
	aggressive optimization involving the object because
	the value of the object might be changed by means
	undetecable by an implementation (memory mapped I/O)
*/

/* "Think of a trait as a small object whose main purpose is
	to carry information used by another object or algorithm 
	to determine 'policy' or 'implementation details'." 
	- Bjarne Stroustrup
	
	"Function overloading in C++ is based on different types, which
	prevent compile-time integral constants taking part into function
	overload resolution.

	enable-if ididom:
		allow function overload based on arbitrary
		properties of type

	you need to make the member templates' enable_if depend
	on a parameter of the member template itself
	deduction dependent types?
*/

/* in overload resolution the compiler tries to pick
	the most specific overload. Usually a normal function 
	has precedence over a templated function (remember
	that templated functions can be more precise sometimes) */

/* traits are useful with curiously recurring template pattern */