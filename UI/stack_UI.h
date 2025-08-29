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

#include "stack.h"

#include "save_or_not_UI.h"
#include "example_func.h"
#include "creation_UI.h"
#include "concat_UI.h"
#include "map_where_reduce_UI.h"

template <typename T>
void *StackUI(Stack<T> *&stack) {
    std::cout << "--- Operations ---\n" <<
        "0. Delete and back to menu\n"
        "\n"
        "1. Print stack\n"
        "2. Get top\n"
        "3. Get size\n"
        "4. Get substack\n"
        "5. Is substack\n"
        "\n"
        "6. Push element\n"
        "7. Pop element\n"
        "\n"
        "8. Map\n"
        "9. Where\n"
        "10. Reduce\n"
        "\n"
        "11. Concatenate\n"
        "12. Count of inversions\n";
    while (true) {
        try {
            std::cout << "\nOperation: ";
            size_t operation = ReadOne<size_t>();
            
            if (operation == 0) {
                delete stack;
                return nullptr;
            }
            else {
                switch (operation) {
                    case 1: {
                        std::cout << "Current stack: " << stack->ToString() << "\n";
                        break;
                    }
                    case 2: {
                        std::cout << "Top element: " << stack->top() << "\n";
                        break;
                    }
                    case 3: {
                        std::cout << "Size: " << stack->size() << "\n";
                        break;
                    }
                    case 4: {
                        std::cout << "Get substack start and end indexes: ";
                        DynamicArray<size_t> *indexes = ReadMany<size_t>(2);
                        Stack<T> *substack = stack->GetSubStack(indexes->Get(0), indexes->Get(1));
                        std::cout << substack->ToString() << "\n";
                        delete indexes;
                        if (SaveOrNot(substack)) {
                            delete stack;
                            stack = substack;
                        }
                        break;
                    }
                    case 5: {
                        std::cout << "Substack: ";
                        Stack<T> *substack = CreationUI<MutableStack<T>, T>();
                        if (stack->IsSubStack(substack)) std::cout << "Include this\n";
                        else std::cout << "Not include this\n";
                        delete substack;
                        break;
                    }
                    case 6: {
                        std::cout << "Push value: ";
                        T value = ReadOne<T>();
                        if (stack->MutType() == mut) {
                            stack->push(value);
                        }
                        else {
                            Stack<T> *new_stack = stack->push(value);
                            if (SaveOrNot(new_stack)) {
                                delete stack;
                                stack = new_stack;
                            }
                        }
                        break;
                    }
                    case 7: {
                        std::cout << "Popping\n";
                        if (stack->MutType() == mut) {
                            stack->pop();
                        }
                        else {
                            Stack<T> *new_stack = stack->pop();
                            if (SaveOrNot(new_stack)) {
                                delete stack;
                                stack = new_stack;
                            }
                        }
                        std::cout << "success\n";
                        break;
                    }
                    case 8: {
                        if (stack->MutType() == mut) {
                            MapUI<Stack<T>, T>(stack);
                        }
                        else {
                            Stack<T> *new_stack = MapUI<Stack<T>, T>(stack);
                            if (SaveOrNot(new_stack)) {
                                delete stack;
                                stack = new_stack;
                            }
                        }
                        break;
                    }
                    case 9: {
                        if (stack->MutType() == mut) {
                            WhereUI<Stack<T>, T>(stack);
                        }
                        else {
                            Stack<T> *new_stack = WhereUI<Stack<T>, T>(stack);
                            if (SaveOrNot(new_stack)) {
                                delete stack;
                                stack = new_stack;
                            }
                        }
                        break;
                    }
                    case 10: {
                        std::cout << "Reduced: " << ReduceUI<Stack<T>, T>(stack) << "\n";
                        break;
                    }
                    case 11: {
                        if (stack->MutType() == mut) {
                            stack = ConcatUI<Stack<T>, T>(stack);
                        }
                        else {
                            Stack<T> *new_stack = ConcatUI<Stack<T>, T>(stack);
                            if (SaveOrNot(new_stack)) {
                                delete stack;
                                stack = new_stack;
                            }
                        }
                        break;
                    }
                    case 12: {
                        std::cout << "Count of inversions: " << stack->CountInversions() << "\n";
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