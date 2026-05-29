#pragma once
#include <initializer_list>
#include <iostream>
#include <algorithm>


template <typename T>
class MojVektor{
  public:
    // O(1)
    MojVektor() : capacity_(10), size_(0), data_{new T[capacity_]}{};
    // O(n)
    MojVektor(const std::initializer_list<T>& l) : capacity_(l.size()), size_(l.size()), data_{new T[capacity_]}{
      std::copy(l.begin(), l.end(), data_);
    }
    // O(n)
    MojVektor(const MojVektor& other) : capacity_(other.capacity_), size_(other.size_), data_{new T[capacity_]}{
      std::copy(other.data_, other.data_ + other.size_, data_);
    };
    // O(n)
    MojVektor& operator=(const MojVektor& other){
      if(this != &other){
        delete[] data_;
        capacity_ = other.capacity_;
        size_ = other.size_;
        data_ = new T[capacity_];
        std::copy(other.data_, other.data_ + other.size_, data_);
      }
      return *this;
    };
    // O(1)
    MojVektor(MojVektor&& other) : capacity_(other.capacity_), size_(other.size_), data_(other.data_){
      other.data_ = nullptr;
      other.capacity_ = 0;
      other.size_ = 0;
    }
    // O(1)
    MojVektor& operator=(MojVektor&& other){
      if (this != &other){
        delete[] data_;
        capacity_ = other.capacity_;
        size_ = other.size_;
        data_ = other.data_;
        other.data_ = nullptr;
        other.capacity_ = other.size_ = 0;
      }
      return *this;
    };
    // O(1)
    ~MojVektor(){
      delete[] data_;
    }


    MojVektor& push_back(const T&); // O(1)
    MojVektor& push_back(T&&); // O(1)

    MojVektor& push_front(const T&); // O(n)
    MojVektor& push_front(T&&); // O(n)

    size_t size() const { return size_;} // O(1)
    bool empty() const { return size_ == 0;} // O(1)
    size_t capacity() const { return capacity_;} // O(1)
  
    T& at(size_t index); // O(1)
    const T& at(size_t index) const; // O(1)

    T& operator[](size_t index); // O(1)
    const T& operator[](size_t index) const; // O(1)

    void clear(); // O(n)

    void resize(size_t newSize, const T& value); // O(n)

    MojVektor& pop_back(); // O(1)
    MojVektor& pop_front(); // O(b)

    T& front(); // O(1)
    T& back(); // O(1)
    const T& front() const; // O(1)
    const T& back() const; // O(1)


    bool operator==(const MojVektor&) const; // O(n)
    bool operator!=(const MojVektor&) const; // O(n)

    bool full() const { // O(1)
      return size_ == capacity_;
    }

    class Iterator;

    Iterator begin() const {
      return Iterator(data_); // O(1)
    }
    Iterator end() const {
      return Iterator(data_ + size_); // O(1)
    }

    Iterator find(const T& value) const; // O(n)

    Iterator erase(Iterator pos); // O(n)

    Iterator erase(Iterator beginIt, Iterator endIt); // O(n)

    Iterator insert(Iterator pos, const T& value); // O(n)

    void rotate(); // O(n)

    template<typename Fn>
    void for_each(Fn fn); // O(n)

    template<typename Fn>
    void remove_if(Fn fn); // O(n)

  private:
    size_t capacity_;
    size_t size_;
    T* data_;
    void reallocate(); // O(n)
};

// O(n)
template<typename T>
void MojVektor<T>::reallocate() {
  size_t new_capacity = capacity_<<= 1;
  T* new_data = new T[new_capacity];
  for(int i = 0; i < size_; ++i){
    new_data[i] = std::move(data_[i]);
  }
  delete[] data_;
  data_ = new_data;
}

// O(1)
template <typename T>
MojVektor<T>& MojVektor<T>::push_back(const T& value) {
  if (capacity_ == size_) reallocate();
  data_[size_++] = value;
  return *this; 
}

