#ifndef SRC_S21_MAP_H
#define SRC_S21_MAP_H

#include <initializer_list>
#include <iostream>

#include "../RedBlackTree/rb_tree.h"

namespace s21 {

template <typename Key, typename T>
class Map : public RedBlackTree<Key, T> {
 public:
  // Member type
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;

  using iterator = typename RedBlackTree<Key, T>::iterator;
  using const_iterator = typename RedBlackTree<Key, T>::const_iterator;

  using size_type = size_t;

  // Functions
  Map() : RedBlackTree<Key, T>(){};
  Map(std::initializer_list<value_type> const& items);
  Map(const Map& other) : RedBlackTree<Key, T>(other){};
  Map(Map&& other) noexcept : RedBlackTree<Key, T>(std::move(other)){};
  ~Map();
  Map& operator=(Map&& other) noexcept;
  Map& operator=(const Map& other);

  // Element access
  T& at(const Key& key);
  T& operator[](const Key& key);

  // Iterators
  iterator begin();
  iterator end();
  const_iterator cbegin() const;
  const_iterator cend() const;

  // Capacity
  bool empty() const { return RedBlackTree<Key, T>::empty(); };
  size_type size() const { return RedBlackTree<Key, T>::size(); };
  size_type max_size() { return RedBlackTree<Key, T>::max_size(); };

  // Modifiers
  void clear();
  std::pair<iterator, bool> insert(const value_type& value);
  std::pair<iterator, bool> insert(const Key& key, const T& obj);
  std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj);
  void erase(iterator pos);
  void swap(Map& other);
  void merge(Map& other);

  // Lookup
  bool contains(const Key& key) { return RedBlackTree<Key, T>::contains(key); }

 private:
  iterator find(const Key& key);

};  // class map
}  // namespace s21

#include "s21_map.tpp"
#endif  // SRC_S21_MAP_H_
