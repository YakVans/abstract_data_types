#pragma once

#include <cstddef>
#include <string>

#include "supported_typeinfo.h"
#include "doubly_linked_list.h"
#include "sequence.h"
#include "array_sequence.h"

template <typename T>
class DoublyListSequence : public Sequence<T> {
protected:
    DoublyLinkedList<T> *list;

public:
    DoublyListSequence() :
        list(new DoublyLinkedList<T>())
    {}
    DoublyListSequence(T *items, size_t count) :
        list(new DoublyLinkedList<T>(items, count))
    {}
    DoublyListSequence(const DoublyLinkedList<T> &lst) :
        list(new DoublyLinkedList<T>(lst))
    {}
    DoublyListSequence(const DoublyListSequence<T> &other) :
        list(new DoublyLinkedList<T>(*other.list))
    {}
    DoublyListSequence(const DynamicArray<T> &other) :
        list(new DoublyLinkedList<T>(other))
    {}
    
    virtual ~DoublyListSequence() {
        delete list;
    }

    DoublyListSequence *Clone() const override = 0;

    T GetFirst() const override {
        return list->GetFirst();
    }
    T GetLast() const override {
        return list->GetLast();
    }
    T Get(size_t index) const override {
        return list->Get(index);
    }
    size_t GetLength() const override {
        return list->GetLength();
    }

    DoublyListSequence *GetSubSequence(size_t start, size_t end) const override
    {
        DoublyLinkedList<T> *subList = list->GetSubList(start, end);
        DoublyListSequence *subSequence = CreateFromList(*subList);
        delete subList;
        return subSequence;
    }
    
    my_type GetType() const override = 0;
    std::string ToString() const override {
        return list->ToString();
    }

protected:
    virtual DoublyListSequence *Instance() = 0;
    virtual DoublyListSequence *CreateFromList(const DoublyLinkedList<T> &lst) const = 0;

public:
    DoublyListSequence *Set(size_t index, T item) override {
        DoublyListSequence* new_list = Instance();
        new_list->list->Set(index, item);
        return new_list;
    }
    DoublyListSequence *Append(T item) override {
        DoublyListSequence* new_list = Instance();
        new_list->list->Append(item);
        return new_list;
    }
    DoublyListSequence *Prepend(T item) override {
        DoublyListSequence* new_list = Instance();
        new_list->list->Prepend(item);
        return new_list;
    }
    DoublyListSequence *InsertAt(size_t index, T item) override {
        DoublyListSequence* new_list = Instance();
        new_list->list->InsertAt(index, item);
        return new_list;
    }
    DoublyListSequence *RemoveAt(size_t index) override {
        DoublyListSequence* new_list = Instance();
        new_list->list->RemoveAt(index);
        return new_list;
    }
    
    DoublyListSequence *Concat(const DoublyListSequence<T> &lst) {
        DoublyListSequence* new_list = Instance();
        new_list->list->ConcatInPlace(*lst.list);
        return new_list;
    }

    DoublyListSequence *Map(T (*func)(T)) override {
        DoublyListSequence *new_seq = Instance();
        new_seq->list->Map(func);
        return new_seq;
    }
    DoublyListSequence *Where(bool (*func)(T)) override {
        DoublyListSequence *new_seq = Instance();
        new_seq->list->Where(func);
        return new_seq;
    }
    T Reduce(T (*func)(T, T), T c) const override {
        T result = list->Reduce(func, c);
        return result;
    }

    bool IsSubSequence(const DoublyListSequence *subseq) const {
        return list->IsSubList(subseq->list);
    }

    int CountInversions() const override {
        return list->CountInversions();
    }

    DoublyListSequence *Sort() {
        DoublyListSequence* new_list = Instance();
        new_list->list->Sort();
        return new_list;
    }
};

template <typename T>
class MutableDoublyListSequence : public DoublyListSequence<T> {
public:
    using DoublyListSequence<T>::DoublyListSequence;

    MutableDoublyListSequence(const DoublyListSequence<T> &other) :
        DoublyListSequence<T>(other)
    {}

    MutableDoublyListSequence *Clone() const override {
        return new MutableDoublyListSequence(*this);
    }
protected:
    MutableDoublyListSequence *Instance() override {
        return this;
    }

    MutableDoublyListSequence *CreateFromList(const DoublyLinkedList<T> &lst) const override {
        return new MutableDoublyListSequence(lst);
    }

public:
    my_type GetType() const override {
        return mut_lst_seq;
    }
};

template <typename T>
class ImmutableDoublyListSequence : public DoublyListSequence<T> {
public:
    using DoublyListSequence<T>::DoublyListSequence;

    ImmutableDoublyListSequence(const DoublyListSequence<T> &other) :
        DoublyListSequence<T>(other)
    {}

    ImmutableDoublyListSequence *Clone() const override {
        return new ImmutableDoublyListSequence(*this);
    }
protected:
    ImmutableDoublyListSequence *Instance() override {
        return Clone();
    }

    ImmutableDoublyListSequence *CreateFromList(const DoublyLinkedList<T> &lst) const override {
        return new ImmutableDoublyListSequence(lst);
    }
public:
    my_type GetType() const override {
        return imm_lst_seq;
    }
};