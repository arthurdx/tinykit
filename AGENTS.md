# AGENTS.md: working on tinykit

tinykit is a small C++17 utility library: string helpers, a ring buffer, and a CLI arg parser.
It exists as a proof-of-concept codebase for agentic software-factory workflows.

## Commands

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug   # configure
cmake --build build -j                         # build (warnings are errors)
ctest --test-dir build --output-on-failure     # run all tests
./build/tinykit_tests                          # run tests directly, with per-test output
```

The build is the gate: a change is done only when it compiles warning-free and all tests pass.

## Layout

| Path | Purpose |
|---|---|
| `include/tinykit/*.hpp` | Public headers. Anything here is public API. |
| `src/*.cpp` | Implementations (`ring_buffer.hpp` is header-only because it is a template). |
| `tests/test_<module>.cpp` | One test file per module, using `tests/test_framework.hpp`. |
| `BACKLOG.md` | Work items. Pick one, do it, tick it off. |

## Conventions

- C++17, no third-party dependencies. Keep it that way.
- Namespace `tinykit`. Files are `snake_case`. Types are `PascalCase`. Functions and variables are `snake_case`.
- Every public function gets a one-line contract comment in its header (including edge cases).
- Every behavior change comes with a test in the same change. Bug fixes start with a failing test.
- New `.cpp` files must be added to `CMakeLists.txt` (library sources and test sources are listed explicitly).
- Don't weaken warning flags or delete tests to make the build pass.
- Keep changes small and scoped to one backlog item at a time.

## Factory workflow

Issue/PR workflow, hard limits and definition of done: see `AGENTS.factory.md`. Both files apply.
