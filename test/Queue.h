#pragma once

#include "String.h"

const int INIT_QUEUE_SIZE = 512;

template<typename T>
class Queue {
public:
    Queue();
    ~Queue();

    void push(const T& value);
    void push(T&& value);
    T& front() const;
    void pop();
    bool empty() const;
    void print() const;
    void printWhole() const;
    int size() const;
private:
    T* _arr;
    int _front, _rear;
    int _size;
    int _capacity;

    void _grow(); // enlargens capacity, size stays the same
};

template<typename T>
Queue<T>::Queue() {
    _front = 0;
    _rear = -1;
    _size = 0;
    _capacity = INIT_QUEUE_SIZE;
    _arr = new T[_capacity];
}

template<typename T>
Queue<T>::~Queue() {
    delete[] _arr;
}

template<typename T>
void Queue<T>::push(const T& value) {
    // std::cout << std::endl;
    // std::cout << "pushed " << value << std::endl;
    // printWhole();
    if (_size == _capacity) {
        _grow();
    }
    // _rear = (_rear + 1) % _capacity;
    ++_rear;
    if (_rear == _capacity)
        _rear = 0;
    _arr[_rear] = value;
    ++_size;
    // printWhole();
    // std::cout << std::endl;
}

template<typename T>
void Queue<T>::push(T&& value) {
    if (_size == _capacity) {
        _grow();
    }
    ++_rear;
    if (_rear == _capacity)
        _rear = 0;
    _arr[_rear] = value;
    ++_size;
}

template<typename T>
T& Queue<T>::front() const {
    return _arr[_front];
}

template<typename T>
void Queue<T>::pop() {
    if (_size == 0)
        throw std::logic_error("Queue is empty");
    // _front = (_front + 1) % _capacity;
    ++_front;
    if (_front == _capacity)
        _front = 0;
    --_size;
    // std::cout << "popped element" << std::endl;
    // for (int i = 0; i < _capacity; ++i)
    //     std::cout << _arr[i] << " ";
    // std::cout << std::endl;
}

template<typename T>
bool Queue<T>::empty() const {
    return _size == 0;
}

template<typename T>
void Queue<T>::print() const {
    for (int i = _front; i < _size + _front && i < _capacity; ++i) {
        std::cout << _arr[i] << " ";
    }
    if (_rear < _front) {
        for (int i = 0; i <= _rear; ++i) {
            std::cout << _arr[i] << " ";
        }
    }
    std::cout << std::endl;
}

template<typename T>
void Queue<T>::printWhole() const {
    for (int i = 0; i < _capacity; ++i)
        std::cout << _arr[i] << " ";
    std::cout << std::endl;
}

template<typename T>
int Queue<T>::size() const {
    return _size;
}

template<typename T>
void Queue<T>::_grow() {
    // std::cout << "started grow()" << std::endl;
    // for (int i = 0; i < _capacity; ++i)
    //     std::cout << _arr[i] << " ";
    // std::cout << std::endl;

    _capacity *= 2;
    T *new_arr = new T[_capacity];

    int j = 0;
    for (int i = _front; i < _capacity / 2 ; ++i) {
        new_arr[j] = std::move(_arr[i]);
        ++j;
    }
    if (_rear < _front) {
        for (int i = 0; i <= _rear; ++i) {
            new_arr[j] = std::move(_arr[i]);
            ++j;
        }
    }

    delete[] _arr;
    _arr = new_arr;
    _front = 0;
    _rear = _size - 1; // or _rear = j - 1

    // std::cout << "capacity grew from " << _capacity / 2 << " to " << _capacity << std::endl;
    // for (int i = 0; i < _capacity; ++i)
    //     std::cout << _arr[i] << " ";
    // std::cout << std::endl;
    // std::cout << "ended grow()" << std::endl;
}
