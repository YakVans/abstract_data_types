#pragma once
#include "doctest.h"

#include "exceptions.h"
#include "linked_list.h"
#include "example_func.h"

TEST_CASE("test_linked_list_constructor") {
    LinkedList<int> list1;
    CHECK(list1.GetLength() == 0);

    int values[] = {4, 0, 56, -2, 9};
    LinkedList<int> list3(values, 5);
    CHECK(list3.GetLength() == 5);
    for (int i = 0; i < 5; i++) {
        CHECK(list3.Get(i) == values[i]);
    }

    LinkedList<int> list4(list3);
    CHECK(list4.GetLength() == 5);
    for (int i = 0; i < 5; i++) {
        CHECK(list4.Get(i) == values[i]);
    }
}

TEST_CASE("test_linked_list_copy_independence") {
    int values[] = {4, 0, 56, -2, 9};
    LinkedList<int> list1(values, 5);
    LinkedList<int> list2(list1);
    list1.Set(2, 14);
    CHECK(list2.Get(2) == 56);
}

TEST_CASE("test_linked_list_getter") {
    int values[] = {4, 0, 56, -2, 9};
    LinkedList<int> list(values, 5);

    CHECK(list.GetLength() == 5);
    CHECK(list.GetFirst() == 4);
    CHECK(list.GetLast() == 9);
    for (int i = 0; i < 5; i++) {
        CHECK(list.Get(i) == values[i]);
    }

    CHECK_THROWS_AS(list.Get(5), IndexOutOfRange);
    CHECK_THROWS_AS(list.Get(10), IndexOutOfRange);
    
    LinkedList<int> empty_list;
    CHECK(empty_list.GetLength() == 0);
    CHECK_THROWS_AS(empty_list.GetFirst(), IndexOutOfRange);
    CHECK_THROWS_AS(empty_list.GetLast(), IndexOutOfRange);
    CHECK_THROWS_AS(empty_list.Get(0), IndexOutOfRange);
}

TEST_CASE("test_linked_list_get_sublist") {
    int values[] = {4, 0, 56, -2, 9};
    LinkedList<int> list(values, 5);

    LinkedList<int> *sub_list = list.GetSubList(1, 4);
    CHECK(sub_list->GetLength() == 3);
    for (int i = 0; i < 3; i++) {
        CHECK(sub_list->Get(i) == values[i + 1]);
    }
    delete(sub_list);

    LinkedList<int> *single_list = list.GetSubList(1, 2);
    CHECK(single_list->GetLength() == 1);
    CHECK(single_list->Get(0) == values[1]);
    delete(single_list);

    CHECK_THROWS_AS(list.GetSubList(1, 8), IndexOutOfRange);
    CHECK_THROWS_AS(list.GetSubList(8, 1), IndexOutOfRange);
    CHECK_THROWS_AS(list.GetSubList(3, 1), InvalidRange);

    LinkedList<int> empty_list;
    CHECK_THROWS_AS(empty_list.GetSubList(0, 0), IndexOutOfRange);
}

TEST_CASE("test_linked_list_set") {
    int values[] = {4, 0, 56, -2, 9};
    int values1[] = {42, -5, 3, 1, -23};
    LinkedList<int> list(values, 5);
    for (int i = 1; i < 4; i++) {
        list.Set(i, values1[i]);
    }

    CHECK(list.Get(0) == values[0]);
    for (int i = 1; i < 4; i++) {
        CHECK(list.Get(i) == values1[i]);
    }
    CHECK(list.Get(4) == values[4]);

    CHECK_THROWS_AS(list.Set(5, 3), IndexOutOfRange);
    CHECK_THROWS_AS(list.Set(10, 3), IndexOutOfRange);
}

TEST_CASE("test_linked_list_append") {
    LinkedList<int> list;

    list.Append(-3);
    CHECK(list.GetLength() == 1);
    CHECK(list.Get(0) == -3);
    CHECK(list.GetFirst() == -3);
    CHECK(list.GetLast() == -3);

    list.Append(56);
    CHECK(list.GetLength() == 2);
    CHECK(list.Get(0) == -3);
    CHECK(list.Get(1) == 56);
    CHECK(list.GetFirst() == -3);
    CHECK(list.GetLast() == 56);
}

