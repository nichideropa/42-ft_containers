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

} // namespace ft


#include <string>
#include <map>

int main(void)
{
    std::map<int ,std::string>      tree_map = {{0, "introspection"},
                                                {1, "nodes"}};

    return 0;
}