#include <gtest/gtest.h>
#include "my_vector.hpp"


TEST(vectorTests, ExplicitConstructor) {
    my_vector<double> a{1.1, 3.14, 5.5};
    EXPECT_EQ(a[0], 1.1);
    EXPECT_EQ(a[1], 3.14);
    EXPECT_EQ(a[2], 5.5);
    EXPECT_EQ(a.size(), 3);
}

TEST(vectorTests, DefaultConstructor) {
    my_vector<int> a;
    EXPECT_EQ(a.size(), 0);
}

TEST(vectorTests, ConstructorIterator) {
    std::vector<int> a{10, 11, 12, 13, 14, 15};
    my_vector<int> b{a.begin(), a.end()};
    for (size_t i = 0; i < a.size(); ++i) {
        EXPECT_EQ(a[i], b[i]);
    }
    EXPECT_EQ(a.size(), b.size());
}

TEST(vectorTests, InitializerList) {
    my_vector<std::string> a{"Hello", "google", "tests", "how", "are", "you"};
    EXPECT_EQ(a.size(), 6);
    EXPECT_EQ(a[0], "Hello");
    EXPECT_EQ(a[1], "google");
    EXPECT_EQ(a[2], "tests");
    EXPECT_EQ(a[3], "how");
    EXPECT_EQ(a[4], "are");
    EXPECT_EQ(a[5], "you");
}

TEST(vectorTests, CopyAssignment) {
    my_vector<int> a = {1, 2, 3};
    my_vector b = a;
    EXPECT_EQ(a, b);
}


TEST(vectorTests, AtThrow) {
    my_vector<int> arr{10, 20, 30};
    EXPECT_THROW(arr.at(3), std::out_of_range);
    EXPECT_THROW(arr.at(100), std::out_of_range);
}

TEST(vectorTests, AtMethod) {
    my_vector<int> arr{10, 20, 30};
    EXPECT_EQ(arr.at(1), 20);
    EXPECT_EQ(arr.at(2), 30);
}

TEST(vectorTests, IsEmptyTest) {
    my_vector<int> arr;
    ASSERT_TRUE(arr.is_empty());
}

TEST(vectorTests, SwapMethod) {
    my_vector<int> v1{1, 2, 3};
    my_vector<int> v2{4, 5, 6};
    v1.swap(v2);
    EXPECT_EQ(v1[0], 4);
    EXPECT_EQ(v1[1], 5);
    EXPECT_EQ(v1[2], 6);
    EXPECT_EQ(v2[0], 1);
    EXPECT_EQ(v2[1], 2);
    EXPECT_EQ(v2[2], 3);
    EXPECT_EQ(v1.size(), v2.size());
}


TEST(vectorTests, ReserveTest) {
    my_vector<int> v1;
    EXPECT_EQ(v1.size(), 0);
    EXPECT_EQ(v1.capacity(), 0);
    v1.reserve(500);
    EXPECT_EQ(v1.size(), 0);
    EXPECT_EQ(v1.capacity(), 500);
}


TEST(vectorTests, ShrinkToFit) {
    my_vector<int> v1{1,2,3,4,5};
    EXPECT_EQ(v1.size(), 5);
    EXPECT_EQ(v1.capacity(), 10);
    v1.shrink_to_fit();
    EXPECT_EQ(v1.size(), 5);
    EXPECT_EQ(v1.capacity(), 5);
}

TEST(vectorTests, Clear) {
    my_vector<float> v1{3.14f, 3.15f, 3.16f};
    EXPECT_EQ(v1.size(), 3);
    EXPECT_EQ(v1.capacity(), 6);
    v1.clear();
    EXPECT_EQ(v1.size(), 0);
    EXPECT_EQ(v1.capacity(), 6);
}

TEST(vectorTests, Resize) {
    my_vector<int> v1{1, 2, 3};
    EXPECT_EQ(v1.size(), 3);
    EXPECT_EQ(v1.capacity(), 6);
    v1.resize(10, 15);
    EXPECT_EQ(v1.size(), 10);
    EXPECT_EQ(v1.capacity(), 20);
    for (size_t i = 3; i < 10; ++i) {
        EXPECT_EQ(v1[i], 15);
    }
    EXPECT_EQ(v1[0], 1);
    EXPECT_EQ(v1[1], 2);
    EXPECT_EQ(v1[2], 3);
}

TEST(vectorTests, InsertSingleElement) {
    my_vector<int> v{10, 20, 30, 40};
    int* it = v.insert(v.begin(), 5);
    EXPECT_EQ(*it, 5);
    EXPECT_EQ(v[0], 5);
    EXPECT_EQ(v.size(), 5);

    it = v.insert(v.begin() + 3, 99);
    EXPECT_EQ(*it, 99);
    EXPECT_EQ(v[3], 99);
    EXPECT_EQ(v.size(), 6);

    it = v.insert(v.end(), 100);
    EXPECT_EQ(*it, 100);
    EXPECT_EQ(v[v.size()-1], 100);
    EXPECT_EQ(v.size(), 7);
}

