#pragma once

#include <map>
#include <string>
#include <vector>

namespace tinykit {

// Minimal long-option parser.
//   Flags:    --verbose
//   Options:  --name=value   or   --name value
//   Anything not starting with "--" is a positional argument.
//   "--" stops option parsing; the rest is positional.
class ArgParser {
public:
    void add_flag(const std::string& name, const std::string& help);
    void add_option(const std::string& name, const std::string& help,
                    const std::string& default_value = "");

    // Parse argv (argv[0] is skipped). Returns false on error; see error().
    bool parse(int argc, const char* const* argv);
    bool parse(const std::vector<std::string>& args);

    bool has_flag(const std::string& name) const;
    // Value of an option, or its default. Empty string if never declared.
    std::string get(const std::string& name) const;
    const std::vector<std::string>& positional() const { return positional_; }
    const std::string& error() const { return error_; }

    // Multi-line usage text listing declared flags and options.
    std::string usage(const std::string& program) const;

private:
    struct Spec {
        bool is_flag = false;
        std::string help;
        std::string default_value;
    };

    std::map<std::string, Spec> specs_;
    std::map<std::string, std::string> values_;
    std::map<std::string, bool> flags_;
    std::vector<std::string> positional_;
    std::string error_;
};

}  // namespace tinykit
