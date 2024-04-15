#ifndef S21_RB_TREE_H
#define S21_RB_TREE_H

#include <iostream>
#include <limits>   // max_size
#include <utility>  // std::pair

namespace s21 {

template <typename Key, typename Data = char>
class RedBlackTree {
 public:
  enum class Colour : char { BLACK, RED };
  struct TreeNode;
  class TreeIterator;
  class ConstTreeIterator;

  using key_type = Key;
  using mapped_type = Data;
  using value_type = std::pair<key_type, mapped_type>;
  using size_type = size_t;
  using node_ptr = TreeNode*;
  using iterator = TreeIterator;
  using const_iterator = ConstTreeIterator;
  using iterator_category = std::bidirectional_iterator_tag;

  // CONSTRUCTORS
  RedBlackTree() : root_(nullptr), size_(0) {}

  RedBlackTree(std::initializer_list<key_type> const& items)
      : root_(nullptr), size_(0) {
    for (const auto& item : items) {
      insert(item);
    }
  }

  RedBlackTree(std::initializer_list<value_type> const& items)
      : root_(nullptr), size_(0) {
    for (const auto& item : items) {
      insert(item);
    }
  }

  RedBlackTree(const RedBlackTree& other) : root_(nullptr), size_(0) {
    root_ = CopyTree(other.root_, nullptr);
    size_ = other.size_;
  }

  RedBlackTree(RedBlackTree&& other) noexcept
      : root_(other.root_), size_(other.size_) {
    other.root_ = nullptr;
    other.size_ = 0;
  }

  ~RedBlackTree() {
    CleanRecursively(root_);
    size_ = 0;
    root_ = nullptr;
  }

  // ASSIGNEMENT OPERATORS
  RedBlackTree& operator=(const RedBlackTree& other) {
    if (this != &other) {
      clear();
      root_ = CopyTree(other.root_, nullptr);
      size_ = other.size_;
    }
    return *this;
  }

  RedBlackTree& operator=(RedBlackTree&& other) noexcept {
    if (this != &other) {
      clear();

      root_ = other.root_;
      size_ = other.size_;

      other.root_ = nullptr;
      other.size_ = 0;
    }
    return *this;
  }

  // CAPACITY
  bool empty() const noexcept { return size_ ? 0 : 1; }
  size_type size() const noexcept { return size_; }
  size_type max_size() {
    return std::numeric_limits<size_type>::max() /
           sizeof(RedBlackTree<key_type, mapped_type>::TreeNode) / 2;
  }

  // MODIFIERS
  void clear() {
    CleanRecursively(root_);
    size_ = 0;
    root_ = nullptr;
  }

  std::pair<iterator, bool> insert(const key_type& value) {
    bool success = false;
    node_ptr new_node = new TreeNode(value);
    success = SimpleInsert(new_node);
    std::pair<iterator, bool> res = std::make_pair(iterator(nullptr), success);
    if (success) {
      res.first = iterator(new_node);
    }
    return res;
  }

  std::pair<iterator, bool> insert(const value_type& value) {
    bool success = false;
    node_ptr new_node = new TreeNode(value.first, value.second);
    success = SimpleInsert(new_node);
    std::pair<iterator, bool> res = std::make_pair(iterator(nullptr), success);
    if (success) {
      res.first = iterator(new_node);
    }
    return res;
  }

  size_type erase(const key_type& key) {
    size_type res = 0;
    node_ptr node = Search(key);
    if (node) {
      RemoveNode(node);
      res = 1;
    }
    return res;
  }

  void erase(iterator pos) {
    if (pos != end()) {
      RemoveNode(pos.node());
    }
  }

  void swap(RedBlackTree& other) noexcept {
    std::swap(root_, other.root_);
    std::swap(size_, other.size_);
  }

  void merge(RedBlackTree& other) {
    if (this->empty()) {
      *this = std::move(other);
    } else if (!other.empty()) {
      node_ptr node = other.root_;
      if (node) {
        MergeRecursively(node);
        other.root_ = nullptr;
        other.size_ = 0;
      }
    }
  }

  // LOOKUP
  iterator find(const key_type& key) { return iterator(Search(key)); }

  bool contains(const key_type& key) { return Search(key); }

  // ITERATORS
  iterator begin() { return iterator(FindLeftmost()); }
  const_iterator cbegin() const { return FindLeftmost(); }

  iterator end() noexcept { return iterator(nullptr); }
  const_iterator cend() const noexcept { return const_iterator(nullptr); }

