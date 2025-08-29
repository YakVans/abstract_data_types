#pragma once

#include <cstddef>
#include <string>

#include "supported_typeinfo.h"
#include "complex_numbers.h"

class ISequence {
public:
    virtual ~ISequence() = default;
    
    virtual size_t GetLength() const = 0;
    virtual my_type GetType() const = 0;
    virtual my_element_type GetElementType() const = 0;
    virtual std::string ToString() const = 0;
};

template <typename T>
class Sequence : public ISequence {
public:
    virtual ~Sequence() = default;

    virtual Sequence *Clone() const = 0;

    virtual T GetFirst() const = 0;
    virtual T GetLast() const = 0;
    virtual T Get(size_t index) const = 0;
    size_t GetLength() const override = 0;
    virtual Sequence *GetSubSequence(size_t start, size_t end) const = 0;
    my_type GetType() const override = 0;
    my_element_type GetElementType() const override {
        if constexpr (std::is_same_v<T, int>) {
            return int_type;
        }
        else if constexpr (std::is_same_v<T, double>) {
            return double_type;
        }
        else if constexpr (std::is_same_v<T, Complex>) {
            return complex_type;
        }
        else {
            return unknown_type;
        }
    }
    std::string ToString() const override = 0;

    virtual Sequence *Set(size_t index, T item) = 0;
    virtual Sequence *Append(T item) = 0;
    virtual Sequence *Prepend(T item) = 0;
    virtual Sequence *InsertAt(size_t index, T item) = 0;
    virtual Sequence *RemoveAt(size_t index) = 0;

    virtual Sequence *Map(T (*func)(T)) = 0;
    virtual Sequence *Where(bool (*func)(T)) = 0;
    virtual T Reduce(T (*func)(T, T), T c) const = 0;

    virtual int CountInversions() const = 0;
};

