#!/usr/bin/env python3
"""Factory gate: the PR description must have the required sections, each with real content.

Reads the PR body from the PR_BODY environment variable. Exit 1 on any problem.
Content = anything left after removing HTML comments and empty checkbox lines.
"""
import os
import re
import sys

REQUIRED = ["Acceptance criteria", "Verified", "NOT verified"]


def sections(body: str) -> dict:
    """Map heading text -> body text, for '## ' headings."""
    body = re.sub(r"<!--.*?-->", "", body, flags=re.S)
    parts = re.split(r"^##\s+(.*?)\s*$", body, flags=re.M)
    # parts = [preamble, heading1, text1, heading2, text2, ...]
    return {parts[i]: parts[i + 1] for i in range(1, len(parts) - 1, 2)}


def has_content(text: str) -> bool:
    for line in text.splitlines():
        if line.strip() and not re.fullmatch(r"\s*[-*]\s*\[[ xX]?\]\s*", line):
            return True
    return False


def main() -> int:
    found = sections(os.environ.get("PR_BODY") or "")
    errors = []
    for name in REQUIRED:
        key = next((h for h in found if h.startswith(name)), None)
        if key is None:
            errors.append(f"missing section: ## {name}")
        elif not has_content(found[key]):
            errors.append(f"section is empty: ## {name}")
    for e in errors:
        print(f"::error::PR description {e}")
    return 1 if errors else 0


if __name__ == "__main__":
    sys.exit(main())
