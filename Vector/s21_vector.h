#ifndef S21_VECTOR_H
#define S21_VECTOR_H

#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <memory>
#include <stdexcept>

namespace s21 {
template <typename T>
class Vector {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;
  using iterator = T *;
  using const_iterator = const T *;
  using Allocator = std::allocator<T>;

  // CONSTRUCTORS
  Vector() noexcept : alloc_(), size_(0), capacity_(0), data_(nullptr) {}

  explicit Vector(size_type n, const_reference value = value_type())
      : alloc_(), size_(n), capacity_(n), data_(alloc_.allocate(n)) {
    Fill(data_, n, value);
  }

  Vector(const std::initializer_list<value_type> &list)
      : alloc_(),
        size_(list.size()),
        capacity_(list.size()),
        data_(alloc_.allocate(list.size())) {
    iterator it = begin();

    for (auto i = list.begin(); i < list.end(); ++i) {
      std::allocator_traits<Allocator>::construct(alloc_, std::addressof(*it),
                                                  *i);
      ++it;
    }
  }

  Vector(const Vector &other)
      : alloc_(),
        size_(other.size_),
        capacity_(other.capacity_),
        data_(alloc_.allocate(size_)) {
    std::uninitialized_copy_n(other.data_, size_, data_);
  }

  Vector(Vector &&other) noexcept
      : alloc_(),
        size_(other.size_),
        capacity_(other.capacity_),
        data_(other.data_) {
    // std::cout << "move constr called\n";
    other.size_ = 0;
    other.capacity_ = 0;
    other.data_ = nullptr;
  }

  ~Vector() {  // destructor
    Uncreate();
    data_ = nullptr;
    capacity_ = size_ = 0;
  }

  // ASSIGNEMENT OPERATORS
  Vector &operator=(const Vector &other) {
    // std::cout << "copy ass operator called\n";
    if (&other != this) {
      if (other.size_ > capacity_) {
        Uncreate();
        size_ = capacity_ = other.size_;
        data_ = alloc_.allocate(size_);
        std::uninitialized_copy_n(other.data_, size_, data_);
      } else {
        std::copy_n(other.cbegin(), other.size(), data_);
        size_ = other.size_;
      }
    }
    return *this;
  }

  Vector &operator=(Vector &&other) noexcept {
    // std::cout << "move ass operator called\n";
    if (&other != this) {
      Uncreate();
      size_ = other.size_;
      capacity_ = other.capacity_;
      data_ = other.data_;
      other.size_ = 0;
      other.capacity_ = 0;
      other.data_ = nullptr;
    }
    return *this;
  }

  // Replaces the contents with count copies of value
  void assign(size_type count, const_reference value) {
    if (count > capacity_) {
      Uncreate();
      data_ = alloc_.allocate(count);
      capacity_ = count;
    } else {
      Destroy();
    }
    Fill(data_, count, value);
    size_ = count;
  }

  value_type *data() noexcept { return data_; }
  const value_type *data() const { return data_; }

  reference operator[](size_type i) {
    if (!size_ || i > size_ - 1)
      throw std::out_of_range("Position out of range");
    else
      return data_[i];
  }

  const_reference operator[](size_type i) const {
    if (i > size_ - 1)
      throw std::out_of_range("Position out of range");
    else
      return data_[i];
  }

  reference at(size_type pos) {
    if (pos >= size_) {
      throw std::out_of_range("Position out of range");
    } else {
      return data_[pos];
    }
  }

  const_reference at(size_type pos) const {
    if (pos >= size_) {
      throw std::out_of_range("Position out of range");
    } else {
      return data_[pos];
    }
  }

  reference front() { return *data_; }
  reference back() { return *(data_ + size_ - 1); }
  const_reference front() const { return *data_; }
  const_reference back() const { return *(data_ + size_ - 1); }

  // CAPACITY
  bool empty() const noexcept { return size_ ? false : true; }
  size_type size() const { return size_; }
  size_type max_size() const noexcept {
    return std::allocator_traits<Allocator>::max_size(alloc_);
  }
  void reserve(size_type new_cap) {
    if (new_cap > capacity_) {
      MoveData(new_cap);
    }
  }

  size_type capacity() { return capacity_; }

  void shrink_to_fit() {
    if (size_ != capacity_) {
      MoveData(size_);
    }
  }

