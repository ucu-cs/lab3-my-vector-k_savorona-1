#ifndef MY_VECTOR_MY_VECTOR_HPP
#define MY_VECTOR_MY_VECTOR_HPP

#include <iterator>
#include <cstddef>
#include <algorithm>

template<typename T>
class my_vector {
public:
    my_vector() : size_m(0), capacity_m(0), data(nullptr) {};

    my_vector(const int &n, const T &d) : size_m(n), capacity_m(n * 2) {
        data = new T[capacity_m];
        for (size_t i = 0; i < n; ++i) {
            data[i] = d;
        }
    }

    template<typename Iter>
    my_vector(Iter start_interval, Iter end_interval) {
        size_m = end_interval - start_interval;
        capacity_m = size_m * 2;
        data = new T[capacity_m];
        T* current = data;
        while (start_interval != end_interval) {
            *current = *start_interval;
            ++start_interval;
            ++current;
        }
    }

    my_vector(const std::initializer_list<T> &arg) {
        size_m = arg.size();
        capacity_m = size_m * 2;
        data = new T[capacity_m];
        size_t i = 0;
        for (const auto &elem : arg) {
            data[i] = elem;
            ++i;
        }
    }

    // copy constructor
    my_vector(const my_vector &other) : size_m(other.size_m), capacity_m(other.capacity_m) {
        data = new T[capacity_m];
        for (size_t i = 0; i < size_m; ++i) {
            data[i] = other[i];
        }
    }

    // move constructor
    my_vector(my_vector &&other) noexcept :
            size_m(other.size_m), capacity_m(other.capacity_m), data(other.data) {
        other.data = nullptr;
        other.size = 0;
        other.capacity = 0;
    };


    // copy assignment
    my_vector& operator=(const my_vector &other) {
        if (&other != this) {
            delete[] data;
            size_m = other.size_m;
            capacity_m = other.capacity_m;
            data = new T[capacity_m];
            for (size_t i = 0; i < size_m; ++i) {
                data[i] = other[i];
            }
        }
        return *this;
    }

    // move constructor
    my_vector& operator=(my_vector &&other) noexcept {
        if (&other != this) {
            delete[] data;
            size_m = other.size_m;
            capacity_m = other.capacity_m;
            data = other.data;
            other.data = nullptr;
            other.size_m = 0;
            other.capacity_m = 0;
        }
        return *this;
    };


    ~my_vector() {
        delete[] data;
        size_m = 0;
        capacity_m = 0;
    }

    T& operator[](const size_t &value) const {
        return *(data + value);
    }

    T& at(const size_t &index) const {
        if (index < 0 || index > size_m - 1) {
            throw std::out_of_range("The index is out of range!");
        }
        return data[index];
    };

    [[nodiscard]] bool is_empty() const {
        return size_m == 0;
    }

    [[nodiscard]] size_t size() const {
        return size_m;
    }

    [[nodiscard]] size_t capacity() const {
        return capacity_m;
    }

    void reserve(size_t value) {
        if (value <= capacity_m) {
            return;
        }
        T* new_data = new T[value];
        for (size_t i = 0; i < size_m; ++i) {
            new_data[i] = data[i];
        }
        delete[] data;
        data = new_data;
        capacity_m = value;
    }

    void shrink_to_fit() {
        if (capacity_m == size_m) {
            return;
        }
        T* new_data = new T[size_m];
        for (size_t i = 0; i < size_m; ++i) {
            new_data[i] = data[i];
        }
        delete[] data;
        data = new_data;
        capacity_m = size_m;
    }

    void swap(my_vector &other) {
        std::swap(data, other.data);
        std::swap(size_m, other.size_m);
        std::swap(capacity_m, other.capacity_m);
    }

    void clear() {
        for (size_t i = 0; i < size_m; ++i) {
            data[i].~T();
        }
        size_m = 0;
    }

    void resize(size_t value, T elem=T()) {
        if (value == size_m) return;
        if (size_m > value) {
            for (size_t i = value; i < size_m; ++i) {
                data[i].~T();
            }
            size_m = value;
        } else {
            if (value > capacity_m) {
                T* new_data = new T[value * 2];
                for (size_t i = 0; i < size_m; ++i) {
                    new_data[i] = data[i];
                }
                for (size_t i = size_m; i < value; ++i) {
                    new_data[i] = elem;
                }
                size_m = value;
                capacity_m = value * 2;
                delete[] data;
                data = new_data;
            } else {
                for (size_t i = size_m; i < value; ++i) {
                    data[i] = elem;
                }
                size_m = value;
            }
        }
    }


