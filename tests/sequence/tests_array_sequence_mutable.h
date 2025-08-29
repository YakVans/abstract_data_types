#pragma once
#include "doctest.h"

#include "array_sequence.h"
#include "example_func.h"

TEST_CASE("test_array_sequence_mutable_constructor") {
    MutableArraySequence<int> arr1;
    CHECK(arr1.GetLength() == 0);

    MutableArraySequence<int> arr2(7);
    CHECK(arr2.GetLength() == 0);

    int values[] = {4, 0, 56, -2, 9};
    MutableArraySequence<int> arr3(values, 5);
    CHECK(arr3.GetLength() == 5);
    for (int i = 0; i < 5; i++) {
        CHECK(arr3.Get(i) == values[i]);
    }

    MutableArraySequence<int> arr4(arr3);
    CHECK(arr4.GetLength() == 5);
    for (int i = 0; i < 5; i++) {
        CHECK(arr4.Get(i) == values[i]);
    }
}

TEST_CASE("test_array_sequence_mutable_copy_independence") {
    int values[] = {4, 0, 56, -2, 9};
    MutableArraySequence<int> arr1(values, 5);
    MutableArraySequence<int> arr2(arr1);
    arr1.Set(2, 14);
    CHECK(arr2.Get(2) == 56);
}

TEST_CASE("test_array_sequence_mutable_getter") {
    int values[] = {4, 0, 56, -2, 9};
    MutableArraySequence<int> arr(values, 5);

    CHECK(arr.GetLength() == 5);
    CHECK(arr.GetFirst() == 4);
    CHECK(arr.GetLast() == 9);
    for (int i = 0; i < 5; i++) {
        CHECK(arr.Get(i) == values[i]);
    }
    CHECK_THROWS_AS(arr.Get(5), IndexOutOfRange);
    CHECK_THROWS_AS(arr.Get(10), IndexOutOfRange);

    MutableArraySequence<int> empty_arr;
    CHECK(empty_arr.GetLength() == 0);
    CHECK_THROWS_AS(empty_arr.GetFirst(), IndexOutOfRange);
    CHECK_THROWS_AS(empty_arr.GetLast(), IndexOutOfRange);
    CHECK_THROWS_AS(empty_arr.Get(0), IndexOutOfRange);
}

TEST_CASE("test_array_sequence_mutable_get_subarray") {
    int values[] = {4, 0, 56, -2, 9};
    MutableArraySequence<int> arr(values, 5);

    ArraySequence<int> *sub_arr = arr.GetSubSequence(1, 4);
    CHECK(sub_arr->GetLength() == 3);
    for (int i = 0; i < 3; i++) {
        CHECK(sub_arr->Get(i) == values[i + 1]);
    }
    delete(sub_arr);

    ArraySequence<int> *single_arr = arr.GetSubSequence(1, 2);
    CHECK(single_arr->GetLength() == 1);
    CHECK(single_arr->Get(0) == values[1]);
    delete(single_arr);

    CHECK_THROWS_AS(arr.GetSubSequence(1, 8), IndexOutOfRange);
    CHECK_THROWS_AS(arr.GetSubSequence(8, 1), IndexOutOfRange);
    CHECK_THROWS_AS(arr.GetSubSequence(3, 1), InvalidRange);

    MutableArraySequence<int> empty_arr;
    CHECK_THROWS_AS(empty_arr.GetSubSequence(0, 0), IndexOutOfRange);
}


TEST_CASE("test_array_sequence_mutable_set") {
    int values[] = {4, 0, 56, -2, 9};
    int init_values[] = {0, 0, 0, 0, 0};
    MutableArraySequence<int> arr(init_values, 5);
    for (int i = 1; i < 4; i++) {
        arr.Set(i, values[i]);
    }
    for (int i = 1; i < 4; i++) {
        CHECK(arr.Get(i) == values[i]);
    }
    CHECK_THROWS_AS(arr.Set(5, 3), IndexOutOfRange);
    CHECK_THROWS_AS(arr.Set(10, 3), IndexOutOfRange);
}

TEST_CASE("test_array_sequence_mutable_append") {
    MutableArraySequence<int> arr;

    arr.Append(-3);
    CHECK(arr.GetLength() == 1);
    CHECK(arr.Get(0) == -3);
    CHECK(arr.GetFirst() == -3);
    CHECK(arr.GetLast() == -3);

    arr.Append(56);
    CHECK(arr.GetLength() == 2);
    CHECK(arr.Get(0) == -3);
    CHECK(arr.Get(1) == 56);
    CHECK(arr.GetFirst() == -3);
    CHECK(arr.GetLast() == 56);
}

TEST_CASE("test_array_sequence_mutable_prepend") {
    MutableArraySequence<int> arr;

    arr.Prepend(-3);
    CHECK(arr.GetLength() == 1);
    CHECK(arr.Get(0) == -3);
    CHECK(arr.GetFirst() == -3);
    CHECK(arr.GetLast() == -3);

    arr.Prepend(56);
    CHECK(arr.GetLength() == 2);
    CHECK(arr.Get(0) == 56);
    CHECK(arr.Get(1) == -3);
    CHECK(arr.GetFirst() == 56);
    CHECK(arr.GetLast() == -3);
}

