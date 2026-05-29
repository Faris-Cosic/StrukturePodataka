#pragma once

#include <stdexcept>
#include <utility>
#include <cstddef>
#include <iterator>
#include <functional>

template <typename T>
class DoubleLinkedList {
  public:
    DoubleLinkedList() = default;
    
    DoubleLinkedList(const DoubleLinkedList& other){
      for(auto temp = other.head_; temp != nullptr;temp = temp->next_)
        push_back(temp->value_);
    }

    DoubleLinkedList(DoubleLinkedList&& other) : head_(other.head_), tail_(other.tail_), size_(other.size_){
      other.head_ = other.tail_ = nullptr;
      other.size_ = 0;
    }

    ~DoubleLinkedList(){
      clear();
    }

    DoubleLinkedList& operator=(const DoubleLinkedList& other){
      if(this == &other) 
        return *this;

      clear();
      for(auto temp = other.head_; temp != nullptr; temp = temp->next_)
        push_back(temp->value_);
      return *this;
    }

    DoubleLinkedList& operator=(DoubleLinkedList&& other){
      clear();
      head_ = other.head_;
      tail_ = other.tail_;
      size_ = other.size_;

      other.head_ = nullptr;
      other.tail_ = nullptr;
      other.size_ = 0;
      return *this;
    }

  
    template<typename U>
    void push_back(U&& element){
      auto temp = new Node(std::forward<U>(element));
      if (empty())
        tail_ = head_ = temp;
      else{
        temp->prev_ = tail_;
        tail_->next_ = temp;
        tail_ = temp;
      }
      size_++;
    }

    template<typename U>
    void push_front(U&& element){
      auto temp = new Node(std::forward<U>(element));
      if(empty())
        tail_ = temp;
      else 
        head_->prev_ = temp;
      temp->next_ = head_;
      head_ = temp;
      size_++; 
    }

    void pop_front();
    void pop_back();

    const T& front() const {
      return head_->value_;
    }
    const T& back() const {
      return tail_->value_;
    }

    T& front() {
      return head_->value_;
    }

    T& back() {
      return tail_->value_;
    }

    void clear(){
      while(head_ != nullptr){
        auto temp = head_;
        head_ = head_->next_;
        delete temp;
      }
      size_ = 0;
      tail_ = nullptr;
      head_ = nullptr;
    }

    bool empty() const{
      return size_ == 0;    
    }

    size_t size() const {
      return size_;
    }

    class iterator;
    using Iterator  = iterator;

    iterator begin() const{
      auto it = iterator(head_);
      it.last_ = tail_;
      return it;
    }

    iterator end() const{
      auto it = iterator(nullptr);
      it.last_ = tail_;
      return it;
    }

    iterator find(const T& value);

    template <typename U>
    iterator insert(const iterator& position, U&& element);
    iterator erase(const iterator& position);
    iterator erase(const iterator& start, const iterator& end);
    template <typename Fn>
    void remove_if(const Fn& fn);
    void reverse();





  private:
    struct Node {
      Node(const T& element, Node *ptrPrev = nullptr, Node *ptrNext = nullptr) : value_(element), next_{ptrNext}, prev_(ptrPrev) {}
      Node(T&& element, Node *ptrPrev = nullptr, Node *ptrNext = nullptr) : value_(std::move(element)), next_(ptrNext), prev_(ptrPrev) {}

      T value_;
      Node* prev_;
      Node* next_;
    };

    Node* head_ = nullptr;
    Node* tail_ = nullptr;
    size_t size_ = 0;
};


template <typename T>
void DoubleLinkedList<T>::pop_back(){
  if(empty())
    throw std::runtime_error("Error, list empty!");

  auto temp = tail_;
  if(size_ == 1){
    head_ = tail_ = nullptr;
  }
  else{
    tail_ = tail_->prev_;
    tail_->next_ = nullptr;
  }
  delete temp;
  size_--;
}