// O(1)
template <typename T>
MojVektor<T>& MojVektor<T>::push_back(T&& value){
  if (capacity_ == size_) reallocate();
  data_[size_++] = std::move(value);
  return *this;
}


// O(n)
template <typename T>
MojVektor<T>& MojVektor<T>::push_front(const T& value){
  if(capacity_ == size_) {
    capacity_ *= 2;
    T* new_data = new T[capacity_];
    new_data[0] = value;
    for(int i = 0; i < size_; ++i){
      new_data[i + 1] = std::move(data_[i]);
    }
    delete[] data_;
    data_ = new_data;
  }
  else {
    for(int i = size_; i > 0; --i){
      data_[i] = data_[i-1];  
    }
    data_[0] = value;
  }
  ++size_;
  return *this;
}

// O(n)
template <typename T>
MojVektor<T>& MojVektor<T>::push_front(T&& value){
  if(capacity_ == size_){
    capacity_ *= 2;
    T* new_data = new T[capacity_];
    new_data[0] = std::move(value);
    for(int i = 0; i < size_; ++i){
      new_data[i + 1] = std::move(data_[i]);
    }
    delete[] data_;
    data_ = new_data;
  }
  else {
    for(int i = size_; i > 0; --i){
      data_[i] = data_[i - 1];
    }
    data_[0] = std::move(value);
  }
  ++size_;
  return *this;
}

// O(1)
template <typename T>
T& MojVektor<T>::at(size_t index) {
  if (index >= size_) throw std::out_of_range("Error, index out of range!"); 
  return data_[index];
}

// O(1)
template <typename T>
const T& MojVektor<T>::at(size_t index) const {
  if (index >= size_) throw std::out_of_range("Error, index out of range!");
  return data_[index];
}

// O(1)
template <typename T>
T& MojVektor<T>::operator[](size_t index) {
  return data_[index];  
}

// O(1)
template <typename T>
const T& MojVektor<T>::operator[](size_t index) const {
  return data_[index];
}

// O(1)
template <typename T>
void MojVektor<T>::clear() {
  size_ = 0;
}

// O(1)
template <typename T>
T& MojVektor<T>::front(){
  if (size_ == 0) 
    throw std::out_of_range("Error, container is empty!");
  return data_[0];
}

// O(1)
template <typename T>
const T& MojVektor<T>::front() const{
  if (size_ == 0)
    throw std::out_of_range("Error, container is empty!");
  return data_[0];
}

// O(1)
template <typename T>
T& MojVektor<T>::back() {
  if (size_ == 0)
    throw std::out_of_range("Error, container is empty!");
  return data_[size_-1];
}

// O(1)
template <typename T>
const T& MojVektor<T>::back() const {
  if (size_ == 0)
    throw std::out_of_range("Error, container is empty!");
  return data_[size_-1];
}

// O(1)
template <typename T>
MojVektor<T>& MojVektor<T>::pop_back(){
  if(size_ == 0)
    throw std::out_of_range("Error, container is empty!");
  size_--;
  return *this;
}

// O(n)
template <typename T>
MojVektor<T>& MojVektor<T>::pop_front(){
  if (size_ == 0)
    throw std::out_of_range("Error, container is empty!");
  --size_;
  for (size_t i = 0; i < size_; ++i)
    data_[i] = data_[i+1];
  return *this;
}

// O(n)
template <typename T>
void MojVektor<T>::resize(size_t newSize, const T& value){
  if (newSize > size_){
    for(auto i = size_; i < newSize; ++i)
      push_back(value);
  }
  else
    size_ = newSize;
}

// O(n)
template <typename T>
bool MojVektor<T>::operator==(const MojVektor& other) const{
  if(size_ != other.size_) 
    return false;
  for(size_t i = 0; i < size_; ++i){
    if (data_[i] != other.data_[i])
      return false;
  }
  return true;
}

// O(n)
template <typename T>
bool MojVektor<T>::operator!=(const MojVektor& other) const {
  return !operator==(other);
}

