#pragma once
#include <vector>
#include <cmath>
#include <cstddef>

// Simple rolling window helper that supports O(1) mean/stddev updates
class RollingWindow {
public:
    RollingWindow(size_t capacity = 0) { reserve(capacity); }
    void reserve(size_t capacity) {
        capacity_ = capacity;
        buffer_.assign(capacity_, 0.0);
        head_ = 0;
        size_ = 0;
        sum_ = 0.0;
        sumsq_ = 0.0;
    }

    void add(double x) {
        if (capacity_ == 0) return;
        if (size_ < capacity_) {
            buffer_[head_] = x;
            head_ = (head_ + 1) % capacity_;
            ++size_;
            sum_ += x;
            sumsq_ += x * x;
        } else {
            // overwrite oldest
            double outgoing = buffer_[head_];
            buffer_[head_] = x;
            head_ = (head_ + 1) % capacity_;
            sum_ += x - outgoing;
            sumsq_ += x * x - outgoing * outgoing;
        }
    }

    size_t size() const { return size_; }
    size_t capacity() const { return capacity_; }

    double mean() const {
        if (size_ == 0) return 0.0;
        return sum_ / static_cast<double>(size_);
    }

    double stddev() const {
        if (size_ == 0) return 0.0;
        double m = mean();
        double var = sumsq_ / static_cast<double>(size_) - m * m;
        if (var <= 0.0) return 0.0;
        return std::sqrt(var);
    }

private:
    std::vector<double> buffer_;
    size_t capacity_ = 0;
    size_t head_ = 0;
    size_t size_ = 0;
    double sum_ = 0.0;
    double sumsq_ = 0.0;
};
