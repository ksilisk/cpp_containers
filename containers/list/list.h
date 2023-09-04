#ifndef SRC_LIST_LIST_H_
#define SRC_LIST_LIST_H_

#include "../utils/defines.h"

namespace s21 {

template <typename T>
class ListNode {
public:
    using value_type = T;
    using const_refernce = const T&;

public:
    value_type data_;
    ListNode* prev_ = nullptr;
    ListNode* next_ = nullptr;

public:
    ListNode(){};
    ListNode(const_refernce value) : data_(value), prev_(nullptr), next_(nullptr) {}
    ListNode(const ListNode& src) : data_(src.data_), prev_(src.prev_), next_(src.next_) {}
    ~ListNode(){};

    bool operator==(const ListNode& other) { return data_ == other.data_; }
    bool operator!=(const ListNode& other) { return !(*this == other); }

    ListNode& operator=(const ListNode& src) noexcept {
        data_ = src.data_;
        prev_ = src.prev_;
        next_ = src.next_;

        return *this;
    }
};

template <typename T>
class ListIterator {
public:
    using value_type = T;
    using const_reference = const ListIterator&;

public:
    ListIterator() {}
    ListIterator(ListNode<value_type>* src) : node_(src) {}
    ListIterator(const_reference src) : node_(src.node_) {}
    ~ListIterator() {}

public:
    bool operator==(const ListIterator& other) { return node_ == other.node_; }
    bool operator!=(const ListIterator& other) { return !(node_ == other.node_); }
    T& operator*() const { return node_->data_; }
    T* operator->() const { return &node_->data_; }

    ListIterator& operator++() {
        node_ = node_->next_;
        return *this;
    }
    ListIterator operator++(int) {
        ListIterator res(*this);
        ++(*this);
        return res;
    }
    ListIterator& operator--() {
        node_ = node_->prev_;
        return *this;
    }
    ListIterator operator--(int) {
        ListIterator res(*this);
        --(*this);
        return res;
    }

private:
    ListNode<value_type>* node_;
};

template <typename T>
class List {
public:
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using size_type = size_t;
    using iterator = ListIterator<T>;

public:
    List() { init_dummy(); }
    List(const size_type n);
    List(const std::initializer_list<T>& src);
    List(const List<T>& src);
    List(List<T>&& src) {
        init_dummy();
        std::move(src);
    }
    ~List() { clear(); }

    iterator begin() const { return iterator(dummy_->next_); }
    iterator end() const { return iterator(dummy_); }

    ListNode<value_type>* get_head(void) const { return dummy_->next_; }

    List<value_type>& operator=(const List<value_type>& src);
    List<value_type>& operator=(List<value_type>&& src) {
        std::swap(size_, src.size_);
        std::swap(dummy_, src.dummy_);

        return *this;
    }

public:
    void push_back(const_reference data) {
        ListNode<value_type>* new_node = new ListNode(data);

        if (this->begin() != this->end()) {
            dummy_->prev_->next_ = new_node;
            new_node->prev_ = dummy_->prev_;
            dummy_->prev_ = new_node;
        } else
            dummy_->next_ = dummy_->prev_ = new_node;

        dummy_->prev_->next_ = dummy_;
        dummy_->next_->prev_ = dummy_;
    }

    const_reference front() const {
        if (!dummy_->next_) {
            throw std::runtime_error("list empty.\n");
        }

        return dummy_->next_->data_;
    }

    reference front() {
        if (!dummy_->next_) {
            throw std::runtime_error("list empty.\n");
        }

        return dummy_->next_->data_;
    }

    bool empty() const noexcept { return (size_ == 0); }
    size_type size() const noexcept { return size_; }

private:
    void clear() {
        if (!dummy_) return;

        ListNode<value_type>* curr = dummy_->next_;
        while (iterator(curr) != this->end()) {
            ListNode<value_type>* next = curr->next_;
            delete curr;
            curr = next;
        }
        delete curr;
    }

    void init_dummy() {
        dummy_ = new ListNode<value_type>(0);
        dummy_->prev_ = dummy_;
        dummy_->next_ = dummy_;
    }

private:
    ListNode<value_type>* dummy_;
    size_type size_ = 0;
};

template <typename T>
List<T>& List<T>::operator=(const List<T>& src) {
    if (this == &src) return *this;

    this->clear();
    for (auto it = src.begin(); it != src.end(); ++it) push_back(*it);

    return *this;
}

template <typename T>
List<T>::List(const size_type n) {
    init_dummy();
    for (int _ = n; _ > 0; --_) push_back(0);
}

template <typename T>
List<T>::List(const std::initializer_list<T>& src) {
    init_dummy();
    for (auto it = src.begin(); it != src.end(); ++it) push_back(*it);
}

template <typename T>
List<T>::List(const List<T>& src) {
    init_dummy();
    for (auto it = src.begin(); it != src.end(); ++it) push_back(*it);
}

}  // namespace s21

#endif  // SRC_LIST_LIST_H_