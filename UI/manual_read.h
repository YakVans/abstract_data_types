#pragma once

#include <iostream>
#include <sstream>
#include <cstddef>
#include <string>

#include "exceptions.h"
#include "dynamic_array.h"


template <typename T>
DynamicArray<T> *string_to_values(const std::string& str) {
    std::istringstream iss(str);
    DynamicArray<T> *result = new DynamicArray<T>();
    T value;
    
    while (iss >> value) {
        result->InsertAt(result->GetSize(), value);
    }
    if (iss.fail() && !iss.eof()) {
        iss.clear();
        char c;
        if (iss >> c) {
            delete result;
            throw InvalidInput(str,
                "Non-numeric characters detected or\n"
                "Number is too big/small");
        }
    }
    
    return result;
}

template <typename T>
DynamicArray<T> *string_to_values(const std::string& str, size_t count) {
    DynamicArray<T> *result = string_to_values<T>(str);
    
    if (result->GetSize() != count) {
        std::string format_msg = "Expected " + std::to_string(count) +
            " values, got " + std::to_string(result->GetSize()) + "\n";
        delete result;
        throw InvalidInput(str, format_msg);
    }
    return result;
}



template <typename T>
DynamicArray<T> *ReadMany() {
    std::string input;
    DynamicArray<T> *arr = nullptr;
    std::getline(std::cin, input);
    arr = string_to_values<T>(input);
    return arr;
}

template <typename T>
DynamicArray<T> *ReadMany(size_t count) {
    std::string input;
    DynamicArray<T> *arr = nullptr;
    std::getline(std::cin, input);
    arr = string_to_values<T>(input, count);
    return arr;
}

template <typename T>
T ReadOne() {
    DynamicArray<T> *result_ptr = ReadMany<T>(1);
    T result = result_ptr->Get(0);
    delete result_ptr;
    return result;
}
