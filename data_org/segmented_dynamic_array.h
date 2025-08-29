#pragma once

#include <cstddef>
#include <sstream>

#include "exceptions.h"
#include "dynamic_array.h"

template <typename T>
class SegmentedDynamicArray {
private:
    T **arr_of_arr;
    size_t start;
    size_t size;
    size_t capacity;

    size_t num_chunks;
    const size_t buf_size = 512;

public:
    SegmentedDynamicArray() :
        arr_of_arr(nullptr),
        start(0),
        size(0),
        capacity(0),
        num_chunks(0)
    {}

    explicit SegmentedDynamicArray(T *items, size_t count) : // items должен содержать >= count элементов
        size(count)
    {
        num_chunks = (count + buf_size - 1) / buf_size;
        capacity = num_chunks * buf_size;
        arr_of_arr = new T*[num_chunks];

        start = (capacity - count) / 2;
        
        size_t current = 0;
        size_t cycle_start = start;
        for (size_t i = 0; i < num_chunks; i++) {
            T *this_chunk_arr = new T[buf_size];

            for (size_t j = cycle_start; j < buf_size && current < count; j++) {
                this_chunk_arr[j] = items[current];
                current++;
            }
            cycle_start = 0;
            arr_of_arr[i] = this_chunk_arr;
        }
    }

    SegmentedDynamicArray(const SegmentedDynamicArray &other) :
        start(other.start),
        size(other.size),
        capacity(other.capacity),
        num_chunks(other.num_chunks)
    {
        if (other.arr_of_arr == nullptr) {
            arr_of_arr = nullptr;
        }
        else {
            arr_of_arr = new T*[num_chunks];

            for (size_t i = 0; i < num_chunks; i++) {
                arr_of_arr[i] = new T[buf_size];
                for (size_t j = 0; j < buf_size; j++) {
                    arr_of_arr[i][j] = other.arr_of_arr[i][j];
                }
            }
        }
    }

    SegmentedDynamicArray(const DynamicArray<T> &other) :
        arr_of_arr(nullptr),
        start(0),
        size(0),
        capacity(0),
        num_chunks(0)
    {
        for (size_t i = 0; i < other.GetSize(); i++) {
            Append(other.Get(i));
        }
        Resize(size);
    }

    ~SegmentedDynamicArray() {
        if (arr_of_arr != nullptr) {
            for (size_t i = 0; i < num_chunks; i++) {
                delete[] arr_of_arr[i];
            }
            delete[] arr_of_arr;
        }
    }

    
    T Get(size_t index) const
    {
        if (index >= size) throw IndexOutOfRange(index, size);
        index += start;
        return arr_of_arr[index / buf_size][index % buf_size];
    }

    size_t GetSize() const {
        return size;
    }

    SegmentedDynamicArray *GetSubArray(size_t start_i, size_t end_i) const {
        if (start_i >= size || end_i > size) {
            throw IndexOutOfRange(end_i, size);
        }
        else if (start_i > end_i) {
            throw InvalidRange(start_i, end_i);
        }
        T *null_val = new T[end_i - start_i]();
        SegmentedDynamicArray *subArray = new SegmentedDynamicArray(null_val, end_i - start_i);
        delete[] null_val;
        for (size_t i = start_i; i < end_i; i++) {
            subArray->Set(i - start_i, Get(i));
        }
        return subArray;
    }

    std::string ToString() const {
        std::stringstream ss;
        ss << "[" << ((size == 0) ? " empty ]" : "");
        for (size_t i = 0; i < size; i++) {
            if (i < size - 1) {
                ss << Get(i) << ", ";
            }
            else if (i == size - 1) {
                ss << Get(i) << "]";
            }
        }
        return ss.str();
    }


    void Set(size_t index, T value)
    {
        if (index >= size) throw IndexOutOfRange(index, size);
        index += start;
        arr_of_arr[index / buf_size][index % buf_size] = value;
    }

