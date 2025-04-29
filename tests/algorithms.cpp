#include <gtest/gtest.h>
#include <vector>
#include <algorithm>

#include "../algorithm.hpp"


/* 
    I am looking to test the code and am now wondering if I should be comparing
    the results of my implementation with that of the STL.
    With these algorithms being pretty simple, it might be better to just
    test for the correct behaviour as described in the documentation.

    Benchmarking the performance requires to compare both implementations
    at the same time, but the framework is not made for specifically that.
    In addition, the comparison of bigger structures like vectors or maps,
    might be worth being tested against the STL.
*/

TEST(equal, equal)
{
    std::vector<int> v1 = {1, 2, 3, 4};
    std::vector<int> v2 = {1, 2, 3, 4};

    EXPECT_TRUE(std::equal(v1.begin(), v1.end(), v2.begin()));
    EXPECT_TRUE(ft::equal(v1.begin(), v1.end(), v2.begin()));
    EXPECT_EQ(std::equal(v1.begin(), v1.end(), v2.begin()),
              ft::equal(v1.begin(), v1.end(), v2.begin()));


    std::string s1 = "alphabet";
    std::string s2 = "alphabet";
    std::string s3 = "Alphabet";
    std::string s4 = "alpha";

    EXPECT_TRUE(ft::equal(s1.begin(), s1.end(), s2.begin()));
    EXPECT_EQ(ft::equal(s1.begin(), s1.end(), s2.begin()),
              std::equal(s1.begin(), s1.end(), s2.begin()));

    EXPECT_FALSE(ft::equal(s1.begin(), s1.end(), s3.begin()));
    EXPECT_EQ(ft::equal(s1.begin(), s1.end(), s3.begin()),
              std::equal(s1.begin(), s1.end(), s3.begin()));

    EXPECT_FALSE(ft::equal(s1.begin(), s1.end(), s4.begin()));
    EXPECT_EQ(ft::equal(s1.begin(), s1.end(), s4.begin()),
              std::equal(s1.begin(), s1.end(), s4.begin()));


    /*
        It makes no sense to compare fundamental types.
        For the fact, that they don't implement iterators and
        because the comparison is already defined.

        We could compare own classes that offer the iterators
        as well as comparisons for the values.
    */

}


/* compares if the first object is lexicographically less than the second */
TEST(lexicographical_compare, lexicographical_compare)
{
    std::vector<int> v1 = {1, 2, 3};
    std::vector<int> v2 = {1, 2, 4};

    EXPECT_TRUE(ft::lexicographical_compare(v1.begin(), v1.end(),
                                            v2.begin(), v2.end()));
    EXPECT_EQ(std::lexicographical_compare(v1.begin(), v1.end(),
                                           v2.begin(), v2.end()),
              ft::lexicographical_compare(v1.begin(), v1.end(),
                                          v2.begin(), v2.end()));

    

    std::string s1 = "alphabet";
    std::string s2 = "alphabet";
    std::string s3 = "Alphabet";
    std::string s4 = "alpha";


    /* compares if the first argument is less than the second and therefore
        is false */
    EXPECT_FALSE(ft::lexicographical_compare(s1.begin(), s1.end(),
                                            s2.begin(), s2.end()));
    EXPECT_EQ(std::lexicographical_compare(s1.begin(), s1.end(),
                                           s2.begin(), s2.end()),
              ft::lexicographical_compare(s1.begin(), s1.end(),
                                          s2.begin(), s2.end()));

    /* compares if the first argument is lexicographically less than the second
        and in this case isn't */                                      
    EXPECT_FALSE(ft::lexicographical_compare(s1.begin(), s1.end(),
                                            s3.begin(), s3.end()));
    EXPECT_EQ(std::lexicographical_compare(s1.begin(), s1.end(),
                                           s3.begin(), s3.end()),
              ft::lexicographical_compare(s1.begin(), s1.end(),
                                          s3.begin(), s3.end()));


    /* same as above with the arguments reversed */
    EXPECT_TRUE(ft::lexicographical_compare(s3.begin(), s3.end(),
                                            s1.begin(), s1.end()));


    EXPECT_TRUE(ft::lexicographical_compare(s4.begin(), s4.end(),
                                            s1.begin(), s1.end()));
    EXPECT_FALSE(ft::lexicographical_compare(s1.begin(), s1.end(),
                                            s4.begin(), s4.end()));
    EXPECT_EQ(std::lexicographical_compare(s4.begin(), s4.end(),
                                           s1.begin(), s1.end()),
              ft::lexicographical_compare(s4.begin(), s4.end(),
                                          s1.begin(), s1.end()));
}       

