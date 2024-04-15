#include <iostream>

#include "s21_map.h"

// s21_map.tpp

namespace s21 {

template <typename Key, typename T>
Map<Key, T>::Map(std::initializer_list<value_type> const &items)
    : RedBlackTree<Key, T>() {
  for (auto i = items.begin(); i != items.end(); ++i) {
    this->insert(*i);
  }
}

template <typename Key, typename T>
Map<Key, T>::~Map() {
  RedBlackTree<Key, T>::clear();
}

template <typename Key, typename T>
Map<Key, T> &Map<Key, T>::operator=(Map &&other) noexcept {
  if (this != &other) {
    RedBlackTree<Key, T>::operator=(std::move(other));
  }
  return *this;
}

template <typename Key, typename T>
Map<Key, T> &Map<Key, T>::operator=(const Map &other) {
  if (this != &other) {
    RedBlackTree<Key, T>::operator=(other);
  }
  return *this;
}

template <typename Key, typename T>
typename Map<Key, T>::iterator Map<Key, T>::begin() {
  return iterator(RedBlackTree<Key, T>::begin().node());
}

template <typename Key, typename T>
typename Map<Key, T>::iterator Map<Key, T>::end() {
  return iterator(RedBlackTree<Key, T>::end().node());
}

template <typename Key, typename T>
typename Map<Key, T>::const_iterator Map<Key, T>::cbegin() const {
  return const_iterator(RedBlackTree<Key, T>::cbegin().node());
}

template <typename Key, typename T>
typename Map<Key, T>::const_iterator Map<Key, T>::cend() const {
  return const_iterator(RedBlackTree<Key, T>::cend().node());
}

template <typename Key, typename T>
typename Map<Key, T>::iterator Map<Key, T>::find(const Key &key) {
  return iterator(RedBlackTree<Key, T>::find(key).node());
}

template <typename Key, typename T>
T &Map<Key, T>::at(const Key &key) {
  iterator it = find(key);
  if (it != end()) {
    return it.node()->value_;
  } else {
    throw std::out_of_range("Key not found in the map");
  }
}

template <typename Key, typename T>
T &Map<Key, T>::operator[](const Key &key) {
  auto it = find(key);
  if (it != end()) {
    return it.node()->value_;
  } else {
    auto result = insert({key, T()});
    return result.first.node()->value_;
  }
}

template <typename Key, typename T>
std::pair<typename Map<Key, T>::iterator, bool> Map<Key, T>::insert(
    const value_type &value) {
  return RedBlackTree<Key, T>::insert(value);
}

template <typename Key, typename T>
std::pair<typename Map<Key, T>::iterator, bool> Map<Key, T>::insert(
    const Key &key, const T &obj) {
  return RedBlackTree<Key, T>::insert({key, obj});
}

template <typename Key, typename T>
std::pair<typename Map<Key, T>::iterator, bool> Map<Key, T>::insert_or_assign(
    const Key &key, const T &obj) {
  iterator it = find(key);
  if (it != end()) {
    it.node()->value_ = obj;
    return {it, false};
  } else {
    return insert({key, obj});
  }
}

template <typename Key, typename T>
void Map<Key, T>::erase(iterator pos) {
  RedBlackTree<Key, T>::erase(pos);
}

template <typename Key, typename T>
void Map<Key, T>::swap(Map &other) {
  RedBlackTree<Key, T>::swap(other);
}

template <typename Key, typename T>
void Map<Key, T>::merge(Map &other) {
  RedBlackTree<Key, T>::merge(other);
}

};  // namespace s21
