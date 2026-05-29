#pragma once
#include <algorithm>

template <typename T>
class stack {
  public:
    stack() : capacity_(10), size_(0), data_{new T[capacity_]} {}
    
    stack(const stack& other) : capacity_(other.capacity_), size_(other.size_), data_{new T[capacity_]}{
      std::copy(other.data_, other.data_ + other.size_, data_);
    }

    stack(stack&& other) : capacity_(0), size_(0), data_(nullptr){
      std::swap(other.capacity_, capacity_);
      std::swap(other.size_, size_);
      std::swap(other.data_, data_);
    }

    stack& operator=(const stack& other){
      if(this != &other){
        auto temp = stack(other);
        std::swap(capacity_, temp.capacity_);
        std::swap(size_, temp.size_);
        std::swap(data_, temp.data_);
      }
      return *this;
    }
    
    stack& operator=(stack&& other){
      if(this != &other) {
        std::swap(capacity_, other.capacity_);
        std::swap(size_, other.size_);
        std::swap(data_, other.data_);
      }
      return *this;
    }

    ~stack(){
      delete[] data_;
    }

    bool empty() const {return size_ == 0;}
    size_t size() const {return size_;}
    const T& top() const;
    T& top();

    template <typename U>
    void push(U&& value);
    void pop();

  private:
    void reallocate();
    size_t capacity_;
    size_t size_;
    T* data_;
};

template <typename T>
void stack<T>::reallocate(){
  capacity_ *= 2;
  T* newData = new T[capacity_];
  std::copy(data_, data_ + size_, newData);
  delete [] data_;
  data_ = newData;
}

template <typename T>
template <typename U>
void stack<T>::push(U&& value) {
  if(capacity_ == size_) 
    reallocate();
  data_[size_++] = std::forward<U>(value);
}

template <typename T>
void stack<T>::pop() {
  if(empty())
    return;
  auto temp = std::move(data_[size_--]);
}

template <typename T>
const T& stack<T>::top() const {
  return data_[size_-1];
}

template <typename T>
T& stack<T>::top() {
  return data_[size_-1];
}

