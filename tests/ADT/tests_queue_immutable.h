#pragma once
#include "doctest.h"

#include "queue.h"

TEST_CASE("test_queue_immutable_constructor") {
    ImmutableQueue<int> list1;
    CHECK(list1.size() == 0);

    int values[] = {4, 0, 56, -2, 9};
    ImmutableQueue<int> list3(values, 5);
    CHECK(list3.size() == 5);
    CHECK(list3.front() == 4);
    CHECK(list3.back() == 9);

    ImmutableQueue<int> list4(list3);
    CHECK(list4.size() == 5);
    CHECK(list4.front() == 4);
    CHECK(list3.back() == 9);
}

TEST_CASE("test_queue_immutable_getter") {
    int values[] = {4, 0, 56, -2, 9};
    ImmutableQueue<int> list(values, 5);

    CHECK(list.size() == 5);
    CHECK(list.front() == 4);
    CHECK(list.back() == 9);

    ImmutableQueue<int> empty_list;
    CHECK(empty_list.size() == 0);
    CHECK_THROWS_AS(empty_list.front(), IndexOutOfRange);
    CHECK_THROWS_AS(empty_list.back(), IndexOutOfRange);
}

TEST_CASE("test_queue_immutable_get_subqueue") {
    int values[] = {4, 0, 56, -2, 9};
    ImmutableQueue<int> seq(values, 5);

    Queue<int> *sub_seq = seq.GetSubQueue(1, 4);
    CHECK(sub_seq->size() == 3);
    CHECK(sub_seq->front() == values[1]);
    CHECK(sub_seq->back() == values[3]);
    delete(sub_seq);

    Queue<int> *single_seq = seq.GetSubQueue(1, 2);
    CHECK(single_seq->size() == 1);
    CHECK(single_seq->front() == values[1]);
    CHECK(single_seq->back() == values[1]);
    delete(single_seq);

    CHECK_THROWS_AS(seq.GetSubQueue(1, 8), IndexOutOfRange);
    CHECK_THROWS_AS(seq.GetSubQueue(8, 1), IndexOutOfRange);
    CHECK_THROWS_AS(seq.GetSubQueue(3, 1), InvalidRange);

    ImmutableQueue<int> empty_seq;
    CHECK_THROWS_AS(empty_seq.GetSubQueue(0, 0), IndexOutOfRange);
}

TEST_CASE("test_queue_immutable_push") {
    ImmutableQueue<int> list;

    Queue<int> *list1 = list.push(-3);
    CHECK(list1->size() == 1);
    CHECK(list1->front() == -3);
    CHECK(list1->back() == -3);

    Queue<int> *list2 = list1->push(56);
    CHECK(list2->size() == 2);
    CHECK(list2->front() == -3);
    CHECK(list2->back() == 56);
    
    delete(list1);
    delete(list2);
}

TEST_CASE("test_queue_immutable_pop") {
    int values[] = {4, 56};
    ImmutableQueue<int> list(values, 2);
    

    Queue<int> *list1 = list.pop();
    CHECK(list1->size() == 1);
    CHECK(list1->front() == 56);
    CHECK(list1->back() == 56);

    Queue<int> *list2 = list1->pop();
    CHECK(list2->size() == 0);
    
    CHECK_THROWS_AS(list2->front(), IndexOutOfRange);
    CHECK_THROWS_AS(list2->back(), IndexOutOfRange);
    CHECK_THROWS_AS(list2->pop(), IndexOutOfRange);
    
    delete(list1);
    delete(list2);
}
