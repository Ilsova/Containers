#include <iostream>

#include "s21_list.h"

namespace s21 {

//______________________________________________________Functions
template <typename T>
List<T>::List() noexcept : head_(nullptr), tail_(nullptr), size_(0) {}

template <typename T>
List<T>::~List() {
  while (head_ != nullptr) pop_front();
}

template <typename T>
List<T>::List(size_t n) : head_(nullptr), tail_(nullptr), size_(0) {
  for (size_type i = 0; i < n; i++) {
    push_back(T());
  }
}

template <typename T>
List<T>::List(std::initializer_list<T> const &items)
    : head_(nullptr), tail_(nullptr), size_(0) {
  for (const T &items : items) {
    push_back(items);
  }
}

template <typename T>
List<T>::List(const List &l) : head_(nullptr), tail_(nullptr), size_(0) {
  for (const Node_ *current = l.head_; current != nullptr;
       current = current->next) {
    push_back(current->data);
  }
}

template <typename T>
List<T>::List(List &&l) : head_(l.head_), tail_(l.tail_), size_(l.size_) {
  l.head_ = nullptr;
  l.tail_ = nullptr;
  l.size_ = 0;
}

template <typename T>
List<T> &List<T>::operator=(List &&l) {
  if (this != &l) {
    clear();

    head_ = l.head_;
    tail_ = l.tail_;
    size_ = l.size_;

    l.head_ = nullptr;
    l.tail_ = nullptr;
    l.size_ = 0;
  }
  return *this;
}

template <typename T>
List<T> &List<T>::operator=(const List &l) {
  if (this != &l) {
    while (!empty()) {
      pop_front();
    }
    Node_ *current = l.head_;
    while (current) {
      push_back(current->data);
      current = current->next;
    }
  }
  return *this;
}

//________________________________________________________________Element access

template <typename T>
typename List<T>::const_reference List<T>::front() const {
  if (head_ == nullptr) {
    throw std::out_of_range("List is empty");
  }
  return head_->data;
}

template <typename T>
typename List<T>::const_reference List<T>::back() const {
  if (head_ == nullptr) {
    throw std::out_of_range("List is empty");
  }
  return tail_->data;
}

//_________________________________________________________________Iterators

template <typename T>
typename List<T>::iterator List<T>::begin() {
  return iterator(head_);
}

template <typename T>
typename List<T>::const_iterator List<T>::c_begin() const {
  return const_iterator(head_);
}

template <typename T>
typename List<T>::iterator List<T>::end() {
  return iterator(tail_);
}

template <typename T>
typename List<T>::const_iterator List<T>::c_end() const {
  return const_iterator(tail_);
}

//__________________________________________________________________Capacity
template <typename T>
bool List<T>::empty() const {
  return size_ == 0;
}

template <typename T>
typename List<T>::size_type List<T>::size() const {
  return size_;
}

template <typename T>
typename List<T>::size_type List<T>::max_size() const noexcept {
  return std::numeric_limits<size_type>::max();
}

//________________________________________________________________________Modifiers

template <typename T>
void List<T>::pop_front() {
  if (head_ != nullptr) {
    Node_ *tmp_node = head_->next;
    if (tmp_node != nullptr) {
      tmp_node->prev = nullptr;
    } else {
      tail_ = nullptr;
    }
    delete head_;
    head_ = tmp_node;
    size_--;
  }
}

template <typename T>
void List<T>::push_back(const_reference value) {
  Node_ *new_node = new Node_(value);
  if (head_ == nullptr) {
    head_ = tail_ = new_node;
  } else {
    tail_->next = new_node;
    new_node->prev = tail_;
    tail_ = new_node;
  }
  size_++;
}

template <typename T>
void List<T>::clear() {
  while (head_ != nullptr && tail_ != nullptr) {
    pop_front();
  }
};

template <typename T>
typename List<T>::iterator List<T>::insert(iterator pos,
                                           const_reference value) {
  Node_ *newNode = new Node_(value);
  if (pos.get_node() == tail_) {
    if (empty()) {
      head_ = newNode;
      tail_ = newNode;
      size_++;
    } else {
      Node_ *tmp = tail_;
      tail_->next = newNode;
      newNode->prev = tmp;
      tail_ = newNode;
      size_++;
    }
  } else {
    Node_ *prevNode = pos.get_node()->prev;
    if (prevNode) {
      prevNode->next = newNode;
      newNode->prev = prevNode;
    }
    newNode->next = pos.get_node();
    pos.get_node()->prev = newNode;
    if (pos.get_node() == head_) {
      head_ = newNode;
    }
    size_++;
  }
  return iterator(newNode);
}

template <typename T>
void List<T>::erase(iterator pos) {
  Node_ *current = pos.get_node();

  if (current == nullptr) {
    throw std::out_of_range(
        "Элемента не существует, попытка удаления неудачна");
  }

  if (current->prev) {
    current->prev->next = current->next;
  }
  if (current->next) {
    current->next->prev = current->prev;
  }

  if (current == head_) {
    head_ = current->next;
  }
  if (current == tail_) {
    tail_ = current->prev;
  }

  if (head_ == nullptr) {
    tail_ = nullptr;
  }

  delete current;
  size_--;
}

template <typename T>
void List<T>::pop_back() {
  if (head_ == nullptr) {
    throw std::out_of_range("List is empty");
  }

  Node_ *tmp_node = tail_->prev;
  if (tmp_node != nullptr) {
    tmp_node->next = nullptr;
  } else {
    head_ = tmp_node;
  }
  delete tail_;
  tail_ = tmp_node;
  size_--;
}

template <typename T>
void List<T>::push_front(const_reference value) {
  Node_ *new_node = new Node_(value);
  if (head_ == nullptr) {
    head_ = tail_ = new_node;
  } else {
    head_->prev = new_node;
    new_node->next = head_;
    head_ = new_node;
  }
  size_++;
}

template <typename T>
void List<T>::merge(List &other) {
  List result;
  iterator this_begin = begin();
  iterator other_begin = other.begin();
  if (other.empty()) {
    return;
  }
  if (empty()) {
    other.sort();
    *this = std::move(other);
    return;
  }
  while (this_begin != ++end()) {
    result.push_back(*this_begin);
    this_begin++;
  }
  while (other_begin != ++other.end()) {
    result.push_back(*other_begin);
    other_begin++;
  }
  result.sort();
  clear();
  *this = std::move(result);
}

template <typename T>
void List<T>::sort() {
  for (auto iter = begin(); iter != ++end(); ++iter) {
    for (auto innerIter = begin(); innerIter != ++end(); ++innerIter) {
      auto nextIter = innerIter;
      ++nextIter;

      if (nextIter != ++end()) {
        if (*innerIter > *nextIter) {
          std::swap(*innerIter, *nextIter);
        }
      }
    }
  }
}

template <typename T>
void List<T>::reverse() noexcept {
  if (head_ == nullptr ||
      head_ == tail_) {  // Пустой список или один элемент - ничего не делаем
    return;
  }
  Node_ *current = head_;
  while (current != nullptr) {
    std::swap(current->prev, current->next);
    current = current->prev;
  }
  std::swap(head_, tail_);
}

template <typename T>
void List<T>::splice(const_iterator pos, List &other) {
  // находим наши узлы
  Node_ *target_node = const_cast<s21::List<int>::Node_ *>(pos.get_node());
  Node_ *first_node_other = other.head_;
  Node_ *last_node_other = other.tail_;
  if (other.head_ == nullptr) return;  // если список пуст, то ничего не делаем
  if (target_node != nullptr) {  // Обновляем указатели в начальном списке
    Node_ *prev_target_node = target_node->prev;
    if (prev_target_node != nullptr) {
      prev_target_node->next = first_node_other;
    }

    first_node_other->prev = prev_target_node;
    last_node_other->next = target_node;
    target_node->prev = last_node_other;
    if (target_node ==
        head_) {  // если pos указывает на начало то нужно обновить head_
      head_ = first_node_other;
    }
  } else {  // если pos указывает на конец начального списка
    if (tail_ != nullptr) {  // если начальный список не пустой
      tail_->next = first_node_other;
      first_node_other->prev = tail_;
    } else {  // если все-таки пустой
      head_ = first_node_other;
    }
    tail_ = last_node_other;
  }
  size_ += other.size_;
  other.size_ = 0;
  other.head_ = nullptr;
  other.tail_ = nullptr;
}

template <typename T>
void List<T>::swap(List &other) noexcept {
  std::swap(head_, other.head_);
  std::swap(tail_, other.tail_);
  std::swap(size_, other.size_);
}

template <typename T>
void List<T>::unique() {
  auto iter = begin();
  Node_ *current_node;
  Node_ *next_node;
  if (empty()) return;
  for (; iter != end();) {
    current_node = iter.get_node();
    next_node = current_node->next;
    if (next_node && current_node->data == next_node->data) {
      erase(iter);
      iter = iterator(next_node);
    } else {
      ++iter;
    }
  }
}

//_________________________________________________________class ListIterator
template <typename T>
List<T>::ListIterator::ListIterator() : iter_(nullptr) {}

template <typename T>
List<T>::ListIterator::ListIterator(const ListIterator &other)
    : iter_(other.iter_) {}

template <typename T>
List<T>::ListIterator::ListIterator(Node_ *iter) : iter_(iter) {}

template <typename T>
typename List<T>::ListIterator &List<T>::ListIterator::operator=(
    const ListIterator &other) {
  iter_ = other.iter_;
  return *this;
}

template <typename T>
bool List<T>::ListIterator::operator==(const ListIterator &other) const {
  return iter_ == other.iter_;
}

template <typename T>
bool List<T>::ListIterator::operator!=(const ListIterator &other) const {
  return iter_ != other.iter_;
}

template <typename T>
typename List<T>::ListIterator List<T>::ListIterator::operator++() {
  iter_ = iter_->next;
  return *this;
}

template <typename T>
typename List<T>::ListIterator List<T>::ListIterator::operator--() {
  iter_ = iter_->prev;
  return *this;
}

template <typename T>
typename List<T>::ListIterator List<T>::ListIterator::operator++(int) {
  ListIterator tmp(*this);
  iter_ = iter_->next;
  return tmp;
}

template <typename T>
T &List<T>::ListIterator::operator*() {
  return iter_->data;
}

template <typename T>
T *List<T>::ListIterator::operator->() {
  return &(iter_->value);
}

template <typename T>
typename List<T>::Node_ *List<T>::ListIterator::get_node() {
  return iter_;
}

//_________________________________________________class ListConstIterator

template <typename T>
List<T>::ListConstIterator::ListConstIterator() : iter_(nullptr) {}

template <typename T>
List<T>::ListConstIterator::ListConstIterator(const ListConstIterator &other)
    : iter_(other.iter_) {}

template <typename T>
List<T>::ListConstIterator::ListConstIterator(Node_ *iter_) : iter_(iter_) {}

template <typename T>
typename List<T>::ListConstIterator &List<T>::ListConstIterator::operator=(
    const ListConstIterator &other) {
  iter_ = other.iter_;
  return *this;
}

template <typename T>
bool List<T>::ListConstIterator::operator==(
    const ListConstIterator &other) const {
  return iter_ == other.iter_;
}

template <typename T>
bool List<T>::ListConstIterator::operator!=(
    const ListConstIterator &other) const {
  return iter_ != other.iter_;
}

template <typename T>
typename List<T>::ListConstIterator List<T>::ListConstIterator::operator++() {
  iter_ = iter_->next;
  return *this;
}

template <typename T>
typename List<T>::ListConstIterator List<T>::ListConstIterator::operator--() {
  iter_ = iter_->prev;
  return *this;
}

template <typename T>
typename List<T>::ListConstIterator List<T>::ListConstIterator::operator++(
    int) {
  ListConstIterator tmp(*this);
  iter_ = iter_->next;
  return tmp;
}

template <typename T>
const T &List<T>::ListConstIterator::operator*() const {
  return iter_->data;
}

template <typename T>
const typename List<T>::Node_ *List<T>::ListConstIterator::get_node() const {
  return iter_;
}

}  // namespace s21