    T* insert(T* pos, const T &value) {
        size_t index = pos - begin();

        if (size_m == capacity_m) {
            T* new_data = new T[capacity_m * 2];
            for (size_t i = 0; i < index; ++i) {
                new_data[i] = data[i];
            }
            new_data[index] = value;
            for (size_t i = index + 1; i < size_m + 1; ++i) {
                new_data[i] = data[i - 1];
            }
            delete[] data;
            data = new_data;
            capacity_m *= 2;
        } else {
            for (size_t i = size_m; i > index; --i) {
                data[i] = data[i - 1];
            }
            data[index] = value;
        }
        size_m++;
        return begin() + index;
    }


    T* insert(T* pos, T* begin_take, T* end_take) {
        size_t index = pos - begin();
        size_t size = end_take - begin_take;
        if (size_m + size >= capacity_m) {
            T* new_data = new T[capacity_m * 2];
            for (size_t i = 0; i < index; ++i) {
                new_data[i] = data[i];
            }
            for (size_t i = index; i < size_m; ++i) {
                new_data[i + size] = data[i];
            }
            size_t i = 0;
            while (begin_take != end_take) {
                new_data[i + index] = *begin_take;
                begin_take++;
                i++;
            }

            size_m += size;
            capacity_m = size_m * 2;
            delete[] data;
            data = new_data;
        } else {
            for (size_t i = size_m; i > index; --i) {
                data[i + size - 1] = data[i - 1];
            }
            size_t i = 0;
            while (begin_take != end_take) {
                data[i + index] = *begin_take;
                begin_take++;
                i++;
            }
            size_m += size;
        }
        return begin() + index;
    }

    T* erase(const size_t pos) {
        for (size_t i = pos; i < size_m - 1; ++i) {
            data[i] = data[i + 1];
        }
        data[size_m - 1].~T();
        size_m--;
        return begin() + pos;
    }

    T* erase(T* begin_, T* end) {
        size_t first_ind = begin_ - data;
        size_t size = end - begin_;
        for (size_t i = first_ind; i < size_m - size; ++i) {
            data[i] = data[i + size];
        }
        for (size_t i = size_m - size; i < size_m; ++i) {
            data[i].~T();
        }
        size_m -= size;
        return begin() + first_ind;
    }

    void pop_back() {
        data[size_m - 1].~T();
        size_m--;
    }

    void push_back(const T &value) {
        insert(end(), value);
    }

    void emplace_back(T &&value) {
        if (size_m == capacity_m) {
            size_t new_capacity = (capacity_m == 0) ? 1 : capacity_m * 2;

            T* new_data = new T[new_capacity];
            for (size_t i = 0; i < size_m; ++i) {
                new_data[i] = std::move(data[i]);
            }

            delete[] data;
            data = new_data;
            capacity_m = new_capacity;
        }

        new (&data[size_m]) T(std::move(value));
        ++size_m;
    }

    friend bool operator==(const my_vector<T>& lhs, const my_vector<T>& rhs) {
        if (lhs.size_m != rhs.size_m) return false;
        for (size_t i = 0; i < lhs.size_m; ++i) {
            if (lhs[i] != rhs[i]) return false;
        }
        return true;
    }

    friend bool operator!=(const my_vector<T>& lhs, const my_vector<T>& rhs) {
        return !(lhs == rhs);
    }

    friend bool operator<(const my_vector<T>& lhs, const my_vector<T>& rhs) {
        return std::lexicographical_compare(lhs.cbegin(), lhs.cend(),
                                            rhs.cbegin(), rhs.cend());
    }

    friend bool operator<=(const my_vector<T>& lhs, const my_vector<T>& rhs) {
        return !(rhs < lhs);
    }

    friend bool operator>(const my_vector<T>& lhs, const my_vector<T>& rhs) {
        return rhs < lhs;
    }

    friend bool operator>=(const my_vector<T>& lhs, const my_vector<T>& rhs) {
        return !(lhs < rhs);
    }

    T* begin() {
        return data;
    }

    const T* cbegin() const {
        return data;
    }

    T*end() {
        return data + size_m;
    }

    const T* cend() const {
        return data + size_m;
    }

    T front() const {
        return data[0];
    }

    T back() const {
        return data[size_m -1];
    }

    std::reverse_iterator<T*> rbegin() {
        return std::reverse_iterator<T*>(data + size_m);
    }

    std::reverse_iterator<const T*> rcbegin() const {
        return std::reverse_iterator<const T*>(data + size_m);
    }

    std::reverse_iterator<T*> rend() {
        return std::reverse_iterator<T*>(data);
    }

    std::reverse_iterator<const T*> rcend() const {
        return std::reverse_iterator<const T*>(data);
    }


private:
    T *data;
    size_t size_m;
    size_t capacity_m;
};

#endif //MY_VECTOR_MY_VECTOR_HPP
