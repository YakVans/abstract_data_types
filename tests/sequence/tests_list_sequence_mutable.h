#pragma once
#include "doctest.h"

#include "list_sequence.h"
#include "example_func.h"

TEST_CASE("test_list_sequence_mutable_constructor") {
    MutableListSequence<int> seq1;
    CHECK(seq1.GetLength() == 0);

    int values[] = {4, 0, 56, -2, 9};
    MutableListSequence<int> seq3(values, 5);
    CHECK(seq3.GetLength() == 5);
    for (int i = 0; i < 5; i++) {
        CHECK(seq3.Get(i) == values[i]);
    }

    MutableListSequence<int> seq4(seq3);
    CHECK(seq4.GetLength() == 5);
    for (int i = 0; i < 5; i++) {
        CHECK(seq4.Get(i) == values[i]);
    }
}

TEST_CASE("test_list_sequence_mutable_copy_independence") {
    int values[] = {4, 0, 56, -2, 9};
    MutableListSequence<int> seq1(values, 5);
    MutableListSequence<int> seq2(seq1);
    seq1.Set(2, 14);
    CHECK(seq2.Get(2) == 56);
}

TEST_CASE("test_list_sequence_mutable_getter") {
    int values[] = {4, 0, 56, -2, 9};
    MutableListSequence<int> seq(values, 5);

    CHECK(seq.GetLength() == 5);
    CHECK(seq.GetFirst() == 4);
    CHECK(seq.GetLast() == 9);
    for (int i = 0; i < 5; i++) {
        CHECK(seq.Get(i) == values[i]);
    }
    CHECK_THROWS_AS(seq.Get(5), IndexOutOfRange);
    CHECK_THROWS_AS(seq.Get(10), IndexOutOfRange);

    MutableListSequence<int> empty_seq;
    CHECK(empty_seq.GetLength() == 0);
    CHECK_THROWS_AS(empty_seq.GetFirst(), IndexOutOfRange);
    CHECK_THROWS_AS(empty_seq.GetLast(), IndexOutOfRange);
    CHECK_THROWS_AS(empty_seq.Get(0), IndexOutOfRange);
}

TEST_CASE("test_list_sequence_mutable_get_subsequence") {
    int values[] = {4, 0, 56, -2, 9};
    MutableListSequence<int> seq(values, 5);

    ListSequence<int> *sub_seq = seq.GetSubSequence(1, 4);
    CHECK(sub_seq->GetLength() == 3);
    for (int i = 0; i < 3; i++) {
        CHECK(sub_seq->Get(i) == values[i + 1]);
    }
    delete(sub_seq);

    ListSequence<int> *single_seq = seq.GetSubSequence(1, 2);
    CHECK(single_seq->GetLength() == 1);
    CHECK(single_seq->Get(0) == values[1]);
    delete(single_seq);

    CHECK_THROWS_AS(seq.GetSubSequence(1, 8), IndexOutOfRange);
    CHECK_THROWS_AS(seq.GetSubSequence(8, 1), IndexOutOfRange);
    CHECK_THROWS_AS(seq.GetSubSequence(3, 1), InvalidRange);

    MutableListSequence<int> empty_seq;
    CHECK_THROWS_AS(empty_seq.GetSubSequence(0, 0), IndexOutOfRange);
}


TEST_CASE("test_list_sequence_mutable_set") {
    int values[] = {4, 0, 56, -2, 9};
    int values1[] = {-12, 13, 21, -2, 9};
    MutableListSequence<int> seq(values1, 5);
    for (int i = 1; i < 4; i++) {
        seq.Set(i, values[i]);
    }
    for (int i = 1; i < 4; i++) {
        CHECK(seq.Get(i) == values[i]);
    }
    CHECK_THROWS_AS(seq.Set(5, 3), IndexOutOfRange);
    CHECK_THROWS_AS(seq.Set(10, 3), IndexOutOfRange);
}

TEST_CASE("test_list_sequence_mutable_append") {
    MutableListSequence<int> seq;

    seq.Append(-3);
    CHECK(seq.GetLength() == 1);
    CHECK(seq.Get(0) == -3);
    CHECK(seq.GetFirst() == -3);
    CHECK(seq.GetLast() == -3);

    seq.Append(56);
    CHECK(seq.GetLength() == 2);
    CHECK(seq.Get(0) == -3);
    CHECK(seq.Get(1) == 56);
    CHECK(seq.GetFirst() == -3);
    CHECK(seq.GetLast() == 56);
}

