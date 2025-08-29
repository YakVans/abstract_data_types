#pragma once

#include <cstddef>

#include "supported_typeinfo.h"
#include "dynamic_array.h"
#include "sequence.h"

template <typename T>
class ArraySequence : public Sequence<T> {
protected:
    DynamicArray<T> *array;

public:
    ArraySequence() :
        array(new DynamicArray<T>())
    {}
    ArraySequence(size_t count) :
        array(new DynamicArray<T>(count))
    {}
    ArraySequence(T *items, size_t count) :
        array(new DynamicArray<T>(items, count))
    {}
    ArraySequence(const DynamicArray<T> &arr) :
        array(new DynamicArray<T>(arr))
    {}
    ArraySequence(const ArraySequence<T> &other) :
        array(new DynamicArray<T>(*other.array))
    {}

    virtual ~ArraySequence() {
        delete array;
    }

    ArraySequence *Clone() const override = 0;
    
    T GetFirst() const override {
        return array->Get(0);
    }
    T GetLast() const override {
        return array->Get(array->GetSize() - 1);
    }
    T Get(size_t index) const override {
        return array->Get(index);
    }
    size_t GetLength() const override {
        return array->GetSize();
    }
    my_type GetType() const override = 0;
    std::string ToString() const override {
        return array->ToString();
    }

    ArraySequence *GetSubSequence(size_t start, size_t end) const override
    {
        DynamicArray<T> *subArray = array->GetSubArray(start, end);
        ArraySequence *subSequence = CreateFromArray(*subArray);
        delete subArray;
        return subSequence;
    }

protected:
    virtual ArraySequence *Instance() = 0;
    virtual ArraySequence *CreateFromArray(const DynamicArray<T> &arr) const = 0;

public:
    ArraySequence *Set(size_t index, T item) override {
        ArraySequence *new_arr = Instance();
        new_arr->array->Set(index, item);
        return new_arr;
    }
    ArraySequence *Append(T item) override {
        ArraySequence *new_arr = Instance();
        new_arr->array->InsertAt(new_arr->array->GetSize(), item);
        return new_arr;
    }
    ArraySequence *Prepend(T item) override {
        ArraySequence *new_arr = Instance();
        new_arr->array->InsertAt(0, item);
        return new_arr;
    }
    ArraySequence *InsertAt(size_t index, T item) override {
        ArraySequence *new_arr = Instance();
        new_arr->array->InsertAt(index, item);
        return new_arr;
    }
    ArraySequence *RemoveAt(size_t index) override {
        ArraySequence *new_arr = Instance();
        new_arr->array->RemoveAt(index);
        return new_arr;
    }

    ArraySequence *Concat(const ArraySequence<T> &arr) {
        ArraySequence* new_array = Instance();
        new_array->array->ConcatInPlace(*arr.array);
        return new_array;
    }

    ArraySequence *Map(T (*func)(T)) override {
        ArraySequence *new_seq = Instance();
        new_seq->array->Map(func);
        return new_seq;
    }
    ArraySequence *Where(bool (*func)(T)) override {
        ArraySequence *new_seq = Instance();
        new_seq->array->Where(func);
        return new_seq;
    }
    T Reduce(T (*func)(T, T), T c) const override {
        T result = array->Reduce(func, c);
        return result;
    }

    bool IsSubSequence(const ArraySequence *subseq) const {
        return array->IsSubArray(subseq->array);
    }

    int CountInversions() const override {
        return array->CountInversions();
    }
};

template <typename T>
class MutableArraySequence : public ArraySequence<T> {
public:
    using ArraySequence<T>::ArraySequence;

    MutableArraySequence(const ArraySequence<T> &other) :
        ArraySequence<T>(other)
    {}

    MutableArraySequence *Clone() const override {
        return new MutableArraySequence(*this);
    }

protected:
    MutableArraySequence *Instance() override {
        return this;
    }

    MutableArraySequence *CreateFromArray(const DynamicArray<T> &arr) const override {
        return new MutableArraySequence(arr);
    }

public:
    my_type GetType() const override {
        return mut_arr_seq;
    }
};

template <typename T>
class ImmutableArraySequence : public ArraySequence<T> {
public:
    using ArraySequence<T>::ArraySequence;

    ImmutableArraySequence(const ArraySequence<T> &other) :
        ArraySequence<T>(other)
    {}

    ImmutableArraySequence *Clone() const override {
        return new ImmutableArraySequence(*this);
    }

protected:
    ImmutableArraySequence *Instance() override {
        return Clone();
    }

    ImmutableArraySequence *CreateFromArray(const DynamicArray<T> &arr) const override {
        return new ImmutableArraySequence(arr);
    }

public:
    my_type GetType() const override {
        return imm_arr_seq;
    }
};