template <typename T>
class MojVektor<T>::Iterator {
  public: 
    using iterator_category = std::random_access_iterator_tag;
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using difference_type = std::ptrdiff_t;
  
    // O(1)
    Iterator(T* p) : ptr_{p} {}

    // O(1)
    Iterator& operator++(){
      ++ ptr_;
      return *this;
    }
    
    // O(1)
    Iterator operator++(int){
      return Iterator(ptr_++);
    }

    // O(1)
    Iterator& operator--() {
      --ptr_;
      return *this;
    }

    // O(1)
    Iterator operator--(int) {
      return Iterator(ptr_--);
    }

    // O(1)
    bool operator==(const Iterator& other) const {
      return other.ptr_ == ptr_;
    }

    // O(1)
    bool operator!=(const Iterator& other) const {
      return !operator==(other);
    }

    // O(1)
    T& operator*(){
      return *ptr_;
    }

    // O(1)
    const T& operator*() const {
      return *ptr_;
    }

    // O(1)
    T* operator->() {
      return ptr_;
    }

    // O(1)
    const T* operator->() const {
      return ptr_;
    }

    // O(1)
    ptrdiff_t operator-(const Iterator& other) const {
      return ptr_ - other.ptr_;
    }

    // O(1)
    Iterator operator+(const int& value) const{
     
      return Iterator(ptr_ + value); 
    }
    
    // O(1)
    Iterator operator-(const int& value) const {
      return Iterator(ptr_ - value); 
    } 

    // O(1)
    bool operator<(const Iterator& other) const {
      return ptr_ < other.ptr_;
    }

    // O(1)
    bool operator>(const Iterator& other) const {
      return ptr_ > other.ptr_;
    }

    // O(1)
    bool operator<=(const Iterator& other) const {
      return ptr_ <= other.ptr_;
    }

    // O(1)
    bool operator>=(const Iterator& other) const {
      return ptr_ >= other.ptr_;
    }

  private:
    T* ptr_;
};

// O(n)
template<typename T>
typename MojVektor<T>::Iterator MojVektor<T>::find(const T& value) const {
  for(auto it = begin(); it != end(); ++it){
    if(*it == value)
      return it;
  }
  return end();
}

// O(n)
template<typename T>
typename MojVektor<T>::Iterator MojVektor<T>::erase(Iterator pos) {
  for(auto it = pos; it != end() - 1; ++it){
    *it = *(it+1);
  }
  --size_;
  return pos;
}

// O(n)
template<typename T>
typename MojVektor<T>::Iterator MojVektor<T>::erase(Iterator beginIt, Iterator endIt) {
  auto distance = endIt - beginIt;
  auto it = beginIt;
  while(endIt != end()){
    *it = *endIt;
    ++endIt;
    ++it;
  }
  size_ -= distance;
  return beginIt;
}

// O(n)
template<typename T>
typename MojVektor<T>::Iterator MojVektor<T>::insert(Iterator pos, const T& value) {
  auto index = pos - begin(); // Ako se desi realokacija pos postaje nevazeci.
  if(size_ == capacity_) 
    reallocate();
  pos = begin() + index;
  for(auto it = end(); it > pos; --it){
    *it = *(it-1);
  }
  size_++;
  *pos = value;
  return pos;
}

// O(n)
template<typename T>
void MojVektor<T>::rotate() {
  MojVektor<T> rotated;
  for(auto it = --end(); it >= begin(); --it){
    rotated.push_back(*it);
  }
  *this = rotated;
}

// O(n)
template <typename T>
template <typename Fn>
void MojVektor<T>::for_each(Fn fn) {
  for(auto it = begin(); it != end(); ++it)
    fn(*it);
}
template <typename T>
template <typename Fn>
void MojVektor<T>::remove_if(Fn fn) {
  for(auto it = begin(); it != end();){
    if(fn(*it))
      it = erase(it);
    else 
      ++it;
  }
}
