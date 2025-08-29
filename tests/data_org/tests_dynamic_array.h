#pragma once
#include "doctest.h"

#include "exceptions.h"
#include "dynamic_array.h"
#include "example_func.h"

TEST_CASE("test_dynamic_array_constructor") {
    DynamicArray<int> arr1;
    CHECK(arr1.GetSize() == 0);

    DynamicArray<int> arr2(7);
    CHECK(arr2.GetSize() == 0);

    int values[] = {4, 0, 56, -2, 9};
    DynamicArray<int> arr3(values, 5);
    CHECK(arr3.GetSize() == 5);
    for (int i = 0; i < 5; i++) {
        CHECK(arr3.Get(i) == values[i]);
    }

    DynamicArray<int> arr4(arr3);
    CHECK(arr4.GetSize() == 5);
    for (int i = 0; i < 5; i++) {
        CHECK(arr4.Get(i) == values[i]);
    }
}

TEST_CASE("test_dynamic_array_copy_independence") {
    int values[] = {4, 0, 56, -2, 9};
    DynamicArray<int> arr1(values, 5);
    DynamicArray<int> arr2(arr1);
    arr1.Set(2, 14);
    CHECK(arr2.Get(2) == 56);
}

TEST_CASE("test_dynamic_array_getter") {
    int values[] = {4, 0, 56, -2, 9};
    DynamicArray<int> arr(values, 5);
    CHECK(arr.GetSize() == 5);
    for (int i = 0; i < 5; i++) {
        CHECK(arr.Get(i) == values[i]);
    }
    CHECK_THROWS_AS(arr.Get(5), IndexOutOfRange);
    CHECK_THROWS_AS(arr.Get(10), IndexOutOfRange);
}

TEST_CASE("test_dynamic_array_get_subarray") {
    int values[] = {4, 0, 56, -2, 9};
    DynamicArray<int> arr(values, 5);

    DynamicArray<int> *sub_arr = arr.GetSubArray(1, 4);
    CHECK(sub_arr->GetSize() == 3);
    for (int i = 0; i < 3; i++) {
        CHECK(sub_arr->Get(i) == values[i + 1]);
    }
    delete(sub_arr);

    DynamicArray<int> *single_arr = arr.GetSubArray(1, 2);
    CHECK(single_arr->GetSize() == 1);
    CHECK(single_arr->Get(0) == values[1]);
    delete(single_arr);

    CHECK_THROWS_AS(arr.GetSubArray(1, 8), IndexOutOfRange);
    CHECK_THROWS_AS(arr.GetSubArray(8, 1), IndexOutOfRange);
    CHECK_THROWS_AS(arr.GetSubArray(3, 1), InvalidRange);

    DynamicArray<int> empty_arr;
    CHECK_THROWS_AS(empty_arr.GetSubArray(0, 0), IndexOutOfRange);
}

TEST_CASE("test_dynamic_array_set") {
    int values[] = {4, 0, 56, -2, 9};
    int init_values[] = {0, 0, 0, 0, 0};
    DynamicArray<int> arr(init_values, 5);
    for (int i = 1; i < 4; i++) {
        arr.Set(i, values[i]);
    }
    for (int i = 1; i < 4; i++) {
        CHECK(arr.Get(i) == values[i]);
    }
    CHECK_THROWS_AS(arr.Set(5, 3), IndexOutOfRange);
    CHECK_THROWS_AS(arr.Set(10, 3), IndexOutOfRange);
}

TEST_CASE("test_dynamic_array_resize") {
    int values[] = {4, 0, 56, -2, 9};
    DynamicArray<int> arr(values, 5);

    arr.Resize(8);
    CHECK(arr.GetSize() == 5);
    for (int i = 0; i < 5; i++) {
        CHECK(arr.Get(i) == values[i]);
    }

    arr.Resize(3);
    CHECK(arr.GetSize() == 3);
    for (int i = 0; i < 3; i++) {
        CHECK(arr.Get(i) == values[i]);
    }
    CHECK_THROWS_AS(arr.Get(3), IndexOutOfRange);

    arr.Resize(0);
    CHECK(arr.GetSize() == 0);
    CHECK_THROWS_AS(arr.Get(0), IndexOutOfRange);
}

