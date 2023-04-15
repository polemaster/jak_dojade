#pragma once
#include <vector>
#include <algorithm>


template<typename T>
class PriorityQueue {
public:
    PriorityQueue() = default;

    void push(const T& value) {
        heap.push_back(value);
        std::push_heap(heap.begin(), heap.end(), compare);
    }

    void pop() {
        std::pop_heap(heap.begin(), heap.end(), compare);
        heap.pop_back();
    }

    const T& top() const {
        return heap.front();
    }

    bool empty() const {
        return heap.empty();
    }

    std::size_t size() const {
        return heap.size();
    }

private:
    std::vector<T> heap;


    static bool compare(const T& a, const T& b) {
        return a > b;
    }
};


