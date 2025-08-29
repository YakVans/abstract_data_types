#pragma once

#include <iostream>
#include <cstddef>
#include <string>

#include "doubly_list_sequence.h"
#include "supported_typeinfo.h"

template <typename T>
class Deque {
protected:
    DoublyListSequence<T> *seq;

    Deque(DoublyListSequence<T>* sequence) :
        seq(sequence)
    {}

public:
    virtual ~Deque() {
        delete seq;
    }

    virtual Deque *Clone() const = 0;

    size_t size() const {
        return seq->GetLength();
    }
    T front() const {
        return seq->GetFirst();
    }
    T back() const {
        return seq->GetLast();
    }

    Deque *GetSubDeque(size_t start, size_t end) const {
        DoublyListSequence<T> *new_seq = seq->GetSubSequence(start, end);
        Deque *new_deque = CreateFromSequence(new_seq);
        delete new_seq;
        return new_deque;
    }

    virtual mut_type MutType() const = 0;

    my_element_type GetElementType() const {
        return seq->GetElementType();
    }

    std::string ToString() const {
        return seq->ToString();
    }

protected:
    virtual Deque *Instance() = 0;
    virtual Deque *CreateFromSequence(DoublyListSequence<T>* sequence) const = 0;

public:
    Deque *push_back(const T &value) {
        if (MutType() == mut) {
            seq->Append(value);
            return this;
        }
        else {
            Deque<T> *new_deque = Instance();
            DoublyListSequence<T> *new_seq = new_deque->seq;
            new_deque->seq = new_deque->seq->Append(value);
            delete new_seq;
            return new_deque;
        }
    }
    Deque *push_front(const T &value) {
        if (MutType() == mut) {
            seq->Prepend(value);
            return this;
        }
        else {
            Deque<T> *new_deque = Instance();
            DoublyListSequence<T> *new_seq = new_deque->seq;
            new_deque->seq = new_deque->seq->Prepend(value);
            delete new_seq;
            return new_deque;
        }
    }
    Deque *pop_back() {
        if (MutType() == mut) {
            seq->RemoveAt(size() - 1);
            return this;
        }
        else {
            Deque<T> *new_deque = Instance();
            DoublyListSequence<T> *new_seq = new_deque->seq;
            new_deque->seq = new_deque->seq->RemoveAt(size() - 1);
            delete new_seq;
            return new_deque;
        }
    }
    Deque *pop_front() {
        if (MutType() == mut) {
            seq->RemoveAt(0);
            return this;
        }
        else {
            Deque<T> *new_deque = Instance();
            DoublyListSequence<T> *new_seq = new_deque->seq;
            new_deque->seq = new_deque->seq->RemoveAt(0);
            delete new_seq;
            return new_deque;
        }
    }

    bool IsSubDeque(const Deque *subdeque) const {
        return seq->IsSubSequence(subdeque->seq);
    }

    Deque *Map(T (*func)(T)) {
        if (MutType() == mut) {
            seq->Map(func);
            return this;
        }
        else {
            Deque<T> *new_deque = Instance();
            DoublyListSequence<T> *new_seq = new_deque->seq;
            new_deque->seq = new_deque->seq->Map(func);
            delete new_seq;
            return new_deque;
        }
    }
    Deque *Where(bool (*func)(T)) {
        if (MutType() == mut) {
            seq->Where(func);
            return this;
        }
        else {
            Deque<T> *new_deque = Instance();
            DoublyListSequence<T> *new_seq = new_deque->seq;
            new_deque->seq = new_deque->seq->Where(func);
            delete new_seq;
            return new_deque;
        }
    }
    T Reduce(T (*func)(T, T), T c) const {
        T result = seq->Reduce(func, c);
        return result;
    }

    Deque *Concat(const Deque &other) {
        if (MutType() == mut) {
            seq->Concat(*other.seq);
            return this;
        }
        else {
            Deque<T> *new_stack = Instance();
            DoublyListSequence<T> *new_seq = new_stack->seq;
            new_stack->seq = new_stack->seq->Concat(*other.seq);
            delete new_seq;
            return new_stack;
        }
    }

    int CountInversions() const {
        return seq->CountInversions();
    }

    Deque *Sort() {
        if (MutType() == mut) {
            seq->Sort();
            return this;
        }
        else {
            Deque<T> *new_deque = Instance();
            DoublyListSequence<T> *new_seq = new_deque->seq;
            new_deque->seq = new_deque->seq->Sort();
            delete new_seq;
            return new_deque;
        }
    }

};

template <typename T>
class MutableDeque : public Deque<T> {
public:
    MutableDeque() :
        Deque<T>(new MutableDoublyListSequence<T>())
    {}
    MutableDeque(T* items, size_t count) : 
        Deque<T>(new MutableDoublyListSequence<T>(items, count))
    {}
    MutableDeque(const DoublyListSequence<T> &other) :
        Deque<T>(new MutableDoublyListSequence<T>(other))
    {}
    MutableDeque(const MutableDeque<T> &other) :
        Deque<T>(new MutableDoublyListSequence<T>(*other.seq))
    {}
    MutableDeque(const Deque<T> &other) :
        Deque<T>(new MutableDoublyListSequence<T>(*other.seq))
    {}

    MutableDeque *Clone() const override {
        return new MutableDeque(*this);
    }

    mut_type MutType() const override {
        return mut;
    }

protected:
    MutableDeque<T> *Instance() override {
        return this;
    }
    Deque<T> *CreateFromSequence(DoublyListSequence<T>* sequence) const override {
        return new MutableDeque(*sequence);
    }
};

template <typename T>
class ImmutableDeque : public Deque<T> {
public:
    ImmutableDeque() :
        Deque<T>(new ImmutableDoublyListSequence<T>())
    {}
    ImmutableDeque(T* items, size_t count) : 
        Deque<T>(new ImmutableDoublyListSequence<T>(items, count))
    {}
    ImmutableDeque(const DoublyListSequence<T> &other) :
        Deque<T>(new MutableDoublyListSequence<T>(other))
    {}
    ImmutableDeque(const ImmutableDeque<T> &other) :
        Deque<T>(new ImmutableDoublyListSequence<T>(*other.seq))
    {}
    ImmutableDeque(const Deque<T> &other) :
        Deque<T>(new ImmutableDoublyListSequence<T>(*other.seq))
    {}

    ImmutableDeque *Clone() const override {
        return new ImmutableDeque(*this);
    }

    mut_type MutType() const override {
        return imm;
    }

protected:
    ImmutableDeque<T> *Instance() override {
        return this->Clone();
    }
    Deque<T> *CreateFromSequence(DoublyListSequence<T>* sequence) const override {
        return new ImmutableDeque(*sequence);
    }
};