TEST_CASE("test_linked_list_prepend") {
    LinkedList<int> list;

    list.Prepend(-3);
    CHECK(list.GetLength() == 1);
    CHECK(list.Get(0) == -3);
    CHECK(list.GetFirst() == -3);
    CHECK(list.GetLast() == -3);

    list.Prepend(56);
    CHECK(list.GetLength() == 2);
    CHECK(list.Get(0) == 56);
    CHECK(list.Get(1) == -3);
    CHECK(list.GetFirst() == 56);
    CHECK(list.GetLast() == -3);
}

TEST_CASE("test_linked_list_insert_at") {
    int values[] = {4, 0, 56, -2, 9};
    LinkedList<int> list;

    list.InsertAt(0, 0);
    CHECK(list.GetLength() == 1);
    CHECK(list.Get(0) == values[1]);
    CHECK(list.GetFirst() == values[1]);
    CHECK(list.GetLast() == values[1]);

    list.InsertAt(1, 56);
    CHECK(list.GetLength() == 2);
    CHECK(list.Get(0) == values[1]);
    CHECK(list.Get(1) == values[2]);
    CHECK(list.GetLast() == values[2]);

    list.InsertAt(2, 9);
    CHECK(list.GetLength() == 3);
    CHECK(list.Get(0) == values[1]);
    CHECK(list.Get(1) == values[2]);
    CHECK(list.Get(2) == values[4]);
    CHECK(list.GetLast() == values[4]);

    list.InsertAt(2, -2);
    CHECK(list.GetLength() == 4);
    CHECK(list.Get(0) == values[1]);
    CHECK(list.Get(1) == values[2]);
    CHECK(list.Get(2) == values[3]);
    CHECK(list.Get(3) == values[4]);

    list.InsertAt(0, 4);
    CHECK(list.GetLength() == 5);
    for (int i = 0; i < 5; i++) {
        CHECK(list.Get(i) == values[i]);
    }
    CHECK(list.GetFirst() == values[0]);

    CHECK_THROWS_AS(list.InsertAt(8, -3), IndexOutOfRange);
}

TEST_CASE("test_linked_list_remove_at") {
    int values[] = {4, 0, 56, -2, 9};
    LinkedList<int> list(values, 5);
    
    CHECK_THROWS_AS(list.RemoveAt(5), IndexOutOfRange);
    CHECK_THROWS_AS(list.RemoveAt(8), IndexOutOfRange);

    list.RemoveAt(0);
    CHECK(list.GetLength() == 4);
    CHECK(list.Get(0) == values[1]);
    CHECK(list.Get(1) == values[2]);
    CHECK(list.Get(2) == values[3]);
    CHECK(list.Get(3) == values[4]);
    CHECK(list.GetFirst() == values[1]);

    list.RemoveAt(3);
    CHECK(list.GetLength() == 3);
    CHECK(list.Get(0) == values[1]);
    CHECK(list.Get(1) == values[2]);
    CHECK(list.Get(2) == values[3]);
    CHECK(list.GetLast() == values[3]);

    list.RemoveAt(1);
    CHECK(list.GetLength() == 2);
    CHECK(list.Get(0) == values[1]);
    CHECK(list.Get(1) == values[3]);

    list.RemoveAt(1);
    CHECK(list.GetLength() == 1);
    CHECK(list.Get(0) == values[1]);
    CHECK(list.GetLast() == values[1]);

    list.RemoveAt(0);
    CHECK(list.GetLength() == 0);
    CHECK_THROWS_AS(list.Get(0), IndexOutOfRange);
    CHECK_THROWS_AS(list.GetFirst(), IndexOutOfRange);
    CHECK_THROWS_AS(list.GetLast(), IndexOutOfRange);
    
    CHECK_THROWS_AS(list.RemoveAt(0), IndexOutOfRange);
}

