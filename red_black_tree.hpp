/* 
    THEORY behind RED-BLACK-TREES 

    Don't know exactly about the structure below the red black tree
    but with introsprection one might be able to figure it out.

    How would one go about that.

    - function declarations 
        insert has an overload with a function with a type
        std::map::node_type which speaks for a separate node class

    - working with the auto keyword and then introspect on the object
        auto &map.at()


    

        As I remember from others working on it there are around 7 cases
        of rotation for insertion/deletion for the entire tree.

        Only the bonus required a Red-Black Tree, in geeneral one could have
        used other format just like a Binary-Search Tree or an AVL-Tree

        requires a max of 2 rotations for self balancing even when tree is big

    
*/

#include "iterator.hpp"

namespace ft {

    enum NODE_COLOR { BLACK, RED };


    /* 
        It originally is implemented as a base class with with the metadata
        and inherited by a class that adds the value of the node. The base
        class additionally provides function to find the min and max of the tree.

    */
    template <typename T>
    struct Node
    {
        typedef T                   value_type;
        typedef Node<T>*            pointer;
        typedef const Node<T>*      const_pointer;

        Node() : val(), color(NODE_COLOR.RED), parent(NULL),
            left(NULL), right() 
        []

        explicit Node(T key, NODE_COLOR color)
            : val(key), color(color), parent(NULL), left(NULL), right(NULL)
        {}

       /*
        Is a copy constructor necessary?
        Usually a map doesn't hold the same value twice, otherwise we can
        copy a tree and therefore the underlying nodes might be copied too.
        */
        Node(const Node& src) : val(src.val), color(src.color),
            parent(src.parent), left(src.left), right(src.right)
        {}


        ~Node() {}


        public:
            value_type              val;
            NODE_COLOR              color;
            pointer                 parent;
            pointer                 left;
            pointer                 right;
    };


    template <typename NodePtr>
    NodePtr tree_min(NodePtr node)
    {
        while (node->left != NULL)
            node = node->left;
        return node;
    }

    template <typename NodePtr>
    NodePtr tree_max(NodePtr node)
    {
        while (node->right != NULL)
            node = node->right;
        return node;
    }

    template <typename NodePtr>
    NodePtr tree_next(NodePtr node)
    {
        if (node->right != NULL)
            return tree_min(node->right);
        NodePtr parent = node->parent;
        while (parent != NULL && node == parent->right)
        {
            node = parent;
            parent = parent->parent;
        }
        return parent;
    }

    template <typename NodePtr>
    NodePtr tree_prev(NodePtr node)
    {
        if (node->left != NULL)
            return tree_max(node->left);
        NodePtr parent = node->parent;
        while (parent != NULL && node == parent->left)
        {
            node = parent;
            parent = parent->parent;
        }
        return parent;
    }



    /*
        Has a helper class called 'header' to manage default initialization
        and contains a counter for the number of nodes in the tree.

        Thought this might be something like a sentinel node, with default values
    */

    
    template <typename T>
    class tree_const_iterator;


    template <typename T>
    class tree_iterator
    {
        public:
            typedef bidirectional_iterator_tag      iterator_category; 
            typedef T                               value_type;
            typedef T&                              reference;
            typedef T*                              pointer;
            typedef ptrdiff_t                       difference_type;
            typedef tree_const_iterator             const_iterator;


        private:
            typedef ft::Node<T>::pointer            node_pointer;
            typedef ft::Node<T>::const_pointer      const_pointer;


        public:
            tree_iterator() : current_(NULL)
            {}

            tree_iterator(node_pointer node) : current_(node)
            {}

            /* 
                I do believe the requirements say that an iterator should be
                copy constructible, as well as assignable.
            */

            tree_iterator(const tree_iterator& src) : current_(src.current)
            {}

            ~tree_iterator()

            tree_iterator& operator=(const tree_iterator& src)
            {
                current_ = src.current_;
                return *this;
            }


            node_pointer base() const { return current_; }

            reference operator*() const { return current_.val; }

