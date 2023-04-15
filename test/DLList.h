#pragma once
#include <iostream>

template<typename T>
class DLList {
public:
    DLList();
    DLList(const DLList<T>& other);
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
    void push_back(const T& value);
    void push_back(T&& value);
    void push_front(T&& value);
    void pop_back();
    void pop_front();
    T& top() const;
    int find(const T& value) const;
    bool remove_node(const T& value);
    bool remove_node_by_index(const std::size_t index);
    bool empty() const;

private:
    struct Node {
        T data;
        Node *next;
        Node *prev;
        Node(const T& value, Node *previous = nullptr, Node *nextt = nullptr)
         : data(value), next(nextt), prev(previous) {};
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



template<typename T>
DLList<T>::DLList() : _head(nullptr), _tail(nullptr), _size(0) {
}

template<typename T>
DLList<T>::DLList(const DLList<T>& other)
: _head(nullptr), _tail(nullptr), _size(0) {

    if (other._size == 0)
        return;

    // Node *current = other._head;

    // Node *new_head = new Node;
    // Node *new_tail = new Node;

    // new_head->data = current->data;
    // new_head->next = nullptr;
    // new_head->prev = nullptr;

    // _head = new_head;
    // _size = other._size;

    // current = current->next;

    // while (current != nullptr) {
    //     new_head->next = new Node;
    //     new_head->next->prev = new_head;
    //     new_head = new_head->next;

    //     new_head->data = current->data;

    //     current = current->next;
    // }
    // new_head->next = nullptr;
    // new_tail = new_head;

    Node *current = other._head;
    while (current != nullptr) {
        push_back(current->data);
        current = current->next;
    }
}

template<typename T>
DLList<T>::DLList(DLList<T>&& other)
: _head(other._head), _tail(other._head), _size(other._size) {

    other._head = nullptr;
    other._tail = nullptr;
    other._size = 0;
}


template<typename T>
void DLList<T>::free() {
    while (_size > 0)
        pop_back();
}

template<typename T>
DLList<T>::~DLList() {
    free();
}

// template<typename T>
// DLList<T>& DLList<T>::operator=(const DLList<T>& right) {
//     if (this == &right)
//         return *this;

//     free();

//     DLList copy(right);
//     std::swap(_head, copy._head);
//     std::swap(_tail, copy._tail);
//     _size = copy._size;
//     copy._size = 0;

//     return *this;
// }

template<typename T>
DLList<T>& DLList<T>::operator=(DLList<T>&& right) {
    if (this == &right)
        return *this;

    free();

    _head = right._head;
    _tail = right._tail;
    _size = right._size;

    right._head = nullptr;
    right._tail = nullptr;
    right._size = 0;

    return *this;
}

template<typename T>
T& DLList<T>::operator[](const std::size_t index) {
    if (index >= _size)
        throw std::out_of_range("Tried to access list element out of bounds");

    Node *tmp = _head;
    for (std::size_t i = 0; i < index; ++i)
        tmp = tmp->next;
    return tmp->data;
}

template<typename T>
const T& DLList<T>::operator[](std::size_t index) const {
    if (index >= _size)
        throw std::out_of_range("Tried to access list element out of bounds");

    Node *tmp = _head;
    for (std::size_t i = 0; i < index; ++i)
        tmp = tmp->next;
    return tmp->data;
}

template<typename T>
T& DLList<T>::getAt(const std::size_t index) {
    if (index >= _size)
        throw std::out_of_range("Tried to access list element out of bounds");

    Node *tmp = _head;
    for (std::size_t i = 0; i < index; ++i)
        tmp = tmp->next;
    return tmp->data;
}

template<typename T>
void DLList<T>::push_back(const T& value) {
    Node* tmp = new Node(value, _tail, nullptr);

    if (_tail == nullptr)
        _head = tmp;
    else
        tmp->prev->next = tmp;

    _tail = tmp;

    ++_size;
}

template<typename T>
void DLList<T>::push_back(T&& value) {
    Node* tmp = new Node(std::move(value), _tail, nullptr);

    if (_tail == nullptr)
        _head = tmp;
    else
        tmp->prev->next = tmp;

    _tail = tmp;

    ++_size;
}

template<typename T>
void DLList<T>::push_front(T&& value) {
    Node* tmp = new Node(std::move(value), nullptr, _head);

    if (_head == nullptr)
        _tail = tmp;
    else
        tmp->next->prev = tmp;

    _head = tmp;

    ++_size;
}

template<typename T>
void DLList<T>::pop_back() {
    if (_size > 0) {
        Node *tmp = _tail->prev;
        delete _tail;
        _tail = tmp;

        if (_tail == nullptr)
            _head = nullptr;
        else
            _tail->next = nullptr;

        --_size;
    }
}

template<typename T>
void DLList<T>::pop_front() {
    if (_size > 0) {
        Node *tmp = _head->next;
        delete _head;
        _head = tmp;

        if (_head == nullptr)
            _tail = nullptr;
        else
            _head->prev = nullptr;

        --_size;
    }
}

template<typename T>
T& DLList<T>::top() const {
    return _tail->data;
}

template<typename T>
int DLList<T>::find(const T& value) const {
    Node *current = _head;
    int i = 0;
    while (current != nullptr) {
        if (current->data == value)
            return i;
        current = current->next;
        ++i;
    }
    return -1;
}

template<typename T>
bool DLList<T>::remove_node(const T& value) {
    Node *current = _head;
    while (current != nullptr) {
        if (current->data == value) {
            if (current == _tail)
                pop_back();
            else if (current == _head)
                pop_front();
            else {
                current->prev->next = current->next;
                current->next->prev = current->prev;
                delete current;
                --_size;
            }
            return true;
        }
        current = current->next;
    }
    return false;
}

template<typename T>
bool DLList<T>::remove_node_by_index(const std::size_t index) {
    if (index >= _size)
        return false;

    Node *current = _head;
    std::size_t i = 0;
    while (i < index) {
        current = current->next;
        ++i;
    }

    if (current == _tail)
        pop_back();
    else if (current == _head)
        pop_front();
    else {
        current->prev->next = current->next;
        current->next->prev = current->prev;
        delete current;
        --_size;
    }
    return true;
}

template<typename T>
bool DLList<T>::empty() const {
    return _size == 0;
}

template<typename T>
std::size_t DLList<T>::size() const {
    return _size;
}

template<typename T>
void DLList<T>::print() const {
    if(_head != nullptr) {
        Node *current = _head;

        while ( current != nullptr) {
            std::cout << current->data << " ";
            current = current->next;
        }
    }
    else
        std::cout << "List is empty." << std::endl;
}


// template class DLList<String>;
// template class DLList<Dictionary<int, int>::Element>;
// template class DLList<Dictionary<String, int>::Element>;