  iterator root() { return iterator(root_); }
  iterator max() { return iterator(FindRightmost(root_)); }

  // EXTRA METHODS
  void PrettyPrint() {
    if (root_) {
      std::cout << "tree size: " << size_ << "\n";
      PrintHelper(root_, "", true);
    } else {
      std::cout << "tree is empty\n";
    }
  }

  // CLASSES AND STRUCTURES
  struct TreeNode {
    key_type key_;
    mapped_type value_;
    TreeNode* parent_ = nullptr;
    TreeNode* left_ = nullptr;   // left child
    TreeNode* right_ = nullptr;  // right child
    Colour colour_ = Colour::RED;

    TreeNode(key_type key, mapped_type value = mapped_type(),
             Colour colour = Colour::RED)
        : key_(key),
          value_(value),
          parent_(nullptr),
          left_(nullptr),
          right_(nullptr),
          colour_(colour) {}

    node_ptr StepForward(node_ptr node) {
      node_ptr res = nullptr;
      if (node->right_) {
        res = node->right_;
        while (res->left_) {
          res = res->left_;
        }
      } else if (node->parent_) {
        res = node->parent_;
        while (res && node == res->right_) {
          node = res;
          res = res->parent_;
        }
      }
      return res;
    }

    node_ptr StepBackward(node_ptr node) {
      node_ptr res = nullptr;
      if (node->left_) {
        res = node->left_;
        while (res->right_) {
          res = res->right_;
        }
      } else if (node->parent_) {
        res = node->parent_;
        while (res && node == res->left_) {
          node = res;
          res = res->parent_;
        }
      }
      return res;
    }
  };

  class TreeIterator {
   public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = mapped_type;
    using difference_type = std::ptrdiff_t;
    using pointer = mapped_type*;
    using reference = mapped_type&;

    TreeIterator() : curr_(nullptr){};
    explicit TreeIterator(node_ptr node) : curr_(node){};

    key_type& operator*() { return curr_->key_; }
    TreeIterator& operator++() {
      curr_ = curr_->StepForward(curr_);
      return *this;
    }

    TreeIterator& operator--() {
      if (curr_) {
        curr_ = curr_->StepBackward(curr_);
      }
      return *this;
    }

    bool operator==(const TreeIterator& other) const {
      return curr_ == other.curr_;
    }

    bool operator!=(const TreeIterator& other) const {
      return curr_ != other.curr_;
    }

    key_type key() const { return curr_->key_; }
    node_ptr node() { return curr_; }

   private:
    node_ptr curr_;
  };

  class ConstTreeIterator {
   public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = mapped_type;
    using difference_type = std::ptrdiff_t;
    using pointer = const mapped_type*;
    using reference = const mapped_type&;

    ConstTreeIterator() : curr_(nullptr){};
    explicit ConstTreeIterator(node_ptr node) : curr_(node){};
    const key_type& operator*() const { return curr_->key_; }

    ConstTreeIterator& operator++() {
      curr_ = curr_->StepForward(curr_);
      return *this;
    }

    ConstTreeIterator& operator--() {
      curr_ = curr_->StepBackward(curr_);
      return *this;
    }

    bool operator==(const ConstTreeIterator& other) const {
      return curr_ == other.curr_;
    }

    bool operator!=(const ConstTreeIterator& other) const {
      return curr_ != other.curr_;
    }

    const key_type key() const { return curr_->key_; }
    node_ptr node() const { return curr_; }

   private:
    node_ptr curr_;
  };

 private:
  void PrintHelper(node_ptr node, std::string indent, bool last) {
    if (node) {
      std::cout << indent;
      if (last) {
        std::cout << "R----";
        indent += "     ";
      } else {
        std::cout << "L----";
        indent += "|    ";
      }

      if (node->colour_ == Colour::RED) {
        std::cout << "\033[31m";
      }
      if (node->value_) {
        std::cout << "{" << node->key_ << ", " << node->value_ << "}";
      } else {
        std::cout << node->key_;
      }
      if (node->colour_ == Colour::RED) {
        std::cout << " (red)\033[0m\n";
      } else {
        std::cout << " (black)\n";
      }
      PrintHelper(node->left_, indent, false);
      PrintHelper(node->right_, indent, true);
    }
  }

  void CleanRecursively(node_ptr node) {
    if (node) {
      CleanRecursively(node->left_);
      CleanRecursively(node->right_);
      delete node;
    }
  }