TEST_CASE("test_dynamic_array_insert_at") {
    int values[] = {4, 0, 56, -2, 9};
    DynamicArray<int> arr;

    arr.InsertAt(0, 0);
    CHECK(arr.GetSize() == 1);
    CHECK(arr.Get(0) == values[1]);

    arr.InsertAt(1, 56);
    CHECK(arr.GetSize() == 2);
    CHECK(arr.Get(0) == values[1]);
    CHECK(arr.Get(1) == values[2]);

    arr.InsertAt(2, 9);
    CHECK(arr.GetSize() == 3);
    CHECK(arr.Get(0) == values[1]);
    CHECK(arr.Get(1) == values[2]);
    CHECK(arr.Get(2) == values[4]);

    arr.InsertAt(2, -2);
    CHECK(arr.GetSize() == 4);
    CHECK(arr.Get(0) == values[1]);
    CHECK(arr.Get(1) == values[2]);
    CHECK(arr.Get(2) == values[3]);
    CHECK(arr.Get(3) == values[4]);

    arr.InsertAt(0, 4);
    CHECK(arr.GetSize() == 5);
    for (int i = 0; i < 5; i++) {
        CHECK(arr.Get(i) == values[i]);
    }

    CHECK_THROWS_AS(arr.InsertAt(8, -3), IndexOutOfRange);
}

TEST_CASE("test_dynamic_array_remove_at") {
    int values[] = {4, 0, 56, -2, 9};
    DynamicArray<int> arr(values, 5);
    
    CHECK_THROWS_AS(arr.RemoveAt(5), IndexOutOfRange);
    CHECK_THROWS_AS(arr.RemoveAt(8), IndexOutOfRange);

    arr.RemoveAt(0);
    CHECK(arr.GetSize() == 4);
    CHECK(arr.Get(0) == values[1]);
    CHECK(arr.Get(1) == values[2]);
    CHECK(arr.Get(2) == values[3]);
    CHECK(arr.Get(3) == values[4]);

    arr.RemoveAt(3);
    CHECK(arr.GetSize() == 3);
    CHECK(arr.Get(0) == values[1]);
    CHECK(arr.Get(1) == values[2]);
    CHECK(arr.Get(2) == values[3]);

    arr.RemoveAt(1);
    CHECK(arr.GetSize() == 2);
    CHECK(arr.Get(0) == values[1]);
    CHECK(arr.Get(1) == values[3]);

    arr.RemoveAt(1);
    CHECK(arr.GetSize() == 1);
    CHECK(arr.Get(0) == values[1]);

    arr.RemoveAt(0);
    CHECK(arr.GetSize() == 0);
    
    CHECK_THROWS_AS(arr.RemoveAt(0), IndexOutOfRange);
}

TEST_CASE("test_dynamic_array_concat_in_place") {
    int values1[] = {4, 0, 56, -2, 9};
    int values2[] = {42, -5, 3, 1};
    DynamicArray<int> arr1(values1, 5);
    DynamicArray<int> arr2(values2, 4);


    arr1.ConcatInPlace(arr2);

    CHECK(arr1.GetSize() == 9);
    for (int i = 0; i < 5; i++) {
        CHECK(arr1.Get(i) == values1[i]);
    }

    CHECK(arr2.GetSize() == 4);
    for (int i = 0; i < 4; i++) {
        CHECK(arr1.Get(i + 5) == values2[i]);
        CHECK(arr2.Get(i) == values2[i]);
    }
    

    DynamicArray<int> empty_arr;

    arr2.ConcatInPlace(empty_arr);

    CHECK(arr2.GetSize() == 4);
    for (int i = 0; i < 4; i++) {
        CHECK(arr2.Get(i) == values2[i]);
    }
    CHECK(empty_arr.GetSize() == 0);

    empty_arr.ConcatInPlace(arr2);

    CHECK(empty_arr.GetSize() == 4);
    for (int i = 0; i < 4; i++) {
        CHECK(empty_arr.Get(i) == values2[i]);
        CHECK(arr2.Get(i) == values2[i]);
    }
}

