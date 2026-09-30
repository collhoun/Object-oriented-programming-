#include "lab01/array_ops.hpp"

#include <gtest/gtest.h>

// ---------------------------------------------------------------------
// array_create
// ---------------------------------------------------------------------

TEST(ArrayCreate, ZeroMemeryCreate) {
    int* arr = array_create(5);

    ASSERT_NE(arr, nullptr);

    for (std::size_t i = 0; i < 5; i++) {
        EXPECT_EQ(arr[i], 0);
    }

    array_delete(arr);
}

// ---------------------------------------------------------------------
// array_delete
// ---------------------------------------------------------------------

TEST(ArrayDelete, CheckPointerNullPtr) {
    int* arr = array_create(3);
    array_delete(arr);

    EXPECT_EQ(arr, nullptr);
}

// ---------------------------------------------------------------------
// array_resize
// ---------------------------------------------------------------------

TEST(ArrayResize, AllValuesNoNewValues) {
    int* arr = array_create(3);
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;

    arr = array_resize(arr, 3, 5);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 3);
    EXPECT_EQ(arr[3], 0);
    EXPECT_EQ(arr[4], 0);

    array_delete(arr);
}

TEST(ArrayResize, ShrinkAndKeepFirstsElemts) {
    int* arr = array_create(5);
    for (int i = 0; i < 5; i++) {
        arr[i] = i + 1;
    }
    arr = array_resize(arr, 5, 3);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 3);

    array_delete(arr);
}

TEST(ArrayResize, SameSizeResize) {
    int* arr = array_create(5);
    int* original_pointer = arr;
    for (int i = 0; i < 5; i++) {
        arr[i] = i + 1;
    }
    arr = array_resize(arr, 5, 5);
    EXPECT_EQ(arr, original_pointer);
    array_delete(arr);
}

TEST(ArrayResize, ShrinkToZeroSize) {
    int* arr = array_create(5);
    for (int i = 0; i < 5; i++) {
        arr[i] = i + 1;
    }
    arr = array_resize(arr, 0, 5);
    EXPECT_NE(arr, nullptr);
    array_delete(arr);
}

// ---------------------------------------------------------------------
// array_insert
// ---------------------------------------------------------------------

TEST(ArrayInsert, InsertInBeginning) {
    int* arr = array_create(5);
    std::size_t size{5};
    for (int i = 0; i < 5; i++) {
        arr[i] = i + 1;
    }
    arr = array_insert(arr, size, 0, 99);
    EXPECT_EQ(arr[0], 99);
    for (int i = 1; i < 5; i++) {
        EXPECT_EQ(arr[i], i);
    }
    array_delete(arr);
}

TEST(ArrayInsert, InsertsInMiddle) {
    int* arr = array_create(3);
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;
    std::size_t size = 3;

    arr = array_insert(arr, size, 1, 99);

    ASSERT_EQ(size, 4u);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 99);
    EXPECT_EQ(arr[2], 2);
    EXPECT_EQ(arr[3], 3);

    array_delete(arr);
}

TEST(ArrayInsert, InsertsAtEndWhenPosEqualsSize) {
    int* arr = array_create(2);
    arr[0] = 1;
    arr[1] = 2;
    std::size_t size = 2;

    arr = array_insert(arr, size, 2, 3);

    ASSERT_EQ(size, 3u);
    EXPECT_EQ(arr[2], 3);

    array_delete(arr);
}

TEST(ArrayInsert, InvalidPosDoesNotModifyArray) {
    int* arr = array_create(2);
    arr[0] = 1;
    arr[1] = 2;
    std::size_t size = 2;

    arr = array_insert(arr, size, 10, 99);

    EXPECT_EQ(size, 2u);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);

    array_delete(arr);
}

// ---------------------------------------------------------------------
// array_remove
// ---------------------------------------------------------------------

TEST(ArrayRemove, RemovesFromMiddle) {
    int* arr = array_create(3);
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;
    std::size_t size = 3;

    arr = array_remove(arr, size, 1);

    ASSERT_EQ(size, 2u);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 3);

    array_delete(arr);
}

TEST(ArrayRemove, RemovingLastElementLeavesNullptr) {
    int* arr = array_create(1);
    arr[0] = 42;
    std::size_t size = 1;

    arr = array_remove(arr, size, 0);

    EXPECT_EQ(size, 0u);
    EXPECT_EQ(arr, nullptr);
}

TEST(ArrayRemove, InvalidPosDoesNotModifyArray) {
    int* arr = array_create(2);
    arr[0] = 1;
    arr[1] = 2;
    std::size_t size = 2;

    arr = array_remove(arr, size, 5);

    EXPECT_EQ(size, 2u);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);

    array_delete(arr);
}

// ---------------------------------------------------------------------
// array_kth_smallest
// ---------------------------------------------------------------------

TEST(KthSmallest, ExampleFromManual) {
    // {4, 2, 7, 1, 9, 3}, k=3 -> 3
    int* arr = array_create(6);
    int values[] = {4, 2, 7, 1, 9, 3};
    for (std::size_t i = 0; i < 6; i++) {
        arr[i] = values[i];
    }

    int result = array_kth_smallest(arr, 6, 3);

    EXPECT_EQ(result, 3);

    array_delete(arr);
}

TEST(KthSmallest, FirstAndLastElement) {
    int* arr = array_create(5);
    int values[] = {5, 3, 1, 4, 2};
    for (std::size_t i = 0; i < 5; i++) {
        arr[i] = values[i];
    }

    EXPECT_EQ(array_kth_smallest(arr, 5, 1), 1);
    EXPECT_EQ(array_kth_smallest(arr, 5, 5), 5);

    array_delete(arr);
}

TEST(KthSmallest, SingleElementArray) {
    int* arr = array_create(1);
    arr[0] = 7;

    EXPECT_EQ(array_kth_smallest(arr, 1, 1), 7);

    array_delete(arr);
}

TEST(KthSmallest, KZeroReturnsZero) {
    int* arr = array_create(3);
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;

    EXPECT_EQ(array_kth_smallest(arr, 3, 0), 0);

    array_delete(arr);
}

TEST(KthSmallest, KGreaterThanSizeReturnsZero) {
    int* arr = array_create(3);
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;

    EXPECT_EQ(array_kth_smallest(arr, 3, 10), 0);

    array_delete(arr);
}

TEST(KthSmallest, EmptyArrayReturnsZero) {
    int* arr = nullptr;

    EXPECT_EQ(array_kth_smallest(arr, 0, 1), 0);
}

TEST(KthSmallest, OriginalArrayNotMutated) {
    int* arr = array_create(4);
    int values[] = {3, 1, 4, 2};
    for (std::size_t i = 0; i < 4; i++) {
        arr[i] = values[i];
    }

    array_kth_smallest(arr, 4, 2);

    EXPECT_EQ(arr[0], 3);
    EXPECT_EQ(arr[1], 1);
    EXPECT_EQ(arr[2], 4);
    EXPECT_EQ(arr[3], 2);

    array_delete(arr);
}