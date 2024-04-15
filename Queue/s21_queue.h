#ifndef SRC_S21_QUEUE_H
#define SRC_S21_QUEUE_H

//#include <cstddef>  //для использования size_t
#include <initializer_list>
#include <iostream>

namespace s21 {

template <typename T>
class Queue {
 public:
  // Functions
  Queue();
  Queue(std::initializer_list<T> const &items);
  Queue(const Queue &q);
  Queue(Queue &&q) noexcept;
  ~Queue();
  Queue &operator=(Queue &&q);

  // Member type
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  // Element access
  const_reference front() const;
  const_reference back() const;

  // Capacity
  bool empty() const;
  size_type size() const;

  // Modifiers
  void push(const_reference value);
  void pop();
  void swap(Queue &q);

 private:
  T *data_;
  size_type size_;
};
}  // namespace s21

#include "s21_queue.tpp"
#endif  // SRC_S21_QUEUE_H_