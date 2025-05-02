#include <gtest/gtest.h>
#include <utility>
#include <algorithm>
#include <iterator>

#include "../utility.hpp"

/*
    Consider to let you implementations inherit from the standard implementation,
    this allows you to compare both classes with one another.
    Alternatively you can implement the comparisons as friend functions
    but it creates overhead and should be removed after testing.


    You can instantiate the pair with more complex objects e.G.
    vector, map and self created objects.
*/

TEST(pair, pair)
{
    
    ft::pair<int, int> p1;
    std::pair<int, int> p1_std;

    EXPECT_EQ(p1.first, 0);
    EXPECT_EQ(p1.second, 0);
    EXPECT_EQ(p1.first, p1_std.first);
    EXPECT_EQ(p1.second, p1_std.second);


    ft::pair<int, int> p2(1, 2);
    ft::pair<int, int> p3(p2);
    std::pair<int, int> p2_std(1, 2);

    EXPECT_EQ(p2.first, 1);
    EXPECT_EQ(p2.second, 2);

    EXPECT_EQ(p2.first, p2_std.first);
    EXPECT_EQ(p2.second, p2_std.second);
    EXPECT_EQ(p3.first, p2_std.first);
    EXPECT_EQ(p3.second, p2_std.second);
    EXPECT_EQ(p3, p2);


    ft::pair<int, int> p4;

    EXPECT_NE(p4, p2);
    p4 = p2;
    EXPECT_EQ(p4, p2);



    // ft::pair<std::string, std::vector<int>> entries;
    // ft::pair<bool, int *> search_result;

}