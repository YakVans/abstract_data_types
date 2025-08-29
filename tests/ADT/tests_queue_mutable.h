#pragma once
#include "doctest.h"

#include "queue.h"

TEST_CASE("test_queue_mutable_constructor") {
    MutableQueue<int> list1;
    CHECK(list1.size() == 0);

    int values[] = {4, 0, 56, -2, 9};
    MutableQueue<int> list3(values, 5);
    CHECK(list3.size() == 5);
    CHECK(list3.front() == 4);
    CHECK(list3.back() == 9);

    MutableQueue<int> list4(list3);
    CHECK(list4.size() == 5);
    CHECK(list4.front() == 4);
    CHECK(list3.back() == 9);
}


TEST_CASE("test_queue_mutable_getter") {
    int values[] = {4, 0, 56, -2, 9};
    MutableQueue<int> list(values, 5);

    CHECK(list.size() == 5);
    CHECK(list.front() == 4);
    CHECK(list.back() == 9);

    MutableQueue<int> empty_list;
    CHECK(empty_list.size() == 0);
    CHECK_THROWS_AS(empty_list.front(), IndexOutOfRange);
    CHECK_THROWS_AS(empty_list.back(), IndexOutOfRange);
}

TEST_CASE("test_queue_mutable_get_subqueue") {
    int values[] = {4, 0, 56, -2, 9};
    MutableQueue<int> seq(values, 5);

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

    MutableQueue<int> empty_seq;
    CHECK_THROWS_AS(empty_seq.GetSubQueue(0, 0), IndexOutOfRange);
}

TEST_CASE("test_queue_mutable_push") {
    MutableQueue<int> list;

    list.push(-3);
    CHECK(list.size() == 1);
    CHECK(list.front() == -3);
    CHECK(list.back() == -3);

    list.push(56);
    CHECK(list.size() == 2);
    CHECK(list.front() == -3);
    CHECK(list.back() == 56);
}

TEST_CASE("test_queue_mutable_pop") {
    int values[] = {4, 56};
    MutableQueue<int> list(values, 2);

    list.pop();
    CHECK(list.size() == 1);
    CHECK(list.front() == 56);
    CHECK(list.back() == 56);

    list.pop();
    CHECK(list.size() == 0);
    
    CHECK_THROWS_AS(list.front(), IndexOutOfRange);
    CHECK_THROWS_AS(list.back(), IndexOutOfRange);
    CHECK_THROWS_AS(list.pop(), IndexOutOfRange);
    
}