template <typename T>
void DoubleLinkedList<T>::pop_front(){
  if(empty())
    throw std::runtime_error("Error, list empty!");
  auto temp = head_;
  if (size_ == 1){
    head_ = tail_ = nullptr;
  }
  else{
    head_ = head_->next_;
    head_->prev_ = nullptr;
  }
  delete temp;
  size_--;
}

template <typename T>
class DoubleLinkedList<T>::iterator{
  public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using difference_type = std::ptrdiff_t;
    friend DoubleLinkedList<T>;

    iterator(Node* p) : ptr_(p) {}
    iterator() = default;

    T& operator*(){
      return ptr_->value_;
    }

    T* operator->(){
      return &ptr_->value_;
    }

    iterator& operator++(){
      if(ptr_)
        ptr_ = ptr_->next_;
      return *this;
    }

    iterator operator++(int){
      auto p = *this;
      if(ptr_)
        ptr_ = ptr_->next_;
      return p;
    }

    bool operator==(const iterator& other) const{
      return ptr_ == other.ptr_;
    }

    bool operator!=(const iterator& other) const{
      return !operator==(other);
    }

    iterator& operator--(){
      if(ptr_){
        ptr_ = ptr_->prev_;
      }
      else {
        ptr_ = last_;
      }
      return *this;
    }

    iterator operator--(int){
      auto p = *this;
      if(ptr_)
        ptr_ = ptr_->prev_;
      else {
        ptr_ = last_;
      }
      return p;
    }

  private:
    Node* ptr_;
    Node* last_;
};


template <typename T>
template <typename U>
typename DoubleLinkedList<T>::iterator DoubleLinkedList<T>::insert(const iterator& position, U&& element){
  if (position == begin()){
    push_front(std::forward<U>(element));
    return begin();
  }
  else if(position == end()){
    push_back(std::forward<U>(element));
    auto it = iterator(tail_);
    it.last_ = tail_;
    return it; 
  }
  else {
    auto node = new Node(std::forward<U>(element));
    node->prev_ = position.ptr_->prev_;
    node->next_ = position.ptr_;
    position.ptr_->prev_ = node;
    node->prev_->next_ = node;
    size_++;
    auto it = iterator(node);
    it.last_ = tail_;
    return it; 
  }
}

template <typename T>
typename DoubleLinkedList<T>::iterator DoubleLinkedList<T>::erase(const iterator& position){
  if(empty())
    throw std::runtime_error("Error, list empty!");
  if(position.ptr_ == tail_){
    pop_back();
    return end();
  }
  else if(position == begin()){
    pop_front();
    return begin();
  }
  else {
    auto temp = position.ptr_;
    auto nextPosition = position.ptr_->next_;
    auto prevPosition = position.ptr_->prev_;
    nextPosition->prev_ = prevPosition;
    prevPosition->next_ = nextPosition;
    delete temp;
    size_--;
    auto it = iterator(nextPosition);
    it.last_ = tail_;
    return it; 
  }
}

template <typename T>
typename DoubleLinkedList<T>::iterator DoubleLinkedList<T>::erase(const iterator& start, const iterator& last){
  for(auto it = start; it != last;){
    it = erase(it);
  }
  return last;
}

template <typename T>
template <typename Fn>
void DoubleLinkedList<T>::remove_if(const Fn& fn){
  for(auto it = begin(); it != end();){
    if(fn(*it))
      it = erase(it);
    else 
      ++it;
  }
}

template <typename T>
typename DoubleLinkedList<T>::iterator DoubleLinkedList<T>::find(const T& value) {
  for(auto it = begin(); it != end(); ++it){
    if(*it == value)
      return it;
  }
  return end();
}

template <typename T>
void DoubleLinkedList<T>::reverse(){
  if(empty()){
    throw std::runtime_error("Error, list empty!");
  }
  if(size_ == 1)
    return;
  for(auto it = begin(); it != end();){
    auto nextIt = it.ptr_->next_;
    std::swap(it.ptr_->next_, it.ptr_->prev_);
    it = nextIt;
  }
  std::swap(head_, tail_);
}


