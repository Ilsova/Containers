#include "s21_queue.h"

namespace s21 {

//______________________________________________________Functions
template <typename T>
Queue<T>::Queue() : data_(nullptr), size_(0) {}

template <typename T>
Queue<T>::Queue(const Queue &q) {
  if (&q != this) {
    size_ = q.size_;
    data_ = new T[size_];
    std::copy(q.data_, q.data_ + size_, data_);
  }
}

template <typename T>
Queue<T>::Queue(std::initializer_list<T> const &items) : Queue() {
  if (items.size() != 0) {
    size_ = items.size();
    data_ = new T[size_];
    std::move(items.begin(), items.end(), data_);
  }
}

template <typename T>
Queue<T>::Queue(Queue &&q) noexcept {
  size_ = q.size_;
  data_ = q.data_;
  q.size_ = 0;
  q.data_ = nullptr;
}

template <typename T>
Queue<T>::~Queue() {
  size_ = 0;
  delete[] data_;
}

template <typename T>
typename Queue<T>::Queue &Queue<T>::operator=(Queue &&q) {
  if (this != &q) {
    delete[] data_;

    size_ = q.size_;
    data_ = q.data_;

    q.size_ = 0;
    q.data_ = nullptr;
  }
  return *this;
}

//______________________________________________________Capacity
template <typename T>
bool Queue<T>::empty() const {
  return size_ == 0;
}

template <typename T>
typename Queue<T>::size_type Queue<T>::size() const {
  return size_;
}

//______________________________________________________Element access
template <typename T>
typename Queue<T>::const_reference Queue<T>::front() const {
  if (empty()) {
    throw std::out_of_range("Queue is empty");
  }
  return data_[0];
}

template <typename T>
typename Queue<T>::const_reference Queue<T>::back() const {
  if (empty()) {
    throw std::out_of_range("Queue is empty");
  }
  return data_[size_ - 1];
}

//_______________________________________________________Modifiers
template <typename T>
void Queue<T>::pop() {
  if (empty()) {
    throw std::out_of_range("Queue is empty");
  }

  T *newData = new T[size_ - 1];
  std::copy(data_ + 1, data_ + size_, newData);
  delete[] data_;
  data_ = newData;
  size_ -= 1;
}

template <typename T>
void Queue<T>::push(const_reference value) {
  try {
    T *newData = new T[size_ + 1];
    std::copy(data_, data_ + size_, newData);
    newData[size_] = std::move(value);
    delete[] data_;
    data_ = newData;
    size_ += 1;
  } catch (const std::bad_alloc &e) {
    std::cerr << "Exception caught: " << e.what() << std::endl;
  }
}

template <typename T>
void Queue<T>::swap(Queue &q) {
  T *tempData = data_;
  data_ = q.data_;
  q.data_ = tempData;

  size_type tempSize = size_;
  size_ = q.size_;
  q.size_ = tempSize;
}

}  // namespace s21