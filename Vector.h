#pragma once

#include <iostream>
#include "String.h"

const int START_CAP = 512;

template<typename T>
class Vector {
public:
    Vector();
    ~Vector();
    Vector(const Vector& other);
    Vector(int size);

    void push_back(const T& value);
    void push_back(T&& value);
    void pop_back();
    int size() const;
    T& operator[](int index);
    const T& operator[](int index) const;
    void print() const;
private:
    int _size;
    int _capacity;
    T *_arr;

    void _grow();
};


template<typename T>
Vector<T>::Vector() {
    _arr = new T[START_CAP];
    _size = 0;
    _capacity = START_CAP;
}

template<typename T>
Vector<T>::Vector(const Vector& other) {
    _size = other._size;
    _capacity = other._capacity;
    _arr = new T[_capacity];
    for (int i = 0; i < _size; ++i)
        _arr[i] = other._arr[i];
}

template<typename T>
Vector<T>::Vector(int size) {
    _size = size;
    _capacity = _size;
    _arr = new T[_capacity];
}

template<typename T>
Vector<T>::~Vector() {
    delete[] _arr;
}

template<typename T>
void Vector<T>::push_back(const T& value) {
    if (_size == _capacity)
        _grow();
    _arr[_size] = value;
    ++_size;
}

template<typename T>
void Vector<T>::push_back(T&& value) {
    if (_size == _capacity)
        _grow();
    _arr[_size] = std::move(value);
    ++_size;
}

template<typename T>
void Vector<T>::pop_back() {
    if (_size == 0)
        throw std::out_of_range("Vector is empty.");
    --_size;
}

template<typename T>
int Vector<T>::size() const {
    return _size;
}

template<typename T>
T& Vector<T>::operator[](int index) {
    return _arr[index];
}

template<typename T>
const T& Vector<T>::operator[](int index) const {
    return _arr[index];
}

template<typename T>
void Vector<T>::print() const {
    for (int i = 0; i < _size; ++i)
        std::cout << _arr[i] << " ";
    std::cout << std::endl;
}

template<typename T>
void Vector<T>::_grow() {
    _capacity *= 2;
    T *new_arr = new T[_capacity];
    for (int i = 0; i < _size; ++i) {
        new_arr[i] = std::move(_arr[i]);
    }
    delete[] _arr;
    _arr = new_arr;
}

std::ostream& operator<< (std::ostream& ostr, const Vector<String>& v) {
    for (int i = 0; i < v.size(); ++i)
        ostr << v[i] << " ";
    ostr << std::endl;
    return ostr;
}
