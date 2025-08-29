#pragma once

#include <cstddef>
#include <string>

#include "list_sequence.h"
#include "supported_typeinfo.h"

template <typename T>
class Queue {
protected:
    ListSequence<T> *seq;

    Queue(ListSequence<T>* sequence) :
        seq(sequence)
    {}

public:
    virtual ~Queue() {
        delete seq;
    }

    virtual Queue *Clone() const = 0;

    size_t size() const {
        return seq->GetLength();
    }
    T front() const {
        return seq->GetFirst();
    }
    T back() const {
        return seq->GetLast();
    }

    Queue *GetSubQueue(size_t start, size_t end) const {
        ListSequence<T> *new_seq = seq->GetSubSequence(start, end);
        Queue *new_queue = CreateFromSequence(new_seq);
        delete new_seq;
        return new_queue;
    }

    virtual mut_type MutType() const = 0;

    my_element_type GetElementType() const {
        return seq->GetElementType();
    }

    std::string ToString() const {
        return seq->ToString();
    }

protected:
    virtual Queue *Instance() = 0;
    virtual Queue *CreateFromSequence(ListSequence<T>* sequence) const = 0;

public:
    Queue *push(const T &value) {
        if (MutType() == mut) {
            seq->Append(value);
            return this;
        }
        else {
            Queue<T> *new_queue = Instance();
            ListSequence<T> *new_seq = new_queue->seq;
            new_queue->seq = new_queue->seq->Append(value);
            delete new_seq;
            return new_queue;
        }
    }
    Queue *pop() {
        if (MutType() == mut) {
            seq->RemoveAt(0);
            return this;
        }
        else {
            Queue<T> *new_queue = Instance();
            ListSequence<T> *new_seq = new_queue->seq;
            new_queue->seq = new_queue->seq->RemoveAt(0);
            delete new_seq;
            return new_queue;
        }
    }

    bool IsSubQueue(const Queue *subqueue) const {
        return seq->IsSubSequence(subqueue->seq);
    }

    Queue *Map(T (*func)(T)) {
        if (MutType() == mut) {
            seq->Map(func);
            return this;
        }
        else {
            Queue<T> *new_queue = Instance();
            ListSequence<T> *new_seq = new_queue->seq;
            new_queue->seq = new_queue->seq->Map(func);
            delete new_seq;
            return new_queue;
        }
    }
    Queue *Where(bool (*func)(T)) {
        if (MutType() == mut) {
            seq->Where(func);
            return this;
        }
        else {
            Queue<T> *new_queue = Instance();
            ListSequence<T> *new_seq = new_queue->seq;
            new_queue->seq = new_queue->seq->Where(func);
            delete new_seq;
            return new_queue;
        }
    }
    T Reduce(T (*func)(T, T), T c) const {
        T result = seq->Reduce(func, c);
        return result;
    }

    Queue *Concat(const Queue &other) {
        if (MutType() == mut) {
            seq->Concat(*other.seq);
            return this;
        }
        else {
            Queue<T> *new_stack = Instance();
            ListSequence<T> *new_seq = new_stack->seq;
            new_stack->seq = new_stack->seq->Concat(*other.seq);
            delete new_seq;
            return new_stack;
        }
    }

    int CountInversions() const {
        return seq->CountInversions();
    }
};

template <typename T>
class MutableQueue : public Queue<T> {
public:
    MutableQueue() :
        Queue<T>(new MutableListSequence<T>())
    {}
    MutableQueue(T* items, size_t count) : 
        Queue<T>(new MutableListSequence<T>(items, count))
    {}
    MutableQueue(const ListSequence<T> &other) :
        Queue<T>(new MutableListSequence<T>(other))
    {}
    MutableQueue(const MutableQueue<T> &other) :
        Queue<T>(new MutableListSequence<T>(*other.seq))
    {}
    MutableQueue(const Queue<T> &other) :
        Queue<T>(new MutableListSequence<T>(*other.seq))
    {}

    MutableQueue *Clone() const override {
        return new MutableQueue(*this);
    }

    mut_type MutType() const override {
        return mut;
    }

protected:
    MutableQueue *Instance() override {
        return this;
    }
    Queue<T> *CreateFromSequence(ListSequence<T>* sequence) const override {
        return new MutableQueue(*sequence);
    }
};

template <typename T>
class ImmutableQueue : public Queue<T> {
public:
    ImmutableQueue() :
        Queue<T>(new ImmutableListSequence<T>())
    {}
    ImmutableQueue(T* items, size_t count) : 
        Queue<T>(new ImmutableListSequence<T>(items, count))
    {}
    ImmutableQueue(const ListSequence<T> &other) :
        Queue<T>(new MutableListSequence<T>(other))
    {}
    ImmutableQueue(const ImmutableQueue<T> &other) :
        Queue<T>(new ImmutableListSequence<T>(*other.seq))
    {}
    ImmutableQueue(const Queue<T> &other) :
        Queue<T>(new ImmutableListSequence<T>(*other.seq))
    {}

    ImmutableQueue *Clone() const override {
        return new ImmutableQueue(*this);
    }

    mut_type MutType() const override {
        return imm;
    }

protected:
    ImmutableQueue<T> *Instance() override {
        return this->Clone();
    }
    Queue<T> *CreateFromSequence(ListSequence<T>* sequence) const override {
        return new ImmutableQueue(*sequence);
    }
};