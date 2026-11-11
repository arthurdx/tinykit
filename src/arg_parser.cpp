#include "tinykit/arg_parser.hpp"

#include "tinykit/strutil.hpp"

namespace tinykit {

void ArgParser::add_flag(const std::string& name, const std::string& help) {
    specs_[name] = Spec{true, help, ""};
}

void ArgParser::add_option(const std::string& name, const std::string& help,
                           const std::string& default_value) {
    specs_[name] = Spec{false, help, default_value};
}

bool ArgParser::parse(int argc, const char* const* argv) {
    std::vector<std::string> args;
    for (int i = 1; i < argc; ++i) args.emplace_back(argv[i]);
    return parse(args);
}

bool ArgParser::parse(const std::vector<std::string>& args) {
    values_.clear();
    flags_.clear();
    positional_.clear();
    error_.clear();

    bool options_done = false;
    for (std::size_t i = 0; i < args.size(); ++i) {
        const std::string& arg = args[i];

        if (options_done || !starts_with(arg, "--")) {
            positional_.push_back(arg);
            continue;
        }
        if (arg == "--") {
            options_done = true;
            continue;
        }

        std::string body = arg.substr(2);
        std::string name = body;
        std::string value;
        bool has_inline_value = false;
        std::size_t eq = body.find('=');
        if (eq != std::string::npos) {
            name = body.substr(0, eq);
            value = body.substr(eq + 1);
            has_inline_value = true;
        }

        auto it = specs_.find(name);
        if (it == specs_.end()) {
            error_ = "unknown option: --" + name;
            return false;
        }

        if (it->second.is_flag) {
            if (has_inline_value) {
                error_ = "flag does not take a value: --" + name;
                return false;
            }
            flags_[name] = true;
        } else {
            if (!has_inline_value) {
                if (i + 1 >= args.size()) {
                    error_ = "missing value for option: --" + name;
                    return false;
                }
                value = args[++i];
            }
            values_[name] = value;
        }
    }
    return true;
}

bool ArgParser::has_flag(const std::string& name) const {
    auto it = flags_.find(name);
    return it != flags_.end() && it->second;
}

std::string ArgParser::get(const std::string& name) const {
    auto v = values_.find(name);
    if (v != values_.end()) return v->second;
    auto s = specs_.find(name);
    if (s != specs_.end()) return s->second.default_value;
    return "";
}

std::string ArgParser::usage(const std::string& program) const {
    std::string out = "Usage: " + program + " [options] [args...]\n\nOptions:\n";
    for (const auto& [name, spec] : specs_) {
        out += "  --" + name;
        if (!spec.is_flag) out += "=<value>";
        out += "\t" + spec.help;
        if (!spec.is_flag && !spec.default_value.empty()) {
            out += " (default: " + spec.default_value + ")";
        }
        out += "\n";
    }
    return out;
}

}  // namespace tinykit
