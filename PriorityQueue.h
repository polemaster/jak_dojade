#pragma once

#define min(a, b) (a <= b ? a : b)

// Priority Queue implemented with min-heap
template<typename T>
class PriorityQueue {
public:
    PriorityQueue();
    void push(T&& val);
    void pop();
    T top() const;
    bool empty() const;
    int size() const;
private:
    Vector<T> _heap;

    void _swim(int index);
    void _sink(int index);
};

template<typename T>
PriorityQueue<T>::PriorityQueue() {
}

template<typename T>
void PriorityQueue<T>::push(T&& val) {
    _heap.push_back(std::move(val));
    _swim(size() - 1); // keep moving up the added element until it satisfies the heap invariant
}

template<typename T>
void PriorityQueue<T>::pop() {
    if (size() == 0)
        throw std::invalid_argument("The size is 0. Can't pop elements");

    std::swap(_heap[0], _heap[size() - 1]);
    _heap.pop_back(); // remove the last element
    _sink(0); // keep moving down the first element until it satisfies the heap invariant
}

template<typename T>
T PriorityQueue<T>::top() const {
    if (size() == 0)
        throw std::invalid_argument("Tried to access top element while size is 0");
    return _heap[0];
}

template<typename T>
bool PriorityQueue<T>::empty() const {
    return size() == 0;
}

template<typename T>
int PriorityQueue<T>::size() const {
    return _heap.size();
}

template<typename T>
void PriorityQueue<T>::_swim(int index) {
    int parent = (index - 1) / 2;
    while (index > 0 && _heap[parent] > _heap[index]) {
        std::swap(_heap[index], _heap[parent]);
        index = parent;
        parent = (index - 1) / 2;
    }
}

template<typename T>
void PriorityQueue<T>::_sink(int index) {
    int left_child = 2 * index + 1;
    int right_child = 2 * index + 2;
    int min_child = min(left_child, right_child);

    while (min_child <= size() - 1 && _heap[index] > _heap[min_child]) {
        std::swap(_heap[index], _heap[min_child]);
        index = min_child;

        left_child = 2 * index + 1;
        right_child = 2 * index + 2;
        min_child = min(left_child, right_child);
    }
}