TEST(vectorTests, InsertSingleElementReallocation) {
    my_vector<int> v;
    v.reserve(1);
    EXPECT_EQ(v.capacity(), 1);
    EXPECT_EQ(v.size(), 0);

    int* it = v.insert(v.begin(), 10);
    EXPECT_EQ(*it, 10);
    EXPECT_EQ(v.size(), 1);
    EXPECT_EQ(v.capacity(), 1);

    it = v.insert(v.end(), 20);
    EXPECT_EQ(*it, 20);
    EXPECT_EQ(v.size(), 2);
    EXPECT_EQ(v.capacity(), 2);

    it = v.insert(v.begin() + 1, 30);
    EXPECT_EQ(*it, 30);
    EXPECT_EQ(v.size(), 3);
    EXPECT_EQ(v.capacity(), 4);
    EXPECT_EQ(v[0], 10);
    EXPECT_EQ(v[1], 30);
    EXPECT_EQ(v[2], 20);
}

TEST(vectorTests, InsertRangeElements) {
    my_vector<int> v{10, 20, 30, 40};
    int arr[] = {100, 200, 300};

    v.insert(v.begin(), arr, arr + 3);
    EXPECT_EQ(v.size(), 7);
    EXPECT_EQ(v[0], 100);
    EXPECT_EQ(v[1], 200);
    EXPECT_EQ(v[2], 300);
    EXPECT_EQ(v[3], 10);
    EXPECT_EQ(v[4], 20);
    EXPECT_EQ(v[5], 30);
    EXPECT_EQ(v[6], 40);

    int arr2[] = {111, 222};
    v.insert(v.begin() + 4, arr2, arr2 + 2);
    EXPECT_EQ(v.size(), 9);
    EXPECT_EQ(v[0], 100);
    EXPECT_EQ(v[1], 200);
    EXPECT_EQ(v[2], 300);
    EXPECT_EQ(v[3], 10);
    EXPECT_EQ(v[4], 111);
    EXPECT_EQ(v[5], 222);
    EXPECT_EQ(v[6], 20);
    EXPECT_EQ(v[7], 30);
    EXPECT_EQ(v[8], 40);

    int arr3[] = {777, 888};
    v.insert(v.end(), arr3, arr3 + 2);
    EXPECT_EQ(v.size(), 11);
    EXPECT_EQ(v[9], 777);
    EXPECT_EQ(v[10], 888);
}

TEST(vectorTests, InsertRangeElementsReallocation) {
    my_vector<int> v{1, 2};
    EXPECT_EQ(v.size(), 2);

    int arr[] = {4, 5};
    v.insert(v.begin() + 1, arr, arr + 2);
    EXPECT_EQ(v.size(), 4);
    EXPECT_EQ(v.capacity(), 8);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 4);
    EXPECT_EQ(v[2], 5);
    EXPECT_EQ(v[3], 2);
}

TEST(vectorTests, InsertRangeElementsReallocation2) {
    my_vector<int> v{1, 2};
    EXPECT_EQ(v.size(), 2);

    int arr[] = {4, 5, 6, 7, 8, 9, 10, 11, 12};
    v.insert(v.begin() + 1, arr, arr + 9);
    EXPECT_EQ(v.size(), 11);
    EXPECT_EQ(v.capacity(), 22);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 4);
    EXPECT_EQ(v[2], 5);
    EXPECT_EQ(v[3], 6);
    EXPECT_EQ(v[4], 7);
    EXPECT_EQ(v[5], 8);
    EXPECT_EQ(v[6], 9);
    EXPECT_EQ(v[7], 10);
    EXPECT_EQ(v[8], 11);
    EXPECT_EQ(v[9], 12);
    EXPECT_EQ(v[10], 2);
}



TEST(vectorTests, EraseSingleElementMiddle) {
    my_vector<int> v{1, 2, 3, 4, 5};
    auto it = v.erase(2);
    EXPECT_EQ(v.size(), 4);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 4);
    EXPECT_EQ(v[3], 5);
    EXPECT_EQ(*it, 4);
}

TEST(vectorTests, EraseSingleElementBeginning) {
    my_vector<int> v{10, 20, 30, 40};
    auto it = v.erase(0);
    EXPECT_EQ(v.size(), 3);
    EXPECT_EQ(v[0], 20);
    EXPECT_EQ(v[1], 30);
    EXPECT_EQ(v[2], 40);
    EXPECT_EQ(*it, 20);
}

TEST(vectorTests, EraseSingleElementEnd) {
    my_vector<int> v{100, 200, 300};
    auto it = v.erase(2);
    EXPECT_EQ(v.size(), 2);
    EXPECT_EQ(v[0], 100);
    EXPECT_EQ(v[1], 200);
    EXPECT_EQ(it, v.end());
}

