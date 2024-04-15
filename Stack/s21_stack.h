#ifndef SRC_S21_STACK_H
#define SRC_S21_STACK_H

#include <initializer_list>
#include <iostream>

#include "../List/s21_list.h"
#include "../Vector/s21_vector.h"

namespace s21 {

template <typename T, typename Container = List<T>>
class Stack {
 public:
  // Functions
  Stack();
  Stack(std::initializer_list<T> const &items);
  Stack(const Stack &other);
  Stack(Stack &&other);
  ~Stack();
  Stack &operator=(Stack &&other) noexcept;
  Stack &operator=(const Stack &other);

  // Member type
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  // Element access
  const_reference top() const;

  // Capacity
  bool empty() const;
  size_type size() const;

  // Modifiers
  void push(const_reference value);
  void pop();
  void swap(Stack &other);

 private:
  Container List_;

};  // class stack
}  // namespace s21

#include "s21_stack.tpp"
#endif  // SRC_S21_STACK_H_