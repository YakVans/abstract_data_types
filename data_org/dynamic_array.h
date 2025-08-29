#pragma once

#include <cstddef>
#include <sstream>

#include "exceptions.h"

template <typename T>
class DynamicArray {
private:
    T *data;
    size_t size;
    size_t capacity;

public:
    DynamicArray() :
        data(nullptr),
        size(0),
        capacity(0)
    {}

    explicit DynamicArray(size_t count) : 
        data(new T[count]), 
        size(0), 
        capacity(count)
    {}

    explicit DynamicArray(T *items, size_t count) : // items должен содержать >= size элементов
        data(new T[count]),
        size(count),
        capacity(count)
    {
        for (size_t i = 0; i < count; i++) data[i] = items[i];
    }

    DynamicArray(const DynamicArray &other) :
        data(new T[other.capacity]),
        size(other.size),
        capacity(other.capacity)
    {
        for (size_t i = 0; i < size; i++) data[i] = other.data[i];
    }


    ~DynamicArray() {
        delete[] data;
    }

    
    T Get(size_t index) const
    {
        if (index >= size) throw IndexOutOfRange(index, size);
        return data[index];
    }

    size_t GetSize() const {
        return size;
    }

    DynamicArray *GetSubArray(size_t start, size_t end) const {
        if (start >= size || end > size) {
            throw IndexOutOfRange(end, size);
        }
        else if (start > end) {
            throw InvalidRange(start, end);
        }
        DynamicArray *subArray = new DynamicArray(end - start);
        for (size_t i = start; i < end; i++) {
            subArray->InsertAt(subArray->size, data[i]);
        }
        return subArray;
    }

    std::string ToString() const {
        std::stringstream ss;
        ss << "[" << ((size == 0) ? " empty ]" : "");
        for (size_t i = 0; i < size - 1; i++) {
            ss << data[i] << ", ";
        }
        ss << data[size - 1] << "]";
        return ss.str();
    }


    void Set(size_t index, T value)
    {
        if (index >= size) throw IndexOutOfRange(index, size);
        data[index] = value;
    }

    void Resize(size_t newCapacity) {
        T *newData = new T[newCapacity];
        size_t newSize = (size < newCapacity) ? size : newCapacity;
        for (size_t i = 0; i < newSize; i++) newData[i] = data[i];
        delete[] data;
        data = newData;
        size = newSize;
        capacity = newCapacity;
    }

    void InsertAt(size_t index, T value) {
        if (index > size) throw IndexOutOfRange(index, size);
        if (size == capacity) Resize(capacity == 0 ? 1 : capacity * 2);
        for (size_t i = size; i > index; i--) data[i] = data[i - 1];
        data[index] = value;
        size++;
    }

    void Append(T value) {
        InsertAt(size, value);
    }

    void Prepend(T value) {
        InsertAt(0, value);
    }

    void RemoveAt(size_t index) {
        if (index >= size) throw IndexOutOfRange(index, size);
        for (size_t i = index; i < size - 1; i++) data[i] = data[i + 1];
        size--;
    }

    DynamicArray *ConcatInPlace(const DynamicArray &other) {
        size_t addSize = other.GetSize();
        for (size_t i = 0; i < addSize; i++) {
            Append(other.Get(i));
        }
        return this;
    }

    DynamicArray *Map(T (*func)(T)) {
        for (size_t i = 0; i < size; i++) {
            data[i] = func(data[i]);
        }
        return this;
    }
    DynamicArray *Where(bool (*func)(T)) {
        size_t newSize = 0;
        for (size_t i = 0; i < size; i++) {
            if (func(data[i])) {
                data[newSize] = data[i];
                newSize++;
            }
        }
        size = newSize;
        return this;
    }
    T Reduce(T (*func)(T, T), T c) const {
        T result = c;
        for (size_t i = 0; i < size; i++) {
            result = func(data[i], result);
        }
        return result;
    }

    bool IsSubArray(const DynamicArray* subarr) const {
        if (subarr == nullptr) return false;
        if (subarr->size == 0) return true;
        if (subarr->size > size) return false;

        for (size_t i = 0; i <= size - subarr->size; i++) {
            bool found = true;
            for (size_t j = 0; j < subarr->size; j++) {
                if (data[i + j] != subarr->data[j]) {
                    found = false;
                    break;
                }
            }
            if (found) return true;
        }
        return false;
    }

    int CountInversions() const {
        int inv = 0;
        for (size_t i = 0; i < size; i++) {
            for (size_t j = i + 1; j < size; j++) {
                if (Get(i) > Get(j)) inv++;
            }
        }
        return inv;
    }
};