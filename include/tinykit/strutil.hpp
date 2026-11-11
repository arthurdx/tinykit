#pragma once

#include <string>
#include <string_view>
#include <vector>

namespace tinykit {

// Remove leading and trailing ASCII whitespace.
std::string trim(std::string_view s);

// Split on a single-character delimiter. Empty fields are preserved:
// split("a,,b", ',') -> {"a", "", "b"}; split("", ',') -> {""}.
std::vector<std::string> split(std::string_view s, char delim);

// Join parts with a separator. join({}, ",") -> "".
std::string join(const std::vector<std::string>& parts, std::string_view sep);

// ASCII-only case conversion.
std::string to_lower(std::string_view s);
std::string to_upper(std::string_view s);

bool starts_with(std::string_view s, std::string_view prefix);
bool ends_with(std::string_view s, std::string_view suffix);

// Replace every non-overlapping occurrence of from with to, scanning left to right.
// Empty from returns s unchanged: replace_all("abc", "", "x") -> "abc".
std::string replace_all(std::string_view s, std::string_view from, std::string_view to);

}  // namespace tinykit
