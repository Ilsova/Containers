#ifndef SRC_S21_LIST_H
#define SRC_S21_LIST_H

#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <limits>

namespace s21 {
template <typename T>
class List {
 public:
  typedef struct Node_ {
    T data;
    Node_ *prev = nullptr;
    Node_ *next = nullptr;
    explicit Node_(const T &data) : data(data), prev(nullptr), next(nullptr) {}
  } Node_;

  // Functions
  List() noexcept;
  List(size_t n);
  List(std::initializer_list<T> const &items);
  List(const List &l);
  List(List &&l);
  ~List();
  List &operator=(List &&l);
  List &operator=(const List &l);

  // Member type
  class ListIterator;
  class ListConstIterator;
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = List<T>::ListIterator;
  using const_iterator = List<T>::ListConstIterator;
  using size_type = size_t;

  // Element access
  const_reference front() const;
  const_reference back() const;

  // Iterators
  iterator begin();
  const_iterator c_begin() const;
  iterator end();
  const_iterator c_end() const;

  // Capacity
  bool empty() const;
  size_type size() const;
  size_type max_size() const noexcept;

  // Modifiers
  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void push_front(const_reference value);
  void pop_front();
  void swap(List &other) noexcept;
  void merge(List &other);
  void splice(const_iterator pos, List &other);
  void reverse() noexcept;
  void unique();
  void sort();

  class ListIterator {
   public:
    ListIterator();
    ListIterator(const ListIterator &other);
    ListIterator(Node_ *iter);

    ListIterator &operator=(const ListIterator &other);
    bool operator==(const ListIterator &other) const;
    bool operator!=(const ListIterator &other) const;
    ListIterator operator++();
    ListIterator operator--();
    ListIterator operator++(int);
    reference operator*();
    T *operator->();
    Node_ *get_node();

   private:
    Node_ *iter_ = nullptr;
  };

  class ListConstIterator {
   public:
    ListConstIterator();
    ListConstIterator(const ListConstIterator &other);
    ListConstIterator(Node_ *iter_);

    ListConstIterator &operator=(const ListConstIterator &other);
    bool operator==(const ListConstIterator &other) const;
    bool operator!=(const ListConstIterator &other) const;
    ListConstIterator operator++();
    ListConstIterator operator--();
    ListConstIterator operator++(int);
    const_reference operator*() const;
    const Node_ *get_node() const;

   private:
    const Node_ *iter_ = nullptr;
  };

 private:
  Node_ *head_;
  Node_ *tail_;
  size_t size_;

};  // class List

}  // namespace s21

#include "s21_list.tpp"
#endif  // SRC_S21_LIST_H_