  // MODIFIERS
  void clear() noexcept {
    Destroy();
    size_ = 0;
  }

  iterator insert(iterator pos, const T &value) {
    if (pos > end() || pos < begin())
      throw std::out_of_range("Position out of range");
    else {
      if (size_ == capacity_) {
        size_type ind = pos - data_;
        MoveData(size_ * 2);
        pos = data_ + ind;
      }
      if (pos != end()) {
        iterator iter = end();
        std::uninitialized_move_n(iter - 1, 1, iter);
        --iter;
        while (iter > pos) {
          *iter = std::move(*(iter - 1));
          --iter;
        }
      }
      ++size_;
      std::allocator_traits<Allocator>::construct(alloc_, pos, value);
      return pos;
    }
  }

  iterator erase(const_iterator pos) {
    if (pos >= end() || pos < begin())
      throw std::out_of_range("Position out of range");
    else {
      std::allocator_traits<Allocator>::destroy(alloc_, pos);
      iterator dest = iterator(const_cast<T *>(pos));
      iterator from = dest + 1;
      while (from != end()) {
        *dest++ = std::move(*from++);
      }
      --size_;
      return iterator(const_cast<T *>(pos));
    }
  }

  void push_back(const_reference value) {
    if (!capacity_) {
      ++capacity_;
      data_ = std::allocator_traits<Allocator>::allocate(alloc_, capacity_);
    } else if (size_ == capacity_) {
      MoveData(capacity_ * 2);
    }
    std::allocator_traits<Allocator>::construct(alloc_, end(), value);
    ++size_;
  }

  void pop_back() {
    if (data_) {
      std::allocator_traits<Allocator>::destroy(alloc_, end() - 1);
      --size_;
    }
  }

  void resize(size_type count, const_reference value = value_type()) {
    if (count < size_) {
      iterator it = data_ + count;
      while (it != end()) {
        std::allocator_traits<Allocator>::destroy(alloc_, it++);
      }
      size_ = count;
    } else if (count > size_) {
      size_type new_cap = count > capacity_ * 2 ? count : capacity_ * 2;
      MoveData(new_cap);
      Fill(end(), count - size_, value);
      capacity_ = size_ = new_cap;
    }
  }

  void swap(Vector &other) noexcept {
    std::swap(alloc_, other.alloc_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
    std::swap(data_, other.data_);
  }

  // ITERATORS
  iterator begin() noexcept { return data_; }
  iterator end() noexcept { return data_ + size_; }
  const_iterator cbegin() const noexcept { return data_; }
  const_iterator cend() const noexcept { return data_ + size_; }

  void PrintVector() {
    std::cout << "size: " << size_ << std::endl;
    std::cout << "capacity: " << capacity_ << std::endl;
    iterator it = data_;
    while (it != end()) {
      // if (!*it)
      //   std::cout << "[null] ";
      // else
      printf("%p ", static_cast<void *>(it));
      std::cout << *it << '\n';
      ++it;
    }
    std::cout << "\n\n";
  }

 private:
  std::allocator<value_type> alloc_;
  size_type size_;
  size_type capacity_;
  value_type *data_;

  void Uncreate() {
    if (data_) {
      Destroy();
      // std::allocator_traits<Allocator>::deallocate(alloc_, data_, capacity_);
      alloc_.deallocate(data_, capacity_);
    }
  }

  void Destroy() {
    value_type *it = data_ + size_;
    while (it != data_) {
      alloc_.destroy(--it);
    }
  }

  void Fill(iterator start, size_type count, const_reference value) {
    try {
      std::uninitialized_fill_n(start, count, value);
    } catch (...) {
      std::allocator_traits<Allocator>::deallocate(alloc_, data_, count);
      throw;
    }
  }

  void MoveData(size_type new_cap) {
    // allocate memory
    value_type *new_data = alloc_.allocate(new_cap);

    try {
      // copy old values into the new location
      std::uninitialized_copy_n(begin(), size_, new_data);
    } catch (...) {
      alloc_.deallocate(new_data, new_cap);
      throw;
    }

    Uncreate();
    data_ = new_data;
    capacity_ = new_cap;
  }
};
}  // namespace s21

// #include "vector.tpp"
#endif  // S21_VECTOR_H
