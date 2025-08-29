#pragma once

#include <cstddef>
#include <sstream>

#include "exceptions.h"
#include "dynamic_array.h"

template <typename T>
class DoublyLinkedList {
private:
    struct Node {
        T data;
        Node *prev;
        Node *next;
        Node () :
            data(0),
            prev(nullptr),
            next(nullptr)
        {}
        Node(T data, Node *prev = nullptr, Node *next = nullptr) :
            data(data),
            prev(prev),
            next(next)
        {}
    };

    Node *head;
    Node *tail;
    size_t size;

public:
    DoublyLinkedList() :
        head(nullptr),
        tail(nullptr),
        size(0)
    {}

    explicit DoublyLinkedList(T *items, size_t count) : // items должен содержать >= size элементов
        head(nullptr),
        tail(nullptr),
        size(0)
    {
        for (size_t i = 0; i < count; i++) Append(items[i]);
    }

    DoublyLinkedList(const DoublyLinkedList &other) :
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

    DoublyLinkedList(const DynamicArray<T> &other) :
        head(nullptr),
        tail(nullptr),
        size(0)
    {
        for (size_t i = 0; i < other.GetSize(); i++) {
            Append(other.Get(i));
        }
    }

    
    ~DoublyLinkedList() {
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

    DoublyLinkedList *GetSubList(size_t start, size_t end) const
    {
        if (start >= size || end > size) {
            throw IndexOutOfRange(end, size);
        }
        else if (start > end) {
            throw InvalidRange(start, end);
        }
        DoublyLinkedList *subList = new DoublyLinkedList();
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
        Node* newNode = new Node(item, tail, nullptr);
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
        Node* newNode = new Node(item, nullptr, head);
        if (!head) {
            head = newNode;
            tail = head;
        }
        else {
            head->prev = newNode;
            head = newNode;
        }
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
            Node *Prev = head;
            for (size_t i = 0; i < index - 1; i++) Prev = Prev->next;
            Node *newNode = new Node(item, Prev, Prev->next);
            Prev->next->prev = newNode;
            Prev->next = newNode;
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
            else {
                head->prev = nullptr;
            }
            delete toDelete;
        }
        else if (index == size - 1) {
            Node *toDelete = tail;
            tail = tail->prev;
            if (size == 1) {
                head = nullptr;
            }
            else {
                tail->next = nullptr;
            }
            delete toDelete;
        }
        else {
            Node *Prev = head;
            for (size_t i = 0; i < index - 1; i++) Prev = Prev->next;
            Node *toDelete = Prev->next;
            Prev->next = toDelete->next;
            Prev->next->prev = Prev;
            delete toDelete;
        }
        size--;
    }


    DoublyLinkedList *ConcatInPlace(const DoublyLinkedList &list) {
        Node *current = list.head;
        size_t addLength = list.GetLength();
        for (size_t i = 0; i < addLength; i++) {
            Append(current->data);
            current = current->next;
        }
        return this;
    }

    DoublyLinkedList *Concat(const DoublyLinkedList &list) const {
        DoublyLinkedList *newList = new DoublyLinkedList(*this);
        Node *current = list.head;
        while (current) {
            newList->Append(current->data);
            current = current->next;
        }
        return newList;
    }

    DoublyLinkedList *Map(T (*func)(T)) {
        Node *current = head;
        while(current) {
            current->data = func(current->data);
            current = current->next;
        }
        return this;
    }
    DoublyLinkedList *Where(bool (*func)(T)) {
        Node *current = head;
        while(current) {
            if (!func(current->data)) {
                if (current->prev) {
                    current->prev->next = current->next;
                }
                else {
                    head = current->next;
                }
                if (current->next) {
                    current->next->prev = current->prev;
                }
                else {
                    tail = current->prev;
                }
                Node *toDelete = current;
                current = current->next;
                delete toDelete;
                size--;
            }
            else {
                current = current->next;
            }
        }
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

    bool IsSubList(const DoublyLinkedList *sublist) const {
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

    void Sort() {
        if (size < 2) return;
        HeadTail ht = MergeSort(head);
        head = ht.head;
        tail = ht.tail;
    }

private:
    struct HeadTail {
        Node* head;
        Node* tail;
    };

    HeadTail MergeSort(Node* start) {
        if (!start->next) return {start, start};
        
        Node* mid = Split(start);
        HeadTail left = MergeSort(start);
        HeadTail right = MergeSort(mid);
        return Merge(left, right);
    }

    Node* Split(Node* start) {
        Node* slow = start;
        Node* fast = start;
        
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        
        Node* mid = slow->next;
        slow->next = nullptr;
        mid->prev = nullptr;
        return mid;
    }

    HeadTail Merge(HeadTail left, HeadTail right) {
        Node dummy;
        Node* current = &dummy;
        dummy.next = nullptr;

        while (left.head && right.head) {
            if (left.head->data <= right.head->data) {
                current->next = left.head;
                left.head->prev = current;
                left.head = left.head->next;
            }
            else {
                current->next = right.head;
                right.head->prev = current;
                right.head = right.head->next;
            }
            current = current->next;
        }

        if (left.head) {
            current->next = left.head;
            left.head->prev = current;
            left.tail->next = nullptr;
            return {dummy.next, left.tail};
        }
        else {
            current->next = right.head;
            right.head->prev = current;
            right.tail->next = nullptr;
            return {dummy.next, right.tail};
        }
    }
};