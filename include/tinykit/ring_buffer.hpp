#pragma once

#include <cstddef>
#include <optional>
#include <stdexcept>
#include <vector>

namespace tinykit {

// Fixed-capacity FIFO. When full, push() overwrites the oldest element.
template <typename T>
class RingBuffer {
public:
    explicit RingBuffer(std::size_t capacity) : data_(capacity) {
        if (capacity == 0) throw std::invalid_argument("RingBuffer capacity must be > 0");
    }

    std::size_t capacity() const { return data_.size(); }
    std::size_t size() const { return size_; }
    bool empty() const { return size_ == 0; }
    bool full() const { return size_ == data_.size(); }

    // Append a value; evicts the oldest element if the buffer is full.
    void push(T value) {
        data_[(head_ + size_) % data_.size()] = std::move(value);
        if (full()) {
            head_ = (head_ + 1) % data_.size();
        } else {
            ++size_;
        }
    }

    // Remove and return the oldest element, or nullopt if empty.
    std::optional<T> pop() {
        if (empty()) return std::nullopt;
        T value = std::move(data_[head_]);
        head_ = (head_ + 1) % data_.size();
        --size_;
        return value;
    }

    // Oldest element. Throws std::out_of_range if empty.
    const T& front() const { return at(0); }
    // Newest element. Throws std::out_of_range if empty.
    const T& back() const { return at(size_ - 1); }

    // Index 0 is the oldest element. Throws std::out_of_range if idx >= size().
    const T& at(std::size_t idx) const {
        if (idx >= size_) throw std::out_of_range("RingBuffer index out of range");
        return data_[(head_ + idx) % data_.size()];
    }

    void clear() {
        head_ = 0;
        size_ = 0;
    }

private:
    std::vector<T> data_;
    std::size_t head_ = 0;
    std::size_t size_ = 0;
};

}  // namespace tinykit
