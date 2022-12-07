#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <vector>
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

    template <typename T>
    class vector
    {
        public:
            typedef T           reference;
    };


} // namespace ft

#endif