#ifndef DYN_ARR_H
#define DYN_ARR_H

#include <cstdint>

// size_t == unsigned long long

template <typename T>
class DynamicArray {
private:
  T* data;
  std::int64_t size = -1; // actual (last occupied)
  std::int64_t capacity; // max

  bool isEmpty() {
    return size == -1;
  }

public:
  DynamicArray(); // default ctor
  DynamicArray(std::int64_t capacity); // parametrized ctor
  DynamicArray(DynamicArray& other);
  ~DynamicArray(); // destructor


  void push_back(T x);
  T add(std::int64_t idx1, std::int64_t idx2);
  T max();
  T min();
  void clear(); // deallocate the data
  void reinitialize(); // restore to default
  void printData();
  ///////
  void push_front(T x);
  T front();
  T back();
  void insert(int idx, T val);
  void del(int idx);
  void erace_after(int idx);
  void increase_capacity(std::int64_t new_capacity);
  void decrease_capacity(std::int64_t new_capacity);

  T operator[](std::int64_t idx);
  T operator()();
};

// ----------------------------------

#include "DynamicArray.h"

#include <cstdlib>
#include <iostream>
#include <stdexcept>

template <typename T>
DynamicArray<T>::DynamicArray() {
  this->capacity = 8;
  this->data = new T[this->capacity];
}

template <typename T>
DynamicArray<T>::DynamicArray(std::int64_t capacity) {
  // check if user is dumb
  if (capacity < 1) {
    throw std::invalid_argument("Capacity < 1"); // https://en.cppreference.com/w/cpp/error/exception.html
    // std::exception like an animal
    // std::invalid_argument like a dog (heir of animal)
  }
  this->capacity = capacity;
  this->data = new T[this->capacity];
}

template <typename T>
DynamicArray<T>::DynamicArray(DynamicArray& other) {
  this->size = other.size;
  this->capacity = other.capacity;
  this->data = new T[this->capacity]; // (*this).data

  for (int i = 0; i <= size; ++i) {
    this->data[i] = other.data[i];
  }
}

template <typename T>
DynamicArray<T>::~DynamicArray() {
  // deallocate if allocated
  if (this->data) {
    delete[] this->data;
  }
}
template <typename T>
void DynamicArray<T>::push_back(T x) {
  // reallocate memory
  // increase capacity
  // copy data
  // dealloc old
  // assign new to old
  if (size + 1 >= capacity) {
    std::int64_t newCapacity = capacity * 2;
    T* tempArray = new T[newCapacity];
    for (int i = 0; i < capacity; ++i) {
      tempArray[i] = data[i];
    }
    delete[] data;
    data = tempArray;
    capacity = newCapacity;
  }
  data[++size] = x;
  // data[size + 1] = x;
  // ++size;
}

template <typename T>
T DynamicArray<T>::add(std::int64_t idx1, std::int64_t idx2) {
  if (idx1 > size || idx2 > size || idx1 < 0 || idx2 < 0) {
    throw std::invalid_argument("idx1 or idx2 out of range");
  }
  return data[idx1] + data[idx2];
}

template <typename T>
T DynamicArray<T>::max() {
  if (isEmpty()) {
    throw std::invalid_argument("Empty array");
  }
  T currentMax = -1e+38; // -1 * 10^38
  // float currentMax = std::numeric_limits<float>::lowest();
  for (int i = 0; i <= size; ++i) {
    if (data[i] >= currentMax) {
      currentMax = data[i];
    }
  }
  return currentMax;
}

template <typename T>
T DynamicArray<T>::min() {
  if (isEmpty()) {
    throw std::invalid_argument("Empty array");
  }
  T currentMin = 1e+38; // -1 * 10^38
  // float currentMin = std::numeric_limits<float>::max();
  for (int i = 0; i <= size; ++i) {
    if (data[i] <= currentMin) {
      currentMin = data[i];
    }
  }
  return currentMin;
}

