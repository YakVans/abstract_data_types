#pragma once

#include <iostream>
#include <string>
#include <stdexcept>

#include "supported_typeinfo.h"
#include "manual_read.h"
#include "dynamic_array.h"
#include "example_func.h"

#include "stack.h"
#include "queue.h"
#include "deque.h"
#include "segmented_deque.h"

template <typename Ts, typename T>
Ts *MapUI(Ts *adt) {
    size_t map_choice;
    std::cout << "Possible map:\n" <<
        "1. * 2\n"
        "2. + 1\n"
        "3. ^2\n";
    
    while (true) {
        try {
            std::cout << "\nMap choice: ";
            map_choice = ReadOne<size_t>();
            if (map_choice < 1 ||
                map_choice > 3) {
                throw InvalidInput(std::to_string(map_choice), "Selection must be in 1-3");
            }
            break;
        }
        catch (const InvalidInput &e) {
            std::cout << e.what();
        }
    }

    if (map_choice == 1) {
        return adt->Map(map_example1<T>);
    }
    else if (map_choice == 2) {
        return adt->Map(map_example2<T>);
    }
    else if (map_choice == 3) {
        return adt->Map(map_example3<T>);
    }
    return nullptr;
}

template <typename Ts, typename T>
Ts *WhereUI(Ts *adt) {
    size_t where_choice;
    std::cout << "Possible where:\n" <<
        "1. >= 1\n"
        "2. == 0\n"
        "3. < -3\n";
    
    while (true) {
        try {
            std::cout << "\nWhere choice: ";
            where_choice = ReadOne<size_t>();
            if (where_choice < 1 ||
                where_choice > 3) {
                throw InvalidInput(std::to_string(where_choice), "Selection must be in 1-3");
            }
            break;
        }
        catch (const InvalidInput &e) {
            std::cout << e.what();
        }
    }

    if (where_choice == 1) {
        return adt->Where(where_example1<T>);
    }
    else if (where_choice == 2) {
        return adt->Where(where_example2<T>);
    }
    else if (where_choice == 3) {
        return adt->Where(where_example3<T>);
    }
    return nullptr;
}

template <typename Ts, typename T>
T ReduceUI(Ts *adt) {
    size_t reduce_choice;
    std::cout << "Possible reduce:\n" <<
        "1. *\n"
        "2. +\n"
        "3. -\n";
    
    while (true) {
        try {
            std::cout << "\nReduce choice: ";
            reduce_choice = ReadOne<size_t>();
            if (reduce_choice < 1 ||
                reduce_choice > 3) {
                throw InvalidInput(std::to_string(reduce_choice), "Selection must be in 1-3");
            }
            break;
        }
        catch (const InvalidInput &e) {
            std::cout << e.what();
        }
    }

    if (reduce_choice == 1) {
        return adt->Reduce(reduce_example1<T>, 1);
    }
    else if (reduce_choice == 2) {
        return adt->Reduce(reduce_example2<T>, 0);
    }
    else if (reduce_choice == 3) {
        return adt->Reduce(reduce_example3<T>, 0);
    }
    return 0;
}