#pragma once

#include <cstddef>
#include <sstream>

#include "exceptions.h"
#include "dynamic_array.h"

template <typename T>
class LinkedList {
private:
    struct Node {
        T data;
        Node *next;
        Node(T data, Node *next = nullptr) :
            data(data),
            next(next)
        {}
    };

    Node *head;
    Node *tail;
    size_t size;

public:
    LinkedList() :
        head(nullptr),
        tail(nullptr),
        size(0)
    {}

    explicit LinkedList(T *items, size_t count) : // items должен содержать >= size элементов
        head(nullptr),
        tail(nullptr),
        size(0)
    {
        for (size_t i = count; i > 0; i--) Prepend(items[i - 1]);
    }

    LinkedList(const LinkedList &other) :
        head(nullptr),
        tail(nullptr),
        size(0)
    {
        Node *current = other.head;
        while (current) {
            Append(current->data);
            current = current->next;
        }
    }

    LinkedList(const DynamicArray<T> &other) :
        head(nullptr),
        tail(nullptr),
        size(0)
    {
        for (size_t i = 0; i < other.GetSize(); i++) {
            Append(other.Get(i));
        }
    }

    
    ~LinkedList() {
        Node *current = head;
        while (current) {
            Node *next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    
    T GetFirst() const {
        if (!head) throw IndexOutOfRange(0, 0);
        return head->data;
    }

    T GetLast() const {
        if (!tail) throw IndexOutOfRange(0, 0);
        return tail->data;
    }

    T Get(size_t index) const
    {
        if (index >= size) throw IndexOutOfRange(index, size);
        Node *current = head;
        for (size_t i = 0; i < index; i++) current = current->next;
        return current->data;
    }

    size_t GetLength() const {
        return size;
    }

    LinkedList *GetSubList(size_t start, size_t end) const
    {
        if (start >= size || end > size) {
            throw IndexOutOfRange(end, size);
        }
        else if (start > end) {
            throw InvalidRange(start, end);
        }
        LinkedList *subList = new LinkedList();
        Node *current = head;
        for (size_t i = 0; i < start; i++) current = current->next;
        for (size_t i = start; i < end; i++) {
            subList->Append(current->data);
            current = current->next;
        }
        return subList;
    }
    std::string ToString() const {
        std::stringstream ss;
        if (size == 0) {
            ss << "[ empty ]";
        }
        else {
            ss << "[";
            Node *current = head;
            for (size_t i = 0; i < size - 1; i++) {
                ss << current->data << ", ";
                current = current->next;
            }
            ss << current->data << "]";
        }
        return ss.str();
    }

    
    void Set(size_t index, T item)
    {
        if (index >= size) throw IndexOutOfRange(index, size);
        Node *curr = head;
        for (size_t i = 0; i < index; i++) curr = curr->next;
        curr->data = item;
    }

    void Append(T item) {
        Node *newNode = new Node(item, nullptr);
        if (!tail) {
            tail = newNode;
            head = tail;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    void Prepend(T item) {
        head = new Node(item, head);
        if (!tail) tail = head;
        size++;
    }

    void InsertAt(size_t index, T item)
    {
        if (index > size) throw IndexOutOfRange(index, size);
        if (index == 0) {
            Prepend(item);
        }
        else if (index == size) {
            Append(item);
        }
        else {
            Node *prev = head;
            for (size_t i = 0; i < index - 1; i++) prev = prev->next;
            prev->next = new Node(item, prev->next);
            size++;
        }
    }

    void RemoveAt(size_t index)
    {
        if (index >= size) throw IndexOutOfRange(index, size);
        if (index == 0) {
            Node *toDelete = head;
            head = head->next;
            if (size == 1) {
                tail = nullptr;
            }
            delete toDelete;
        }
        else {
            Node *prev = head;
            for (size_t i = 0; i < index - 1; i++) prev = prev->next;
            Node *toDelete = prev->next;
            prev->next = toDelete->next;
            if (index == size - 1) {
                tail = prev;
            }
            delete toDelete;
        }
        size--;
    }


    LinkedList *ConcatInPlace(const LinkedList &list) {
        Node *current = list.head;
        size_t addLength = list.GetLength();
        for (size_t i = 0; i < addLength; i++) {
            this->Append(current->data);
            current = current->next;
        }
        return this;
    }

    LinkedList *Concat(const LinkedList &list) const {
        LinkedList *newList = new LinkedList(*this);
        Node *current = list.head;
        while (current) {
            newList->Append(current->data);
            current = current->next;
        }
        return newList;
    }

    LinkedList *Map(T (*func)(T)) {
        Node *current = head;
        while(current) {
            current->data = func(current->data);
            current = current->next;
        }
        return this;
    }
    LinkedList *Where(bool (*func)(T)) {
        Node *prev = nullptr;
        Node *current = head;
        Node *toDelete;
        while(current) {
            if (!func(current->data)) {
                if (prev == nullptr) {
                    head = current->next;
                }
                else {
                    prev->next = current->next;
                }
                toDelete = current;
                current = current->next;
                delete toDelete;
                size--;
            }
            else {
                prev = current;
                current = current->next;
            }
        }
        tail = prev;
        return this;
    }
    T Reduce(T (*func)(T, T), T c) const {
        T result = c;
        Node *current = head;
        while (current) {
            result = func(current->data, result);
            current = current->next;
        }
        return result;
    }

    bool IsSubList(const LinkedList *sublist) const {
        if (sublist == nullptr) return false;
        if (sublist->size == 0) return true;
        if (sublist->size > size) return false;

        Node *curr_start = head;
        Node *subcurr = sublist->head;
        
        while (curr_start) {
            Node *curr_check = curr_start;
            subcurr = sublist->head;
            
            while (curr_check && subcurr && (curr_check->data == subcurr->data)) {
                curr_check = curr_check->next;
                subcurr = subcurr->next;
            }
            
            if (subcurr == nullptr) return true;
            curr_start = curr_start->next;
        }
        
        return false;
    }

    int CountInversions() const {
        int inv = 0;
        Node *slow = head;
        Node *fast = head;
        while (slow) {
            fast = slow->next;
            while (fast) {
                if (slow->data > fast->data) inv++;
                fast = fast->next;
            }
            slow = slow->next;
        }
        return inv;
    }
};