TEST_CASE("test_linked_list_concat_in_place") {
    int values1[] = {4, 0, 56, -2, 9};
    int values2[] = {42, -5, 3, 1};
    LinkedList<int> list1(values1, 5);
    LinkedList<int> list2(values2, 4);


    list1.ConcatInPlace(list2);

    CHECK(list1.GetLength() == 9);
    for (int i = 0; i < 5; i++) {
        CHECK(list1.Get(i) == values1[i]);
    }

    CHECK(list2.GetLength() == 4);
    for (int i = 0; i < 4; i++) {
        CHECK(list1.Get(i + 5) == values2[i]);
        CHECK(list2.Get(i) == values2[i]);
    }
    CHECK(list1.GetLast() == values2[3]);
    

    LinkedList<int> empty_list;

    list2.ConcatInPlace(empty_list);

    CHECK(list2.GetLength() == 4);
    for (int i = 0; i < 4; i++) {
        CHECK(list2.Get(i) == values2[i]);
    }
    CHECK(empty_list.GetLength() == 0);

    empty_list.ConcatInPlace(list2);

    CHECK(empty_list.GetLength() == 4);
    for (int i = 0; i < 4; i++) {
        CHECK(empty_list.Get(i) == values2[i]);
        CHECK(list2.Get(i) == values2[i]);
    }
}

TEST_CASE("test_linked_list_concat_in_place_with_self") {
    int values1[] = {4, 0, 56, -2, 9};
    LinkedList<int> list1(values1, 5);

    list1.ConcatInPlace(list1);

    CHECK(list1.GetLength() == 10);
    for (int i = 0; i < 5; i++) {
        CHECK(list1.Get(i) == values1[i]);
        CHECK(list1.Get(i + 5) == values1[i]);
    }

    LinkedList<int> empty_list;

    empty_list.ConcatInPlace(empty_list);

    CHECK(empty_list.GetLength() == 0);
}

TEST_CASE("test_linked_list_map_where_reduce") {
    int values[] = {4, 0, 56, -2, 9};
    LinkedList<int> list(values, 5);

    int map_values[] = {8, 0, 112, -4, 18};
    list.Map(map_example1);
    for (int i = 0; i < 5; i++) {
        CHECK(list.Get(i) == map_values[i]);
    }

    int where_values[] = {8, 112, 18};
    list.Where(where_example1);
    for (int i = 0; i < 3; i++) {
        CHECK(list.Get(i) == where_values[i]);
    }

    CHECK(list.Reduce(reduce_example1, -1) == 8 * 112 * 18 * (-1));
}

TEST_CASE("test_linked_list_call_chaining") {
    int values[] = {4, 0, 56, -2, 9};
    LinkedList<int> list(values, 5);

    CHECK(list.Map(map_example1)->Where(where_example1)->Reduce(reduce_example1, -1) == 8 * 112 * 18 * (-1));
}

TEST_CASE("test_linked_list_is_sublist") {
    int values[] = {4, 0, 56, -2, 9};
    int start_values[] = {4, 0, 56};
    int end_values[] = {9};
    int wrong_values[] = {4, 0, 51};
    int larger_values[] = {4, 0, 56, -2, 9, 1};

    LinkedList<int> list(values, 5);
    LinkedList<int> start_list(start_values, 3);
    LinkedList<int> end_list(end_values, 1);
    LinkedList<int> wrong_list(wrong_values, 3);
    LinkedList<int> empty_list(values, 0);
    LinkedList<int> larger_list(larger_values, 6);

    CHECK(list.IsSubList(&start_list) == true);
    CHECK(list.IsSubList(&end_list) == true);
    CHECK(list.IsSubList(&wrong_list) == false);
    CHECK(list.IsSubList(&empty_list) == true);
    CHECK(empty_list.IsSubList(&empty_list) == true);
    CHECK(list.IsSubList(&larger_list) == false);
}

TEST_CASE("test_linked_list_count_inversions") {
    int values1[] = {1, 2, 3, 4, 5};
    LinkedList<int> list1(values1, 5);
    CHECK(list1.CountInversions() == 0);

    int values2[] = {1, 3, 2, 4, 5};
    LinkedList<int> list2(values2, 5);
    CHECK(list2.CountInversions() == 1);

    int values3[] = {5, 4, 3, 2, 1};
    LinkedList<int> list3(values3, 5);
    CHECK(list3.CountInversions() == 10);

    LinkedList<int> list4;
    CHECK(list4.CountInversions() == 0);

    int values5[] = {2, 1};
    LinkedList<int> list5(values5, 2);
    CHECK(list5.CountInversions() == 1);

    int values6[] = {1};
    LinkedList<int> list6(values6, 1);
    CHECK(list6.CountInversions() == 0);
}