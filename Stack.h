#pragma once

const int INIT_STACK_SIZE = 512;

template<typename T>
class Stack {
public:
    Stack();
    ~Stack();

    void push(const T& value);
    void push(T&& value);
    void pop();
    bool empty() const;
    const T& top() const;
    void print() const;
private:
    T* _arr;
    int _size;
    int _capacity;

    void _grow();
};


template<typename T>
Stack<T>::Stack() {
    _capacity = INIT_STACK_SIZE;
    _arr = new T[_capacity];
    _size = 0;
}

template<typename T>
Stack<T>::~Stack() {
    delete[] _arr;
}

template<typename T>
void Stack<T>::push(const T& value) {
    if (_size == _capacity)
        _grow();
    _arr[_size++] = value;
}

template<typename T>
void Stack<T>::push(T&& value) {
    if (_size == _capacity)
        _grow();
    _arr[_size++] = std::move(value);
}

template<typename T>
void Stack<T>::pop() {
    --_size;
}

template<typename T>
bool Stack<T>::empty() const {
    return _size == 0;
}

template<typename T>
const T& Stack<T>::top() const {
    return _arr[_size - 1];
}

template<typename T>
void Stack<T>::print() const {
    for (int i = 0; i < _size; ++i)
        std::cout << _arr[i] << " ";
    std::cout << std::endl;

    for (int i = 0; i < _capacity; ++i)
        std::cout << _arr[i] << " ";
    std::cout << std::endl;
}

template<typename T>
void Stack<T>::_grow() {
    _capacity *= 2;
    T* new_arr = new T[_capacity];
    for (int i = 0; i < _size; ++i)
        new_arr[i] = _arr[i];
    delete[] _arr;
    _arr = new_arr;
}