TEST_CASE("test_list_sequence_mutable_prepend") {
    MutableListSequence<int> seq;

    seq.Prepend(-3);
    CHECK(seq.GetLength() == 1);
    CHECK(seq.Get(0) == -3);
    CHECK(seq.GetFirst() == -3);
    CHECK(seq.GetLast() == -3);

    seq.Prepend(56);
    CHECK(seq.GetLength() == 2);
    CHECK(seq.Get(0) == 56);
    CHECK(seq.Get(1) == -3);
    CHECK(seq.GetFirst() == 56);
    CHECK(seq.GetLast() == -3);
}

TEST_CASE("test_list_sequence_mutable_insert_at") {
    int values[] = {4, 0, 56, -2, 9};
    MutableListSequence<int> seq;

    seq.InsertAt(0, 0);
    CHECK(seq.GetLength() == 1);
    CHECK(seq.Get(0) == values[1]);

    seq.InsertAt(1, 56);
    CHECK(seq.GetLength() == 2);
    CHECK(seq.Get(0) == values[1]);
    CHECK(seq.Get(1) == values[2]);

    seq.InsertAt(2, 9);
    CHECK(seq.GetLength() == 3);
    CHECK(seq.Get(0) == values[1]);
    CHECK(seq.Get(1) == values[2]);
    CHECK(seq.Get(2) == values[4]);

    seq.InsertAt(2, -2);
    CHECK(seq.GetLength() == 4);
    CHECK(seq.Get(0) == values[1]);
    CHECK(seq.Get(1) == values[2]);
    CHECK(seq.Get(2) == values[3]);
    CHECK(seq.Get(3) == values[4]);

    seq.InsertAt(0, 4);
    CHECK(seq.GetLength() == 5);
    for (int i = 0; i < 5; i++) {
        CHECK(seq.Get(i) == values[i]);
    }

    CHECK_THROWS_AS(seq.InsertAt(8, -3), IndexOutOfRange);
}

TEST_CASE("test_list_sequence_mutable_remove_at") {
    int values[] = {4, 0, 56, -2, 9};
    MutableListSequence<int> seq(values, 5);
    
    CHECK_THROWS_AS(seq.RemoveAt(5), IndexOutOfRange);
    CHECK_THROWS_AS(seq.RemoveAt(8), IndexOutOfRange);

    seq.RemoveAt(0);
    CHECK(seq.GetLength() == 4);
    CHECK(seq.Get(0) == values[1]);
    CHECK(seq.Get(1) == values[2]);
    CHECK(seq.Get(2) == values[3]);
    CHECK(seq.Get(3) == values[4]);

    seq.RemoveAt(3);
    CHECK(seq.GetLength() == 3);
    CHECK(seq.Get(0) == values[1]);
    CHECK(seq.Get(1) == values[2]);
    CHECK(seq.Get(2) == values[3]);

    seq.RemoveAt(1);
    CHECK(seq.GetLength() == 2);
    CHECK(seq.Get(0) == values[1]);
    CHECK(seq.Get(1) == values[3]);

    seq.RemoveAt(1);
    CHECK(seq.GetLength() == 1);
    CHECK(seq.Get(0) == values[1]);

    seq.RemoveAt(0);
    CHECK(seq.GetLength() == 0);
    
    CHECK_THROWS_AS(seq.RemoveAt(0), IndexOutOfRange);
}

TEST_CASE("test_list_sequence_mutable_concat_in_place") {
    int values1[] = {4, 0, 56, -2, 9};
    int values2[] = {42, -5, 3, 1};
    MutableListSequence<int> seq1(values1, 5);
    MutableListSequence<int> seq2(values2, 4);


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
    

    MutableListSequence<int> empty_seq;

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

TEST_CASE("test_list_sequence_mutable_concat_in_place_with_self") {
    int values1[] = {4, 0, 56, -2, 9};
    MutableListSequence<int> seq1(values1, 5);

    seq1.Concat(seq1);

    CHECK(seq1.GetLength() == 10);
    for (int i = 0; i < 5; i++) {
        CHECK(seq1.Get(i) == values1[i]);
        CHECK(seq1.Get(i + 5) == values1[i]);
    }

    MutableListSequence<int> empty_seq;

    empty_seq.Concat(empty_seq);

    CHECK(empty_seq.GetLength() == 0);
}

TEST_CASE("test_list_sequence_map_where_reduce") {
    int values[] = {4, 0, 56, -2, 9};
    MutableListSequence<int> arr(values, 5);

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

TEST_CASE("test_list_sequence_call_chaining") {
    int values[] = {4, 0, 56, -2, 9};
    MutableListSequence<int> arr(values, 5);

    CHECK(arr.Map(map_example1)->Where(where_example1)->Reduce(reduce_example1, -1) == 8 * 112 * 18 * (-1));
}