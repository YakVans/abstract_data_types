#pragma once
#include "doctest.h"

#include "doubly_list_sequence.h"
#include "example_func.h"

TEST_CASE("test_doubly_list_sequence_immutable_constructor") {
    ImmutableDoublyListSequence<int> seq1;
    CHECK(seq1.GetLength() == 0);

    int values[] = {4, 0, 56, -2, 9};
    ImmutableDoublyListSequence<int> seq3(values, 5);
    CHECK(seq3.GetLength() == 5);
    for (int i = 0; i < 5; i++) {
        CHECK(seq3.Get(i) == values[i]);
    }

    ImmutableDoublyListSequence<int> seq4(seq3);
    CHECK(seq4.GetLength() == 5);
    for (int i = 0; i < 5; i++) {
        CHECK(seq4.Get(i) == values[i]);
    }
}

TEST_CASE("test_doubly_list_sequence_immutable_getter") {
    int values[] = {4, 0, 56, -2, 9};
    ImmutableDoublyListSequence<int> seq(values, 5);

    CHECK(seq.GetLength() == 5);
    CHECK(seq.GetFirst() == 4);
    CHECK(seq.GetLast() == 9);
    for (int i = 0; i < 5; i++) {
        CHECK(seq.Get(i) == values[i]);
    }
    CHECK_THROWS_AS(seq.Get(5), IndexOutOfRange);
    CHECK_THROWS_AS(seq.Get(10), IndexOutOfRange);

    ImmutableDoublyListSequence<int> empty_seq;
    CHECK(empty_seq.GetLength() == 0);
    CHECK_THROWS_AS(empty_seq.GetFirst(), IndexOutOfRange);
    CHECK_THROWS_AS(empty_seq.GetLast(), IndexOutOfRange);
    CHECK_THROWS_AS(empty_seq.Get(0), IndexOutOfRange);
}

TEST_CASE("test_doubly_list_sequence_immutable_get_subsequence") {
    int values[] = {4, 0, 56, -2, 9};
    ImmutableDoublyListSequence<int> seq(values, 5);

    DoublyListSequence<int> *sub_seq = seq.GetSubSequence(1, 4);
    CHECK(sub_seq->GetLength() == 3);
    for (int i = 0; i < 3; i++) {
        CHECK(sub_seq->Get(i) == values[i + 1]);
    }
    delete(sub_seq);

    DoublyListSequence<int> *single_seq = seq.GetSubSequence(1, 2);
    CHECK(single_seq->GetLength() == 1);
    CHECK(single_seq->Get(0) == values[1]);
    delete(single_seq);

    CHECK_THROWS_AS(seq.GetSubSequence(1, 8), IndexOutOfRange);
    CHECK_THROWS_AS(seq.GetSubSequence(8, 1), IndexOutOfRange);
    CHECK_THROWS_AS(seq.GetSubSequence(3, 1), InvalidRange);

    ImmutableDoublyListSequence<int> empty_seq;
    CHECK_THROWS_AS(empty_seq.GetSubSequence(0, 0), IndexOutOfRange);
}

TEST_CASE("test_doubly_list_sequence_immutable_set") {
    int values[] = {4, 0, 56, -2, 9};
    int values1[] = {-12, 13, 21, -2, 9};

    ImmutableDoublyListSequence<int> seq1(values, 5);

    DoublyListSequence<int> *seq2 = seq1.Set(0, -12);

    DoublyListSequence<int> *seq3 = seq2->Set(2, 21);
    
    DoublyListSequence<int> *seq4 = seq3->Set(1, 13);
    
    for (int i = 1; i < 4; i++) {
        CHECK(seq4->Get(i) == values1[i]);
    }
    delete(seq2);
    delete(seq3);
    delete(seq4);

    CHECK_THROWS_AS(seq1.Set(5, 3), IndexOutOfRange);
    CHECK_THROWS_AS(seq1.Set(10, 3), IndexOutOfRange);
}

TEST_CASE("test_doubly_list_sequence_immutable_append") {
    ImmutableDoublyListSequence<int> seq;

    DoublyListSequence<int> *seq1 = seq.Append(-3);
    CHECK(seq1->GetLength() == 1);
    CHECK(seq1->Get(0) == -3);
    CHECK(seq1->GetFirst() == -3);
    CHECK(seq1->GetLast() == -3);

    DoublyListSequence<int> *seq2 = seq1->Append(56);
    CHECK(seq2->GetLength() == 2);
    CHECK(seq2->Get(0) == -3);
    CHECK(seq2->Get(1) == 56);
    CHECK(seq2->GetFirst() == -3);
    CHECK(seq2->GetLast() == 56);
    
    delete(seq1);
    delete(seq2);
}

TEST_CASE("test_doubly_list_sequence_immutable_prepend") {
    ImmutableDoublyListSequence<int> seq;

    DoublyListSequence<int> *seq1 = seq.Prepend(-3);
    CHECK(seq1->GetLength() == 1);
    CHECK(seq1->Get(0) == -3);
    CHECK(seq1->GetFirst() == -3);
    CHECK(seq1->GetLast() == -3);

    DoublyListSequence<int> *seq2 = seq1->Prepend(56);
    CHECK(seq2->GetLength() == 2);
    CHECK(seq2->Get(0) == 56);
    CHECK(seq2->Get(1) == -3);
    CHECK(seq2->GetFirst() == 56);
    CHECK(seq2->GetLast() == -3);

    delete(seq1);
    delete(seq2);
}

