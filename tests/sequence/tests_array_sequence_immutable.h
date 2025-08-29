#pragma once
#include "doctest.h"

#include "array_sequence.h"
#include "example_func.h"

TEST_CASE("test_array_sequence_immutable_constructor") {
    ImmutableArraySequence<int> arr1;
    CHECK(arr1.GetLength() == 0);

    ImmutableArraySequence<int> arr2(7);
    CHECK(arr2.GetLength() == 0);

    int values[] = {4, 0, 56, -2, 9};
    ImmutableArraySequence<int> arr3(values, 5);
    CHECK(arr3.GetLength() == 5);
    for (int i = 0; i < 5; i++) {
        CHECK(arr3.Get(i) == values[i]);
    }

    ImmutableArraySequence<int> arr4(arr3);
    CHECK(arr4.GetLength() == 5);
    for (int i = 0; i < 5; i++) {
        CHECK(arr4.Get(i) == values[i]);
    }
}

TEST_CASE("test_array_sequence_immutable_getter") {
    int values[] = {4, 0, 56, -2, 9};
    ImmutableArraySequence<int> arr(values, 5);

    CHECK(arr.GetLength() == 5);
    CHECK(arr.GetFirst() == 4);
    CHECK(arr.GetLast() == 9);
    for (int i = 0; i < 5; i++) {
        CHECK(arr.Get(i) == values[i]);
    }
    CHECK_THROWS_AS(arr.Get(5), IndexOutOfRange);
    CHECK_THROWS_AS(arr.Get(10), IndexOutOfRange);

    ImmutableArraySequence<int> empty_arr;
    CHECK(empty_arr.GetLength() == 0);
    CHECK_THROWS_AS(empty_arr.GetFirst(), IndexOutOfRange);
    CHECK_THROWS_AS(empty_arr.GetLast(), IndexOutOfRange);
    CHECK_THROWS_AS(empty_arr.Get(0), IndexOutOfRange);
}

TEST_CASE("test_array_sequence_immutable_get_subarray") {
    int values[] = {4, 0, 56, -2, 9};
    ImmutableArraySequence<int> arr(values, 5);

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

    ImmutableArraySequence<int> empty_arr;
    CHECK_THROWS_AS(empty_arr.GetSubSequence(0, 0), IndexOutOfRange);
}

TEST_CASE("test_array_sequence_immutable_set") {
    int values[] = {4, 0, 56, -2, 9};
    int values1[] = {-12, 13, 21, -2, 9};

    ImmutableArraySequence<int> arr1(values, 5);

    ArraySequence<int> *arr2 = arr1.Set(0, -12);

    ArraySequence<int> *arr3 = arr2->Set(2, 21);
    
    ArraySequence<int> *arr4 = arr3->Set(1, 13);
    
    for (int i = 1; i < 4; i++) {
        CHECK(arr4->Get(i) == values1[i]);
    }
    delete(arr2);
    delete(arr3);
    delete(arr4);

    CHECK_THROWS_AS(arr1.Set(5, 3), IndexOutOfRange);
    CHECK_THROWS_AS(arr1.Set(10, 3), IndexOutOfRange);
}

TEST_CASE("test_array_sequence_immutable_append") {
    ImmutableArraySequence<int> arr;

    ArraySequence<int> *arr1 = arr.Append(-3);
    CHECK(arr1->GetLength() == 1);
    CHECK(arr1->Get(0) == -3);
    CHECK(arr1->GetFirst() == -3);
    CHECK(arr1->GetLast() == -3);

    ArraySequence<int> *arr2 = arr1->Append(56);
    CHECK(arr2->GetLength() == 2);
    CHECK(arr2->Get(0) == -3);
    CHECK(arr2->Get(1) == 56);
    CHECK(arr2->GetFirst() == -3);
    CHECK(arr2->GetLast() == 56);
    
    delete(arr1);
    delete(arr2);
}

TEST_CASE("test_array_sequence_immutable_prepend") {
    ImmutableArraySequence<int> arr;

    ArraySequence<int> *arr1 = arr.Prepend(-3);
    CHECK(arr1->GetLength() == 1);
    CHECK(arr1->Get(0) == -3);
    CHECK(arr1->GetFirst() == -3);
    CHECK(arr1->GetLast() == -3);

    ArraySequence<int> *arr2 = arr1->Prepend(56);
    CHECK(arr2->GetLength() == 2);
    CHECK(arr2->Get(0) == 56);
    CHECK(arr2->Get(1) == -3);
    CHECK(arr2->GetFirst() == 56);
    CHECK(arr2->GetLast() == -3);

    delete(arr1);
    delete(arr2);
}

