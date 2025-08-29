#pragma once

#include <iostream>
#include <string>
#include <stdexcept>

#include "manual_read.h"

template <typename T>
bool SaveOrNot(T *el) {
    std::cout << "Save or not?\n"
        "1. Save and work with this\n"
        "0. Cancel\n";
    while (true) {
        std::cout << "\nChoice: ";
        size_t choice = ReadOne<size_t>();
        if (choice == 0) {
            delete el;
            return false;
        }
        else if (choice == 1) {
            return true;
        }
        else {
            try {
                throw InvalidInput(std::to_string(choice), "Wrong index of option");
            }
            catch (const InvalidInput &e) {
                std::cout << e.what();
            }
        }
    }
}