TEST_CASE("test_dynamic_array_concat_in_place_with_self") {
    int values1[] = {4, 0, 56, -2, 9};
    DynamicArray<int> arr1(values1, 5);

    arr1.ConcatInPlace(arr1);

    CHECK(arr1.GetSize() == 10);
    for (int i = 0; i < 5; i++) {
        CHECK(arr1.Get(i) == values1[i]);
        CHECK(arr1.Get(i + 5) == values1[i]);
    }

    DynamicArray<int> empty_arr;

    empty_arr.ConcatInPlace(empty_arr);

    CHECK(empty_arr.GetSize() == 0);
}

TEST_CASE("test_dynamic_array_map_where_reduce") {
    int values[] = {4, 0, 56, -2, 9};
    DynamicArray<int> arr(values, 5);

    int map_values[] = {8, 0, 112, -4, 18};
    arr.Map(map_example1);
    for (int i = 0; i < 5; i++) {
        CHECK(arr.Get(i) == map_values[i]);
    }

    int where_values[] = {8, 112, 18};
    arr.Where(where_example1);
    for (int i = 0; i < 3; i++) {
        CHECK(arr.Get(i) == where_values[i]);
    }

    CHECK(arr.Reduce(reduce_example1, -1) == 8 * 112 * 18 * (-1));
}

TEST_CASE("test_dynamic_array_call_chaining") {
    int values[] = {4, 0, 56, -2, 9};
    DynamicArray<int> arr(values, 5);

    CHECK(arr.Map(map_example1)->Where(where_example1)->Reduce(reduce_example1, -1) == 8 * 112 * 18 * (-1));
}

TEST_CASE("test_dynamic_array_is_subarray") {
    int values[] = {4, 0, 56, -2, 9};
    int start_values[] = {4, 0, 56};
    int end_values[] = {9};
    int wrong_values[] = {4, 0, 51};
    int larger_values[] = {4, 0, 56, -2, 9, 1};

    DynamicArray<int> arr(values, 5);
    DynamicArray<int> start_arr(start_values, 3);
    DynamicArray<int> end_arr(end_values, 1);
    DynamicArray<int> wrong_arr(wrong_values, 3);
    DynamicArray<int> empty_arr(values, 0);
    DynamicArray<int> larger_arr(larger_values, 6);

    CHECK(arr.IsSubArray(&start_arr) == true);
    CHECK(arr.IsSubArray(&end_arr) == true);
    CHECK(arr.IsSubArray(&wrong_arr) == false);
    CHECK(arr.IsSubArray(&empty_arr) == true);
    CHECK(empty_arr.IsSubArray(&empty_arr) == true);
    CHECK(arr.IsSubArray(&larger_arr) == false);
}

TEST_CASE("test_dynamic_array_count_inversions") {
    int values1[] = {1, 2, 3, 4, 5};
    DynamicArray<int> arr1(values1, 5);
    CHECK(arr1.CountInversions() == 0);

    int values2[] = {1, 3, 2, 4, 5};
    DynamicArray<int> arr2(values2, 5);
    CHECK(arr2.CountInversions() == 1);

    int values3[] = {5, 4, 3, 2, 1};
    DynamicArray<int> arr3(values3, 5);
    CHECK(arr3.CountInversions() == 10);

    DynamicArray<int> arr4;
    CHECK(arr4.CountInversions() == 0);

    int values5[] = {2, 1};
    DynamicArray<int> arr5(values5, 2);
    CHECK(arr5.CountInversions() == 1);

    int values6[] = {1};
    DynamicArray<int> arr6(values6, 1);
    CHECK(arr6.CountInversions() == 0);
}