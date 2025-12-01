#ifndef DYN_ARR_STACK
#define DYN_ARR_STACK

#include "DynamicArray.h"
#include <cstdint>

template <typename T>
class Stack {
private:

    DynamicArray<T> data;
    std::int64_t size = -1;
    std::int64_t capacity;

public:
    Stack(std::int64_t capacity);
    Stack(Stack& other);
    //~Stack();

    void push(T x);
    T top();
    T pop();
    bool IsEmpty();

};

#endif


#include <stdexcept>


template <typename T>
Stack<T>::Stack(std::int64_t capacity)
    : data(capacity), size(-1), capacity(capacity)
{
    if (capacity < 1) {
        throw std::invalid_argument("Capacity < 1");
    }
}

template <typename T>
Stack<T>::Stack(Stack& other) {

    this->size = other.size;
    this->capacity = other.capacity;
    this->data = other.data;

}


template <typename T>
void Stack<T>::push(T x) {
    if (size + 1 >= capacity){
        throw std::invalid_argument("StackOverflow");
    }
    data.push_back(x);
    ++size;
}

template <typename T>
T Stack<T>::top() {
    return data.back();
}

template <typename T>
T Stack<T>::pop() {
    T buf = data.back();
    data.del(size);
    --size;
    return buf;
}

template <typename T>
bool Stack<T>::IsEmpty() {
    return (size == -1);
}
