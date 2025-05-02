#include <gtest/gtest.h>
#include <algorithm>
#include <vector>

#include "../vector.hpp"

TEST(vector, constructor)
{
    // scope for redefinition with different types
    {
        ft::vector<int> v1;
        EXPECT_TRUE(v1.empty());
        EXPECT_EQ(v1.capacity(), 0);


        ft::vector<int> v2(17);
        EXPECT_FALSE(v2.empty());
        EXPECT_EQ(v2.size(), 17);
        EXPECT_EQ(v2[0], 0);


        ft::vector<int> v3(11, 42);
        EXPECT_FALSE(v3.empty());
        EXPECT_EQ(v3.size(), 11);
        EXPECT_EQ(v3[0], 42);


        ft::vector<int> v4(v2);
        EXPECT_FALSE(v4.empty());
        EXPECT_EQ(v4.size(), 17);
        EXPECT_EQ(v4[0], 0);


        ft::vector<int> v5 = v3;
        EXPECT_FALSE(v5.empty());
        EXPECT_EQ(v5.size(), 11);
        EXPECT_EQ(v5[0], 42);


        ft::vector<int> v6;
        for (int i = 0; i < 10; ++i)
            v6.push_back(i * 2);


        EXPECT_FALSE(v6.empty());
        EXPECT_EQ(v6.size(), 10);
        EXPECT_EQ(v6[3], 6);


        ft::vector<int> v7(v6.begin(), v6.end());
        EXPECT_FALSE(v7.empty());
        EXPECT_EQ(v7.size(), 10);
        EXPECT_EQ(v7[3], 6);
    }

    {
        ft::vector<std::string> v1;
        EXPECT_TRUE(v1.empty());
        EXPECT_EQ(v1.capacity(), 0);


        ft::vector<std::string> v2(17);
        EXPECT_FALSE(v2.empty());
        EXPECT_EQ(v2.size(), 17);
        EXPECT_EQ(v2[0], std::string());


        ft::vector<std::string> v3(11, "42");
        EXPECT_FALSE(v3.empty());
        EXPECT_EQ(v3.size(), 11);
        EXPECT_EQ(v3[7], "42");


        ft::vector<std::string> v4(v2);
        EXPECT_FALSE(v4.empty());
        EXPECT_EQ(v4.size(), 17);
        EXPECT_EQ(v4[0], std::string());


        ft::vector<std::string> v5 = v3;
        EXPECT_FALSE(v5.empty());
        EXPECT_EQ(v5.size(), 11);
        EXPECT_EQ(v5[7], "42");


        ft::vector<std::string> v6;
        for (int i = 0; i < 10; ++i)
            v6.push_back(std::to_string(i * 2));

        EXPECT_FALSE(v6.empty());
        EXPECT_EQ(v6.size(), 10);
        EXPECT_EQ(v6[3], "6");

        ft::vector<std::string> v7(v6.begin(), v6.end());
        EXPECT_FALSE(v7.empty());
        EXPECT_EQ(v7.size(), 10);
        EXPECT_EQ(v7[3], "6");
    }
}

TEST(vector, iterator)
{
    ft::vector<int> v1;
    EXPECT_FALSE(v1.begin() != v1.end());
    EXPECT_GE(v1.begin(), v1.end());
    EXPECT_LE(v1.begin(), v1.end());

    // use resize instead?
    for (int i = 0; i < 9; ++i)
        v1.push_back(i);

    EXPECT_TRUE(v1.begin() != v1.end());
    EXPECT_GE(v1.end(), v1.begin());
    EXPECT_LE(v1.begin(), v1.end());


    ft::vector<int>::iterator it = v1.begin();
    for (ft::vector<int>::iterator end = v1.end(); it != end - 1; ++it)
        EXPECT_LT(*it, *(it + 1));

    // the iterators themselves cannot be compared
    // but their values still inform us that they point to the right data
    ft::vector<int>::reverse_iterator rit = v1.rbegin();
    EXPECT_EQ(*it, *rit);
    // the iterators are located on opposite ends of the vector
    EXPECT_NE(*(v1.begin()), *rit);


    for (ft::vector<int>::reverse_iterator rend = v1.rend(); rit != rend - 1; ++rit)
        EXPECT_GT(*rit, *(rit + 1));


    ft::vector<int>::size_type size = 0;
    for (ft::vector<int>::const_iterator it1 = v1.begin(); it1 != v1.end(); it1 = it1 + 3, ++size)
        ;
    EXPECT_TRUE(size == v1.size() / 3);
    

    // no issue with casting from non-const to const
    ft::vector<int>::const_iterator cit = it;
    EXPECT_EQ(*it, *cit);


    // this initialized the reverse iterator at the same position
    // as the normal iterator (in this case at the beginning)
    // iterating from beginning to end would result in nothing
    // *r2 == *(v1.begin())
    // *(++r2) -> unexpected because out of bounds
    ft::vector<int>::reverse_iterator r2(v1.begin());

    
    ft::vector<int> v2;
    ft::vector<int>::iterator it2 = v2.begin();
    EXPECT_NE(v1.begin(), it2);
}

