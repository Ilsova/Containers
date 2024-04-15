#ifndef S21_SET_H
#define S21_SET_H

#include "../RedBlackTree/rb_tree.h"

namespace s21 {
template <typename Key>
class Set : public RedBlackTree<Key> {
 public:
  using Base = RedBlackTree<Key>;
  using value_type = Key;

  // Inherit constructor from the base class
  using Base::RedBlackTree;

  Set(std::initializer_list<value_type> const& items) : Base(items) {}

  // pretty printout
  friend std::ostream& operator<<(std::ostream& os, const Set<Key>& set) {
    if (set.size()) {
      auto it = set.cbegin();
      os << "Set is: {";
      if (it != set.cend()) {
        os << it.key();
        ++it;
      }
      while (it != set.cend()) {
        os << ", " << it.key();
        ++it;
      }
      os << "}\n";
    }
    return os;
  }
};
}  // namespace s21

#endif  // S21_SET_H
