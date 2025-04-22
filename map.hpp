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

    private:
        typedef ft::rb_tree<value_type, value_compare, allocator_type>  tree_type;

    public:
        typedef typename tree_type::iterator                iterator;
        typedef typename tree_type::const_iterator          const_iterator;
        typedef typename tree_type::reverse_iterator        reverse_iterator;
        typedef typename tree_type::const_reverse_iterator  const_reverse_iterator;


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

        

        explicit map(const Compare& comp, Allocator& alloc = Allocator())
            : tree_(value_compare(comp), alloc)
        {}

        template <typename InputIt>
        map(InputIt first, InputIt last, const Compare& comp = Compare(),
            const Allocator& alloc = Allocator());
        {}

        map(const map& other);
            : tree_(other.tree_)
        {}

        ~map();


        map& operator=(const map& other)
        {
            if (this != &other)
                tree_ = other.tree_;
            return *this;
        }


        iterator begin()
        { return tree_.begin(); }

        const_iterator begin() const
        { return tree_.begin(); }

        iterator end()
        { return tree_.end(); }
        
        const_iterator end() const
        { return tree_.end(); }

        reverse_iterator rbegin()
        { return reverse_iterator(end()); }

        const_reverse_iterator rbegin() const
        { return const_reverse_iterator(end()); }

        reverse_iterator rend()
        { return reverse_iterator(begin()); }

        const_reverse_iterator rend()
        { return const_reverse_iterator(begin()); }

        bool empty() const { return !tree_.size(); }

        size_type size() const { return tree_.size(); }

        size_type max_size() const { return tree_.max_size(); }

        mapped_type& operator[](const key_type& key)
        {}

        mapped_type& at(const key_type& key);

        const mapped_type& at(const key_type& key) const;

        ft::pair<iterator, bool> insert(const value_type& val);

        iterator insert(iterator position, const value_type& val);

        template <typename InputIt>
        void insert(InputIt first, InputIt last);

        iterator erase(iterator position);

        iterator erase(iterator first, iterator last);

        size_type erase(const Key& key);

        void clear()
        {
            tree_.clear();
        }

        key_compare key_comp() const
        {
            return key_compare();
        }

        value_compare value_comp() const
        {
            return tree_.value_comp();
        }

        iterator find(const Key& key)
        {
            return tree_.find(key);
        }

        const_iterator find(const Key& key) const
        {
            return tree_.find(key);
        }

        size_type count(const Key& key) const { return tree_.count(key); }

        iterator lower_bound(const Key& key);

        const_iterator lower_bound(const Key& key) const;

        iterator upper_bound(const Key& key);

        const_iterator upper_bound(const Key& key) const;

        ft::pair<iterator, iterator> equal_range(const Key& key);

        ft::pair<const_iterator, const_iterator> equal_range(const Key& key);

        void swap(map& other)
        {
            tree_.swap(other.tree_);
        }

        allocator_type get_allocator() const
        { return tree_.get_allocator(); }
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