TEST(vector, assign)
{
    std::vector<int> v1;

    v1.assign(10, 42);
    EXPECT_EQ(v1.size(), 10);
    EXPECT_EQ(v1[7], 42);


    v1.assign(14, 42);
    EXPECT_EQ(v1.size(), 14);
    EXPECT_EQ(v1[7], 42);

    int cap = v1.capacity();

    v1.assign(1, 1);
    EXPECT_EQ(v1.size(), 1);
    EXPECT_EQ(v1.capacity(), cap);
    // I don't know if this should work but the original behaves equally
    EXPECT_EQ(v1[7], 42);
    

    v1.assign(0, 7);
    EXPECT_EQ(v1.size(), 0);
    EXPECT_TRUE(v1.empty());
    EXPECT_EQ(v1[0], 1);
    EXPECT_EQ(v1[1], 42);


    // cannot use assign with std containers
    // but should be possible no matter what
    std::vector<int> s1;
    for (int i = 0; i < 100; ++i)
        s1.push_back(i);


    // one could think that it appends the objects to the end of the
    // array but this is not the case
    ft::vector<int> v2;
    v2.assign(s1.begin(), s1.end());
    EXPECT_EQ(v2.size(), s1.size());

    v2.assign(s1.begin(), s1.begin() + 3);
    EXPECT_NE(v2.size(), s1.size());

    v2.assign(s1.end(), s1.end());
    EXPECT_TRUE(v2.empty());
}

TEST(vector, insert)
{
    ft::vector<int> v1;

    v1.insert(v1.begin(), 1);
    v1.insert(v1.begin(), 2);
    v1.insert(v1.begin(), 3);
    EXPECT_EQ(v1[0], 3);

    v1.insert(v1.end(), 4);
    EXPECT_EQ(v1[3], 4);

    v1.insert(v1.end() - 1, 5, 42);
    EXPECT_EQ(v1[3], 42);

    ft::vector<int> v2(2, 13);
    v1.insert(v1.begin() + 1, v2.begin(), v2.end());
    EXPECT_EQ(v1[1], 13);
    EXPECT_EQ(v1[3], 2);
}

TEST(vector, erase)
{
    ft::vector<int> v1;

    for (int i = 0; i < 10; ++i)
        v1.push_back(i);

    v1.erase(v1.begin() + 5);
    EXPECT_EQ(v1.size(), 9);
    EXPECT_EQ(v1[5], 6);

    v1.erase(v1.begin());
    EXPECT_EQ(v1[0], 1);

    v1.erase(v1.begin() + 2, v1.end() - 2);
    EXPECT_EQ(v1.size(), 4);

    while (!v1.empty())
        v1.erase(v1.begin());

    EXPECT_TRUE(v1.empty());
}

TEST(vector, push_and_pop)
{
    ft::vector<int> v1;

    EXPECT_TRUE(v1.empty());
    EXPECT_EQ(v1.capacity(), 0);

    for (int i = 0; i < 100; ++i)
        v1.push_back(i);

    EXPECT_EQ(v1.size(), 100);
    EXPECT_GE(v1.capacity(), 100);

    v1.pop_back();
    EXPECT_EQ(v1.size() + 1, 100);

    while (!v1.empty())
        v1.pop_back();

    EXPECT_TRUE(v1.empty());

    // this causes an infinite loop but shouldn't
    // v1.pop_back();
}

