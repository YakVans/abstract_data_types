#pragma once

#include <iostream>
#include <string>
#include <stdexcept>

#include "complex_numbers.h"
#include "manual_read.h"
#include "dynamic_array.h"
#include "sequence.h"
#include "assign_UI.h"
#include "concat_UI.h"

void MainMenuUI() {
    while (true) {
        std::cout << "--- Main menu ---\n"
            "\n"
            "1. int\n"
            "2. double\n"
            "3. complex\n"
            "\n"
            "0. Exit\n";
        size_t choice;
        while (true) {
            std::cout << "\nChoice: ";
            try {
                choice = ReadOne<size_t>();
                if (choice > 3) {
                    throw InvalidInput(std::to_string(choice), "Wrong index of operation");
                }
                break;
            }
            catch (const InvalidInput &e) {
                std::cout << e.what() << "\n";
            }
        }
        
        if (choice == 0) {
            break;
        }
        else if (choice == 1) {
            AssignUI<int>();
        }
        else if (choice == 2) {
            AssignUI<double>();
        }
        else if (choice == 3) {
            AssignUI<Complex>();
        }
    }
}