#pragma once

#include <cstddef>
#include <string>

#include "list_sequence.h"
#include "supported_typeinfo.h"

template <typename T>
class Stack {
protected:
    ListSequence<T> *seq;

    Stack(ListSequence<T>* sequence) :
        seq(sequence)
    {}

public:
    virtual ~Stack() {
        delete seq;
    }

    virtual Stack *Clone() const = 0;

    size_t size() const {
        return seq->GetLength();
    }
    T top() const {
        return seq->GetFirst();
    }

    Stack *GetSubStack(size_t start, size_t end) const {
        ListSequence<T> *new_seq = seq->GetSubSequence(start, end);
        Stack *new_stack = CreateFromSequence(new_seq);
        delete new_seq;
        return new_stack;
    }

    virtual mut_type MutType() const = 0;

    my_element_type GetElementType() const {
        return seq->GetElementType();
    }

    std::string ToString() const {
        return seq->ToString();
    }

protected:
    virtual Stack *Instance() = 0;
    virtual Stack *CreateFromSequence(ListSequence<T>* sequence) const = 0;

public:
    Stack *push(const T &value) {
        if (MutType() == mut) {
            seq->Prepend(value);
            return this;
        }
        else {
            Stack<T> *new_stack = Instance();
            ListSequence<T> *new_seq = new_stack->seq;
            new_stack->seq = new_stack->seq->Prepend(value);
            delete new_seq;
            return new_stack;
        }
    }
    Stack *pop() {
        if (MutType() == mut) {
            seq->RemoveAt(0);
            return this;
        }
        else {
            Stack<T> *new_stack = Instance();
            ListSequence<T> *new_seq = new_stack->seq;
            new_stack->seq = new_stack->seq->RemoveAt(0);
            delete new_seq;
            return new_stack;
        }
    }

    bool IsSubStack(const Stack *substack) const {
        return seq->IsSubSequence(substack->seq);
    }

    Stack *Map(T (*func)(T)) {
        if (MutType() == mut) {
            seq->Map(func);
            return this;
        }
        else {
            Stack<T> *new_stack = Instance();
            ListSequence<T> *new_seq = new_stack->seq;
            new_stack->seq = new_stack->seq->Map(func);
            delete new_seq;
            return new_stack;
        }
    }
    Stack *Where(bool (*func)(T)) {
        if (MutType() == mut) {
            seq->Where(func);
            return this;
        }
        else {
            Stack<T> *new_stack = Instance();
            ListSequence<T> *new_seq = new_stack->seq;
            new_stack->seq = new_stack->seq->Where(func);
            delete new_seq;
            return new_stack;
        }
    }
    T Reduce(T (*func)(T, T), T c) const {
        T result = seq->Reduce(func, c);
        return result;
    }

    Stack *Concat(const Stack &other) {
        if (MutType() == mut) {
            seq->Concat(*other.seq);
            return this;
        }
        else {
            Stack<T> *new_stack = Instance();
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
class MutableStack : public Stack<T> {
public:
    MutableStack() :
        Stack<T>(new MutableListSequence<T>())
    {}
    MutableStack(T* items, size_t count) : 
        Stack<T>(new MutableListSequence<T>(items, count))
    {}
    MutableStack(const ListSequence<T> &other) :
        Stack<T>(new MutableListSequence<T>(other))
    {}
    MutableStack(const MutableStack &other) :
        Stack<T>(new MutableListSequence<T>(*other.seq))
    {}
    MutableStack(const Stack<T> &other) :
        Stack<T>(new MutableListSequence<T>(*other.seq))
    {}

    MutableStack *Clone() const override {
        return new MutableStack(*this);
    }

    mut_type MutType() const override {
        return mut;
    }

protected:
    MutableStack *Instance() override {
        return this;
    }
    Stack<T> *CreateFromSequence(ListSequence<T>* sequence) const override {
        return new MutableStack(*sequence);
    }
};

template <typename T>
class ImmutableStack : public Stack<T> {
public:
    ImmutableStack() :
        Stack<T>(new ImmutableListSequence<T>())
    {}
    ImmutableStack(T* items, size_t count) : 
        Stack<T>(new ImmutableListSequence<T>(items, count))
    {}
    ImmutableStack(const ListSequence<T> &other) :
        Stack<T>(new ImmutableListSequence<T>(other))
    {}
    ImmutableStack(const ImmutableStack<T> &other) :
        Stack<T>(new ImmutableListSequence<T>(*other.seq))
    {}
    ImmutableStack(const Stack<T> &other) :
        Stack<T>(new ImmutableListSequence<T>(*other.seq))
    {}

    ImmutableStack *Clone() const override {
        return new ImmutableStack(*this);
    }

    mut_type MutType() const override {
        return imm;
    }

protected:
    ImmutableStack<T> *Instance() override {
        return this->Clone();
    }
    Stack<T> *CreateFromSequence(ListSequence<T>* sequence) const override {
        return new ImmutableStack(*sequence);
    }
};