TEST(vector, clear)
{
    ft::vector<int> v1;
    EXPECT_TRUE(v1.empty());

    v1.assign(100, 22);
    EXPECT_FALSE(v1.empty());

    v1.clear();
    EXPECT_TRUE(v1.empty());
    EXPECT_EQ(v1.size(), 0);
    EXPECT_TRUE(v1.capacity() != 0);

    v1.clear();
}

TEST(vector, resize)
{
	ft::vector<int> v1;

	v1.resize(3, 3);
    EXPECT_FALSE(v1.empty());
    EXPECT_EQ(v1.size(), 3);
    EXPECT_EQ(v1[0], 3);

    int cap = v1.capacity();

	v1.resize(5, 5);
    EXPECT_EQ(v1.size(), 5);
    EXPECT_EQ(v1[0], 3);
    EXPECT_EQ(v1[3], 5);
    EXPECT_GE(v1.capacity(), cap);

	v1.resize(8);
    EXPECT_EQ(v1[7], 0);

	v1.resize(0);
    EXPECT_TRUE(v1.empty());
    EXPECT_NE(v1.capacity(), 0);
}

TEST(vector, reserve)
{
    ft::vector<int> v1;

    for (int i = 0; i < 7; ++i)
        v1.push_back(i);

    v1.reserve(1);
    EXPECT_EQ(v1.size(), 7);
    EXPECT_GE(v1.capacity(), 7);

    v1.reserve(13);
    EXPECT_EQ(v1.size(), 7);
    EXPECT_GT(v1.capacity(), 7);
}

TEST(vector, access)
{
    ft::vector<int> v1;

    for (int i = 0; i < 100; ++i)
        v1.push_back(i);

    EXPECT_EQ(v1.at(17), 17);
    EXPECT_EQ(v1.at(87), 87);
    EXPECT_EQ(v1[22], 22);
    EXPECT_EQ(v1.at(43), v1[43]);

    ASSERT_THROW(v1.at(100), std::out_of_range);
}

TEST(vector, swap)
{
    ft::vector<int> v1(17, 22);
    ft::vector<int> v2(9, 8);

    EXPECT_EQ(v1.size(), 17);
    EXPECT_EQ(v2.size(), 9);


    v1.swap(v2);

    EXPECT_EQ(v1.size(), 9);
    EXPECT_EQ(v2.size(), 17);
    EXPECT_EQ(v1[0], 8);
    EXPECT_EQ(v2[0], 22);

    v2.swap(v1);
    EXPECT_EQ(v1.size(), 17);
    EXPECT_EQ(v2.size(), 9);
}


/* comparisons follow the rule of lexicographical compare */
TEST(vector, comparisons)
{
    ft::vector<int> v1(10, 1);
    ft::vector<int> v2(10, 1);

    EXPECT_TRUE(v1 == v2);
    EXPECT_FALSE(v1 != v2);
    EXPECT_FALSE(v1 < v2);
    EXPECT_TRUE(v1 <= v2);
    EXPECT_FALSE(v1 > v2);
    EXPECT_TRUE(v1 >= v2);


    v2[9] = 2;
    EXPECT_FALSE(v1 == v2);
    EXPECT_TRUE(v1 != v2);
    EXPECT_TRUE(v1 < v2);
    EXPECT_TRUE(v1 <= v2);
    EXPECT_FALSE(v1 > v2);
    EXPECT_FALSE(v1 >= v2);


    v2.pop_back();
    EXPECT_FALSE(v1 == v2);
    EXPECT_TRUE(v1 != v2);
    EXPECT_FALSE(v1 < v2);
    EXPECT_FALSE(v1 <= v2);
    EXPECT_TRUE(v1 > v2);
    EXPECT_TRUE(v1 >= v2);

    v1[1] = 0;
    EXPECT_FALSE(v1 == v2);
    EXPECT_TRUE(v1 != v2);
    EXPECT_TRUE(v1 < v2);
    EXPECT_TRUE(v1 <= v2);
    EXPECT_FALSE(v1 > v2);
    EXPECT_FALSE(v1 >= v2);
}