TEST_CASE("test_doubly_list_sequence_immutable_insert_at") {
    int values[] = {4, 0, 56, -2, 9};
    ImmutableDoublyListSequence<int> seq;

    DoublyListSequence<int> *seq1 = seq.InsertAt(0, 0);
    CHECK(seq1->GetLength() == 1);
    CHECK(seq1->Get(0) == values[1]);

    DoublyListSequence<int> *seq2 = seq1->InsertAt(1, 56);
    CHECK(seq2->GetLength() == 2);
    CHECK(seq2->Get(0) == values[1]);
    CHECK(seq2->Get(1) == values[2]);

    DoublyListSequence<int> *seq3 = seq2->InsertAt(2, 9);
    CHECK(seq3->GetLength() == 3);
    CHECK(seq3->Get(0) == values[1]);
    CHECK(seq3->Get(1) == values[2]);
    CHECK(seq3->Get(2) == values[4]);

    DoublyListSequence<int> *seq4 = seq3->InsertAt(2, -2);
    CHECK(seq4->GetLength() == 4);
    CHECK(seq4->Get(0) == values[1]);
    CHECK(seq4->Get(1) == values[2]);
    CHECK(seq4->Get(2) == values[3]);
    CHECK(seq4->Get(3) == values[4]);

    DoublyListSequence<int> *seq5 = seq4->InsertAt(0, 4);
    CHECK(seq5->GetLength() == 5);
    for (int i = 0; i < 5; i++) {
        CHECK(seq5->Get(i) == values[i]);
    }

    CHECK_THROWS_AS(seq5->InsertAt(8, -3), IndexOutOfRange);

    delete(seq1);
    delete(seq2);
    delete(seq3);
    delete(seq4);
    delete(seq5);
}

TEST_CASE("test_doubly_list_sequence_immutable_remove_at") {
    int values[] = {4, 0, 56, -2, 9};
    ImmutableDoublyListSequence<int> seq(values, 5);
    
    CHECK_THROWS_AS(seq.RemoveAt(5), IndexOutOfRange);
    CHECK_THROWS_AS(seq.RemoveAt(8), IndexOutOfRange);

    DoublyListSequence<int> *seq1 = seq.RemoveAt(0);
    CHECK(seq1->GetLength() == 4);
    CHECK(seq1->Get(0) == values[1]);
    CHECK(seq1->Get(1) == values[2]);
    CHECK(seq1->Get(2) == values[3]);
    CHECK(seq1->Get(3) == values[4]);

    DoublyListSequence<int> *seq2= seq1->RemoveAt(3);
    CHECK(seq2->GetLength() == 3);
    CHECK(seq2->Get(0) == values[1]);
    CHECK(seq2->Get(1) == values[2]);
    CHECK(seq2->Get(2) == values[3]);

    DoublyListSequence<int> *seq3 = seq2->RemoveAt(1);
    CHECK(seq3->GetLength() == 2);
    CHECK(seq3->Get(0) == values[1]);
    CHECK(seq3->Get(1) == values[3]);

    DoublyListSequence<int> *seq4 = seq3->RemoveAt(1);
    CHECK(seq4->GetLength() == 1);
    CHECK(seq4->Get(0) == values[1]);

    DoublyListSequence<int> *seq5 = seq4->RemoveAt(0);
    CHECK(seq5->GetLength() == 0);
    
    CHECK_THROWS_AS(seq5->RemoveAt(0), IndexOutOfRange);
    
    delete(seq1);
    delete(seq2);
    delete(seq3);
    delete(seq4);
    delete(seq5);
}

TEST_CASE("test_doubly_list_sequence_immutable_concat") {
    int values1[] = {4, 0, 56, -2, 9};
    int values2[] = {42, -5, 3, 1};
    ImmutableDoublyListSequence<int> seq1(values1, 5);
    ImmutableDoublyListSequence<int> seq2(values2, 4);


    DoublyListSequence<int> *seq3 = seq1.Concat(seq2);

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
    

    ImmutableDoublyListSequence<int> empty_seq;

    DoublyListSequence<int> *seq4 = seq2.Concat(empty_seq);

    CHECK(seq4->GetLength() == 4);
    for (int i = 0; i < 4; i++) {
        CHECK(seq4->Get(i) == values2[i]);
    }
    delete(seq4);

    
    DoublyListSequence<int> *seq5 = empty_seq.Concat(seq2);

    CHECK(seq5->GetLength() == 4);
    for (int i = 0; i < 4; i++) {
        CHECK(seq5->Get(i) == values2[i]);
    }
    delete(seq5);
}

TEST_CASE("test_doubly_list_sequence_map_where_reduce") {
    int values[] = {4, 0, 56, -2, 9};
    ImmutableDoublyListSequence<int> seq(values, 5);

    int map_values[] = {8, 0, 112, -4, 18};
    DoublyListSequence<int> *seq1 = seq.Map(map_example1);
    for (int i = 0; i < 5; i++) {
        CHECK(seq1->Get(i) == map_values[i]);
    }

    int where_values[] = {8, 112, 18};
    DoublyListSequence<int> *seq2 = seq1->Where(where_example1);
    
    for (int i = 0; i < 3; i++) {
        CHECK(seq2->Get(i) == where_values[i]);
    }

    CHECK(seq2->Reduce(reduce_example1, -1) == 8 * 112 * 18 * (-1));

    delete seq1;
    delete seq2;
}