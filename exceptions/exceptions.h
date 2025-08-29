#pragma once
#include <stdexcept>
#include <cstddef>
#include <string>

class IndexOutOfRange : public std::logic_error{
public:
    IndexOutOfRange(
        size_t index,
        size_t size
    )
        : std::logic_error(create_message(index, size))
    {}
private:
    static std::string create_message(
        size_t index, 
        size_t size)
    {
        std::string msg;
        if (size == 0) {
            msg = "Invalid index " + std::to_string(index) +
            ": container is empty\n";
        }
        else {
            msg = "Index " + std::to_string(index) +
            " out of range [0, " + std::to_string(size - 1) + "]\n";
        }

        return msg;
    }
};

class InvalidRange : public std::logic_error {
public:
    InvalidRange(
        size_t start, 
        size_t end
    )
        : std::logic_error(create_message(start, end))
    {}
private:
    static std::string create_message(
        size_t start, 
        size_t end)
    {
        std::string msg;
        msg = "Invalid range: start(" + std::to_string(start) +
            ") > end(" + std::to_string(end) +")\n";

        return msg;
    }
};

class InvalidInput : public std::logic_error {
public:
    InvalidInput(
        std::string input = "",
        std::string message = ""
    )
        : std::logic_error(create_message(input, message))
    {}
private:
    static std::string create_message(
        std::string input,
        std::string message)
    {
        std::string msg;
        msg = "Invalid input: " + input + "\n";

        return msg + message;
    }
};

class UnsupportedType : public std::logic_error {
public:
    UnsupportedType()
        : std::logic_error(create_message())
    {}
private:
    static std::string create_message()
    {
        return "Unsupported element type\n";
    }
};