TEST_CASE("test_array_sequence_mutable_insert_at") {
    int values[] = {4, 0, 56, -2, 9};
    MutableArraySequence<int> arr;

    arr.InsertAt(0, 0);
    CHECK(arr.GetLength() == 1);
    CHECK(arr.Get(0) == values[1]);

    arr.InsertAt(1, 56);
    CHECK(arr.GetLength() == 2);
    CHECK(arr.Get(0) == values[1]);
    CHECK(arr.Get(1) == values[2]);

    arr.InsertAt(2, 9);
    CHECK(arr.GetLength() == 3);
    CHECK(arr.Get(0) == values[1]);
    CHECK(arr.Get(1) == values[2]);
    CHECK(arr.Get(2) == values[4]);

    arr.InsertAt(2, -2);
    CHECK(arr.GetLength() == 4);
    CHECK(arr.Get(0) == values[1]);
    CHECK(arr.Get(1) == values[2]);
    CHECK(arr.Get(2) == values[3]);
    CHECK(arr.Get(3) == values[4]);

    arr.InsertAt(0, 4);
    CHECK(arr.GetLength() == 5);
    for (int i = 0; i < 5; i++) {
        CHECK(arr.Get(i) == values[i]);
    }

    CHECK_THROWS_AS(arr.InsertAt(8, -3), IndexOutOfRange);
}

TEST_CASE("test_array_sequence_mutable_remove_at") {
    int values[] = {4, 0, 56, -2, 9};
    MutableArraySequence<int> arr(values, 5);
    
    CHECK_THROWS_AS(arr.RemoveAt(5), IndexOutOfRange);
    CHECK_THROWS_AS(arr.RemoveAt(8), IndexOutOfRange);

    arr.RemoveAt(0);
    CHECK(arr.GetLength() == 4);
    CHECK(arr.Get(0) == values[1]);
    CHECK(arr.Get(1) == values[2]);
    CHECK(arr.Get(2) == values[3]);
    CHECK(arr.Get(3) == values[4]);

    arr.RemoveAt(3);
    CHECK(arr.GetLength() == 3);
    CHECK(arr.Get(0) == values[1]);
    CHECK(arr.Get(1) == values[2]);
    CHECK(arr.Get(2) == values[3]);

    arr.RemoveAt(1);
    CHECK(arr.GetLength() == 2);
    CHECK(arr.Get(0) == values[1]);
    CHECK(arr.Get(1) == values[3]);

    arr.RemoveAt(1);
    CHECK(arr.GetLength() == 1);
    CHECK(arr.Get(0) == values[1]);

    arr.RemoveAt(0);
    CHECK(arr.GetLength() == 0);
    
    CHECK_THROWS_AS(arr.RemoveAt(0), IndexOutOfRange);
}


TEST_CASE("test_array_sequence_mutable_concat_in_place") {
    int values1[] = {4, 0, 56, -2, 9};
    int values2[] = {42, -5, 3, 1};
    MutableArraySequence<int> seq1(values1, 5);
    MutableArraySequence<int> seq2(values2, 4);


    seq1.Concat(seq2);

    CHECK(seq1.GetLength() == 9);
    for (int i = 0; i < 5; i++) {
        CHECK(seq1.Get(i) == values1[i]);
    }

    CHECK(seq2.GetLength() == 4);
    for (int i = 0; i < 4; i++) {
        CHECK(seq1.Get(i + 5) == values2[i]);
        CHECK(seq2.Get(i) == values2[i]);
    }
    CHECK(seq1.GetLast() == values2[3]);
    

    MutableArraySequence<int> empty_seq;

    seq2.Concat(empty_seq);

    CHECK(seq2.GetLength() == 4);
    for (int i = 0; i < 4; i++) {
        CHECK(seq2.Get(i) == values2[i]);
    }
    CHECK(empty_seq.GetLength() == 0);

    empty_seq.Concat(seq2);

    CHECK(empty_seq.GetLength() == 4);
    for (int i = 0; i < 4; i++) {
        CHECK(empty_seq.Get(i) == values2[i]);
        CHECK(seq2.Get(i) == values2[i]);
    }
}

TEST_CASE("test_array_sequence_mutable_concat_in_place_with_self") {
    int values1[] = {4, 0, 56, -2, 9};
    MutableArraySequence<int> seq1(values1, 5);

    seq1.Concat(seq1);

    CHECK(seq1.GetLength() == 10);
    for (int i = 0; i < 5; i++) {
        CHECK(seq1.Get(i) == values1[i]);
        CHECK(seq1.Get(i + 5) == values1[i]);
    }

    MutableArraySequence<int> empty_seq;

    empty_seq.Concat(empty_seq);

    CHECK(empty_seq.GetLength() == 0);
}

TEST_CASE("test_array_sequence_map_where_reduce") {
    int values[] = {4, 0, 56, -2, 9};
    MutableArraySequence<int> arr(values, 5);

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

TEST_CASE("test_array_sequence_call_chaining") {
    int values[] = {4, 0, 56, -2, 9};
    MutableArraySequence<int> arr(values, 5);

    CHECK(arr.Map(map_example1)->Where(where_example1)->Reduce(reduce_example1, -1) == 8 * 112 * 18 * (-1));
}