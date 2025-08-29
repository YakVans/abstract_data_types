#pragma once

#include <iostream>

#include "supported_typeinfo.h"
#include "manual_read.h"
#include "list_sequence.h"
#include "assign_UI.h"

template <typename Ts, typename T>
Ts *ConcatUI(Ts *seq) {
    std::cout << "--- Concat ---\n"
        "First:\n";
    Ts *first_seq = ConcatOptionUI<T>(seq);

    std::cout << "Second:\n";
    Ts *second_seq = ConcatOptionUI<T>(seq);

    Ts *result_seq = first_seq->Concat(*second_seq);
    if (seq->MutType() == imm) delete first_seq;
    delete second_seq;
    return result_seq;
}

template <typename T>
Stack<T> *ConcatOptionUI(Stack<T> *seq) {
    Stack<T> *chosen_seq = nullptr;
    
    std::cout << "Options:\n"
        "1. Input new\n"
        "2. Subsequence\n"
        "3. Current\n"
        "\n";
    while (true) {
        std::cout << "\nOption: ";
        try {
            size_t choice = ReadOne<size_t>();
            switch (choice) {
                case 1: {
                    if (seq->MutType() == mut) {
                        chosen_seq = CreationUI<MutableStack<T>, T>();
                    }
                    else {
                        chosen_seq = CreationUI<ImmutableStack<T>, T>();
                    }
                    break;
                }
                case 2: {
                    std::cout << "Start and end index: ";
                    DynamicArray<size_t> *indexes = ReadMany<size_t>(2);
                    chosen_seq = seq->GetSubStack(
                        indexes->Get(0), indexes->Get(1));
                    delete indexes;
                    break;
                }
                case 3: {
                    if (seq->size() == 0) {
                        if (seq->MutType() == mut) {
                            chosen_seq = CreationUI<MutableStack<T>, T>();
                        }
                        else {
                            chosen_seq = CreationUI<ImmutableStack<T>, T>();
                        }
                    }
                    else {
                        chosen_seq = seq->GetSubStack(
                            0, seq->size() - 1);
                    }
                    break;
                }
                default: {
                    throw InvalidInput(std::to_string(choice),"Wrong index of option");
                    break;
                }
            }
            break;
        }
        catch (const std::logic_error &e) {
            std::cout << e.what() << "\n";
        }
    }
    return chosen_seq;
}

template <typename T>
Queue<T> *ConcatOptionUI(Queue<T> *seq) {
    Queue<T> *chosen_seq = nullptr;
    
    std::cout << "Options:\n"
        "1. Input new\n"
        "2. Subsequence\n"
        "3. Current\n"
        "\n";
    while (true) {
        std::cout << "\nOption: ";
        try {
            size_t choice = ReadOne<size_t>();
            switch (choice) {
                case 1: {
                    if (seq->MutType() == mut) {
                        chosen_seq = CreationUI<MutableQueue<T>, T>();
                    }
                    else {
                        chosen_seq = CreationUI<ImmutableQueue<T>, T>();
                    }
                    break;
                }
                case 2: {
                    std::cout << "Start and end index: ";
                    DynamicArray<size_t> *indexes = ReadMany<size_t>(2);
                    chosen_seq = seq->GetSubQueue(
                        indexes->Get(0), indexes->Get(1));
                    delete indexes;
                    break;
                }
                case 3: {
                    if (seq->size() == 0) {
                        if (seq->MutType() == mut) {
                            chosen_seq = CreationUI<MutableQueue<T>, T>();
                        }
                        else {
                            chosen_seq = CreationUI<ImmutableQueue<T>, T>();
                        }
                    }
                    else {
                        chosen_seq = seq->GetSubQueue(
                            0, seq->size() - 1);
                    }
                    break;
                }
                default: {
                    throw InvalidInput(std::to_string(choice),"Wrong index of option");
                    break;
                }
            }
            break;
        }
        catch (const std::logic_error &e) {
            std::cout << e.what() << "\n";
        }
    }
    return chosen_seq;
}

template <typename T>
Deque<T> *ConcatOptionUI(Deque<T> *seq) {
    Deque<T> *chosen_seq = nullptr;
    
    std::cout << "Options:\n"
        "1. Input new\n"
        "2. Subsequence\n"
        "3. Current\n"
        "\n";
    while (true) {
        std::cout << "\nOption: ";
        try {
            size_t choice = ReadOne<size_t>();
            switch (choice) {
                case 1: {
                    if (seq->MutType() == mut) {
                        chosen_seq = CreationUI<MutableDeque<T>, T>();
                    }
                    else {
                        chosen_seq = CreationUI<ImmutableDeque<T>, T>();
                    }
                    break;
                }
                case 2: {
                    std::cout << "Start and end index: ";
                    DynamicArray<size_t> *indexes = ReadMany<size_t>(2);
                    chosen_seq = seq->GetSubDeque(
                        indexes->Get(0), indexes->Get(1));
                    delete indexes;
                    break;
                }
                case 3: {
                    if (seq->size() == 0) {
                        if (seq->MutType() == mut) {
                            chosen_seq = CreationUI<MutableDeque<T>, T>();
                        }
                        else {
                            chosen_seq = CreationUI<ImmutableDeque<T>, T>();
                        }
                    }
                    else {
                        chosen_seq = seq->GetSubDeque(
                            0, seq->size() - 1);
                    }
                    break;
                }
                default: {
                    throw InvalidInput(std::to_string(choice),"Wrong index of option");
                    break;
                }
            }
            break;
        }
        catch (const std::logic_error &e) {
            std::cout << e.what() << "\n";
        }
    }
    return chosen_seq;
}

template <typename T>
SegmentedDeque<T> *ConcatOptionUI(SegmentedDeque<T> *seq) {
    SegmentedDeque<T> *chosen_seq = nullptr;
    
    std::cout << "Options:\n"
        "1. Input new\n"
        "2. Subsequence\n"
        "3. Current\n"
        "\n";
    while (true) {
        std::cout << "\nOption: ";
        try {
            size_t choice = ReadOne<size_t>();
            switch (choice) {
                case 1: {
                    if (seq->MutType() == mut) {
                        chosen_seq = CreationUI<MutableSegmentedDeque<T>, T>();
                    }
                    else {
                        chosen_seq = CreationUI<ImmutableSegmentedDeque<T>, T>();
                    }
                    break;
                }
                case 2: {
                    std::cout << "Start and end index: ";
                    DynamicArray<size_t> *indexes = ReadMany<size_t>(2);
                    chosen_seq = seq->GetSubSegDeque(
                        indexes->Get(0), indexes->Get(1));
                    delete indexes;
                    break;
                }
                case 3: {
                    if (seq->size() == 0) {
                        if (seq->MutType() == mut) {
                            chosen_seq = CreationUI<MutableSegmentedDeque<T>, T>();
                        }
                        else {
                            chosen_seq = CreationUI<ImmutableSegmentedDeque<T>, T>();
                        }
                    }
                    else {
                        chosen_seq = seq->GetSubSegDeque(
                            0, seq->size() - 1);
                    }
                    break;
                }
                default: {
                    throw InvalidInput(std::to_string(choice),"Wrong index of option");
                    break;
                }
            }
            break;
        }
        catch (const std::logic_error &e) {
            std::cout << e.what() << "\n";
        }
    }
    return chosen_seq;
}