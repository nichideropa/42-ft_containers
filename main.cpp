#include <iostream>
#include <string>
#include <cstddef> // std::size_t

/* all standard containers*/
/* sequence */
// #include <array>		// c++11
#include <vector>
#include <deque>
// #include <forward_list>	// c++11
#include <list>
/* adapters*/
#include <stack>
#include <queue>
/* associative */
#include <map>
#include <set>

// std::pair
#include <utility>


/* own container */
#include "stack.hpp"


# define GREEN	"\033[32m"
# define RESET	"\033[0m"
# define PRINT(_msg)(std::cout << GREEN << _msg << RESET << std::endl)

// overloaded output operators
std::ostream &operator<<(std::ostream &os, std::stack<int> s)
{
	std::stack<int>::size_type	_size = s.size();
	for (std::stack<int>::size_type i = 0; i < _size; ++i)
	{
		os << s.top() << ' ';
		s.pop();
	}
	return (os);
}

std::ostream &operator<<(std::ostream &os, ft::stack<int> f)
{
	ft::stack<int>::size_type	_size = f.size();
	for (ft::stack<int>::size_type i = 0; i < _size; ++i)
	{
		os << f.top() << ' ';
		f.pop();
	}
	return (os);
}



/* mains */

int	main()
{
	PRINT("STD:");
	std::stack<int>		s1;

	s1.push(3);
	s1.push(2);
	s1.push(1);
	std::cout << s1 << std::endl;

	// copy constructor
	std::stack<int>		s2(s1);
	std::cout << s2 << std::endl;

	// assignment operator
	std::stack<int>		s3;
	s3 = s2;

	std::cout << s3 << std::endl;
	std::stack<int>		s4(std::stack<int>::reference cntr);

	PRINT("");
	PRINT("FT:");
	ft::stack<int>		f1;

	f1.push(3);
	f1.push(2);
	f1.push(1);
	std::cout << f1 << std::endl;

	ft::stack<int>		f2(f1);
	std::cout << f2 << std::endl;

	ft::stack<int>		f3;
	f3 = f2;
	std::cout << f3 << std::endl;
	ft::stack<int>		f4(std::deque<int>::reference cntr);

	std::pair<int, int>			p1;
	std::pair<int, int>			p2(-78, 129);
	std::pair<int, int>			p3(p1);
	std::pair<int, int>			p4 = p2;
}
