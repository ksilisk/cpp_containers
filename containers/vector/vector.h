#ifndef VECTOR_HPP_
#define VECTOR_HPP_

#include <limits>
#include <memory>

#include "../utils/defines.h"
#include "iterator.h"

namespace s21 {
//пока что убрал final(для тестов), потом надо будет вернуть на место
using namespace defines;
template <typename T, typename Allocator = std::allocator<T>>
class vector {
 public:
  using value_type = T;
  using allocator_type = Allocator;
  using size_type = typename Allocator::size_type;
  using difference_type = typename Allocator::difference_type;
  using reference = typename Allocator::reference;
  using const_reference = typename Allocator::const_reference;
  using pointer = typename Allocator::pointer;
  using const_pointer = typename Allocator::const_pointer;

 public:
  using iterator = iterator_wrapper<T, NON_CONST>;
  using const_iterator = iterator_wrapper<T, CONST>;
  using reverse_iterator = s21::reverse_iterator<iterator>;
  using const_reverse_iterator = s21::reverse_iterator<const_iterator>;

 private:
  pointer data_;
  std::size_t size_;
  std::size_t capacity_;
  Allocator allocator_;

 public:
  explicit constexpr vector(std::size_t t_capacity = DEFAULT_CAPACITY)
      : size_(0), capacity_(t_capacity * FACTOR) {
    data_ = allocator_.allocate(capacity_);
  }

  constexpr vector(std::size_t t_size, const_reference t_element)
      : size_(t_size), capacity_(t_size * FACTOR) {
    data_ = allocator_.allocate(capacity_);
    fill(t_element);
  }

  constexpr vector(const std::initializer_list<T>& t_list)
      : vector(std::distance(t_list.begin(), t_list.end())) {
    std::transform(
        t_list.begin(), t_list.end(), std::back_inserter(*this),
        // Если не форвардить обьект, то будет вызываться лишний консутрктор
        // копирования https://godbolt.org/z/9Kj48r5ab
        [](auto&& t_elem) { return std::forward<decltype(t_elem)>(t_elem); });
  }

  // проверяю тип на итератор при помощи неявного преобразования InputIt к
  // категории итератора.
  template <typename InputIt,
            typename = std::enable_if_t<std::is_convertible<
                typename std::iterator_traits<InputIt>::iterator_category,
                std::input_iterator_tag>::value>>
  constexpr vector(InputIt t_first, InputIt t_last)
      : vector(std::distance(t_first, t_last)) {
    std::transform(t_first, t_last, std::back_inserter(*this),
                   [](auto& t_elem) { return t_elem; });
  }

  template <typename CC, typename = std::enable_if_t<std::is_same_v<
                             vector, std::remove_reference_t<CC>>>>
  constexpr explicit vector(CC&& t_vector) {
    initialize(std::forward<CC>(t_vector));
  }

  ~vector() { allocator_.deallocate(data_, capacity_); }

 public:
  template <typename TT, typename = std::enable_if_t<std::is_same_v<
                             vector, std::remove_reference_t<TT>>>>
  constexpr vector& operator=(TT&& t_vector) {
    if (this != &t_vector) {
      allocator_.deallocate(data_, size_);
      initialize(std::forward<TT>(t_vector));
    }

    return *this;
  }

  const_reference operator[](size_type t_i) const {
    if (t_i >= size_) {
      throw std::out_of_range("index out of range.\n");
    }

    return data_[t_i];
  }

  reference operator[](size_type t_i) {
    if (t_i >= size_) {
      throw std::out_of_range("index out of range.\n");
    }

    return data_[t_i];
  }

 protected:
  template <typename Iter>
  void safe_cpy(Iter t_from, Iter t_to, std::size_t t_size) {
    if (!t_from || !t_to) {
      throw std::invalid_argument("invalid iterator provided.\n");
    }

    try {
      std::uninitialized_move(t_from, t_from + t_size, t_to);
    } catch (...) {
      // удаляю память через deallocate, который вызовет деструкторы у обьектов
      allocator_.deallocate(t_to, t_size);
      THROW_FURTHER;
    }
  }

  template <typename Y>
  constexpr void initialize(Y&& t_vector) noexcept(
      !std::is_lvalue_reference_v<Y>) {
    if constexpr (std::is_lvalue_reference_v<Y>) {
      size_ = t_vector.size_;
      capacity_ = t_vector.capacity_;
      allocator_ = t_vector.allocator_;
      data_ = allocator_.allocate(capacity_);
      safe_cpy(t_vector.data_, data_, size_);
    } else {
      size_ = std::exchange(t_vector.size_, 0);
      capacity_ = std::exchange(t_vector.capacity_, 0);
      data_ = std::exchange(t_vector.data_, nullptr);
      std::swap(allocator_, t_vector.allocator_);
    }
  }

 public:
  constexpr const_reference at(std::size_t t_i) const {
    if (t_i >= size_) {
      throw std::out_of_range("index out of range.\n");
    }

    return data_[t_i];
  }

  constexpr reference at(std::size_t t_i) {
    if (t_i >= size_) {
      throw std::out_of_range("index out of range.\n");
    }

    return data_[t_i];
  }

  constexpr void fill(const_reference t_value) {
    std::fill(begin(), end(), t_value);
  }

  constexpr pointer data() noexcept { return data_; }

