#ifndef S21_SET_ITERATOR_H_
#define S21_SET_ITERATOR_H_

#include <initializer_list>
#include <iostream>
// #include <set>
#include <stdexcept>

#include "tree_iterator.h"

using std::out_of_range;

namespace s21 {
template <typename Key, typename T = int>
class SetIterator : public TreeIterator<Key, T> {
 public:
  // iterator's operator
  Key& operator*() { return this->iter->values.first; }

  // iterator's constructor
  SetIterator() : TreeIterator<Key, T>() {}

  SetIterator(tree_el_<Key, T>* cur_iter) : TreeIterator<Key, T>(cur_iter) {}
};
}  // namespace s21

#endif  // S21_SET_ITERATOR_H_