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

#include "queue.h"

#include "save_or_not_UI.h"
#include "example_func.h"
#include "creation_UI.h"
#include "concat_UI.h"
#include "map_where_reduce_UI.h"

template <typename T>
void *QueueUI(Queue<T> *&queue) {
    std::cout << "--- Operations ---\n" <<
        "0. Delete and back to menu\n"
        "\n"
        "1. Print queue\n"
        "2. Get front\n"
        "3. Get back\n"
        "4. Get size\n"
        "5. Get subqueue\n"
        "6. Is subqueue\n"
        "\n"
        "7. Push element\n"
        "8. Pop element\n"
        "\n"
        "9. Map\n"
        "10. Where\n"
        "11. Reduce\n"
        "\n"
        "12. Concatenate\n"
        "13. Count of inversions\n";
    while (true) {
        try {
            std::cout << "\nOperation: ";
            size_t operation = ReadOne<size_t>();
            
            if (operation == 0) {
                delete queue;
                return nullptr;
            }
            else {
                switch (operation) {
                    case 1: {
                        std::cout << "Current queue: " << queue->ToString() << "\n";
                        break;
                    }
                    case 2: {
                        std::cout << "Front element: " << queue->front() << "\n";
                        break;
                    }
                    case 3: {
                        std::cout << "Back element: " << queue->back() << "\n";
                        break;
                    }
                    case 4: {
                        std::cout << "Size: " << queue->size() << "\n";
                        break;
                    }
                    case 5: {
                        std::cout << "Get subqueue start and end indexes: ";
                        DynamicArray<size_t> *indexes = ReadMany<size_t>(2);
                        Queue<T> *subqueue = queue->GetSubQueue(indexes->Get(0), indexes->Get(1));
                        std::cout << subqueue->ToString() << "\n";
                        delete indexes;
                        if (SaveOrNot(subqueue)) {
                            delete queue;
                            queue = subqueue;
                        }
                        break;
                    }
                    case 6: {
                        std::cout << "Subqueue: ";
                        Queue<T> *subqueue = CreationUI<MutableQueue<T>, T>();
                        if (queue->IsSubQueue(subqueue)) std::cout << "Include this\n";
                        else std::cout << "Not include this\n";
                        delete subqueue;
                        break;
                    }
                    case 7: {
                        std::cout << "Push value: ";
                        T value = ReadOne<T>();
                        if (queue->MutType() == mut) {
                            queue->push(value);
                        }
                        else {
                            Queue<T> *new_queue = queue->push(value);
                            if (SaveOrNot(new_queue)) {
                                delete queue;
                                queue = new_queue;
                            }
                        }
                        break;
                    }
                    case 8: {
                        std::cout << "Popping\n";
                        if (queue->MutType() == mut) {
                            queue->pop();
                        }
                        else {
                            Queue<T> *new_queue = queue->pop();
                            if (SaveOrNot(new_queue)) {
                                delete queue;
                                queue = new_queue;
                            }
                        }
                        std::cout << "success\n";
                        break;
                    }
                    case 9: {
                        if (queue->MutType() == mut) {
                            MapUI<Queue<T>, T>(queue);
                        }
                        else {
                            Queue<T> *new_queue = MapUI<Queue<T>, T>(queue);
                            if (SaveOrNot(new_queue)) {
                                delete queue;
                                queue = new_queue;
                            }
                        }
                        break;
                    }
                    case 10: {
                        if (queue->MutType() == mut) {
                            WhereUI<Queue<T>, T>(queue);
                        }
                        else {
                            Queue<T> *new_queue = WhereUI<Queue<T>, T>(queue);
                            if (SaveOrNot(new_queue)) {
                                delete queue;
                                queue = new_queue;
                            }
                        }
                        break;
                    }
                    case 11: {
                        std::cout << "Reduced: " << ReduceUI<Queue<T>, T>(queue) << "\n";
                        break;
                    }
                    case 12: {
                        if (queue->MutType() == mut) {
                            queue = ConcatUI<Queue<T>, T>(queue);
                        }
                        else {
                            Queue<T> *new_queue = ConcatUI<Queue<T>, T>(queue);
                            if (SaveOrNot(new_queue)) {
                                delete queue;
                                queue = new_queue;
                            }
                        }
                        break;
                    }
                    case 13: {
                        std::cout << "Count of inversions: " << queue->CountInversions() << "\n";
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