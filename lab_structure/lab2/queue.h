#ifndef STACK_QUEUE
#define STACK_QUEUE

#include "stack.h"
#include <cstdint>
#include <type_traits>

template <typename T>
class Queue {
private:

    Stack<T> stin;
    Stack<T> stout;
    std::int64_t size = 0;
    std::int64_t capacity;

public:
    Queue(std::int64_t capacity);
    Queue(Queue& other);

    void enqueue(T x);
    T dequeue();
    bool IsEmpty();
    std::int64_t get_size();
};

#endif
//-------------------------------
template <typename T>
Queue<T>::Queue(std::int64_t capacity) 
    : stin(capacity), stout(capacity), size(-1), capacity(capacity)
{
    if (capacity < 1) {
        throw std::invalid_argument("Capacity < 1");
    }
}

template <typename T>
Queue<T>::Queue(Queue& other) {
    this->size = other.size;
    this->capacity = other.capacity;
    this->stin = other.stin;
    this->stout = other.stout;
}

template <typename T>
void Queue<T>::enqueue(T x) {
    if (size + 1 >= capacity){
        throw std::invalid_argument("StackOverflow");
    }
    stin.push(x);
    ++size;
}

template <typename T>
T Queue<T>::dequeue() {
    if (stout.IsEmpty()) {
        for (int i = 0; i < size; ++i) {
            stout.push(stin.pop());
        }
    }
    --size;
    return stout.pop();
}

template <typename T>
bool Queue<T>::IsEmpty() {
    return (size == -1);
}

template <typename T>
std::int64_t Queue<T>::get_size() {
    return size;
}
