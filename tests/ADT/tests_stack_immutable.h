#pragma once
#include "doctest.h"

#include "stack.h"

TEST_CASE("test_stack_immutable_constructor") {
    ImmutableStack<int> list1;
    CHECK(list1.size() == 0);

    int values[] = {4, 0, 56, -2, 9};
    ImmutableStack<int> list3(values, 5);
    CHECK(list3.size() == 5);
    CHECK(list3.top() == 4);

    ImmutableStack<int> list4(list3);
    CHECK(list4.size() == 5);
    CHECK(list4.top() == 4);
}

TEST_CASE("test_stack_immutable_getter") {
    int values[] = {4, 0, 56, -2, 9};
    ImmutableStack<int> list(values, 5);

    CHECK(list.size() == 5);
    CHECK(list.top() == 4);

    ImmutableStack<int> empty_list;
    CHECK(empty_list.size() == 0);
    CHECK_THROWS_AS(empty_list.top(), IndexOutOfRange);
}

TEST_CASE("test_stack_immutable_get_substack") {
    int values[] = {4, 0, 56, -2, 9};
    ImmutableStack<int> seq(values, 5);

    Stack<int> *sub_seq = seq.GetSubStack(1, 4);
    CHECK(sub_seq->size() == 3);
    CHECK(sub_seq->top() == 0);
    delete(sub_seq);

    Stack<int> *single_seq = seq.GetSubStack(1, 2);
    CHECK(single_seq->size() == 1);
    CHECK(single_seq->top() == values[1]);
    delete(single_seq);

    CHECK_THROWS_AS(seq.GetSubStack(1, 8), IndexOutOfRange);
    CHECK_THROWS_AS(seq.GetSubStack(8, 1), IndexOutOfRange);
    CHECK_THROWS_AS(seq.GetSubStack(3, 1), InvalidRange);

    ImmutableStack<int> empty_seq;
    CHECK_THROWS_AS(empty_seq.GetSubStack(0, 0), IndexOutOfRange);
}

TEST_CASE("test_stack_immutable_push") {
    ImmutableStack<int> list;

    Stack<int> *list1 = list.push(-3);
    CHECK(list1->size() == 1);
    CHECK(list1->top() == -3);

    Stack<int> *list2 = list1->push(56);
    CHECK(list2->size() == 2);
    CHECK(list2->top() == 56);
    
    delete(list1);
    delete(list2);
}

TEST_CASE("test_stack_immutable_pop") {
    int values[] = {4, 56};
    ImmutableStack<int> list(values, 2);
    

    Stack<int> *list1 = list.pop();
    CHECK(list1->size() == 1);
    CHECK(list1->top() == 56);

    Stack<int> *list2 = list1->pop();
    CHECK(list2->size() == 0);
    
    CHECK_THROWS_AS(list2->pop(), IndexOutOfRange);
    
    delete(list1);
    delete(list2);
}
