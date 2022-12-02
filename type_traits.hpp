#ifndef TYPE_TRAITS_HPP
# define TYPE_TRAITS_HPP

#include <type_traits>

namespace ft {

	/* SFINAE (substitution-failure-is-not-an-error) 
		if condition is true enable_if has public member
		typedef 'type' equal to T, otherwise no member typedef */
	template <bool condition, typename T=void>
	struct enable_if
	{};

	/* this is a partial template specialization */
	template <typename T>
	struct enable_if<true, T>
	{
		typedef T				type;
	};

	/* provides compile time constants as types */
	template <typename T, T v>
	struct integral_constant
	{
		// typedefs
		typedef T								value_type;
		typedef integral_constant<T, v>			type;

		/* attributes */
		static const T	value = v;
		/* inline initialization of constexpr is possible
			(non-type template parameters become constexpr) */

		/* conversion operator */
		operator value_type() const
		{
			return (value);
		}
	};

	/* instantiations of integral_constant to represent bool values */
	typedef integral_constant<bool, true>		true_type;
	typedef integral_constant<bool, false>		false_type;

	template <typename T>
	struct is_integral : false_type {};

	/* for all fundamental integral types including their 
		cv-qualified variants */
	template<>
	struct is_integral<bool> : public true_type {};

	template<>
	struct is_integral<const bool> : public true_type {};

	template<>
	struct is_integral<volatile bool> : public true_type {};

	template<>
	struct is_integral<const volatile bool> : public true_type {};

	template<>
	struct is_integral<char> : public true_type {};

	template<>
	struct is_integral<const char> : public true_type {};

	template<>
	struct is_integral<volatile char> : public true_type {};

	template<>
	struct is_integral<const volatile char> : public true_type {};

	template<>
	struct is_integral<wchar_t> : public true_type {};

	template<>
	struct is_integral<const wchar_t> : public true_type {};

	template<>
	struct is_integral<volatile wchar_t> : public true_type {};

	template<>
	struct is_integral<const volatile wchar_t> : public true_type {};

	template<>
	struct is_integral<signed char> : public true_type {};

	template<>
	struct is_integral<const signed char> : public true_type {};

	template<>
	struct is_integral<volatile signed char> : public true_type {};

	template<>
	struct is_integral<const volatile signed char> : public true_type {};

	template<>
	struct is_integral<short> : public true_type {};

	template<>
	struct is_integral<const short> : public true_type {};

	template<>
	struct is_integral<volatile short> : public true_type {};

	template<>
	struct is_integral<const volatile short> : public true_type {};

	template<>
	struct is_integral<int> : public true_type {};

	template<>
	struct is_integral<const int> : public true_type {};

	template<>
	struct is_integral<volatile int> : public true_type {};

	template<>
	struct is_integral<const volatile int> : public true_type {};

	template<>
	struct is_integral<long> : public true_type {};

	template<>
	struct is_integral<const long> : public true_type {};

	template<>
	struct is_integral<volatile long> : public true_type {};

	template<>
	struct is_integral<const volatile long> : public true_type {};

	template<>
	struct is_integral<unsigned char> : public true_type {};

	template<>
	struct is_integral<const unsigned char> : public true_type {};

	template<>
	struct is_integral<volatile unsigned char> : public true_type {};

	template<>
	struct is_integral<const volatile unsigned char> : public true_type {};

	template<>
	struct is_integral<unsigned short> : public true_type {};

	template<>
	struct is_integral<const unsigned int> : public true_type {};

	template<>
	struct is_integral<volatile unsigned int> : public true_type {};

	template<>
	struct is_integral<const volatile unsigned int> : public true_type {};

	template<>
	struct is_integral<unsigned long> : public true_type {};

	template<>
	struct is_integral<const unsigned long> : public true_type {};

	template<>
	struct is_integral<volatile unsigned long> : public true_type {};

	template<>
	struct is_integral<const volatile unsigned long> : public true_type {};

	/* long long, char16_t and char32_t are C++11 */

} // namespace ft


#endif // TYPE_TRAITS_HPP