  bool SimpleInsert(node_ptr node) {
    node_ptr curr = root_;
    node_ptr prev = nullptr;
    bool bigger = 0;
    bool success = 1;
    while (curr != nullptr && success) {
      prev = curr;
      if (node->key_ > curr->key_) {
        curr = curr->right_;
        bigger = 1;
      } else if (node->key_ < curr->key_) {
        curr = curr->left_;
        bigger = 0;
      } else if (node->key_ == curr->key_) {
        delete node;
        success = 0;
      }
    }

    if (success) {
      node->parent_ = prev;
      if (!prev)
        root_ = node;
      else if (bigger)
        prev->right_ = node;
      else
        prev->left_ = node;
      ++size_;
      FixInsert(node);
    }

    return success;
  }

  void FixInsert(node_ptr node) {
    node_ptr uncle = nullptr;
    while (node->parent_ && node->parent_->colour_ == Colour::RED) {
      if (IsLeftChild(node->parent_)) {
        uncle = node->parent_->parent_->right_;
        node = FixLeftChild(node, uncle);
      } else {
        uncle = node->parent_->parent_->left_;
        node = FixRightChild(node, uncle);
      }
    }
    root_->colour_ = Colour::BLACK;
  }

  node_ptr FixRedUncle(node_ptr node, node_ptr uncle) {
    uncle->colour_ = Colour::BLACK;
    node->parent_->colour_ = Colour::BLACK;
    node->parent_->parent_->colour_ = Colour::RED;
    return node->parent_->parent_;
  }

  node_ptr FixRightChild(node_ptr node, node_ptr uncle) {
    if (uncle && uncle->colour_ == Colour::RED) {
      node = FixRedUncle(node, uncle);
    } else {
      if (IsLeftChild(node)) {
        node = node->parent_;
        RotateRight(node);
      }
      if (node->parent_) {
        node->parent_->colour_ = Colour::BLACK;
        if (node->parent_->parent_) {
          node->parent_->parent_->colour_ = Colour::RED;
          RotateLeft(node->parent_->parent_);
        }
      }
    }
    return node;
  }

  node_ptr FixLeftChild(node_ptr node, node_ptr uncle) {
    if (uncle && uncle->colour_ == Colour::RED) {
      node = FixRedUncle(node, uncle);
    } else {
      if (!IsLeftChild(node)) {
        node = node->parent_;
        RotateLeft(node);
      }
      if (node->parent_) {
        node->parent_->colour_ = Colour::BLACK;
        if (node->parent_->parent_) {
          node->parent_->parent_->colour_ = Colour::RED;
          RotateRight(node->parent_->parent_);
        }
      }
    }
    return node;
  }

  void RotateLeft(node_ptr x) {
    node_ptr y = x->right_;
    x->right_ = y->left_;
    if (y->left_ != nullptr) {
      y->left_->parent_ = x;
    }
    RotationFixup(x, y);
    y->left_ = x;
    x->parent_ = y;
  }

  void RotateRight(node_ptr x) {
    node_ptr y = x->left_;
    x->left_ = y->right_;
    if (y->right_ != nullptr) {
      y->right_->parent_ = x;
    }
    RotationFixup(x, y);
    y->right_ = x;
    x->parent_ = y;
  }

  void RotationFixup(node_ptr x, node_ptr y) {
    y->parent_ = x->parent_;
    if (x->parent_ == nullptr) {
      root_ = y;
    } else if (IsLeftChild(x)) {
      x->parent_->left_ = y;
    } else {
      x->parent_->right_ = y;
    }
  }

  node_ptr FindLeftmost() {
    node_ptr res = root_;
    while (res->left_) {
      res = res->left_;
    }
    return res;
  }

  const_iterator FindLeftmost() const {
    node_ptr res = root_;
    while (res->left_) {
      res = res->left_;
    }
    return const_iterator(res);
  }

  node_ptr FindRightmost(node_ptr node) {
    while (node->right_) {
      node = node->right_;
    }
    return node;
  }

  node_ptr CopyTree(const node_ptr other, node_ptr parent) {
    node_ptr res = nullptr;
    if (other) {
      node_ptr new_node =
          new TreeNode(other->key_, other->value_, other->colour_);
      new_node->parent_ = parent;
      new_node->left_ = CopyTree(other->left_, new_node);
      new_node->right_ = CopyTree(other->right_, new_node);
      res = new_node;
    }
    return res;
  }

  node_ptr Search(const key_type& key) {
    node_ptr res = root_;
    char flag = 0;
    while (res && !flag) {
      if (key < res->key_) {
        res = res->left_;
      } else if (key > res->key_) {
        res = res->right_;
      } else {
        flag = 1;
      }
    }
    return res;
  }

