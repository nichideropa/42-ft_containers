#include <gtest/gtest.h>
#include <stack>
#include <deque>

#include "../stack.hpp"

#define VOLUME 100

// using namespace ft;
using namespace std;


/*
    The container used internally must support specific functionalities
    such as:
        - push_back
        - pop_back
        - back
        - empty
        - size

    fulfilled by vector, deque and list as an example
*/


TEST(stack, constructor)
{
    // default constructor - uses vector internally
    stack<int> s1;

    // default constructor with container argument as deque
    stack<int, std::deque<int>> s2;
   
    // default constructor with container that doesn't fulfull the requirements
    // but can still be instantiated without errors
    // in C++11 this causes an error at compile time
    // stack<int, std::map<int, int>> s3;
    // s3.push(1); // error: cannot convert the type int to const value_type& in this case
}

TEST(stack, methods)
{
    stack<int> s1;
    stack<int> s2;

    EXPECT_TRUE(s1.empty());
    EXPECT_EQ(s1, s2);

    for (int i = 0; i < VOLUME; ++i)
        s1.push(i);

    EXPECT_FALSE(s1.empty());
    EXPECT_EQ(s1.size(), 100);

    s1.top();
    EXPECT_EQ(s1.size(), VOLUME);

    for (int i = 0; i < VOLUME / 2; ++i)
        s1.pop();

    EXPECT_NE(s1.size(), VOLUME);
    EXPECT_NE(s1, s2);

    // we are popping more than there are in the container
    for (int i = 0; i < VOLUME; ++i)
        s1.pop();

}