TEST(vectorTests, EraseRangeMiddle) {
    my_vector<int> v{10, 20, 30, 40, 50, 60, 70};
    auto it = v.erase(v.begin() + 2, v.begin() + 4);
    EXPECT_EQ(v.size(), 5);
    EXPECT_EQ(v[0], 10);
    EXPECT_EQ(v[1], 20);
    EXPECT_EQ(v[2], 50);
    EXPECT_EQ(v[3], 60);
    EXPECT_EQ(v[4], 70);
    EXPECT_EQ(*it, 50);
}

TEST(vectorTests, EraseRangeBeginning) {
    my_vector<int> v{5, 10, 15, 20, 25};
    auto it = v.erase(v.begin(), v.begin() + 2);
    EXPECT_EQ(v.size(), 3);
    EXPECT_EQ(v[0], 15);
    EXPECT_EQ(v[1], 20);
    EXPECT_EQ(v[2], 25);
    EXPECT_EQ(*it, 15);
}

TEST(vectorTests, EraseRangeEnd) {
    my_vector<int> v{7, 14, 21, 28, 35};
    auto it = v.erase(v.begin() + 3, v.end());
    EXPECT_EQ(v.size(), 3);
    EXPECT_EQ(v[0], 7);
    EXPECT_EQ(v[1], 14);
    EXPECT_EQ(v[2], 21);
    EXPECT_EQ(it, v.end());
}

TEST(vectorTests, EraseRangeFullVector) {
    my_vector<int> v{1, 2, 3, 4};
    auto it = v.erase(v.begin(), v.end());
    EXPECT_EQ(v.size(), 0);
    EXPECT_EQ(it, v.begin());
}

TEST(vectorTests, PopBack) {
    my_vector<int> v{17, 25, 44};
    v.pop_back();
    EXPECT_EQ(v.size(), 2);
    EXPECT_EQ(v[0], 17);
    EXPECT_EQ(v[1], 25);
}

TEST(vectorTests, PopBackToTheEnd) {
    my_vector<int> v{17, 25, 44};
    v.pop_back();
    v.pop_back();
    v.pop_back();
    EXPECT_EQ(v.size(), 0);
}

TEST(vectorTests, PushBack) {
    my_vector<int> v{17, 25, 44};
    v.push_back(5);
    v.push_back(6);
    v.push_back(7);
    v.push_back(8);

    EXPECT_EQ(v.size(), 7);
    EXPECT_EQ(v[0], 17);
    EXPECT_EQ(v[1], 25);
    EXPECT_EQ(v[2], 44);
    EXPECT_EQ(v[3], 5);
    EXPECT_EQ(v[4], 6);
    EXPECT_EQ(v[5], 7);
    EXPECT_EQ(v[6], 8);
}

TEST(vectorTests, EmplaceBackAddsElement) {
    my_vector<int> v;
    EXPECT_EQ(v.size(), 0);

    v.emplace_back(10);
    EXPECT_EQ(v.size(), 1);
    EXPECT_EQ(v[0], 10);

    v.emplace_back(20);
    EXPECT_EQ(v.size(), 2);
    EXPECT_EQ(v[1], 20);
}

TEST(vectorTests, ReverseIterationNonConst) {
    my_vector<int> vec{};
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(5);
    std::vector<int> expected = {5, 4, 3, 2, 1};
    std::vector<int> result;
    for (auto it = vec.rbegin(); it != vec.rend(); ++it) {
        result.push_back(*it);
    }
    EXPECT_EQ(expected, result);
}

TEST(vectorTests, EqualityOperatorTrue) {
    my_vector<int> a{1, 2, 3};
    my_vector<int> b{1, 2, 3};
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
}

TEST(vectorTests, EqualityOperatorFalseDifferentElements) {
    my_vector<int> a{1, 2, 3};
    my_vector<int> b{1, 2, 4};
    EXPECT_FALSE(a == b);
    EXPECT_TRUE(a != b);
}

TEST(vectorTests, LessThanOperator_True) {
    my_vector<int> a{1, 2, 3};
    my_vector<int> b{1, 2, 4};
    EXPECT_TRUE(a < b);
    EXPECT_FALSE(a >= b);
}

TEST(vectorTests, LessThanOperator_FalseWhenGreater) {
    my_vector<int> a{2, 5, 6};
    my_vector<int> b{2, 5, 5};
    EXPECT_FALSE(a < b);
    EXPECT_TRUE(a > b);
}

TEST(vectorTests, ShorterVectorIsLessWhenPrefix) {
    my_vector<int> a{1, 2, 3};
    my_vector<int> b{1, 2};
    EXPECT_TRUE(b < a);
    EXPECT_FALSE(b > a);
    EXPECT_TRUE(b <= a);
    EXPECT_FALSE(b >= a);
}

TEST(vectorTests, GreaterThanOrEqual) {
    my_vector<int> a{5, 5, 5};
    my_vector<int> b{5, 5, 4};
    EXPECT_TRUE(a >= b);
    EXPECT_TRUE(a > b);
    EXPECT_FALSE(a <= b);
    EXPECT_FALSE(a < b);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}