            pointer operator->() const { return &(operator*()); }

            tree_iterator& operator++()
            {
                current_ = tree_next<node_pointer>(current_);
                return *this;
            }

            tree_iterator& operator++(int)
            {
                tree_iterator tmp = *this;
                ++(*this);
                return tmp;
            }

            tree_iterator& operator--()
            {
                current_ = tree_prev<node_pointer>(current_);
                return *this;
            }

            tree_iterator& operator--(int)
            {
                tree_iterator tmp = *this;
                --(*this);
                return tmp;
            }



            /* 
                Do I really need an overload for equality operators?
                What sense does it make to compare const iterators inside
                the non-const iterator class?
            */
            bool operator==(const tree_iterator& rhs) const
            {
                return current_ == rhs.current_;
            }

            bool operator!=(const tree_iterator& rhs) const
            {
                return current_ != rhs.current_;
            }



        private:
            node_pointer    current_;
    };
    

    template <typename T>
    class tree_const_iterator
    {
        public:
            typedef bidirectional_iterator_tag      iterator_category; 
            typedef T                               value_type;
            typedef T&                              reference;
            typedef T*                              pointer;
            typedef ptrdiff_t                       difference_type;
            typedef tree_iterator                   iterator;

        private:
            typedef ft::Node<T>::pointer            node_pointer;
            typedef ft::Node<T>::const_pointer      const_pointer;


        public:
            tree_const_iterator() : current_(NULL)
            {}

            tree_const_iterator(node_pointer node) : current_(node)
            {}

            /* 
                I do believe the requirements say that an iterator should be
                copy constructible, as well as assignable.
            */

            tree_const_iterator(const tree_iterator& src) : current_(src.current)
            {}

            tree_const_iterator(const tree_const_iterator& src) : current_(src.current)
            {}

            ~tree_iterator()

            tree_const_iterator& operator=(const tree_const_iterator& src)
            {
                current_ = src.current_;
                return *this;
            }


            const_node_pointer base() const { return current_; }

            reference operator*() const { return current_.val; }

            pointer operator->() const { return &(operator*()); }

            tree_const_iterator& operator++()
            {
                current_ = tree_next<node_pointer>(current_);
                return *this;
            }

            tree_const_iterator& operator++(int)
            {
                tree_const_iterator tmp = *this;
                ++(*this);
                return tmp;
            }

            tree_const_iterator& operator--()
            {
                current_ = tree_prev<node_pointer>(current_);
                return *this;
            }

            tree_const_iterator& operator--(int)
            {
                tree_const_iterator tmp = *this;
                --(*this);
                return tmp;
            }



            /* 
                Do I really need an overload for equality operators?
                What sense does it make to compare const iterators inside
                the non-const iterator class?
            */
            bool operator==(const tree_const_iterator& rhs) const
            {
                return current_ == rhs.current_;
            }

            bool operator!=(const tree_const_iterator& rhs) const
            {
                return current_ != rhs.current_;
            }


        private:
            const_node_pointer    current_;
    };


    template <typename T, typename Compare, typename Allocator>
    class rb_tree
    {
        public:
            typedef T                                           value_type;
            typedef Compare                                     value_compare;
            typedef Allocator                                   allocator_type;

            typedef typename Node<value_type>                   node_type;
            typedef typename node_type::pointer                 node_pointer;
            typedef typename node_type::const_pointer           const_node_pointer;
            typedef typename allocator_type::template \
            rebind<node_type>::other                            node_allocator_type;
            typedef typename allocator_type::pointer            pointer;
            typedef typename allocator_type::const_pointer      const_pointer;
            typedef typename allocator_type::size_type          size_type;
            typedef typename allocator_type::difference_type    difference_type;

            typedef ft::tree_iterator                           iterator;
            typedef ft::tree_const_iterator                     const_iterator;
            typedef ft::reverse_iterator<iterator>              reverse_iterator;
            typedef ft::reverse_iterator<const_iterator>        const_reverse_iterator;

