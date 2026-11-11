#include "tinykit/strutil.hpp"

#include <cctype>

namespace tinykit {

namespace {
bool is_space(char c) { return std::isspace(static_cast<unsigned char>(c)) != 0; }
}  // namespace

std::string trim(std::string_view s) {
    std::size_t begin = 0;
    std::size_t end = s.size();
    while (begin < end && is_space(s[begin])) ++begin;
    while (end > begin && is_space(s[end - 1])) --end;
    return std::string(s.substr(begin, end - begin));
}

std::vector<std::string> split(std::string_view s, char delim) {
    std::vector<std::string> out;
    std::size_t start = 0;
    while (true) {
        std::size_t pos = s.find(delim, start);
        if (pos == std::string_view::npos) {
            out.emplace_back(s.substr(start));
            return out;
        }
        out.emplace_back(s.substr(start, pos - start));
        start = pos + 1;
    }
}

std::string join(const std::vector<std::string>& parts, std::string_view sep) {
    std::string out;
    for (std::size_t i = 0; i < parts.size(); ++i) {
        if (i > 0) out.append(sep);
        out.append(parts[i]);
    }
    return out;
}

std::string to_lower(std::string_view s) {
    std::string out(s);
    for (char& c : out) c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    return out;
}

std::string to_upper(std::string_view s) {
    std::string out(s);
    for (char& c : out) c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
    return out;
}

bool starts_with(std::string_view s, std::string_view prefix) {
    return s.size() >= prefix.size() && s.substr(0, prefix.size()) == prefix;
}

bool ends_with(std::string_view s, std::string_view suffix) {
    return s.size() >= suffix.size() && s.substr(s.size() - suffix.size()) == suffix;
}

}  // namespace tinykit
