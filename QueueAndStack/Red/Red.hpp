#pragma once
#include <initializer_list>
#include <algorithm>

template <typename T>
class red {
  public:
    red() : capacity_(100), data_{new T[capacity_]}, size_(0), head_(0), tail_(0) {}

    red(const std::initializer_list<T>& lista) : capacity_(lista.size() ? lista.size() : 1),data_{new T[capacity_]}, size_{lista.size()}, head_(0), tail_(lista.size()){
      std::copy(lista.begin(), lista.end(), data_);
    }

    red(const red& other) : capacity_(other.capacity_), data_(new T[capacity_]), size_(other.size_), head_(0), tail_(size_){
      if(other.head_ >= other.tail_ && size_){
        std::copy(other.data_ + other.head_, other.data_ + capacity_, data_);
        std::copy(other.data_, other.data_ + other.tail_, data_ + (other.capacity_ - other.head_));
      }
      else 
        std::copy(other.data_ + other.head_, other.data_ + other.tail_, data_);
    }


    red(red&& other) : capacity_(other.capacity_), data_(other.data_), size_(other.size_), head_(other.head_), tail_(other.tail_) {
      other.data_ = nullptr;
      other.tail_ = 0;
      other.head_ = 0;
      other.size_ = 0;
    }

    red& operator=(red other) {
      std::swap(data_, other.data_);
      std::swap(capacity_, other.capacity_);
      std::swap(size_, other.size_);
      std::swap(head_, other.head_);
      std::swap(tail_, other.tail_);
      return *this;
    }

    red& operator=(red&& other){
      if(this != &other){
        delete[] data_;
        data_ = other.data_;
        capacity_ = other.capacity_;
        size_ = other.size_;
        head_ = other.head_;
        tail_ = other.tail_;
        other.data_ = nullptr;
        other.head_ = other.tail_ = other.size_ = 0;
      }
      return *this;
   }
    ~red() {
      delete[] data_;
    }


    template <typename U>
    red<T>& push(U&& element);
    void pop();
    const T& back() const;
    const T& front() const;
    T& back();
    T& front();
    std::size_t size() const { return size_;}
    bool empty() const {return size_ == 0;};
  
  private:
    std::size_t capacity_;
    T* data_;
    std::size_t size_;
    std::size_t head_;
    std::size_t tail_;
    void reallocate();
};

template <typename T>
void red<T>::reallocate(){
  size_t newCapacity_ = capacity_ * 2;
  T* temp = new T[newCapacity_];
  for(auto i = 0; i < size_; ++i){
    temp[i] = std::move(data_[(head_ + i) % capacity_]);
  }
  delete [] data_;
  capacity_ = newCapacity_;
  data_ = temp;
  head_ = 0;
  tail_ = size_;
}

template <typename T>
template <typename U>
red<T>& red<T>::push(U&& element){
  if(size_ == capacity_) reallocate();
  data_[tail_] = std::forward<U>(element);
  tail_ = (tail_+1) % capacity_;
  ++size_;
  return *this;
}

template <typename T>
void red<T>::pop() {
  if(empty())
    return;
  auto temp = std::move(data_[head_]);
  head_ = (head_ + 1) % capacity_;
  --size_;
}

template <typename T>
const T& red<T>::back() const {
  return data_[(tail_ - 1 + capacity_) % capacity_];
}

template <typename T>
T& red<T>::back() {
  return data_[(tail_ - 1 + capacity_) % capacity_];
}

template <typename T>
const T& red<T>::front() const {
  return data_[head_];
}

template <typename T>
T& red<T>::front(){
  return data_[head_];
}