TEST_CASE("test_array_sequence_immutable_insert_at") {
    int values[] = {4, 0, 56, -2, 9};
    ImmutableArraySequence<int> arr;

    ArraySequence<int> *arr1 = arr.InsertAt(0, 0);
    CHECK(arr1->GetLength() == 1);
    CHECK(arr1->Get(0) == values[1]);

    ArraySequence<int> *arr2 = arr1->InsertAt(1, 56);
    CHECK(arr2->GetLength() == 2);
    CHECK(arr2->Get(0) == values[1]);
    CHECK(arr2->Get(1) == values[2]);

    ArraySequence<int> *arr3 = arr2->InsertAt(2, 9);
    CHECK(arr3->GetLength() == 3);
    CHECK(arr3->Get(0) == values[1]);
    CHECK(arr3->Get(1) == values[2]);
    CHECK(arr3->Get(2) == values[4]);

    ArraySequence<int> *arr4 = arr3->InsertAt(2, -2);
    CHECK(arr4->GetLength() == 4);
    CHECK(arr4->Get(0) == values[1]);
    CHECK(arr4->Get(1) == values[2]);
    CHECK(arr4->Get(2) == values[3]);
    CHECK(arr4->Get(3) == values[4]);

    ArraySequence<int> *arr5 = arr4->InsertAt(0, 4);
    CHECK(arr5->GetLength() == 5);
    for (int i = 0; i < 5; i++) {
        CHECK(arr5->Get(i) == values[i]);
    }

    CHECK_THROWS_AS(arr5->InsertAt(8, -3), IndexOutOfRange);

    delete(arr1);
    delete(arr2);
    delete(arr3);
    delete(arr4);
    delete(arr5);
}

TEST_CASE("test_array_sequence_immutable_remove_at") {
    int values[] = {4, 0, 56, -2, 9};
    ImmutableArraySequence<int> arr(values, 5);
    
    CHECK_THROWS_AS(arr.RemoveAt(5), IndexOutOfRange);
    CHECK_THROWS_AS(arr.RemoveAt(8), IndexOutOfRange);

    ArraySequence<int> *arr1 = arr.RemoveAt(0);
    CHECK(arr1->GetLength() == 4);
    CHECK(arr1->Get(0) == values[1]);
    CHECK(arr1->Get(1) == values[2]);
    CHECK(arr1->Get(2) == values[3]);
    CHECK(arr1->Get(3) == values[4]);

    ArraySequence<int> *arr2= arr1->RemoveAt(3);
    CHECK(arr2->GetLength() == 3);
    CHECK(arr2->Get(0) == values[1]);
    CHECK(arr2->Get(1) == values[2]);
    CHECK(arr2->Get(2) == values[3]);

    ArraySequence<int> *arr3 = arr2->RemoveAt(1);
    CHECK(arr3->GetLength() == 2);
    CHECK(arr3->Get(0) == values[1]);
    CHECK(arr3->Get(1) == values[3]);

    ArraySequence<int> *arr4 = arr3->RemoveAt(1);
    CHECK(arr4->GetLength() == 1);
    CHECK(arr4->Get(0) == values[1]);

    ArraySequence<int> *arr5 = arr4->RemoveAt(0);
    CHECK(arr5->GetLength() == 0);
    
    CHECK_THROWS_AS(arr5->RemoveAt(0), IndexOutOfRange);
    
    delete(arr1);
    delete(arr2);
    delete(arr3);
    delete(arr4);
    delete(arr5);
}

TEST_CASE("test_array_sequence_immutable_concat") {
    int values1[] = {4, 0, 56, -2, 9};
    int values2[] = {42, -5, 3, 1};
    ImmutableArraySequence<int> seq1(values1, 5);
    ImmutableArraySequence<int> seq2(values2, 4);


    ArraySequence<int> *seq3 = seq1.Concat(seq2);

    CHECK(seq3->GetLength() == 9);
    CHECK(seq1.GetLength() == 5);
    for (int i = 0; i < 5; i++) {
        CHECK(seq3->Get(i) == values1[i]);
    }

    CHECK(seq2.GetLength() == 4);
    for (int i = 0; i < 4; i++) {
        CHECK(seq3->Get(i + 5) == values2[i]);
    }
    CHECK(seq3->GetLast() == values2[3]);
    delete(seq3);
    

    ImmutableArraySequence<int> empty_seq;

    ArraySequence<int> *seq4 = seq2.Concat(empty_seq);

    CHECK(seq4->GetLength() == 4);
    for (int i = 0; i < 4; i++) {
        CHECK(seq4->Get(i) == values2[i]);
    }
    delete(seq4);

    
    ArraySequence<int> *seq5 = empty_seq.Concat(seq2);

    CHECK(seq5->GetLength() == 4);
    for (int i = 0; i < 4; i++) {
        CHECK(seq5->Get(i) == values2[i]);
    }
    delete(seq5);
}

TEST_CASE("test_array_sequence_map_where_reduce") {
    int values[] = {4, 0, 56, -2, 9};
    ImmutableArraySequence<int> seq(values, 5);

    int map_values[] = {8, 0, 112, -4, 18};
    ArraySequence<int> *seq1 = seq.Map(map_example1);
    for (int i = 0; i < 5; i++) {
        CHECK(seq1->Get(i) == map_values[i]);
    }

    int where_values[] = {8, 112, 18};
    ArraySequence<int> *seq2 = seq1->Where(where_example1);
    
    for (int i = 0; i < 3; i++) {
        CHECK(seq2->Get(i) == where_values[i]);
    }

    CHECK(seq2->Reduce(reduce_example1, -1) == 8 * 112 * 18 * (-1));

    delete seq1;
    delete seq2;
}
