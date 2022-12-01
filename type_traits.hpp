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
	struct is_integral<bool> : true_type {};

	template<>
	struct is_integral<const bool> : true_type {};

	template<>
	struct is_integral<volatile bool> : true_type {};

	template<>
	struct is_integral<const volatile bool> : true_type {};

	template<>
	struct is_integral<char> : true_type {};

	template<>
	struct is_integral<const char> : true_type {};

	template<>
	struct is_integral<volatile char> : true_type {};

	template<>
	struct is_integral<const volatile char> : true_type {};

	template<>
	struct is_integral<wchar_t> : true_type {};

	template<>
	struct is_integral<const wchar_t> : true_type {};

	template<>
	struct is_integral<volatile wchar_t> : true_type {};

	template<>
	struct is_integral<const volatile wchar_t> : true_type {};

	template<>
	struct is_integral<signed char> : true_type {};

	template<>
	struct is_integral<const signed char> : true_type {};

	template<>
	struct is_integral<volatile signed char> : true_type {};

	template<>
	struct is_integral<const volatile signed char> : true_type {};

	template<>
	struct is_integral<short> : true_type {};

	template<>
	struct is_integral<const short> : true_type {};

	template<>
	struct is_integral<volatile short> : true_type {};

	template<>
	struct is_integral<const volatile short> : true_type {};

	template<>
	struct is_integral<int> : true_type {};

	template<>
	struct is_integral<const int> : true_type {};

	template<>
	struct is_integral<volatile int> : true_type {};

	template<>
	struct is_integral<const volatile int> : true_type {};

	template<>
	struct is_integral<long> : true_type {};

	template<>
	struct is_integral<const long> : true_type {};

	template<>
	struct is_integral<volatile long> : true_type {};

	template<>
	struct is_integral<const volatile long> : true_type {};

	template<>
	struct is_integral<unsigned char> : true_type {};

	template<>
	struct is_integral<const unsigned char> : true_type {};

	template<>
	struct is_integral<volatile unsigned char> : true_type {};

	template<>
	struct is_integral<const volatile unsigned char> : true_type {};

	template<>
	struct is_integral<unsigned short> : true_type {};

	template<>
	struct is_integral<const unsgined int> : true_type {};

	template<>
	struct is_integral<volatile unsgined int> : true_type {};

	template<>
	struct is_integral<const volatile unsgined int> : true_type {};

	template<>
	struct is_integral<unsigned long> : true_type {};

	template<>
	struct is_integral<const unsigned long> : true_type {};

	template<>
	struct is_integral<volatile unsigned long> : true_type {};

	template<>
	struct is_integral<const volatile unsigned long> : true_type {};

	/* long long, char16_t and char32_t are C++11 */

} // namespace ft


#endif // TYPE_TRAITS_HPP