#pragma once

#include <cstddef>
#include <string>

#include "supported_typeinfo.h"
#include "linked_list.h"
#include "sequence.h"

template <typename T>
class ListSequence : public Sequence<T> {
protected:
    LinkedList<T> *list;

public:
    ListSequence() :
        list(new LinkedList<T>())
    {}
    ListSequence(T *items, size_t count) :
        list(new LinkedList<T>(items, count))
    {}
    ListSequence(const LinkedList<T> &lst) :
        list(new LinkedList<T>(lst))
    {}
    ListSequence(const ListSequence<T> &other) :
        list(new LinkedList<T>(*other.list))
    {}
    ListSequence(const DynamicArray<T> &other) :
        list(new ListSequence<T>(other))
    {}
    
    virtual ~ListSequence() {
        delete list;
    }

    ListSequence *Clone() const override = 0;

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

    ListSequence *GetSubSequence(size_t start, size_t end) const override
    {
        LinkedList<T> *subList = list->GetSubList(start, end);
        ListSequence *subSequence = CreateFromList(*subList);
        delete subList;
        return subSequence;
    }
    
    my_type GetType() const override = 0;
    std::string ToString() const override {
        return list->ToString();
    }

protected:
    virtual ListSequence *Instance() = 0;
    virtual ListSequence *CreateFromList(const LinkedList<T> &lst) const = 0;

public:
    ListSequence *Set(size_t index, T item) override {
        ListSequence* new_list = Instance();
        new_list->list->Set(index, item);
        return new_list;
    }
    ListSequence *Append(T item) override {
        ListSequence* new_list = Instance();
        new_list->list->Append(item);
        return new_list;
    }
    ListSequence *Prepend(T item) override {
        ListSequence* new_list = Instance();
        new_list->list->Prepend(item);
        return new_list;
    }
    ListSequence *InsertAt(size_t index, T item) override {
        ListSequence* new_list = Instance();
        new_list->list->InsertAt(index, item);
        return new_list;
    }
    ListSequence *RemoveAt(size_t index) override {
        ListSequence* new_list = Instance();
        new_list->list->RemoveAt(index);
        return new_list;
    }
    
    ListSequence *Concat(const ListSequence<T> &lst) {
        ListSequence* new_list = Instance();
        new_list->list->ConcatInPlace(*lst.list);
        return new_list;
    }

    ListSequence *Map(T (*func)(T)) override {
        ListSequence *new_seq = Instance();
        new_seq->list->Map(func);
        return new_seq;
    }
    ListSequence *Where(bool (*func)(T)) override {
        ListSequence *new_seq = Instance();
        new_seq->list->Where(func);
        return new_seq;
    }
    T Reduce(T (*func)(T, T), T c) const override {
        T result = list->Reduce(func, c);
        return result;
    }

    bool IsSubSequence(const ListSequence *subseq) const {
        return list->IsSubList(subseq->list);
    }

    int CountInversions() const override {
        return list->CountInversions();
    }
};

template <typename T>
class MutableListSequence : public ListSequence<T> {
public:
    using ListSequence<T>::ListSequence;
    
    MutableListSequence(const ListSequence<T> &other) :
        ListSequence<T>(other)
    {}

    MutableListSequence *Clone() const override {
        return new MutableListSequence(*this);
    }
protected:
    MutableListSequence *Instance() override {
        return this;
    }

    MutableListSequence *CreateFromList(const LinkedList<T> &lst) const override {
        return new MutableListSequence(lst);
    }

public:
    my_type GetType() const override {
        return mut_lst_seq;
    }
};

template <typename T>
class ImmutableListSequence : public ListSequence<T> {
public:
    using ListSequence<T>::ListSequence;

    ImmutableListSequence(const ListSequence<T> &other) :
        ListSequence<T>(other)
    {}

    ImmutableListSequence *Clone() const override {
        return new ImmutableListSequence(*this);
    }
protected:
    ImmutableListSequence *Instance() override {
        return Clone();
    }

    ImmutableListSequence *CreateFromList(const LinkedList<T> &lst) const override {
        return new ImmutableListSequence(lst);
    }
public:
    my_type GetType() const override {
        return imm_lst_seq;
    }
};