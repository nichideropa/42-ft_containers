# 42-containers

The objective of this project was to reimplement some of the C++ STL containers, getting us
familiar with them and data structures in general.

## Description
Container:<br>
- `vector` without its bool specialization
- `stack` with vector as its default underlying container
- `map` which uses a 'red-black tree' as an internal data structure

underlying structures:<br>
- `iterator_traits` for the implementation of specific iterators and algorithms
- `pair` and `make_pair` as the class to store key-value pairs inside a map

and more.

## References
### 1. General
- [cplusplus](https://cplusplus.com/reference/stl/)
- [cppreference](https://en.cppreference.com/w/cpp/container)
- [GNU Compiler](https://github.com/gcc-mirror/gcc/tree/master/libstdc++-v3/include/bits)
- [LLVM Compiler](https://github.com/llvm-mirror/libcxx/tree/master/include)

### 2. Red-Black Tree

### 3. Miscellaneous
- [enable_if and SFINAE](https://eli.thegreenplace.net/2014/sfinae-and-enable_if)
- [SFINAE](https://www.fluentcpp.com/2019/08/23/how-to-make-sfinae-pretty-and-robust)

