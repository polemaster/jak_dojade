#pragma once
#include <iostream>

template<typename T1, typename T2>
class Pair {
public:
    // Constructors
    Pair() : first(), second() {}
    Pair(const T1& x, const T2& y) : first(x), second(y) {}
    Pair(const Pair<T1, T2>& other) : first(other.first), second(other.second) {}
    Pair(Pair<T1, T2>&& other) : first(std::move(other.first)), second(std::move(other.second)) {}

    Pair<T1, T2>& operator=(const Pair<T1, T2>& other);
    Pair<T1, T2>& operator=(Pair<T1, T2>&& other);

    T1 first;
    T2 second;
};

template<typename T1, typename T2>
bool operator>(const Pair<T1, T2>& left, const Pair<T1, T2>& right) {
    return left.first > right.first;
}

template<typename T1, typename T2>
bool operator<(const Pair<T1, T2>& left, const Pair<T1, T2>& right) {
    return left.first < right.first;
}

template<typename T1, typename T2>
Pair<T1, T2>& Pair<T1, T2>::operator=(const Pair<T1, T2>& other) {
    first = other.first;
    second = other.second;

    return *this;
}

template<typename T1, typename T2>
Pair<T1, T2>& Pair<T1, T2>::operator=(Pair<T1, T2>&& other) {
    first = std::move(other.first);
    second = std::move(other.second);

    return *this;
}

template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& ostr, const Pair<T1, T2> &p) {
    ostr << p.first << " " << p.second;

    return ostr;
}
