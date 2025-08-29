#pragma once
#include "doctest.h"

#include "segmented_deque.h"

TEST_CASE("test_segmented_deque_immutable_constructor") {
    ImmutableSegmentedDeque<int> list1;
    CHECK(list1.size() == 0);

    int values[] = {4, 0, 56, -2, 9};
    ImmutableSegmentedDeque<int> list3(values, 5);
    CHECK(list3.size() == 5);
    CHECK(list3.front() == 4);
    CHECK(list3.back() == 9);

    ImmutableSegmentedDeque<int> list4(list3);
    CHECK(list4.size() == 5);
    CHECK(list4.front() == 4);
    CHECK(list3.back() == 9);
}

TEST_CASE("test_segmented_deque_immutable_getter") {
    int values[] = {4, 0, 56, -2, 9};
    ImmutableSegmentedDeque<int> list(values, 5);

    CHECK(list.size() == 5);
    CHECK(list.front() == 4);
    CHECK(list.back() == 9);

    ImmutableSegmentedDeque<int> empty_list;
    CHECK(empty_list.size() == 0);
    CHECK_THROWS_AS(empty_list.front(), IndexOutOfRange);
    CHECK_THROWS_AS(empty_list.back(), IndexOutOfRange);
}

TEST_CASE("test_segmented_deque_immutable_get_subsegdeque") {
    int values[] = {4, 0, 56, -2, 9};
    ImmutableSegmentedDeque<int> seq(values, 5);

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

    ImmutableSegmentedDeque<int> empty_seq;
    CHECK_THROWS_AS(empty_seq.GetSubSegDeque(0, 0), IndexOutOfRange);
}

TEST_CASE("test_segmented_deque_immutable_push_back") {
    ImmutableSegmentedDeque<int> list;

    SegmentedDeque<int> *list1 = list.push_back(-3);
    CHECK(list1->size() == 1);
    CHECK(list1->front() == -3);
    CHECK(list1->back() == -3);

    SegmentedDeque<int> *list2 = list1->push_back(56);
    CHECK(list2->size() == 2);
    CHECK(list2->front() == -3);
    CHECK(list2->back() == 56);
    
    delete(list1);
    delete(list2);
}

TEST_CASE("test_segmented_deque_immutable_push_front") {
    ImmutableSegmentedDeque<int> list;

    SegmentedDeque<int> *list1 = list.push_front(-3);
    CHECK(list1->size() == 1);
    CHECK(list1->front() == -3);
    CHECK(list1->back() == -3);

    SegmentedDeque<int> *list2 = list1->push_front(56);
    CHECK(list2->size() == 2);
    CHECK(list2->front() == 56);
    CHECK(list2->back() == -3);
    
    delete(list1);
    delete(list2);
}

TEST_CASE("test_segmented_deque_immutable_pop_back") {
    int values[] = {4, 56};
    ImmutableSegmentedDeque<int> list(values, 2);
    

    SegmentedDeque<int> *list1 = list.pop_back();
    CHECK(list1->size() == 1);
    CHECK(list1->front() == 4);
    CHECK(list1->back() == 4);

    SegmentedDeque<int> *list2 = list1->pop_back();
    CHECK(list2->size() == 0);
    
    CHECK_THROWS_AS(list2->front(), IndexOutOfRange);
    CHECK_THROWS_AS(list2->back(), IndexOutOfRange);
    CHECK_THROWS_AS(list2->pop_back(), IndexOutOfRange);
    
    delete(list1);
    delete(list2);
}

TEST_CASE("test_segmented_deque_immutable_pop_front") {
    int values[] = {4, 56};
    ImmutableSegmentedDeque<int> list(values, 2);
    

    SegmentedDeque<int> *list1 = list.pop_front();
    CHECK(list1->size() == 1);
    CHECK(list1->front() == 56);
    CHECK(list1->back() == 56);

    SegmentedDeque<int> *list2 = list1->pop_front();
    CHECK(list2->size() == 0);
    
    CHECK_THROWS_AS(list2->front(), IndexOutOfRange);
    CHECK_THROWS_AS(list2->back(), IndexOutOfRange);
    CHECK_THROWS_AS(list2->pop_front(), IndexOutOfRange);
    
    delete(list1);
    delete(list2);
}
