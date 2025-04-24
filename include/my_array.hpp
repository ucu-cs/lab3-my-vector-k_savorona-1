#ifndef MY_VECTOR_MY_ARRAY_HPP
#define MY_VECTOR_MY_ARRAY_HPP

#include <cstddef>
#include <algorithm>
#include <iterator>
#include <stdexcept>


template< typename T, size_t N>
class my_array {
public:
    my_array()=default;
    my_array(const my_array &other)=default;
    my_array &operator=(const my_array &other)=default;
    my_array(my_array &&other)=default;
    my_array &operator=(my_array &&other)=default;
    ~my_array()=default;


    explicit my_array(T value) {
        for (size_t i = 0; i < N; ++i) {
            data[i] = value;
        }
    }

    my_array(const std::initializer_list<T> &list) {
        int i = 0;
        size_t list_size = list.size();
        for (const auto &value : list) {
            data[i] = value;
            i++;
        }
        for (size_t j = list_size; j < N; ++j) {
            data[j] = T();
        }
    }

    T& operator[](size_t value) noexcept {
        return data[value];
    }

    const T& operator[](size_t value) const noexcept {
        return data[value];
    }

    T& at(size_t value) {
        if (value >= N) {
            throw std::out_of_range("The index is out of range!");
        }
        return data[value];
    }

    const T& at(size_t value) const {
        if (value >= N) {
            throw std::out_of_range("The index is out of range!");
        }
        return data[value];
    }

    T& front() {
        return data[0];
    }

    const T& front() const {
        return data[0];
    }

    T& back() {
        return data[N - 1];
    }

    const T& back() const {
        return data[N - 1];
    }

    [[nodiscard]] bool is_empty() const {
        return !N;
    }

    [[nodiscard]] size_t size() const {
        return N;
    }

    T* begin() {
        return data;
    }

    const T* cbegin() const {
        return data;
    }

    T*end() {
        return data + N;
    }

    const T* cend() const {
        return data + N;
    }

    std::reverse_iterator<T*> rbegin() {
        return std::reverse_iterator<T*>(data + N);
    }

    std::reverse_iterator<const T*> rcbegin() const {
        return std::reverse_iterator<const T*>(data + N);
    }

    std::reverse_iterator<T*> rend() {
        return std::reverse_iterator<T*>(data);
    }

    std::reverse_iterator<const T*> rcend() const {
        return std::reverse_iterator<const T*>(data);
    }

    void swap(my_array &other) {
        for (size_t i = 0; i < N; ++i) {
            std::swap(data[i], other.data[i]);
        }
    }

    void fill(const T &value) {
        for (size_t i = 0; i < N; ++i) {
            data[i] = value;
        }
    }

    friend bool operator==(const my_array<T, N>& lhs, const my_array<T, N>& rhs) {
        if (lhs.size() != rhs.size()) return false;
        for (size_t i = 0; i < lhs.size(); ++i) {
            if (lhs[i] != rhs[i]) return false;
        }
        return true;
    }

    friend bool operator!=(const my_array<T, N>& lhs, const my_array<T, N>& rhs) {
        return !(lhs == rhs);
    }

    friend bool operator<(const my_array<T, N>& lhs, const my_array<T, N>& rhs) {
        return std::lexicographical_compare(lhs.cbegin(), lhs.cend(),
                                            rhs.cbegin(), rhs.cend());
    }

    friend bool operator<=(const my_array<T, N>& lhs, const my_array<T, N>& rhs) {
        return !(rhs < lhs);
    }

    friend bool operator>(const my_array<T, N>& lhs, const my_array<T, N>& rhs) {
        return rhs < lhs;
    }

    friend bool operator>=(const my_array<T, N>& lhs, const my_array<T, N>& rhs) {
        return !(lhs < rhs);
    }

private:
    T data[N];
};

#endif //MY_VECTOR_MY_ARRAY_HPP