        protected:
            value_compare           value_compare_;

            /*
                This is the allocator that allocates the type a user thinks
                the underlying structure holds
                e.G. std::map<std::string, int> map
                    -> std::pair<std::string, int>
            */
            allocator_type          value_alloc_;

            /* 
                A data structure needs a way to hold the elements of itself and relate
                them to one another. This is achieved by wrapping them with another
                structure in this case the Node class.
                This is the allocator that allocates a Node which  holds a
                std::pair<std::string, int> as in the example above
            */
            node_allocator_type     node_alloc_;


            /* it might be possible to implement the tree without a root/head node
                but makes it easier. the leftmost node also helps with performance 
                and is sugar for some operations */

            /*
                We need to keep track of how many Nodes a tree holds. In the original
                implementation this was done by a Node wrapping class. */
            size_type               size_;

            /*
                This is the placeholder for any Node that has no value
            */
            node_pointer            nil_;


            node_pointer            leftmost_;

        public:

            /* implicit default constructor */

            explicit rb_tree(const Compare& comp, const allocator_type& alloc)
                : value_compare_(comp), value_alloc_(alloc), node_alloc(alloc), size_(0)
            {}

            rb_tree(const rb_tree& other)
                : value_compare_(other.value_compare_), value_alloc_(other.value_alloc_),
                node_alloc_(other.node_alloc_), size_(other.size_)
            {}

            ~rb_tree()
            {}

            rb_tree& operator=(const rb_tree& src)
            {

            }


            iterator begin() { return iterator(leftmost_); }

            const_iterator begin() { return const_iterator(leftmost_); }

            iterator end() { return iterator(nil_); }

            const_iterator end() { return const_iterator(nil_); }

            value_compare& value_comp() const { return value_compare_; }

            /* original implementation includes the reverse iterators
            inside the rb_tree class and not only in the map */



            const value_compare& value_comp() const { return value_compare_; }

            size_type size() const { return size_; }

            size_type max_size() const { return node_alloc_.max_size(); }

            pair<iterator, bool> insert_unique(const value_type& val)
            {}

            iterator insert_unique(interator pos, const value_type& val)
            {}

            template <typename InputIt>
            void insert_range_unique(InputIt first, InputIt last)
            {
                for (; first != last; ++first)
                    insert_unique(*first);
            }

            pair<iterator, iterator> equal_range(const value_type& val)
            {}

            pair<const_iterator, const_iterator> equal_range(const value_type& val) const
            {}

            void erase(const_iterator position)
            {}

            void erase_range(const_iterator first, const_iterator last)
            {}

            size_type erase_unique(const value_type& val)
            {}

            void clear()
            {}

            /*
                the original implementation uses
                -> const key_type& k for these functions

                can change up to use a template parameter
                for the key_type instead of the value_type
                -> template <typename Key
                   iterator find(const Key& k)
            */

            iterator find(const value_type& val)
            {}

            const_iterator find(const value_type& val) const
            {}

            iterator lower_bound(const value_type& val)
            {}

            const_iterator lower_bound(const value_type& val) const
            {}

            iterator upper_bound(const value_type& val)
            {}

            const_iterator upper_bound(const value_type& val) const
            {}

            size_type count(const value_type& val) const
            {
                if (find(val) != end())
                    return 1;
                else
                    return 0;
            }

            /* finished */
            void swap(rb_tree& other)
            {
                ft::swap(value_compare_, other.value_compare);
                ft::swap(value_alloc_, other.value_alloc_);
                ft::swap(node_alloc_, other.node_alloc_);
                ft::swap(size_, other.size_);
                ft::swap(nil_, other.nil_);
                ft::swap(leftmost_, other.leftmost_);
            }

            allocator_type get_allocator() const { return value_alloc_; }


                
                
                
        private:
            tree_type               tree_;
    
    };


} // namespace ft


#include <string>
#include <map>

int main(void)
{
    std::map<int ,std::string>      tree_map = {{0, "introspection"},
                                                {1, "nodes"}};

    return 0;
}