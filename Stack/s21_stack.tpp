#include "s21_stack.h"

namespace s21 {
template <typename T, typename Container>
Stack<T, Container>::Stack() : List_() {}

template <typename T, typename Container>
Stack<T, Container>::Stack(std::initializer_list<T> const& items) {
  for (auto i = items.begin(); i != items.end(); i++) {
    push(*i);
  }
}

template <typename T, typename Container>
Stack<T, Container>::Stack(const Stack& other) : List_(other.List_) {}

template <typename T, typename Container>
Stack<T, Container>::Stack(Stack&& other) : List_(std::move(other.List_)) {}

template <typename T, typename Container>
Stack<T, Container>::~Stack() {}

template <typename T, typename Container>
Stack<T, Container>& Stack<T, Container>::operator=(const Stack& other) {
  if (this != &other) {
    List_ = other.List_;
  }
  return *this;
}

template <typename T, typename Container>
Stack<T, Container>& Stack<T, Container>::operator=(Stack&& other) noexcept {
  if (this != &other) {
    List_ = std::move(other.List_);
  }
  return *this;
}

template <typename T, typename Container>
typename Stack<T, Container>::const_reference Stack<T, Container>::top() const {
  if constexpr (std::is_same_v<Container, s21::Vector<T>>) {
    return List_.back();
  } else {
    return List_.front();
  }
}

template <typename T, typename Container>
bool Stack<T, Container>::empty() const {
  return List_.empty();
}

template <typename T, typename Container>
typename Stack<T, Container>::size_type Stack<T, Container>::size() const {
  return List_.size();
}

template <typename T, typename Container>
void Stack<T, Container>::push(const_reference value) {
  if constexpr (std::is_same_v<Container, Vector<T>>) {
    List_.push_back(value);
  } else {
    List_.push_front(value);
  }
}

template <typename T, typename Container>
void Stack<T, Container>::pop() {
  if constexpr (std::is_same_v<Container, Vector<T>>) {
    List_.pop_back();
  } else {
    List_.pop_front();
  }
}

template <typename T, typename Container>
void Stack<T, Container>::swap(Stack& other) {
  List_.swap(other.List_);
}

}  // namespace s21