  bool HasRedKids(const node_ptr node) {
    bool res = 0;
    if (node->right_) {
      if (node->right_->colour_ == Colour::RED) {
        res = 1;
      }
    } else if (node->left_) {
      if (node->left_->colour_ == Colour::RED) {
        res = 1;
      }
    }
    return res;
  }

  bool IsLeftChild(const node_ptr node) {
    bool res = false;
    if (node->parent_) {
      if (node == node->parent_->left_) res = true;
    }
    return res;
  }

  void RemoveNode(node_ptr node) {
    node_ptr replacement =
        (!node->left_ || !node->right_) ? node : node->StepForward(node);

    node_ptr child =
        replacement->left_ ? replacement->left_ : replacement->right_;

    if (child) {
      child->parent_ = replacement->parent_;
    }

    if (!replacement->parent_) {
      root_ = child;
    } else {
      if (IsLeftChild(replacement)) {
        replacement->parent_->left_ = child;
      } else {
        replacement->parent_->right_ = child;
      }
    }

    if (replacement != node) {
      node->key_ = std::move(replacement->key_);
      node->value_ = std::move(replacement->value_);
    }

    if (replacement->colour_ == Colour::BLACK) {
      FixDoubleBlack(child, replacement->parent_);
    }

    delete replacement;
    --size_;
  }

  void FixDoubleBlack(node_ptr child, node_ptr parent) {
    while ((!child || child->colour_ == Colour::BLACK) && child != root_) {
      if (child == parent->left_) {
        child = HandleLeftKid(child, parent);
      } else {
        child = HandleRightKid(child, parent);
      }
    }

    if (child) {
      child->colour_ = Colour::BLACK;
    }
  }

  node_ptr HandleLeftKid(node_ptr child, node_ptr parent) {
    node_ptr bro = parent->right_;
    if (bro->colour_ == Colour::RED) {
      bro->colour_ = Colour::BLACK;
      parent->colour_ = Colour::RED;
      RotateLeft(parent);
      bro = parent->right_;
    }
    if (HasRedKids(bro)) {
      if (!bro->right_ || bro->right_->colour_ == Colour::BLACK) {
        if (bro->left_) bro->left_->colour_ = Colour::BLACK;
        bro->colour_ = Colour::RED;
        RotateRight(bro);
        bro = parent->right_;
      }
      bro->colour_ = parent->colour_;
      parent->colour_ = Colour::BLACK;
      if (bro->right_) bro->right_->colour_ = Colour::BLACK;
      RotateLeft(parent);
      child = root_;
    } else {
      bro->colour_ = Colour::RED;
      child = parent;
      parent = child->parent_;
    }
    return child;
  }

  node_ptr HandleRightKid(node_ptr child, node_ptr parent) {
    node_ptr bro = parent->left_;
    if (bro->colour_ == Colour::RED) {
      bro->colour_ = Colour::BLACK;
      parent->colour_ = Colour::RED;
      RotateRight(parent);
      bro = parent->left_;
    }

    if (HasRedKids(bro)) {
      if (!bro->left_ || bro->left_->colour_ == Colour::BLACK) {
        bro->right_->colour_ = Colour::BLACK;
        bro->colour_ = Colour::RED;
        RotateLeft(bro);
        bro = parent->left_;
      }

      bro->colour_ = parent->colour_;
      parent->colour_ = Colour::BLACK;
      bro->left_->colour_ = Colour::BLACK;
      RotateRight(parent);
      child = root_;
    } else {
      bro->colour_ = Colour::RED;
      child = parent;
      parent = child->parent_;
    }

    return child;
  }

  void MergeRecursively(node_ptr node) {
    if (node) {
      node_ptr left = node->left_;
      node_ptr right = node->right_;

      if (node->parent_) {
        if (IsLeftChild(node)) {
          node->parent_->left_ = nullptr;
        } else {
          node->parent_->right_ = nullptr;
        }
        node->parent_ = nullptr;
      }
      if (node->left_) {
        node->left_->parent_ = nullptr;
        node->left_ = nullptr;
      } else if (node->right_) {
        node->right_->parent_ = nullptr;
        node->right_ = nullptr;
      }
      node->colour_ = Colour::RED;
      SimpleInsert(node);
      MergeRecursively(left);
      MergeRecursively(right);
    }
  }

  node_ptr root_;
  size_type size_ = 0;
};

}  // namespace s21
#endif  // S21_RB_TREE_H