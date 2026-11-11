#include "test_framework.hpp"
#include "tinykit/arg_parser.hpp"
#include "tinykit/strutil.hpp"

using namespace tinykit;

namespace {
ArgParser make() {
    ArgParser p;
    p.add_flag("verbose", "chatty output");
    p.add_option("name", "who to greet", "world");
    return p;
}
}  // namespace

TEST(arg_parser, defaults_when_absent) {
    auto p = make();
    CHECK(p.parse(std::vector<std::string>{}));
    CHECK(!p.has_flag("verbose"));
    CHECK_EQ(p.get("name"), std::string("world"));
}

TEST(arg_parser, flag_and_inline_value) {
    auto p = make();
    CHECK(p.parse(std::vector<std::string>{"--verbose", "--name=bob"}));
    CHECK(p.has_flag("verbose"));
    CHECK_EQ(p.get("name"), std::string("bob"));
}

TEST(arg_parser, separate_value) {
    auto p = make();
    CHECK(p.parse(std::vector<std::string>{"--name", "alice"}));
    CHECK_EQ(p.get("name"), std::string("alice"));
}

TEST(arg_parser, positionals_and_double_dash) {
    auto p = make();
    CHECK(p.parse(std::vector<std::string>{"a", "--verbose", "--", "--name", "b"}));
    CHECK_EQ(p.positional(), (std::vector<std::string>{"a", "--name", "b"}));
    CHECK_EQ(p.get("name"), std::string("world"));
}

TEST(arg_parser, errors) {
    auto p = make();
    CHECK(!p.parse(std::vector<std::string>{"--nope"}));
    CHECK(starts_with(p.error(), "unknown option"));
    CHECK(!p.parse(std::vector<std::string>{"--name"}));
    CHECK(starts_with(p.error(), "missing value"));
    CHECK(!p.parse(std::vector<std::string>{"--verbose=1"}));
    CHECK(starts_with(p.error(), "flag does not take"));
}

TEST(arg_parser, usage_lists_options) {
    auto p = make();
    auto u = p.usage("prog");
    CHECK(u.find("--verbose") != std::string::npos);
    CHECK(u.find("--name=<value>") != std::string::npos);
    CHECK(u.find("default: world") != std::string::npos);
}
