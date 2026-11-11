#pragma once

// A tiny self-registering test framework (no external dependencies).
//
//   TEST(suite, name) { CHECK(1 + 1 == 2); CHECK_EQ(a, b); CHECK_THROWS(f()); }

#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace tf {

struct TestCase {
    std::string name;
    std::function<void()> fn;
};

inline std::vector<TestCase>& registry() {
    static std::vector<TestCase> r;
    return r;
}

inline int& failures() {
    static int n = 0;
    return n;
}

struct Registrar {
    Registrar(const std::string& name, std::function<void()> fn) {
        registry().push_back({name, std::move(fn)});
    }
};

inline void report_failure(const char* file, int line, const std::string& msg) {
    ++failures();
    std::cerr << "    FAIL " << file << ":" << line << ": " << msg << "\n";
}

// Stream a value for failure messages; vectors print as ["a", "b"].
template <typename T>
void show(std::ostream& os, const T& v) {
    os << v;
}

template <typename T>
void show(std::ostream& os, const std::vector<T>& v) {
    os << "[";
    for (std::size_t i = 0; i < v.size(); ++i) {
        if (i > 0) os << ", ";
        show(os, v[i]);
    }
    os << "]";
}

inline void show(std::ostream& os, const std::string& s) { os << '"' << s << '"'; }

template <typename A, typename B>
void check_eq(const A& a, const B& b, const char* ea, const char* eb, const char* file,
              int line) {
    if (!(a == b)) {
        std::ostringstream os;
        os << ea << " == " << eb << " (got ";
        show(os, a);
        os << " vs ";
        show(os, b);
        os << ")";
        report_failure(file, line, os.str());
    }
}

inline int run_all() {
    int failed_tests = 0;
    for (const auto& t : registry()) {
        int before = failures();
        try {
            t.fn();
        } catch (const std::exception& e) {
            report_failure(__FILE__, __LINE__, std::string("unexpected exception: ") + e.what());
        }
        bool ok = failures() == before;
        std::cout << (ok ? "[ OK ] " : "[FAIL] ") << t.name << "\n";
        if (!ok) ++failed_tests;
    }
    std::cout << registry().size() - static_cast<std::size_t>(failed_tests) << "/"
              << registry().size() << " tests passed\n";
    return failed_tests == 0 ? 0 : 1;
}

}  // namespace tf

#define TEST(suite, name)                                                         \
    static void test_##suite##_##name();                                          \
    static tf::Registrar reg_##suite##_##name(#suite "." #name,                   \
                                              test_##suite##_##name);             \
    static void test_##suite##_##name()

#define CHECK(expr)                                                               \
    do {                                                                          \
        if (!(expr)) tf::report_failure(__FILE__, __LINE__, "CHECK(" #expr ")");  \
    } while (0)

#define CHECK_EQ(a, b) tf::check_eq((a), (b), #a, #b, __FILE__, __LINE__)

#define CHECK_THROWS(expr)                                                        \
    do {                                                                          \
        bool threw_ = false;                                                      \
        try {                                                                     \
            (void)(expr);                                                         \
        } catch (...) {                                                           \
            threw_ = true;                                                        \
        }                                                                         \
        if (!threw_) tf::report_failure(__FILE__, __LINE__, "expected throw: " #expr); \
    } while (0)
