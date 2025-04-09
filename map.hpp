#ifndef MAP_HPP
# define MAP_HPP

#include <utility> // std::pair
#include <functional> // std::less
#include <map>


#include "utility.hpp"

namespace ft {

template <typename Key, typename T, typename Compare = std::less<Key>,
            typename Allocator = std::allocator<ft::pair<const Key, T>>>
class map
{
    public:
        typedef Key                                         key_type;
        typedef T                                           mapped_type;
        typedef ft::pair<const Key, T>                      value_type;
        typedef Compare                                     key_compare;
        typedef Allocator                                   allocator_type;
        typedef typename allocator_type::reference          reference;
        typedef typename allocator_type::const_reference    const_reference;
        typedef typename allocator_type::pointer            pointer;
        typedef typename allocator_type::const_pointer      const_pointer;
        typedef typename allocator_type::size_type          size_type;
        typedef typename allocator_type::difference_type    difference_type;

        /* iterator typedefs to be added */


        /* typedefs are inherited by the binary_function struct */
        class value_compare: public std::binary_function<value_type, value_type, bool>
        {
            friend class map;

            protected:
                key_compare     compare_;

                value_compare(key_ompare c) : compare_(c)
                {}


            public:

                bool operator()(const value_type& lhs, const value_type& rhs) const
                {
                    return compare_(lhs.first, rhs.first);
                }
        }

        

        map();

        explicit map(const Compare& comp, Allocator& alloc = Allocator());

        template <typename InputIt>
        map(InputIt first, InputIt last, const Compare& comp = Compare(),
            const Allocator& alloc = Allocator() );

        map(const map& other);

        ~map();


        map& operator=(const map& other);


        allocator_type get_allocator() const;

        iterator begin();

        const_iterator begin() const;

        iterator end();
        
        const_iterator end() const;

        reverse_iterator rbegin();

        const_reverse_iterator rbegin() const;

        reverse_iterator rend();

        const_reverse_iterator rend();

        bool empty() const;

        size_type size() const;

        size_type max_size() const;

        mapped_type& operator[](const key_type& key);

        mapped_type& at(const key_type& key);

        const mapped_type& at(const key_type& key) const;

        ft::pair<iterator, bool> insert(const value_type& val);

        iterator insert(iterator position, const value_type& val);

        template <typename InputIt>
        void insert(InputIt first, InputIt last);

        iterator erase(iterator position);

        iterator erase(iterator first, iterator last);

        size_type erase(const Key& key);

        void clear();

        key_compare key_comp() const;

        value_compare value_comp() const;

        iterator find(const Key& key);

        const_iterator find(const Key& key) const;

        size_type count(const Key& key) const;

        iterator lower_bound(const Key& key);

        const_iterator lower_bound(const Key& key) const;

        iterator upper_bound(const Key& key);

        const_iterator upper_bound(const Key& key) const;

        ft::pair<iterator, iterator> equal_range(const Key& key);

        ft::pair<const_iterator, const_iterator> equal_range(const Key& key);

        void swap(map& other);
};

template <typename Key, typename T, typename Compare, typename Alloc>
bool operator==(const map<Key, T, Compare, Alloc>& lhs,
                const map<Key, T, Compare, Alloc>& rhs);

template <typename Key, typename T, typename Compare, typename Alloc>
bool operator!=(const map<Key, T, Compare, Alloc>& lhs,
                const map<Key, T, Compare, Alloc>& rhs);

template <typename Key, typename T, typename Compare, typename Alloc>
bool operator<(const map<Key, T, Compare, Alloc>& lhs,
               const map<Key, T, Compare, Alloc>& rhs);

template <typename Key, typename T, typename Compare, typename Alloc>
bool operator<=(const map<Key, T, Compare, Alloc>& lhs,
                const map<Key, T, Compare, Alloc>& rhs);

template <typename Key, typename T, typename Compare, typename Alloc>
bool operator>(const map<Key, T, Compare, Alloc>& lhs,
                const map<Key, T, Compare, Alloc>& rhs);

template <typename Key, typename T, typename Compare, typename Alloc>
bool operator>=(const map<Key, T, Compare, Alloc>& lhs,
                const map<Key, T, Compare, Alloc>& rhs);

template <typename Key, typename T, typename Compare, typename Alloc>
void swap(ft::map<Key, T, Compare, Alloc>& lhs,
            ft::map<Key, T, Compare, Alloc>&rhs)
{
    lhs.swap(rhs);
}


} // namespace ft

#endif // MAP_HPP