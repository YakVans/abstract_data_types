#pragma once

#include <iostream>
#include <cstddef>
#include <string>

#include "segmented_array_sequence.h"
#include "supported_typeinfo.h"

template <typename T>
class SegmentedDeque {
protected:
    SegmentedArraySequence<T> *seq;

    SegmentedDeque(SegmentedArraySequence<T>* sequence) :
        seq(sequence)
    {}

public:
    virtual ~SegmentedDeque() {
        delete seq;
    }

    virtual SegmentedDeque *Clone() const = 0;

    size_t size() const {
        return seq->GetLength();
    }
    T front() const {
        return seq->Get(0);
    }
    T back() const {
        return seq->Get(size() - 1);
    }

    SegmentedDeque *GetSubSegDeque(size_t start, size_t end) const {
        SegmentedArraySequence<T> *new_seq = seq->GetSubSequence(start, end);
        SegmentedDeque *new_seg_deque = CreateFromSequence(new_seq);
        delete new_seq;
        return new_seg_deque;
    }

    virtual mut_type MutType() const = 0;

    my_element_type GetElementType() const {
        return seq->GetElementType();
    }

    std::string ToString() const {
        return seq->ToString();
    }

protected:
    virtual SegmentedDeque<T> *Instance() = 0;
    virtual SegmentedDeque *CreateFromSequence(SegmentedArraySequence<T>* sequence) const = 0;

public:
    SegmentedDeque *push_back(const T &value) {
        if (MutType() == mut) {
            seq->Append(value);
            return this;
        }
        else {
            SegmentedDeque<T> *new_deque = Instance();
            SegmentedArraySequence<T> *new_seq = new_deque->seq;
            new_deque->seq = new_deque->seq->Append(value);
            delete new_seq;
            return new_deque;
        }
    }
    SegmentedDeque *push_front(const T &value) {
        if (MutType() == mut) {
            seq->Prepend(value);
            return this;
        }
        else {
            SegmentedDeque<T> *new_deque = Instance();
            SegmentedArraySequence<T> *new_seq = new_deque->seq;
            new_deque->seq = new_deque->seq->Prepend(value);
            delete new_seq;
            return new_deque;
        }
    }
    SegmentedDeque *pop_back() {
        if (MutType() == mut) {
            seq->RemoveAt(size() - 1);
            return this;
        }
        else {
            SegmentedDeque<T> *new_deque = Instance();
            SegmentedArraySequence<T> *new_seq = new_deque->seq;
            new_deque->seq = new_deque->seq->RemoveAt(size() - 1);
            delete new_seq;
            return new_deque;
        }
    }
    SegmentedDeque *pop_front() {
        if (MutType() == mut) {
            seq->RemoveAt(0);
            return this;
        }
        else {
            SegmentedDeque<T> *new_deque = Instance();
            SegmentedArraySequence<T> *new_seq = new_deque->seq;
            new_deque->seq = new_deque->seq->RemoveAt(0);
            delete new_seq;
            return new_deque;
        }
    }

    bool IsSubSegDeque(const SegmentedDeque *subsegdeque) const {
        return seq->IsSubSequence(subsegdeque->seq);
    }

    SegmentedDeque *Map(T (*func)(T)) {
        if (MutType() == mut) {
            seq->Map(func);
            return this;
        }
        else {
            SegmentedDeque<T> *new_deque = Instance();
            SegmentedArraySequence<T> *new_seq = new_deque->seq;
            new_deque->seq = new_deque->seq->Map(func);
            delete new_seq;
            return new_deque;
        }
    }
    SegmentedDeque *Where(bool (*func)(T)) {
        if (MutType() == mut) {
            seq->Where(func);
            return this;
        }
        else {
            SegmentedDeque<T> *new_deque = Instance();
            SegmentedArraySequence<T> *new_seq = new_deque->seq;
            new_deque->seq = new_deque->seq->Where(func);
            delete new_seq;
            return new_deque;
        }
    }
    T Reduce(T (*func)(T, T), T c) const {
        T result = seq->Reduce(func, c);
        return result;
    }

