#include <gtest/gtest.h>
#include "my_array.hpp"

TEST(arrayTests, ExplicitConstructor) {
    my_array<int, 5> arr(7);
    for (int i : arr) {
        EXPECT_EQ(i, 7);
    }
}

TEST(arrayTests, InitializerList) {
    my_array<int, 4> arr{1, 2, 3};
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 3);
    EXPECT_EQ(arr[3], 0);
}

TEST(arrayTests, AtMethod) {
    my_array<int, 3> arr{10, 20, 30};
    EXPECT_EQ(arr.at(1), 20);
    EXPECT_EQ(arr.at(2), 30);
}

TEST(arrayTests, AtMethodInvalidIndex) {
    my_array<int, 3> arr{10, 20, 30};
    EXPECT_THROW(arr.at(3), std::out_of_range);
    EXPECT_THROW(arr.at(100), std::out_of_range);
}

TEST(arrayTests, FrontBackMethods) {
    my_array<int, 4> arr{4, 3, 2, 1};
    EXPECT_EQ(arr.front(), 4);
    EXPECT_EQ(arr.back(), 1);
}

TEST(arrayTests, FillMethod) {
    my_array<int, 6> arr(0);
    arr.fill(5);
    for (int i : arr) {
        EXPECT_EQ(i, 5);
    }
}

TEST(arrayTests, SwapMethod) {
    my_array<int, 3> arr1{1, 2, 3};
    my_array<int, 3> arr2{4, 5, 6};
    arr1.swap(arr2);
    EXPECT_EQ(arr1[0], 4);
    EXPECT_EQ(arr1[1], 5);
    EXPECT_EQ(arr1[2], 6);
    EXPECT_EQ(arr2[0], 1);
    EXPECT_EQ(arr2[1], 2);
    EXPECT_EQ(arr2[2], 3);
}

TEST(arrayTests, IteratorFunctionality) {
    my_array<int, 4> arr{10, 20, 30, 40};
    int expected[] = {10, 20, 30, 40};
    size_t index = 0;
    for (auto it = arr.begin(); it != arr.end(); ++it) {
        EXPECT_EQ(*it, expected[index]);
        ++index;
    }
}

TEST(arrayTests, RelationalOperators) {
    my_array<int, 3> arr1{1, 2, 3};
    my_array<int, 3> arr2{1, 2, 3};
    my_array<int, 3> arr3{1, 2, 4};
    my_array<int, 3> arr4{2, 3, 4};

    EXPECT_TRUE(arr1 == arr2);
    EXPECT_FALSE(arr1 != arr2);

    EXPECT_TRUE(arr1 < arr3);
    EXPECT_TRUE(arr1 <= arr3);
    EXPECT_FALSE(arr1 > arr3);
    EXPECT_FALSE(arr1 >= arr3);

    EXPECT_TRUE(arr4 > arr3);
    EXPECT_TRUE(arr4 >= arr3);
    EXPECT_FALSE(arr4 < arr3);
    EXPECT_FALSE(arr4 <= arr3);
}

TEST(arrayTests, IsEmptyTest) {
    my_array<int, 0> arr{};
    EXPECT_TRUE(arr.is_empty());
}

TEST(arrayDoubleTests, ExplicitConstructor) {
    my_array<double, 5> arr(3.14);
    for (double i : arr) {
        EXPECT_DOUBLE_EQ(i, 3.14);
    }
}

TEST(arrayTests, ReverseIterationNonConst) {
    my_array<int, 5> array{};
    array[0] = 1;
    array[1] = 2;
    array[2] = 3;
    array[3] = 4;
    array[4] = 5;

    std::vector<int> expected = {5, 4, 3, 2, 1};
    std::vector<int> result;
    for (auto it = array.rbegin(); it != array.rend(); ++it) {
        result.push_back(*it);
    }
    EXPECT_EQ(expected, result);
}

TEST(arrayDoubleTests, InitializerListConstructor_ExactSize) {
    my_array<double, 3> arr{1.1, 2.2, 3.3, 4.4};
    EXPECT_DOUBLE_EQ(arr[0], 1.1);
    EXPECT_DOUBLE_EQ(arr[1], 2.2);
    EXPECT_DOUBLE_EQ(arr[2], 3.3);
    EXPECT_DOUBLE_EQ(arr[3], 4.4);
}

TEST(arrayDoubleTests, FillMethod) {
    my_array<double, 6> arr(0.0);
    arr.fill(9.9);
    for (double i : arr) {
        EXPECT_DOUBLE_EQ(i, 9.9);
    }
}


int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}