  constexpr const_pointer data() const noexcept { return data_; }

  constexpr iterator begin() const noexcept { return iterator(data_); }

  constexpr iterator end() const noexcept { return iterator(data_ + size_); }

  constexpr const_iterator cbegin() const noexcept {
    return const_iterator(data_);
  }

  constexpr const_iterator cend() const noexcept {
    return const_iterator(data_ + size_);
  }

  constexpr reverse_iterator rbegin() const noexcept {
    return reverse_iterator(data_ + size_);
  }

  constexpr reverse_iterator rend() const noexcept {
    return reverse_iterator(data_);
  }

  constexpr const_reverse_iterator crbegin() const noexcept {
    return const_reverse_iterator(data_ + size_);
  }

  constexpr const_reverse_iterator crend() const noexcept {
    return const_reverse_iterator(data_);
  }

  [[nodiscard]] constexpr reference back() { return data_[size_ - 1]; }

  [[nodiscard]] constexpr reference front() { return data_[0]; }

  [[nodiscard]] constexpr const_reference back() const {
    return data_[size_ - 1];
  }

  [[nodiscard]] constexpr const_reference front() const { return data_[0]; }

  [[nodiscard]] constexpr std::size_t size() const noexcept { return size_; }

  [[nodiscard]] constexpr std::size_t capacity() const noexcept {
    return capacity_;
  }

  [[nodiscard]] constexpr bool empty() const noexcept {
    return begin() == end();
  }

  [[nodiscard]] constexpr size_t max_size() const noexcept {
    // тк аллокатор выделяет память, надо брать значения у него
    return allocator_.max_size();
    /* вычисляется по формуле: (2^SYS_BITS)/SIZE_TYPE - 1 где:
     * SYS_BITS - это битность OC
     * SIZE_TYPE - это размер типа, размером с который выделяется память
     */
  }

  template <typename... Args>
  constexpr reference emplace_back(Args&&... t_args) {
    if (capacity_ == size_) {
      reserve(size_ * FACTOR);
    }
    // не использую allocator.construct для практики с new placement
    return *new (data_ + size_++) T(std::forward<Args>(t_args)...);
  }

  template <typename PP>
  void push_back(PP&& t_elem) {
    if (capacity_ == size_) {
      reserve(size_ * FACTOR);
    }
    new (data_ + size_++) T(std::forward<PP>(t_elem));
  }

  constexpr void pop_back() {
    if (size_ == 0) {
      throw std::underflow_error("vector is empty.\n");
    }
    (data_ + --size_)->~T();
  }

  constexpr void resize(std::size_t t_size) {
    if (t_size > capacity_) {
      reserve(t_size);
    }
    size_ = t_size;
  }

  constexpr void reserve(std::size_t t_size) {
    auto new_arr = allocator_.allocate(t_size);
    safe_cpy(data_, new_arr, size_);
    allocator_.deallocate(data_, capacity_);
    data_ = std::exchange(new_arr, nullptr);
    capacity_ = t_size;
  }

  constexpr void shrink_to_fit() {
    if (size_ == 0) {
      throw std::runtime_error("size is equal to zero.\n");
    }

    reserve(size_);
  }

  template <typename II>
  iterator insert(const_iterator t_pos, II&& t_elem) {
    auto pos = std::distance(cbegin(), t_pos);
    if (pos > size_) {
      throw std::out_of_range("iterator position are out of range.\n");
    }

    const auto new_size = size_ + 1;
    if (new_size > capacity_) {
      reserve(new_size * FACTOR);
    }

    for (auto i = size_; i > pos; i--) {
      data_[i] = std::move(data_[i - 1]);
    };
    new (data_ + pos) T(std::forward<II>(t_elem));
    size_++;
    return iterator(data_ + pos);
  }

  void erase(iterator t_pos) {
    auto pos = std::distance(begin(), t_pos);
    if (pos > size_) {
      throw std::out_of_range("iterator position are out of range.\n");
    }

    for (auto i = pos; i < size_ - 1; i++) {
      data_[i] = std::move(data_[i + 1]);
    }
    size_--;
  }

  template <typename Y>
  iterator emplace(const_iterator t_pos, Y&& t_arg) {
    return insert(t_pos, std::forward<Y>(t_arg));
  }

  // на самом деле это insert, просто спецификация от школы требует такого
  // кринжа
  template <typename LL, typename... Args>
  iterator emplace(const_iterator t_pos, LL&& t_elem, Args&&... t_args) {
    insert(t_pos, std::forward<LL>(t_elem));
    emplace(t_pos, std::forward<Args>(t_args)...);
    return iterator(data_ + sizeof...(t_args));
  }

  constexpr void clear() noexcept {
    // вызывает деструкторы у всех обьектов в диапозоне
    std::destroy(begin(), end());
    size_ = 0;
  }

  void swap(vector<T>& t_other) {
    std::swap(data_, t_other.data_);
    std::swap(size_, t_other.size_);
    std::swap(capacity_, t_other.capacity_);
    std::swap(allocator_, t_other.allocator_);
  }
};

// deduction hint для того чтобы вектор вывел тип от итератора через трейты
template <typename InputIt>
vector(InputIt t_first, InputIt t_last)
    -> vector<typename std::iterator_traits<InputIt>::value_type>;

}  // namespace s21

#endif
