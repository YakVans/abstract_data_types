#pragma once

#include <cstddef>
#include <string>

#include "supported_typeinfo.h"
#include "segmented_dynamic_array.h"
#include "sequence.h"

template <typename T>
class SegmentedArraySequence : public Sequence<T> {
protected:
    SegmentedDynamicArray<T> *array;

public:
    SegmentedArraySequence() :
        array(new SegmentedDynamicArray<T>())
    {}
    SegmentedArraySequence(T *items, size_t count) :
        array(new SegmentedDynamicArray<T>(items, count))
    {}
    SegmentedArraySequence(const SegmentedDynamicArray<T> &arr) :
        array(new SegmentedDynamicArray<T>(arr))
    {}
    SegmentedArraySequence(const SegmentedArraySequence<T> &other) :
        array(new SegmentedDynamicArray<T>(*other.array))
    {}
    SegmentedArraySequence(const DynamicArray<T> &other) :
        array(new SegmentedArraySequence<T>(other))
    {}
    
    virtual ~SegmentedArraySequence() {
        delete array;
    }

    SegmentedArraySequence *Clone() const override = 0;

    size_t GetLength() const override {
        return array->GetSize();
    }
    T GetFirst() const override {
        return array->Get(0);
    }
    T GetLast() const override {
        return array->Get(GetLength() - 1);
    }
    T Get(size_t index) const override {
        return array->Get(index);
    }

    SegmentedArraySequence *GetSubSequence(size_t start, size_t end) const override
    {
        SegmentedDynamicArray<T> *subArray = array->GetSubArray(start, end);
        SegmentedArraySequence *subSequence = CreateFromArray(*subArray);
        delete subArray;
        return subSequence;
    }
    
    my_type GetType() const override = 0;
    std::string ToString() const override {
        return array->ToString();
    }

protected:
    virtual SegmentedArraySequence *Instance() = 0;
    virtual SegmentedArraySequence *CreateFromArray(const SegmentedDynamicArray<T> &arr) const = 0;

public:
    SegmentedArraySequence *Set(size_t index, T item) override {
        SegmentedArraySequence* new_array = Instance();
        new_array->array->Set(index, item);
        return new_array;
    }
    SegmentedArraySequence *Append(T item) override {
        SegmentedArraySequence* new_array = Instance();
        new_array->array->Append(item);
        return new_array;
    }
    SegmentedArraySequence *Prepend(T item) override {
        SegmentedArraySequence* new_array = Instance();
        new_array->array->Prepend(item);
        return new_array;
    }
    SegmentedArraySequence *InsertAt(size_t index, T item) override {
        SegmentedArraySequence* new_array = Instance();
        new_array->array->InsertAt(index, item);
        return new_array;
    }
    SegmentedArraySequence *RemoveAt(size_t index) override {
        SegmentedArraySequence* new_array = Instance();
        new_array->array->RemoveAt(index);
        return new_array;
    }
    
    SegmentedArraySequence *Concat(const SegmentedArraySequence<T> &arr) {
        SegmentedArraySequence* new_array = Instance();
        new_array->array->ConcatInPlace(*arr.array);
        return new_array;
    }

    SegmentedArraySequence *Map(T (*func)(T)) override {
        SegmentedArraySequence *new_seq = Instance();
        new_seq->array->Map(func);
        return new_seq;
    }
    SegmentedArraySequence *Where(bool (*func)(T)) override {
        SegmentedArraySequence *new_seq = Instance();
        new_seq->array->Where(func);
        return new_seq;
    }
    T Reduce(T (*func)(T, T), T c) const override {
        T result = array->Reduce(func, c);
        return result;
    }

    bool IsSubSequence(const SegmentedArraySequence *subseq) const {
        return array->IsSubArray(subseq->array);
    }

    int CountInversions() const override {
        return array->CountInversions();
    }

    SegmentedArraySequence *Sort() {
        SegmentedArraySequence* new_seq = Instance();
        new_seq->array->Sort();
        return new_seq;
    }
};

template <typename T>
class MutableSegmentedArraySequence : public SegmentedArraySequence<T> {
public:
    using SegmentedArraySequence<T>::SegmentedArraySequence;

    MutableSegmentedArraySequence(const SegmentedArraySequence<T> &other) :
        SegmentedArraySequence<T>(other)
    {}

    MutableSegmentedArraySequence *Clone() const override {
        return new MutableSegmentedArraySequence(*this);
    }
protected:
    MutableSegmentedArraySequence *Instance() override {
        return this;
    }

    MutableSegmentedArraySequence *CreateFromArray(const SegmentedDynamicArray<T> &arr) const override {
        return new MutableSegmentedArraySequence(arr);
    }

public:
    my_type GetType() const override {
        return mut_lst_seq;
    }
};

template <typename T>
class ImmutableSegmentedArraySequence : public SegmentedArraySequence<T> {
public:
    using SegmentedArraySequence<T>::SegmentedArraySequence;

    ImmutableSegmentedArraySequence(const SegmentedArraySequence<T> &other) :
        SegmentedArraySequence<T>(other)
    {}

    ImmutableSegmentedArraySequence *Clone() const override {
        return new ImmutableSegmentedArraySequence(*this);
    }
protected:
    ImmutableSegmentedArraySequence *Instance() override {
        return Clone();
    }

    ImmutableSegmentedArraySequence *CreateFromArray(const SegmentedDynamicArray<T> &arr) const override {
        return new ImmutableSegmentedArraySequence(arr);
    }
public:
    my_type GetType() const override {
        return imm_lst_seq;
    }
};