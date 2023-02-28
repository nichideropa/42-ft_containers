#ifndef TYPE_TRAITS_HPP
# define TYPE_TRAITS_HPP

#include <type_traits>

/* Generic Programming */

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
	
	/* long long, char16_t and char32_t belong to C++11 */


	/* might be of interest in conversions of iterator */
	template <typename, typename>
	struct are_same
	{
		enum {value = 0};
		typedef false_type type;
	};

	template <typename T>
	struct are_same<T, T>
	{
		enum {value = 1};
		typedef true_type type;
	};

	// template <typename, typename>
	// struct are_same : public false_type {};

	// template <typename T>
	// struct are_same<T, T> : public true_type {}


	/* different approach (presently) to defining the is_integral specification */
	// template <typename T>
	// struct remove_const
	// {
	// 	typedef T		type;
	// };

	// template <typename T>
	// struct remove_const<T const>
	// {
	// 	typedef T		type;
	// };

	// template <typename T>
	// struct remove_volatile
	// {
	// 	typedef T		type;
	// };

	// template <typename T>
	// struct remove_volatile<T volatile>
	// {
	// 	typedef T		type;
	// };

	// template <typename T>
	// struct remove_cv
	// {
	// 	typedef typename remove_const<typename remove_volatile<T>::type>::type		type;
	// };


	// template <typename T>
	// struct is_integral_helper : public false_type {};

	// template <>
	// struct is_integral_helper<bool> : public true_type {};

	// template <>
	// struct is_integral_helper<char> : public true_type {};

	// template <>
	// struct is_integral_helper<wchar_t> : public true_type {};

	// template <>
	// struct is_integral_helper<signed char> : public true_type {};

	// template <>
	// struct is_integral_helper<short> : public true_type {};

	// template <>
	// struct is_integral_helper<int> : public true_type {};

	// template <>
	// struct is_integral_helper<long> : public true_type {};

	// template <>
	// struct is_integral_helper<unsigned char> : public true_type {};

	// template <>
	// struct is_integral_helper<unsigned short> : public true_type {};

	// template <>
	// struct is_integral_helper<unsigned long> : public true_type {};

	// template <typename T>
	// struct is_integral : public is_integral_helper<remove_cv<T>::type>::type {};


} // namespace ft


#endif // TYPE_TRAITS_HPP