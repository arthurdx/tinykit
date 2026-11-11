# Factory rules (shared by humans and agents)

Same rules for everyone. If a rule is not enforced by CI, it is a request that
will eventually be ignored: promote it to a check. Project-specific build
commands and conventions live in AGENTS.md; this file is the workflow layer.

## Workflow
1. Work enters as a GitHub issue using the `task` template (intent + acceptance criteria).
2. Triage sets exactly one `impact:` label (`low`, `medium`, `high`).
3. Implementation happens on a branch `factory/<issue-number>-<slug>`; never on `main`.
4. Open a PR using the PR template. Link the issue.
5. CI must pass. Review is tied to the reviewed commit SHA; a new push needs a new review.
6. A human merges. Agents do not merge in the PoC.

## Hard limits for agents
- Never push to `main`, never edit `.github/workflows/`, never read or print secrets.
- No deploys or production changes.
- Maximum 3 fix rounds on one PR, then stop and label `needs-human`.
- If a task fails or times out, report and stop. No blind retries.
- If the label `factory:halt` is on the issue or repo, do nothing.
- If the issue has an open design question, ask in a comment and label `needs-human`. Do not guess.
- Do not claim tests pass unless you ran them and can paste the output.

## Definition of done
- Each acceptance criterion in the issue is addressed in the PR description.
- Tests added or updated for changed behavior; CI green.
- PR lists what was verified and what the agent could NOT verify.
