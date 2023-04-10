#pragma once
#include <iostream>

template<typename T>
class DLList {
public:
    DLList();
    // DLList(const DLList<T>& other);
    DLList(DLList<T>&& other);
    ~DLList();

    // DLList<T>& operator=(const DLList<T>& right);
    DLList<T>& operator=(DLList<T>&& right);
    T& operator[](const std::size_t index);
    const T& operator[](std::size_t index) const;

    std::size_t size() const;

    T& getAt(const std::size_t index);
    void free();
    void print() const;
    // void push_back(const T& value);
    void push_back(T&& value);
    void push_front(T&& value);
    void pop_back();
    void pop_front();
    int find(const T& value) const;
    bool remove_node(const T& value);
    bool remove_node_by_index(const std::size_t index);

private:
    struct Node {
        T data;
        Node *next;
        Node *prev;
        // Node(const T& value, Node *previous = nullptr, Node *nextt = nullptr)
        //  : data(value), next(nextt), prev(previous) {};
        Node(T&& value, Node *previous = nullptr, Node *nextt = nullptr)
         : data(std::move(value)), next(nextt), prev(previous) {};
    };

    Node *_head;
    Node *_tail;
    std::size_t _size;

public:
    class Iterator {
    private:
        Node* current;

    public:
        Iterator(Node* node) : current(node) {}
        Iterator& operator++() {
            current = current->next;
            return *this;
        }
        Iterator& operator--() {
            current = current->prev;
            return *this;
        }
        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }
        T& operator*() const {
            return current->data;
        }
        T* operator->() const {
            return &current->data;
        }
    };

    Iterator begin() const {
        return Iterator(_head);
    }
    Iterator end() const {
        return Iterator(nullptr);
    }

    Iterator beginFromEnd() const {
        return Iterator(_tail);
    }
    Iterator endFromEnd() const {
        return Iterator(nullptr);
    }
};
