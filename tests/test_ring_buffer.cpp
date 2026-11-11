#include <string>

#include "test_framework.hpp"
#include "tinykit/ring_buffer.hpp"

using namespace tinykit;

TEST(ring_buffer, starts_empty) {
    RingBuffer<int> rb(3);
    CHECK(rb.empty());
    CHECK(!rb.full());
    CHECK_EQ(rb.size(), std::size_t{0});
    CHECK_EQ(rb.capacity(), std::size_t{3});
    CHECK(!rb.pop().has_value());
}

TEST(ring_buffer, zero_capacity_throws) { CHECK_THROWS(RingBuffer<int>(0)); }

TEST(ring_buffer, fifo_order) {
    RingBuffer<int> rb(3);
    rb.push(1);
    rb.push(2);
    CHECK_EQ(rb.front(), 1);
    CHECK_EQ(rb.back(), 2);
    CHECK_EQ(*rb.pop(), 1);
    CHECK_EQ(*rb.pop(), 2);
    CHECK(rb.empty());
}

TEST(ring_buffer, overwrites_oldest_when_full) {
    RingBuffer<int> rb(3);
    for (int i = 1; i <= 5; ++i) rb.push(i);
    CHECK(rb.full());
    CHECK_EQ(rb.size(), std::size_t{3});
    CHECK_EQ(rb.at(0), 3);
    CHECK_EQ(rb.at(1), 4);
    CHECK_EQ(rb.at(2), 5);
}

TEST(ring_buffer, wraps_around_after_pops) {
    RingBuffer<std::string> rb(2);
    rb.push("a");
    rb.push("b");
    CHECK_EQ(*rb.pop(), std::string("a"));
    rb.push("c");
    CHECK_EQ(rb.front(), std::string("b"));
    CHECK_EQ(rb.back(), std::string("c"));
}

TEST(ring_buffer, bounds_checked_access) {
    RingBuffer<int> rb(2);
    CHECK_THROWS(rb.front());
    CHECK_THROWS(rb.back());
    rb.push(1);
    CHECK_THROWS(rb.at(1));
}

TEST(ring_buffer, clear_resets) {
    RingBuffer<int> rb(2);
    rb.push(1);
    rb.push(2);
    rb.clear();
    CHECK(rb.empty());
    rb.push(9);
    CHECK_EQ(rb.front(), 9);
}
