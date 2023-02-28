#include <iostream>
#include <string>
#include <algorithm>		// std::equal, std::lexicographical_compare
#include <type_traits>		// true_type, false_type, ...

# define BASE		"\033["
# define SEPARATOR	";"
# define END		"m"
# define RESET		"\033[0m"

# define NORMAL		"0"
# define BOLD 		"1"

# define C_BLACK	"30"
# define C_RED		"31"
# define C_GREEN	"32"
# define C_YELLO	"33"
# define C_BLUE		"34"
# define C_MAGENTA	"35"
# define C_CYAN		"36"
# define C_WHITE	"37"

# define BLACK		BASE NORMAL SEPARATOR C_BLACK END
# define RED		BASE NORMAL SEPARATOR C_RED END
# define GREEN		BASE NORMAL SEPARATOR C_GREEN END
# define YELLO		BASE NORMAL SEPARATOR C_YELLOW END
# define BLUE		BASE NORMAL SEPARATOR C_BLUE END
# define MAGENTA	BASE NORMAL SEPARATOR C_MAGENTA END
# define CYAN		BASE NORMAL SEPARATOR C_CYAN END
# define WHITE		BASE NORMAL SEPARATOR C_WHITE END

# define BBLACK		BASE BOLD SEPARATOR C_BLACK END
# define BRED		BASE BOLD SEPARATOR C_RED END
# define BGREEN		BASE BOLD SEPARATOR C_GREEN END
# define BYELLO		BASE BOLD SEPARATOR C_YELLOW END
# define BBLUE		BASE BOLD SEPARATOR C_BLUE END
# define BMAGENTA	BASE BOLD SEPARATOR C_MAGENTA END
# define BCYAN		BASE BOLD SEPARATOR C_CYAN END
# define BWHITE		BASE BOLD SEPARATOR C_WHITE END

# define PRINT_BLACK(_msg)(std::cout << BLACK << _msg << RESET)
# define PRINT_RED(_msg)(std::cout << RED << _msg << RESET)
# define PRINT_GREEN(_msg)(std::cout << GREEN << _msg << RESET)
# define PRINT_YELLOW(_msg)(std::cout << YELLOW << _msg << RESET)
# define PRINT_BLUE(_msg)(std::cout << BLUE << _msg << RESET)
# define PRINT_MAGENTA(_msg)(std::cout << MAGENTA << _msg << RESET)
# define PRINT_CYAN(_msg)(std::cout << CYAN << _msg << RESET)
# define PRINT_WHITE(_msg)(std::cout << WHITE << _msg << RESET)

# define PRINT_BLACK_N(_msg)(std::cout << BLACK << _msg << RESET << std::endl)
# define PRINT_RED_N(_msg)(std::cout << RED << _msg << RESET << std::endl)
# define PRINT_GREEN_N(_msg)(std::cout << GREEN << _msg << RESET << std::endl)
# define PRINT_YELLOW_N(_msg)(std::cout << YELLOW << _msg << RESET << std::endl)
# define PRINT_BLUE_N(_msg)(std::cout << BLUE << _msg << RESET << std::endl)
# define PRINT_MAGENTA_N(_msg)(std::cout << MAGENTA << _msg << RESET << std::endl)
# define PRINT_CYAN_N(_msg)(std::cout << CYAN << _msg << RESET << std::endl)
# define PRINT_WHITE_N(_msg)(std::cout << WHITE << _msg << RESET << std::endl)



template <typename T>
void	are_equal(T v1, T v2)
{
	std::true_type
	std::cout << v1 << " | " << v2 << "    [";
	if (std::equal(v1.begin(), v1.end(), v2.begin()))
		PRINT_GREEN("EQUAL");
	else
		PRINT_RED("NOT EQUAL");
	std::cout << "]" << std::endl;
}

int	main(void)
{
	/* std::equal tests */
	std::string		s1;
	std::string		s2;

	s1 = "Indefinite";
	s2 = "Indefinit";
	are_equal(s1, s2);
	return (0);
}












































// #include <iostream>
// #include <string>
// #include <cstddef> // std::size_t

// /* all standard containers*/
// /* sequence */
// // #include <array>		// c++11
// #include <vector>
// #include <deque>
// // #include <forward_list>	// c++11
// #include <list>
// /* adapters*/
// #include <stack>
// #include <queue>
// /* associative */
// #include <map>
// #include <set>

// // std::pair
// #include <utility>


// /* own container */
// #include "stack.hpp"


// # define GREEN	"\033[32m"
// # define RESET	"\033[0m"
// # define PRINT(_msg)(std::cout << GREEN << _msg << RESET << std::endl)

// // overloaded output operators
// std::ostream &operator<<(std::ostream &os, std::stack<int> s)
// {
// 	std::stack<int>::size_type	_size = s.size();
// 	for (std::stack<int>::size_type i = 0; i < _size; ++i)
// 	{
// 		os << s.top() << ' ';
// 		s.pop();
// 	}
// 	return (os);
// }

// std::ostream &operator<<(std::ostream &os, ft::stack<int> f)
// {
// 	ft::stack<int>::size_type	_size = f.size();
// 	for (ft::stack<int>::size_type i = 0; i < _size; ++i)
// 	{
// 		os << f.top() << ' ';
// 		f.pop();
// 	}
// 	return (os);
// }



// /* mains */

// int	main()
// {
// 	PRINT("STD:");
// 	std::stack<int>		s1;

// 	s1.push(3);
// 	s1.push(2);
// 	s1.push(1);
// 	std::cout << s1 << std::endl;

// 	// copy constructor
// 	std::stack<int>		s2(s1);
// 	std::cout << s2 << std::endl;

// 	// assignment operator
// 	std::stack<int>		s3;
// 	s3 = s2;

// 	std::cout << s3 << std::endl;
// 	std::stack<int>		s4(std::stack<int>::reference cntr);

// 	PRINT("");
// 	PRINT("FT:");
// 	ft::stack<int>		f1;

// 	f1.push(3);
// 	f1.push(2);
// 	f1.push(1);
// 	std::cout << f1 << std::endl;

// 	ft::stack<int>		f2(f1);
// 	std::cout << f2 << std::endl;

// 	ft::stack<int>		f3;
// 	f3 = f2;
// 	std::cout << f3 << std::endl;
// 	ft::stack<int>		f4(std::deque<int>::reference cntr);

// 	std::pair<int, int>			p1;
// 	std::pair<int, int>			p2(-78, 129);
// 	std::pair<int, int>			p3(p1);
// 	std::pair<int, int>			p4 = p2;
// }
