#pragma once
#include "doctest.h"

#include "segmented_deque.h"

TEST_CASE("test_segmented_deque_mutable_constructor") {
    MutableSegmentedDeque<int> list1;
    CHECK(list1.size() == 0);

    int values[] = {4, 0, 56, -2, 9};
    MutableSegmentedDeque<int> list3(values, 5);
    CHECK(list3.size() == 5);
    CHECK(list3.front() == 4);
    CHECK(list3.back() == 9);

    MutableSegmentedDeque<int> list4(list3);
    CHECK(list4.size() == 5);
    CHECK(list4.front() == 4);
    CHECK(list3.back() == 9);
}


TEST_CASE("test_segmented_deque_mutable_getter") {
    int values[] = {4, 0, 56, -2, 9};
    MutableSegmentedDeque<int> list(values, 5);

    CHECK(list.size() == 5);
    CHECK(list.front() == 4);
    CHECK(list.back() == 9);

    MutableSegmentedDeque<int> empty_list;
    CHECK(empty_list.size() == 0);
    CHECK_THROWS_AS(empty_list.front(), IndexOutOfRange);
    CHECK_THROWS_AS(empty_list.back(), IndexOutOfRange);
}

TEST_CASE("test_segmented_deque_mutable_get_subsegdeque") {
    int values[] = {4, 0, 56, -2, 9};
    MutableSegmentedDeque<int> seq(values, 5);

    SegmentedDeque<int> *sub_seq = seq.GetSubSegDeque(1, 4);
    CHECK(sub_seq->size() == 3);
    CHECK(sub_seq->front() == values[1]);
    CHECK(sub_seq->back() == values[3]);
    delete(sub_seq);

    SegmentedDeque<int> *single_seq = seq.GetSubSegDeque(1, 2);
    CHECK(single_seq->size() == 1);
    CHECK(single_seq->front() == values[1]);
    CHECK(single_seq->back() == values[1]);
    delete(single_seq);

    CHECK_THROWS_AS(seq.GetSubSegDeque(1, 8), IndexOutOfRange);
    CHECK_THROWS_AS(seq.GetSubSegDeque(8, 1), IndexOutOfRange);
    CHECK_THROWS_AS(seq.GetSubSegDeque(3, 1), InvalidRange);

    MutableSegmentedDeque<int> empty_seq;
    CHECK_THROWS_AS(empty_seq.GetSubSegDeque(0, 0), IndexOutOfRange);
}

TEST_CASE("test_segmented_deque_mutable_push_back") {
    MutableSegmentedDeque<int> list;

    list.push_back(-3);
    CHECK(list.size() == 1);
    CHECK(list.front() == -3);
    CHECK(list.back() == -3);

    list.push_back(56);
    CHECK(list.size() == 2);
    CHECK(list.front() == -3);
    CHECK(list.back() == 56);
}

TEST_CASE("test_segmented_deque_mutable_push_front") {
    MutableSegmentedDeque<int> list;

    list.push_front(-3);
    CHECK(list.size() == 1);
    CHECK(list.front() == -3);
    CHECK(list.back() == -3);

    list.push_front(56);
    CHECK(list.size() == 2);
    CHECK(list.front() == 56);
    CHECK(list.back() == -3);
}

TEST_CASE("test_segmented_deque_mutable_pop_back") {
    int values[] = {4, 56};
    MutableSegmentedDeque<int> list(values, 2);

    list.pop_back();
    CHECK(list.size() == 1);
    CHECK(list.front() == 4);
    CHECK(list.back() == 4);

    list.pop_back();
    CHECK(list.size() == 0);
    
    CHECK_THROWS_AS(list.front(), IndexOutOfRange);
    CHECK_THROWS_AS(list.back(), IndexOutOfRange);
    CHECK_THROWS_AS(list.pop_back(), IndexOutOfRange);
}

TEST_CASE("test_segmented_deque_mutable_pop_front") {
    int values[] = {4, 56};
    MutableSegmentedDeque<int> list(values, 2);

    list.pop_front();
    CHECK(list.size() == 1);
    CHECK(list.front() == 56);
    CHECK(list.back() == 56);

    list.pop_front();
    CHECK(list.size() == 0);
    
    CHECK_THROWS_AS(list.front(), IndexOutOfRange);
    CHECK_THROWS_AS(list.back(), IndexOutOfRange);
    CHECK_THROWS_AS(list.pop_front(), IndexOutOfRange);
}