    SegmentedDeque *Concat(const SegmentedDeque &other) {
        if (MutType() == mut) {
            seq->Concat(*other.seq);
            return this;
        }
        else {
            SegmentedDeque<T> *new_stack = Instance();
            SegmentedArraySequence<T> *new_seq = new_stack->seq;
            new_stack->seq = new_stack->seq->Concat(*other.seq);
            delete new_seq;
            return new_stack;
        }
    }

    int CountInversions() const {
        return seq->CountInversions();
    }

    SegmentedDeque *Sort() {
        if (MutType() == mut) {
            seq->Sort();
            return this;
        }
        else {
            SegmentedDeque<T> *new_deque = Instance();
            SegmentedArraySequence<T> *new_seq = new_deque->seq;
            new_deque->seq = new_deque->seq->Sort();
            delete new_seq;
            return new_deque;
        }
    }
};

template <typename T>
class MutableSegmentedDeque : public SegmentedDeque<T> {
public:
    MutableSegmentedDeque() :
        SegmentedDeque<T>(new MutableSegmentedArraySequence<T>())
    {}
    MutableSegmentedDeque(T* items, size_t count) : 
        SegmentedDeque<T>(new MutableSegmentedArraySequence<T>(items, count))
    {}
    MutableSegmentedDeque(const SegmentedArraySequence<T> &other) :
        SegmentedDeque<T>(new MutableSegmentedArraySequence<T>(other))
    {}
    MutableSegmentedDeque(const MutableSegmentedDeque<T> &other) :
        SegmentedDeque<T>(new MutableSegmentedArraySequence<T>(*other.seq))
    {}
    MutableSegmentedDeque(const SegmentedDeque<T> &other) :
        SegmentedDeque<T>(new MutableSegmentedArraySequence<T>(*other.seq))
    {}

    MutableSegmentedDeque *Clone() const override {
        return new MutableSegmentedDeque(*this);
    }

    mut_type MutType() const override {
        return mut;
    }

protected:
    MutableSegmentedDeque<T> *Instance() override {
        return this;
    }
    SegmentedDeque<T> *CreateFromSequence(SegmentedArraySequence<T>* sequence) const override {
        return new MutableSegmentedDeque(*sequence);
    }
};

template <typename T>
class ImmutableSegmentedDeque : public SegmentedDeque<T> {
public:
    ImmutableSegmentedDeque() :
        SegmentedDeque<T>(new ImmutableSegmentedArraySequence<T>())
    {}
    ImmutableSegmentedDeque(T* items, size_t count) : 
        SegmentedDeque<T>(new ImmutableSegmentedArraySequence<T>(items, count))
    {}
    ImmutableSegmentedDeque(const SegmentedArraySequence<T> &other) :
        SegmentedDeque<T>(new MutableSegmentedArraySequence<T>(other))
    {}
    ImmutableSegmentedDeque(const ImmutableSegmentedDeque<T> &other) :
        SegmentedDeque<T>(new ImmutableSegmentedArraySequence<T>(*other.seq))
    {}
    ImmutableSegmentedDeque(const SegmentedDeque<T> &other) :
        SegmentedDeque<T>(new ImmutableSegmentedArraySequence<T>(*other.seq))
    {}

    ImmutableSegmentedDeque *Clone() const override {
        return new ImmutableSegmentedDeque(*this);
    }

    mut_type MutType() const override {
        return imm;
    }

protected:
    ImmutableSegmentedDeque<T> *Instance() override {
        return this->Clone();
    }
    SegmentedDeque<T> *CreateFromSequence(SegmentedArraySequence<T>* sequence) const override {
        return new ImmutableSegmentedDeque(*sequence);
    }
};