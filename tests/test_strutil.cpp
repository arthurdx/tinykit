#include "test_framework.hpp"
#include "tinykit/strutil.hpp"

using namespace tinykit;

TEST(strutil, trim) {
    CHECK_EQ(trim("  hi \t\n"), std::string("hi"));
    CHECK_EQ(trim(""), std::string(""));
    CHECK_EQ(trim("   "), std::string(""));
    CHECK_EQ(trim("a b"), std::string("a b"));
}

TEST(strutil, split) {
    CHECK_EQ(split("a,b,c", ','), (std::vector<std::string>{"a", "b", "c"}));
    CHECK_EQ(split("a,,b", ','), (std::vector<std::string>{"a", "", "b"}));
    CHECK_EQ(split("", ','), (std::vector<std::string>{""}));
    CHECK_EQ(split(",", ','), (std::vector<std::string>{"", ""}));
}

TEST(strutil, join) {
    CHECK_EQ(join({"a", "b", "c"}, ", "), std::string("a, b, c"));
    CHECK_EQ(join({}, ","), std::string(""));
    CHECK_EQ(join({"solo"}, ","), std::string("solo"));
}

TEST(strutil, case_conversion) {
    CHECK_EQ(to_lower("HeLLo 123"), std::string("hello 123"));
    CHECK_EQ(to_upper("HeLLo 123"), std::string("HELLO 123"));
}

TEST(strutil, prefix_suffix) {
    CHECK(starts_with("foobar", "foo"));
    CHECK(!starts_with("foobar", "bar"));
    CHECK(starts_with("foo", ""));
    CHECK(!starts_with("fo", "foo"));
    CHECK(ends_with("foobar", "bar"));
    CHECK(!ends_with("foobar", "foo"));
    CHECK(ends_with("foo", ""));
    CHECK(!ends_with("ar", "bar"));
}