template <typename T>
void DynamicArray<T>::clear() {
  if (this->data) {
    delete[] this->data;
    this->data = nullptr;
  }
  size = -1;
  capacity = 8;
}

template <typename T>
void DynamicArray<T>::reinitialize() {
  clear();
  data = new T[capacity](); // init with zeros
}

template <typename T>
void DynamicArray<T>::printData() {
  if (isEmpty()) {
    return;
  }
  for (int i = 0; i <= size; ++i) {
    std::cout << data[i] << " ";
  }
  std::cout << std::endl;
}

template <typename T>
T DynamicArray<T>::operator[](std::int64_t idx) {
  if (isEmpty() || idx < 0 || idx > size) {
    throw std::invalid_argument("Out of range");
  }
  //return data[size - idx]; // Arabic operator[]
  return data[idx];     // European operator[]
}

template <typename T>
T DynamicArray<T>::operator()() {
  if (isEmpty()) {
    return 0;
  }
  float sum = 0;
  for (int i = 0; i <= size; ++i) {
    sum += data[i];
  }
  return sum;
}
// ПОШЛО ДЗ

template <typename T>
void DynamicArray<T>::push_front(T x){
  if (isEmpty()){
    data[0] = x;
    size++;
    return;
  }

  if (size + 1 >= capacity) {
    std::int64_t newCapacity = capacity * 2;
    T* tempArray = new T[newCapacity];
    for (int i = 0; i < capacity; ++i) {
      tempArray[i] = data[i];
    }
    delete[] data;
    data = tempArray;
    capacity = newCapacity;
  }

  size++;
  for (int i = 0; i < size+1; ++i){
    data[size-i+1] = data[size-i];
  }
  data[0] = x;
  return;
}

template <typename T>
T DynamicArray<T>::front(){
  return data[0];
}

template <typename T>
T DynamicArray<T>::back(){
  return data[size];
}

template <typename T>
void DynamicArray<T>::insert(int idx, T val){
  if (idx > size || idx < 0) {
    throw std::invalid_argument("out of range");
  }
  if (size + 1 >= capacity) {
    std::int64_t newCapacity = capacity * 2;
    T* tempArray = new T[newCapacity];
    for (int i = 0; i < capacity; ++i) {
      tempArray[i] = data[i];
    }
    delete[] data;
    data = tempArray;
    capacity = newCapacity;
  }
  for (int i = 0; i < size-idx+1; ++i){
    data[size+1-i] = data[size-i];
  }
  data[idx] = val;
  return;
}

template <typename T>
void DynamicArray<T>::del(int idx){
  if (idx > size || idx < 0) {
    throw std::invalid_argument("out of range");
  }
  for (int i = 0; i < size-idx; ++i){
    data[idx+i] = data[idx+i+1];
  }
  size--;
  return;
}

template <typename T>
void DynamicArray<T>::erace_after(int idx){
  if (idx > size || idx < 0) {
    throw std::invalid_argument("out of range");
  }
  size = idx;
};

template <typename T>
void DynamicArray<T>::increase_capacity(std::int64_t new_capacity){
  if (new_capacity < capacity){
    throw std::invalid_argument("new capacity must be greater, use decrease_capacity method");
  }
  T* tempArray = new T[new_capacity];
  for (int i = 0; i < capacity; ++i) {
      tempArray[i] = data[i];
    }
  delete[] data;
  data = tempArray;
  capacity = new_capacity;
}

template <typename T>
void DynamicArray<T>::decrease_capacity(std::int64_t new_capacity){
  if (new_capacity > capacity){
    throw std::invalid_argument("new capacity must be less, use increase_capacity method");
  }
  
  T* tempArray = new T[new_capacity];
  for (int i = 0; i < capacity; ++i) {
      tempArray[i] = data[i];
    }
  delete[] data;
  data = tempArray;
  capacity = new_capacity;
}


#endif // DYN_ARR_H
