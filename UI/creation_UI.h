#pragma once

#include <iostream>
#include <string>
#include <stdexcept>

#include "supported_typeinfo.h"
#include "manual_read.h"
#include "dynamic_array.h"

template <typename T>
T *dynamic_arr_to_c_arr(DynamicArray<T> *arr) {
    T *result = new T[arr->GetSize()];
    for (size_t i = 0; i < arr->GetSize(); i++) {
        result[i] = arr->Get(i);
    }
    return result;
}

template <typename Ts, typename Te>
Ts *CreationUI() {
    while (true) {
        try {
            std::cout << "\nInput: ";
            DynamicArray<Te> *arr = ReadMany<Te>();
            Te *c_arr = dynamic_arr_to_c_arr(arr);
            Ts *adt = new Ts(c_arr, arr->GetSize());

            delete arr;
            delete[] c_arr;
            return adt;
        }
        catch (const InvalidInput &e) {
            std::cout << e.what() << "\n";
        }
    }
}