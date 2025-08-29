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
#include "queue.h"
#include "deque.h"
#include "segmented_deque.h"

#include "creation_UI.h"
#include "stack_UI.h"
#include "queue_UI.h"
#include "deque_UI.h"
#include "segmented_deque_UI.h"


template <typename T>
void AssignUI() {
    std::cout << "--- ADT creation ---\n";
    size_t adt_choice;

    std::cout << "\nADT type:\n"
        "1. Stack\n"
        "2. Queue\n"
        "3. Deque\n"
        "4. Segmented deque\n";
    while (true) {
        try {
            std::cout << "\nSelect type: ";
            adt_choice = ReadOne<size_t>();
            if (adt_choice < 1 ||
                adt_choice > 4) {
                throw InvalidInput(std::to_string(adt_choice), "Selection must be in 1-4");
            }
            break;
        }
        catch (const InvalidInput &e) {
            std::cout << e.what();
        }
    }
    size_t mut_choice;
    
    std::cout << "\nMutability:\n"
        "1. Mutable\n"
        "2. Immutable\n";
    while (true) {
        try {
            std::cout << "\nSelect mutability: ";
            mut_choice = ReadOne<size_t>();
            if (mut_choice < 1 ||
                mut_choice > 2) {
                throw InvalidInput(std::to_string(mut_choice), "Selection must be in 1-2");
            }
            break;
        }
        catch (const InvalidInput &e) {
            std::cout << e.what();
        }
    }
    
    if (adt_choice == 1) {
        if (mut_choice == 1) {
            Stack<T> *stack = new MutableStack<T>();
            stack = CreationUI<MutableStack<T>, T>();
            StackUI<T>(stack);
        }
        else {
            Stack<T> *stack = new ImmutableStack<T>();
            stack = CreationUI<ImmutableStack<T>, T>();
            StackUI<T>(stack);
        }
    }
    else if (adt_choice == 2) {
        if (mut_choice == 1) {
            Queue<T> *queue = new MutableQueue<T>();
            queue = CreationUI<MutableQueue<T>, T>();
            QueueUI<T>(queue);
        }
        else {
            Queue<T> *queue = new ImmutableQueue<T>();
            queue = CreationUI<ImmutableQueue<T>, T>();
            QueueUI<T>(queue);
        }
    }
    else if (adt_choice == 3) {
        if (mut_choice == 1) {
            Deque<T> *deque = new MutableDeque<T>();
            deque = CreationUI<MutableDeque<T>, T>();
            DequeUI<T>(deque);
        }
        else {
            Deque<T> *deque = new ImmutableDeque<T>();
            deque = CreationUI<ImmutableDeque<T>, T>();
            DequeUI<T>(deque);
        }
    }
    else if (adt_choice == 4) {
        if (mut_choice == 1) {
            SegmentedDeque<T> *segdeque = new MutableSegmentedDeque<T>();
            segdeque = CreationUI<MutableSegmentedDeque<T>, T>();
            SegmentedDequeUI<T>(segdeque);
        }
        else {
            SegmentedDeque<T> *segdeque = new ImmutableSegmentedDeque<T>();
            segdeque = CreationUI<ImmutableSegmentedDeque<T>, T>();
            SegmentedDequeUI<T>(segdeque);
        }
    }
}
