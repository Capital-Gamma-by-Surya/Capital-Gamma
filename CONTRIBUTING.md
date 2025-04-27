# Contributing to Capital‑Gamma

First off, **thank you** for taking the time to contribute!  
Every issue, pull request, and suggestion helps make this library more robust and useful.

> If you’re new to open source, start with [How to Contribute to Open Source](https://opensource.guide/how-to-contribute/).

---

## Code of Conduct

This project adheres to the [Contributor Covenant](https://www.contributor-covenant.org/) Code of Conduct, version 2.1.  
By participating, you are expected to uphold these guidelines. Report unacceptable behavior to **maintainers@capital‑gamma.dev**.

---

## How Can I Contribute?

### 1. Reporting Bugs

* **Search existing issues** to avoid duplicates.  
* Open a new issue with the **Bug report** template.  
* Include reproduction steps, expected vs. actual behavior, and environment details.

### 2. Requesting Enhancements

* Use the **Feature request** template.  
* Explain the use‑case and, if possible, provide sample API or pseudo‑code.

### 3. Submitting Changes

1. **Fork** the repository, create a new branch from `main`.  
2. Follow [Coding Standards](#coding-standards).  
3. [Run the Test Suite](#running-tests) and ensure it passes.  
4. Open a pull request (PR) against `main` with a clear description.  
5. A maintainer will review—please be responsive to feedback.

---

## Development Setup

```bash
# clone your fork
git clone https://github.com/<your-username>/Capital-Gamma.git
cd Capital-Gamma

# C++ build
mkdir -p build && cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake --build . -j
ctest          # run C++ tests

# Python tests
pip install -r requirements.txt
pytest
```

> Tip: Use `pre-commit install` to enable automatic formatting & linting hooks.

---

## Coding Standards

| Language | Formatter / Linter | Command |
|----------|--------------------|---------|
| C++17    | `clang-format`     | `clang-format -i $(git ls-files '*.hpp' '*.cpp')` |
| Python   | `black` + `ruff`   | `black . && ruff .` |

*Prefer composition over inheritance.*  
*Keep headers free of implementation details.*  
Document public interfaces with Doxygen comments.

---

## Commit & PR Guidelines

* Use present‑tense *imperative* commit messages: “Add option vega calculation”.  
* One logical change per PR.  
* Update **CHANGELOG.md** if the change is user‑facing.  
* CI **must** pass before merge.  
* Squash commits when requested by a reviewer.

---

## Running Tests

```bash
# In build directory
ctest         # C++
pytest        # Python
```

Add new tests alongside your features or bug‑fixes.

---

## Release Process

1. Maintainer bumps version following **Semantic Versioning**.  
2. `CHANGELOG.md` updated.  
3. Git tag `vX.Y.Z` pushed, triggering GitHub Release & PyPI wheel upload.

---

Thank you again for contributing!  
Feel free to reach out in Discussions or open an issue for any clarifications.
