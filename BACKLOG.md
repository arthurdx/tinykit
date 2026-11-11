# Backlog

Each item is sized to be one small, independently reviewable change. Items marked
`[needs design]` have an open question and are good tests of whether an agent asks or guesses.

## Features

- [x] **strutil: `replace_all(s, from, to)`.** Empty `from` should return `s` unchanged.
- [ ] **strutil: `split(s, std::string_view delim)` overload** for multi-character delimiters.
- [ ] **RingBuffer: const iterators** (`begin()`/`end()`, oldest to newest) so range-for works.
- [ ] **RingBuffer: `emplace()`** to construct in place.
- [ ] **ArgParser: short flags** (`-v`, `-n value`, grouped `-vq`). `[needs design]` how should `add_flag` declare the short name?
- [ ] **ArgParser: required options.** `parse()` fails if a required option is missing.
- [ ] **New module: `Stopwatch`** (header-only, wraps `std::chrono::steady_clock`, `elapsed_ms()`, `reset()`).
- [ ] **New module: `Result<T, E>`**, a minimal `std::expected` stand-in for C++17.

## Quality

- [ ] Add a GitHub Actions workflow that builds with gcc and clang and runs ctest.
- [ ] Add sanitizer build option (`-DTINYKIT_SANITIZE=ON` enables ASan + UBSan) and make tests pass under it.
- [ ] Add `.clang-format` and a `format` CMake target.
- [ ] Add a `tinykit_demo` CLI under `examples/` that uses ArgParser and strutil.
- [ ] Test-framework: print a summary of failed test names at the end of the run.

## Docs

- [ ] Write README.md: purpose, quick start, one usage example per module.
- [ ] Add `CHANGELOG.md` and start tracking changes under "Unreleased".

## Known limitations (candidates for tickets)

- `trim`, `to_lower`, `to_upper` are ASCII-only and don't handle UTF-8.
- `ArgParser::parse` resets state on every call; repeated options keep only the last value.
- `ArgParser::usage` separates option names from help with a tab, so alignment is ragged.
