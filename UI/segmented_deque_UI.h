#pragma once

#include <iostream>
#include <string>
#include <stdexcept>

#include "supported_typeinfo.h"
#include "manual_read.h"
#include "dynamic_array.h"
#include "sequence.h"
#include "array_sequence.h"
#include "list_sequence.h"

#include "segmented_deque.h"

#include "save_or_not_UI.h"
#include "example_func.h"
#include "creation_UI.h"
#include "concat_UI.h"
#include "map_where_reduce_UI.h"

template <typename T>
void *SegmentedDequeUI(SegmentedDeque<T> *&deque) {
    std::cout << "--- Operations ---\n" <<
        "0. Delete and back to menu\n"
        "\n"
        "1. Print deque\n"
        "2. Get front\n"
        "3. Get back\n"
        "4. Get size\n"
        "5. Get subdeque\n"
        "6. Is subdeque\n"
        "\n"
        "7. Push back element\n"
        "8. Push front element\n"
        "9. Pop back element\n"
        "10. Pop front element\n"
        "\n"
        "11. Map\n"
        "12. Where\n"
        "13. Reduce\n"
        "\n"
        "14. Concatenate\n"
        "15. Sort\n"
        "16. Count of inversions\n";
    while (true) {
        try {
            std::cout << "\nOperation: ";
            size_t operation = ReadOne<size_t>();
            
            if (operation == 0) {
                delete deque;
                return nullptr;
            }
            else {
                switch (operation) {
                    case 1: {
                        std::cout << "Current deque: " << deque->ToString() << "\n";
                        break;
                    }
                    case 2: {
                        std::cout << "Front element: " << deque->front() << "\n";
                        break;
                    }
                    case 3: {
                        std::cout << "Back element: " << deque->back() << "\n";
                        break;
                    }
                    case 4: {
                        std::cout << "Size: " << deque->size() << "\n";
                        break;
                    }
                    case 5: {
                        std::cout << "Get subdeque start and end indexes: ";
                        DynamicArray<size_t> *indexes = ReadMany<size_t>(2);
                        SegmentedDeque<T> *subdeque = deque->GetSubSegDeque(indexes->Get(0), indexes->Get(1));
                        std::cout << subdeque->ToString() << "\n";
                        delete indexes;
                        if (SaveOrNot(subdeque)) {
                            delete deque;
                            deque = subdeque;
                        }
                        break;
                    }
                    case 6: {
                        std::cout << "Subdeque: ";
                        SegmentedDeque<T> *subdeque = CreationUI<MutableSegmentedDeque<T>, T>();
                        if (deque->IsSubSegDeque(subdeque)) std::cout << "Include this\n";
                        else std::cout << "Not include this\n";
                        delete subdeque;
                        break;
                    }
                    case 7: {
                        std::cout << "Push back value: ";
                        T value = ReadOne<T>();
                        if (deque->MutType() == mut) {
                            deque->push_back(value);
                        }
                        else {
                            SegmentedDeque<T> *new_deque = deque->push_back(value);
                            if (SaveOrNot(new_deque)) {
                                delete deque;
                                deque = new_deque;
                            }
                        }
                        break;
                    }
                    case 8: {
                        std::cout << "Push front value: ";
                        T value = ReadOne<T>();
                        if (deque->MutType() == mut) {
                            deque->push_front(value);
                        }
                        else {
                            SegmentedDeque<T> *new_deque = deque->push_front(value);
                            if (SaveOrNot(new_deque)) {
                                delete deque;
                                deque = new_deque;
                            }
                        }
                        break;
                    }
                    case 9: {
                        std::cout << "Popping back\n";
                        if (deque->MutType() == mut) {
                            deque->pop_back();
                        }
                        else {
                            SegmentedDeque<T> *new_deque = deque->pop_back();
                            if (SaveOrNot(new_deque)) {
                                delete deque;
                                deque = new_deque;
                            }
                        }
                        std::cout << "success\n";
                        break;
                    }
                    case 10: {
                        std::cout << "Popping front\n";
                        if (deque->MutType() == mut) {
                            deque->pop_front();
                        }
                        else {
                            SegmentedDeque<T> *new_deque = deque->pop_front();
                            if (SaveOrNot(new_deque)) {
                                delete deque;
                                deque = new_deque;
                            }
                        }
                        std::cout << "success\n";
                        break;
                    }
                    case 11: {
                        if (deque->MutType() == mut) {
                            MapUI<SegmentedDeque<T>, T>(deque);
                        }
                        else {
                            SegmentedDeque<T> *new_deque = MapUI<SegmentedDeque<T>, T>(deque);
                            if (SaveOrNot(new_deque)) {
                                delete deque;
                                deque = new_deque;
                            }
                        }
                        break;
                    }
                    case 12: {
                        if (deque->MutType() == mut) {
                            WhereUI<SegmentedDeque<T>, T>(deque);
                        }
                        else {
                            SegmentedDeque<T> *new_deque = WhereUI<SegmentedDeque<T>, T>(deque);
                            if (SaveOrNot(new_deque)) {
                                delete deque;
                                deque = new_deque;
                            }
                        }
                        break;
                    }
                    case 13: {
                        std::cout << "Reduced: " << ReduceUI<SegmentedDeque<T>, T>(deque) << "\n";
                        break;
                    }
                    case 14: {
                        if (deque->MutType() == mut) {
                            deque = ConcatUI<SegmentedDeque<T>, T>(deque);
                        }
                        else {
                            SegmentedDeque<T> *new_deque = ConcatUI<SegmentedDeque<T>, T>(deque);
                            if (SaveOrNot(new_deque)) {
                                delete deque;
                                deque = new_deque;
                            }
                        }
                        break;
                    }
                    case 15: {
                        std::cout << "Sorting\n";
                        if (deque->MutType() == mut) {
                            deque->Sort();
                        }
                        else {
                            SegmentedDeque<T> *new_deque = deque->Sort();
                            if (SaveOrNot(new_deque)) {
                                delete deque;
                                deque = new_deque;
                            }
                        }
                        std::cout << "success\n";
                        break;
                    }
                    case 16: {
                        std::cout << "Count of inversions: " << deque->CountInversions() << "\n";
                        break;
                    }
                    default: {
                        throw InvalidInput(std::to_string(operation), "Wrong index of operation");
                        break;
                    }
                }
            }
        }
        catch (const std::logic_error &e) {
            std::cout << e.what();
        }
    }
}