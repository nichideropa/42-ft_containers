#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <vector>
#include <memory>		// std::allocator
#include <exception>
#include <limits>


#include "iterator.hpp"
#include "algorithm.hpp"
#include "type_traits.hpp"

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
		typedef Allocator											allocator_type;
		typedef typename allocator_type::size_type					size_type;
		typedef typename allocator_type::difference_type			difference_type;
		typedef typename allocator_type::reference					reference;
		typedef typename allocator_type::const_reference			const_reference;
		typedef typename allocator_type::pointer					pointer;
		typedef typename allocator_type::const_pointer				const_pointer;
		typedef ft::normal_iterator<pointer, vector>					iterator;
		typedef ft::normal_iterator<const_pointer, vector>				const_iterator;
		typedef ft::reverse_iterator<iterator>							reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>					const_reverse_iterator;

	private:
		allocator_type		alloc_;
		pointer				begin_;
		pointer				end_;
		pointer				end_cap_;

	public:

		// constructors 
		explicit vector(const allocator_type &alloc = allocator_type())
			: alloc_(alloc), begin_(NULL), end_(NULL), end_cap_(NULL)
		{}

		explicit vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type())
			: alloc_(alloc), begin_(NULL), end_(NULL), end_cap_(NULL)
		{
			try {
				if (n > 0)
				{
					vallocate_(n);
					construct_at_end_(n, val);
				}
			} catch(...) {
				vdeallocate_();
				throw;
			} 
		}

		template <typename InputIterator>
		vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type(),
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0)
			: alloc_(alloc), begin_(NULL), end_(NULL), end_cap_(NULL)
		{
			try {
				assign(first, last);
			} catch (...) {
				vdeallocate_();
				throw;
			}
		}

		vector(const vector &other)
			: alloc_(other.alloc_), begin_(NULL), end_(NULL), end_cap_(NULL)
		{
			try {
				if (other.size() > 0)
				{
					vallocate_(other.size());
					construct_at_end_(other.begin_, other.end_, ft::iterator_category(other.begin_));
				}
			} catch (...) {
				vdeallocate_();
				throw;
			}
		}

		// destructors
		~vector()
		{
			vdeallocate_();
		}


		// operator=
		vector	&operator=(const vector& other)
		{
			if (this != &other)
			{
				alloc_ = other.get_allocator();
				assign(other.begin(), other.end());
			}

			return *this;
		}


		// iterators
		iterator begin()
		{
			return iterator(begin_);
		}

		const_iterator begin() const
		{
			return const_iterator(begin_);
		}

		iterator end()
		{
			return iterator(end_);
		}

		const_iterator end() const
		{
			return const_iterator(end_);
		}

		reverse_iterator rbegin()
		{
			return reverse_iterator(end());
		}

		const_reverse_iterator rbegin() const
		{
			return const_reverse_iterator(end());
		}

		reverse_iterator rend()
		{
			return reverse_iterator(begin());
		}

		const_reverse_iterator rend() const
		{
			return const_reverse_iterator(begin());
		}


		size_type size() const
		{
			return static_cast<size_type>(end_ - begin_);
		}

		size_type max_size() const
		{
			return ft::min<size_type>(alloc_.max_size(),
				std::numeric_limits<difference_type>::max());
		}

		void resize(size_type n, value_type val=value_type())
		{
			const size_type current_size = size();

			if (current_size < n) 
			{ 
				reserve(recommend_size(n));
				construct_at_end_(n - current_size, val);
			} else if (current_size > n) {
				erase_at_end_(begin_ + n);
			}
		}


		size_type capacity() const
		{
			return static_cast<size_type>(end_cap_ - begin_);
		}

		bool empty() const
		{
			return begin_ == end_;
		}


		void reserve(size_type n)
		{
			if (n > capacity()) {
				vector tmp(alloc_);
				tmp.vallocate_(n);
				tmp.construct_at_end_(begin_, end_, ft::iterator_category(begin_));
				swap(tmp);	
			}

			// because the old vector goes out of scope
			// the memory is deallocated (tmp == old vector)
		}


		// element access
		reference at(size_type pos)
		{
			if (pos >= size())
				throw std::out_of_range("ft::vector");
			return (*this)[pos];
		}

		const_reference at(size_type pos) const
		{
			if (pos >= size())
				throw std::out_of_range("ft::vector");
			return (*this)[pos];
		}

		reference front()
		{
			return *begin_;
		}

		const_reference front() const
		{
			return *begin_;
		}

		reference back()
		{
			return *(end_ - 1);
		}

		const_reference back() const
		{
			return *(end_ - 1);
		}

		value_type *data() noexcept
		{
			return begin_;
		}

		const value_type *data() const noexcept
		{
			return begin_;
		}


		reference operator[](size_type pos)
		{
			return begin_[pos];
		}

		const_reference operator[](size_type pos) const
		{
			return begin_[pos];
		}


		// modifiers
		void assign(size_type n, const value_type &val)
		{
			if (n > capacity())
			{
				vector tmp(n, val);
				swap(tmp);
			} else {
				const size_type _size = size();

				ft::fill_n(begin_, ft::min(_size, n), val);
				if (n < _size)
					erase_at_end_(begin_ + n);
				else
					construct_at_end_(n - _size, val);
			}
		}

		template <typename InputIterator>
		void assign(InputIterator first, InputIterator last,
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type * = 0)
		{
			assign_range_(first, last, ft::iterator_category(first));
		}


		void push_back(const value_type &val)
		{
			if (end_ == end_cap_)
				reserve(recommend_size(capacity() + 1)); // improvement here recommend size
			construct_at_end_(1, val);
		}

		void pop_back()
		{
			erase_at_end_(end_ - 1);
		}


		iterator insert(iterator position, const value_type &val)
		{
			difference_type offset = position - begin();
			insert(position, 1, val);
			return begin() + offset;
		}

		void insert(iterator position, size_type n, const value_type &val)
		{
			if (n != 0)
			{
				const size_type offset = position - begin();
				const size_type old_size = size();

				resize(old_size + n);
				ft::copy_backward(begin_ + offset, begin_ + old_size, begin_ + size());
				ft::fill_n(begin_ + offset, n, val);
			}
		}

		template <typename InputIterator>
		void insert(iterator pos, InputIterator first, InputIterator last,
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type * = 0)
		{
			insert_range_(pos, first, last, ft::iterator_category(first));
		}


		iterator erase(iterator position)
		{
			if (position + 1 != end())
				ft::copy(position + 1, end(), position);
			pop_back();

			return position;
		}

		iterator erase(iterator first, iterator last)
		{
			size_type n = ft::distance(first, last);
			if (n > 0)
			{
				ft::copy(begin_ + (last - begin()) + 1, end_, begin_ + (first - begin()));
				erase_at_end_(end_ - n);
			}

			return first;
		}


		void swap(vector &a)
		{
			ft::swap(alloc_, a.alloc_);
			ft::swap(begin_, a.begin_);
			ft::swap(end_, a.end_);
			ft::swap(end_cap_, a.end_cap_);
		}

		void clear()
		{
			erase_at_end_(begin_);
		}

		allocator_type get_allocator() const
		{
			return alloc_;
		}


	private:

		inline void construct_(pointer p, const_reference val)
		{
			alloc_.construct(p, val);
		}

		inline void destroy_(pointer p)
		{
			alloc_.destroy(p);
		}

		/* allocates memory using the allocator for the vector to be ready.
			Does nothing else - preparation for the construction of vector */
		inline void vallocate_(size_type n)
		{
			if (n > max_size())
				throw std::length_error("ft::vector");

			begin_ = end_ = alloc_.allocate(n);
			end_cap_ = begin_ + n;
		}


		/* deallocates the entire memory reserved for the vector.
			Cleans up after any operation and leaves a clean plate */
		inline void vdeallocate_()
		{
			if (begin_ == NULL)
				return ;

			clear();
			alloc_.deallocate(begin_, capacity());
			begin_ = end_ = end_cap_ = NULL;
		}

		inline void construct_at_end_(size_type n, const_reference val = value_type())
		{
			for (size_type i = 0; i < n; ++i, ++end_)
				construct_(end_, val);
		}

		template <typename ForwardIterator>
		inline void construct_at_end_(ForwardIterator first, ForwardIterator last,
										ft::forward_iterator_tag)
		{
			for (; first != last; ++first, ++end_)
				construct_(end_, *first);
		}

		inline void erase_at_end_(pointer pos)
		{
			while (end_ != pos)
				destroy_(--end_);
		}

		template <typename InputIterator>
		inline void assign_range_(InputIterator first, InputIterator last,
									ft::input_iterator_tag)
		{
			clear();
			for (; first != last; ++first)
				push_back(*first);
		}

		template <typename ForwardIterator>
		inline void assign_range_(ForwardIterator first, ForwardIterator last,
									ft::forward_iterator_tag)
		{
			clear();

			size_type n = static_cast<size_type>(ft::distance(first, last));
			if (n > 0)
			{
				if (n > capacity())
				{
					vdeallocate_();
					vallocate_(n);
				}
				construct_at_end_(first, last, ft::iterator_category(first));
			}
		}

		template <typename InputIterator>
		inline void insert_range_(iterator pos, InputIterator first,
						InputIterator last, ft::input_iterator_tag)
		{
			if (pos == end())
			{
				for (; first != last; ++first)
					push_back(*first);
			}
			else
			{
				vector tmp(first, last);
				insert(pos, tmp.begin(), tmp.end());
			}
		}

		template <typename ForwardIterator>
		inline void insert_range_(iterator pos, ForwardIterator first,
						ForwardIterator last, ft::forward_iterator_tag)
		{
			size_type n = static_cast<size_type>(ft::distance(first, last));

			if (n > 0)
			{
				const difference_type offset = pos - begin();
				const size_type old_size = size();

				resize(old_size + n);
				ft::copy_backward(begin_ + offset, begin_ + old_size, begin_ + size());
				ft::copy(first, last, begin_ + offset);
			}
		}


		/* multiple sources claim a growth factor of 2 is suboptimal, if not 
			the worst possible (fbvectors) 
			
			the code worked with limits when it was first implemented, because
			instead of allocating the required memory next to the block a new
			location was used everytime which has a penalty on performance
			
			therefore a growth factor of 1.5 was suggested because it grows
			more according to the needs of the vector, as well as can use
			memory relocation better */
		size_type recommend_size(size_type new_size)
		{
			const size_type size_max = max_size();

			if (new_size > size_max)
				throw std::length_error("ft::vector");

			const size_type cap = capacity();
			if (new_size < cap)
				return cap;
			
			if (cap >= size_max / 2)
				return size_max;
			
			return ft::max(cap * 2, new_size);
		}

		
};


	template <typename T, typename Alloc>
	inline bool operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template <typename T, typename Alloc>
	inline bool operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return !(lhs == rhs);
	}

	template <typename T, typename Alloc>
	inline bool operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()); 
	}

	template <typename T, typename Alloc>
	bool operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return !(rhs < lhs);
	}

	template <typename T, typename Alloc>
	bool operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return rhs < lhs;
	}

	template <typename T, typename Alloc>
	bool operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return !(lhs < rhs);
	}

	template <typename T, typename Alloc>
	void swap(vector<T, Alloc>& lhs, vector<T, Alloc>& rhs)
	{
		lhs.swap(rhs);
	}


} // namespace ft

#endif
