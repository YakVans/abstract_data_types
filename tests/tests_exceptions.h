#pragma once
#include <string>
#include "doctest.h"

#include "exceptions.h"

TEST_CASE("test_index_out_of_range") {
    try {
        throw IndexOutOfRange(0, 0);
    }
    catch (const IndexOutOfRange &e) {
        std::string message = e.what();
        CHECK(message.find("Invalid index 0: container is empty") != std::string::npos);
    }

    try {
        throw IndexOutOfRange(7, 7);
    }
    catch (const IndexOutOfRange &e) {
        std::string message = e.what();
        CHECK(message.find("Index 7 out of range [0, 6]") != std::string::npos);
    }

    try {
        throw IndexOutOfRange(10, 7);
    }
    catch (const IndexOutOfRange &e) {
        std::string message = e.what();
        CHECK(message.find("Index 10 out of range [0, 6]") != std::string::npos);
    }
}

TEST_CASE("test_invalid_range") {
    try {
        throw InvalidRange(12, 10);
    }
    catch (const InvalidRange &e) {
        std::string message = e.what();
        CHECK(message.find("Invalid range: start(12) > end(10)") != std::string::npos);
    }
}