    void Resize(size_t raw_new_capacity) {
        size_t new_num_chunks = (raw_new_capacity + buf_size - 1) / buf_size;
        size_t new_capacity = new_num_chunks * buf_size;
        size_t new_size = (size < new_capacity) ? size : new_capacity;
        size_t new_start = (new_capacity - new_size) / 2;

        T **new_arr_of_arr = new T*[new_num_chunks];
        for (size_t i = 0; i < new_num_chunks; i++) {
            new_arr_of_arr[i] = new T[buf_size];
        }

        for (size_t i = 0; i < new_size; i++) {
            new_arr_of_arr[(i + new_start) / buf_size][(i + new_start) % buf_size] = Get(i);
        }

        if (arr_of_arr != nullptr) {
            for (size_t i = 0; i < num_chunks; i++) {
                delete[] arr_of_arr[i];
            }
            delete[] arr_of_arr;
        }
        arr_of_arr = new_arr_of_arr;
        start = new_start;
        size = new_size;
        capacity = new_capacity;
        num_chunks = new_num_chunks;
    }
    
    void Append(T value) {
        if (start + size == capacity) Resize((capacity == 0) ? buf_size : capacity * 2);
        arr_of_arr[(start + size) / buf_size][(start + size) % buf_size] = value;
        size++;
    }

    void Prepend(T value) {
        if (start == 0) Resize((capacity == 0) ? buf_size : capacity * 2);
        if (size != 0) start--;
        arr_of_arr[start / buf_size][start % buf_size] = value;
        size++;
    }

    void InsertAt(size_t index, T value)
    {
        if (index > size) throw IndexOutOfRange(index, size);
        if (index == size) {
            Append(value);
        }
        else if(index == 0) {
            Prepend(value);
        }
        else {
            if (index >= size / 2) {
                Append(Get(size - 1));
                for (size_t end_i = size - 2; end_i > index; end_i--) {
                    Set(end_i, Get(end_i - 1));
                }
            }
            else {
                Prepend(Get(0));
                for (size_t start_i = 1; start_i < index; start_i++) {
                    Set(start_i, Get(start_i + 1));
                }
            }
            Set(index, value);
        }
    }

    void RemoveAt(size_t index)
    {
        if (index >= size) throw IndexOutOfRange(index, size);
        if (index >= size / 2) {
            for (; index < size - 1; index++) {
                Set(index, Get(index + 1));
            }
        }
        else {
            for (; index > 0; index--) {
                Set(index, Get(index - 1));
            }
            start++;
        }
        size--;
    }

    SegmentedDynamicArray *ConcatInPlace(const SegmentedDynamicArray &other) {
        size_t addSize = other.GetSize();
        for (size_t i = 0; i < addSize; i++) {
            Append(other.Get(i));
        }
        return this;
    }

    SegmentedDynamicArray *Map(T (*func)(T)) {
        for (size_t i = 0; i < size; i++) {
            Set(i, func(Get(i)));
        }
        return this;
    }
    SegmentedDynamicArray *Where(bool (*func)(T)) {
        size_t newSize = 0;
        for (size_t i = 0; i < size; i++) {
            if (func(Get(i))) {
                Set(newSize, Get(i));
                newSize++;
            }
        }
        size = newSize;
        Resize(size);
        return this;
    }
    T Reduce(T (*func)(T, T), T c) const {
        T result = c;
        for (size_t i = 0; i < size; i++) {
            result = func(Get(i), result);
        }
        return result;
    }

    bool IsSubArray(const SegmentedDynamicArray* subarr) const {
        if (subarr == nullptr) return false;
        if (subarr->size == 0) return true;
        if (subarr->size > size) return false;

        for (size_t i = 0; i <= size - subarr->size; i++) {
            bool found = true;
            for (size_t j = 0; j < subarr->size; j++) {
                if (Get(i + j) != subarr->Get(j)) {
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

    void Sort() {
        if (size > 0) {
            QuickSort(0, size - 1);
        }
    }

private:
    size_t partition(size_t low, size_t high) {
        T pivot = Get(high);
        size_t i = low;

        for (size_t j = low; j < high; j++) {
            if (Get(j) <= pivot) {
                T temp = Get(i);
                Set(i, Get(j));
                Set(j, temp);
                i++;
            }
        }
        T temp = Get(i);
        Set(i, Get(high));
        Set(high, temp);
        return i;
    }

    void QuickSort(size_t low, size_t high) {
        if (low < high) {
            size_t pi = partition(low, high);
            if (pi > 0) {
                QuickSort(low, pi - 1);
            }
            QuickSort(pi + 1, high);
        }
    }
};
