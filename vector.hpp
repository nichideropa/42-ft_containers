#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <vector>
#include <memory>		// std::allocator
#include "iterator.hpp"

/* iterator type of std::vector is implementation defined. It can be a nested
    class or just simply an alias for the pointer of the value_type */

/* simple example:
    template <typename T, // here is a second parameter //> 
    class vector 
    {
        ...
        typedef T*          pointer;
        typedef const T*    const_pointer;
        ...
        
        1.
        typedef pointer         iterator;
        typedef const pointer   const_iterator;

        2.
        typedef __wrap_iterator<pointer>        iterator;
        typedef __wrap_iterator<const_pointer>  const_iterator;
    }
*/

namespace ft {

    template <typename T, typename Allocator=std::allocator<T> >
    class vector
    {
        public:
		typedef T													value_type;
		typedef typename Allocator									allocator_type;
		typedef typename allocator_type::reference					reference;
		typedef typename allocator_type::const_reference			const_reference;
		typedef typename allocator_type::pointer					pointer;
		typedef typename allocator_type::const_pointer				const_pointer;
		typedef typename normal_iterator<pointer>					iterator;
		typedef typename normal_iterator<const_pointer>				const_iterator;
		typedef typename reverse_iterator<iterator>					reverse_iterator;
		typedef typename reverse_iterator<const_iterator>			const_reverse_iterator;
		typedef size_t												size_type;
		typedef ptrdiff_t											difference_type;

		private:
			allocator_type		m_alloc;
			pointer				*m_begin;
			pointer				*m_end;
			pointer				*m_end_storage;

		public:

		// constructors 
		explicit vector(const allocator_type &alloc = allocator_type())
			: m_alloc(alloc), m_begin(0), m_end(0), m_end_storage(0)
		{}

		explicit vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type())
			: m_alloc(alloc), m_begin(0), m_end(0), m_end_storage(0)
		{}

		template <typename InputIterator>
		vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type());
			: m_alloc(alloc), m_begin(0), m_end(0), m_end_storage(0)
		{}

		vector(const vector &other)
		{
			*this = other;
		}

		// destructors
		~vector();


		// operator=
		vector	&operator= (const vector& other);


		// iterators
		iterator begin();

		const_iterator begin() const;

		iterator end();

		const_iterator end() const;

		reverse_iterator rbegin();

		const_reverse_iterator rbegin() const;

		reverse_iterator end();

		const_reverse_iterator end() const;

		// capacity
		size_type size() const;

		size_type max_size() const;

		void resize(size_type n, value_type val=value_type());

		size_type capacity() const;

		bool empty() const;

		void reserve(size_type n);

		// c++11
		void shrink_to_fit();

		// element access
		reference at(size_type pos);

		const_reference at(size_type pos) const;

		reference front();

		const_reference front() const;

		reference back();

		const_reference back() const;

		value_type *data() noexcept;

		const value_type *data() const noexcept;

		reference operator[](size_type pos);

		const_reference operator[](size_type pos) const;

		// modifiers
		void assign(size_type n, const value_type &val);

		template <typename InputIterator>
		void assign(InputIterator first, InputIterator last);

		void push_back(const value_type &val);

		void pop_back();

		iterator insert(iterator position, const value_type &val);

		void insert(iterator position, size_type n, const value_type &val);

		template <typename InputIterator>
		void insert(iterator pos, InputIterator first, InputIterator last);

		iterator erase(iterator position);

		iterator erase(iterator first, iterator last);

		void swap(vector &a);

		void clear();

		// allocator

		allocator_type get_allocator() const;
			
    };


} // namespace ft

#endif
