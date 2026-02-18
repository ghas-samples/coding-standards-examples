# CodeQL Coding Standards — Training Examples

This repository demonstrates how to use the [CodeQL Coding Standards](https://github.com/github/codeql-coding-standards) **packs** and **query suites** to detect violations of **MISRA C**, **CERT C**, **AUTOSAR C++14**, **CERT C++**, and **MISRA C++** in a third-party library or any C/C++ codebase.

> **Purpose:** Train engineers on integrating coding-standard checks into CI/CD pipelines using CodeQL packs published from `github/codeql-coding-standards`.

---

## Repository structure

```
.
├── .github/workflows/
│   └── codeql-coding-standards.yml   # GitHub Actions workflow
├── src/
│   ├── c/
│   │   ├── misra_violations.c        # Intentional MISRA C 2012 violations
│   │   └── cert_c_violations.c       # Intentional CERT C violations
│   └── cpp/
│       ├── autosar_violations.cpp    # Intentional AUTOSAR C++14 violations
│       ├── cert_cpp_violations.cpp   # Intentional CERT C++ violations
│       └── misra_cpp_violations.cpp  # Intentional MISRA C++ violations
├── Makefile                          # Build system (traced by CodeQL)
└── README.md                         # This file
```

---

## Available CodeQL packs

The `github/codeql-coding-standards` project publishes the following **query packs** to the GitHub Container Registry. You reference them by name in the CodeQL CLI or in GitHub Actions:

| Pack name | Standard | Language |
|---|---|---|
| `codeql/misra-c-coding-standards` | MISRA C 2012 / 2023 | C |
| `codeql/cert-c-coding-standards` | SEI CERT C 2016 | C |
| `codeql/autosar-cpp-coding-standards` | AUTOSAR C++14 (R22-11) | C++ |
| `codeql/cert-cpp-coding-standards` | SEI CERT C++ 2016 | C++ |
| `codeql/misra-cpp-coding-standards` | MISRA C++ | C++ |

---

## Query suites

Each pack ships with multiple **query suites** under `codeql-suites/`. The available suites vary by standard:

**AUTOSAR C++:**
| Suite | Description |
|---|---|
| `autosar-default.qls` | All automated queries |
| `autosar-audit.qls` | Audit-only queries (candidates for manual review) |
| `autosar-advisory.qls` | Advisory-level queries only |
| `autosar-required.qls` | Required-level queries only |
| `autosar-single-translation-unit.qls` | Queries scoped to a single translation unit |

**MISRA C:**
| Suite | Description |
|---|---|
| `misra-c-default.qls` | All automated queries |
| `misra-c-audit.qls` | Audit-only queries |
| `misra-c-strict.qls` | Strict queries (likely intentional violations) |
| `misra-c-mandatory.qls` | Mandatory-level queries only |
| `misra-c-required.qls` | Required-level queries only |
| `misra-c-advisory.qls` | Advisory-level queries only |

**CERT C:**
| Suite | Description |
|---|---|
| `cert-c-default.qls` | All automated queries |
| `cert-c-l1.qls` | Level 1 rules (highest severity) |
| `cert-c-l2.qls` | Level 2 rules |
| `cert-c-l3.qls` | Level 3 rules |
| `cert-c-recommendation.qls` | Recommendation-level queries |

**CERT C++:**
| Suite | Description |
|---|---|
| `cert-cpp-default.qls` | All automated queries |
| `cert-cpp-l1.qls` | Level 1 rules (highest severity) |
| `cert-cpp-l2.qls` | Level 2 rules |
| `cert-cpp-l3.qls` | Level 3 rules |

You select a suite with the `:<suite-path>` suffix, e.g.:

```
codeql/autosar-cpp-coding-standards:codeql-suites/autosar-required.qls
```

---

## How to use — GitHub Actions (recommended)

The workflow in [`.github/workflows/codeql-coding-standards.yml`](.github/workflows/codeql-coding-standards.yml) runs automatically on push/PR. It has three jobs demonstrating different usage patterns:

### 1. Using packs directly

Specify one or more packs in the `packs` input of `github/codeql-action/init`:

```yaml
- uses: github/codeql-action/init@v3
  with:
    languages: c-cpp
    packs: |
      codeql/misra-c-coding-standards
      codeql/cert-c-coding-standards
```

### 2. Pinning a specific version

Append `@<version>` to lock the pack:

```yaml
packs: |
  codeql/autosar-cpp-coding-standards@2.38.0
```

### 3. Using a specific query suite

Append `:codeql-suites/<suite>.qls` to run only that suite:

```yaml
packs: |
  codeql/autosar-cpp-coding-standards:codeql-suites/autosar-required.qls
```

---

## How to use — CodeQL CLI (local / offline)

### Prerequisites

1. **CodeQL CLI** — download from [github/codeql-cli-binaries](https://github.com/github/codeql-cli-binaries/releases) or use the [CodeQL bundle](https://github.com/github/codeql-action/releases).
2. **A C/C++ compiler** — `gcc` and `g++` are used in the Makefile.

### Step 1 — Download the coding standards packs

```bash
# Download individual packs into the local cache
codeql pack download codeql/misra-c-coding-standards
codeql pack download codeql/cert-c-coding-standards
codeql pack download codeql/autosar-cpp-coding-standards
codeql pack download codeql/cert-cpp-coding-standards
codeql pack download codeql/misra-cpp-coding-standards
```

### Step 2 — Create a CodeQL database

```bash
# C database
codeql database create codeql-db-c \
  --language=cpp \
  --command="make c"

# C++ database
codeql database create codeql-db-cpp \
  --language=cpp \
  --command="make cpp"
```

### Step 3 — Run the analysis

```bash
# Run MISRA C + CERT C against the C database
codeql database analyze codeql-db-c \
  --format=sarifv2.1.0 \
  --output=results-c.sarif \
  codeql/misra-c-coding-standards \
  codeql/cert-c-coding-standards

# Run AUTOSAR + CERT C++ + MISRA C++ against the C++ database
codeql database analyze codeql-db-cpp \
  --format=sarifv2.1.0 \
  --output=results-cpp.sarif \
  codeql/autosar-cpp-coding-standards \
  codeql/cert-cpp-coding-standards \
  codeql/misra-cpp-coding-standards
```

### Step 4 — Run with a specific query suite

```bash
# Run only the AUTOSAR required-level queries
codeql database analyze codeql-db-cpp \
  --format=sarifv2.1.0 \
  --output=results-autosar-required.sarif \
  "codeql/autosar-cpp-coding-standards:codeql-suites/autosar-required.qls"

# Run only CERT C level-1 (highest severity) queries
codeql database analyze codeql-db-c \
  --format=sarifv2.1.0 \
  --output=results-cert-c-l1.sarif \
  "codeql/cert-c-coding-standards:codeql-suites/cert-c-l1.qls"

# Run only MISRA C strict queries
codeql database analyze codeql-db-c \
  --format=sarifv2.1.0 \
  --output=results-misra-strict.sarif \
  "codeql/misra-c-coding-standards:codeql-suites/misra-c-strict.qls"
```

### Step 5 — List queries in a suite (useful for auditing)

```bash
codeql resolve queries \
  "codeql/autosar-cpp-coding-standards:codeql-suites/autosar-default.qls"
```

### Step 6 (optional) — Upload SARIF to GitHub Code Scanning

```bash
codeql github upload-results \
  --sarif=results-cpp.sarif \
  --repository=<owner>/<repo> \
  --ref=refs/heads/main \
  --commit=$(git rev-parse HEAD)
```

---

## What violations will be found?

### C — MISRA C 2012

| File | Rule | Description |
|---|---|---|
| `misra_violations.c` | Rule 2.2 | Dead code (value assigned but never read) |
| | Rule 8.4 | Missing compatible declaration for extern function |
| | Rule 10.1 | Shift of essentially character type |
| | Rule 10.3 | Implicit narrowing conversion |
| | Rule 11.3 | Cast between incompatible pointer types |
| | Rule 12.1 | Ambiguous operator precedence |
| | Rule 14.4 | Non-boolean controlling expression |
| | Rule 15.6 | Loop body without compound statement |
| | Rule 17.7 | Discarded return value |
| | Rule 21.3 | Use of malloc/free |
| | Rule 21.6 | Use of printf (stdio) |
| | Dir 4.6 | Use of basic numerical types instead of fixed-width |

### C — CERT C

| File | Rule | Description |
|---|---|---|
| `cert_c_violations.c` | EXP30-C | Side-effect order dependence |
| | EXP33-C | Read of uninitialized variable |
| | ARR30-C | Out-of-bounds array access |
| | MEM30-C | Use-after-free |
| | MEM35-C | Insufficient allocation |
| | STR31-C | Buffer overflow via strcpy |
| | ERR33-C | Unchecked return value (fopen) |
| | SIG30-C | Non-async-safe function in signal handler |
| | MSC32-C | Unseeded PRNG |
| | INT31-C | Lossy integer conversion |
| | DCL30-C | Returning address of local variable |

### C++ — AUTOSAR C++14

| File | Rule | Description |
|---|---|---|
| `autosar_violations.cpp` | A0-1-1 | Unused value assignment |
| | A0-1-2 | Discarded non-void return value |
| | A2-10-1 | Identifier shadowing |
| | A5-1-1 | Magic number |
| | A7-1-5 | Inappropriate use of auto |
| | A11-0-2 | Private member in struct |
| | A15-1-2 | Throwing a pointer as exception |
| | A18-1-1 | C-style array |
| | A18-5-1 | Use of malloc/free |
| | M5-0-3 | Implicit type conversion |
| | A5-2-2 | C-style cast |
| | A3-9-1 | Basic numerical type instead of fixed-width |
| | M6-4-1 | Missing else clause |
| | A8-4-7 | Large parameter passed by value |

### C++ — CERT C++

| File | Rule | Description |
|---|---|---|
| `cert_cpp_violations.cpp` | ERR50-CPP | Abrupt program termination |
| | ERR58-CPP | Exception during static initialization |
| | DCL50-CPP | C-style variadic function |
| | OOP57-CPP | memcpy on class types |
| | EXP55-CPP | Modification via const_cast |
| | CTR50-CPP | Out-of-bounds container access |
| | MEM52-CPP | Unchecked allocation failure |
| | ERR61-CPP | Exception caught by value (slicing) |
| | MSC50-CPP | Use of std::rand() |
| | OOP51-CPP | Object slicing |

### C++ — MISRA C++

| File | Rule | Description |
|---|---|---|
| `misra_cpp_violations.cpp` | 0-1-1 | Unreachable code |
| | 2-10-2 | Identifier shadowing |
| | 5-0-3 | Implicit conversion |
| | 5-2-4 | C-style cast |
| | 6-4-2 | Missing else clause |
| | 6-6-5 | Multiple return points |
| | 15-3-5 | Exception not caught by reference |
| | 18-0-1 | Use of C library (strcpy) |
| | 18-4-1 | Dynamic heap allocation |
| | 27-0-1 | Use of cstdio |

---

## Using packs in a third-party library

When analyzing a **third-party library** you don't own, the approach is identical — you just point the database creation at the library's build system:

```bash
# 1. Clone the third-party library
git clone https://github.com/example/third-party-lib.git
cd third-party-lib

# 2. Create a CodeQL database using the library's build command
codeql database create codeql-db \
  --language=cpp \
  --command="cmake --build build"

# 3. Run whichever coding standard packs you need
codeql database analyze codeql-db \
  --format=sarifv2.1.0 \
  --output=results.sarif \
  codeql/misra-c-coding-standards \
  codeql/cert-c-coding-standards

# 4. View results in VS Code with the SARIF Viewer extension,
#    or upload to GitHub Code Scanning
```

For GitHub Actions, add the `packs` input to the `codeql-action/init` step in the library's workflow — no other changes needed.

---

## Tips for training

1. **Start with one pack** — e.g. `codeql/cert-c-coding-standards` — so learners see a focused set of results before combining multiple standards.
2. **Compare suites** — run `default` vs. `audit` vs. `required` / `advisory` against the same database and compare the SARIF outputs to understand query categorization.
3. **Use `codeql resolve queries`** — to list every query a suite will run, so learners understand what's being checked.
4. **Install the SARIF Viewer extension** in VS Code to browse results interactively.
5. **Pin pack versions** in production to ensure reproducible results across builds.

---

## References

- [CodeQL Coding Standards — User Manual](https://github.com/github/codeql-coding-standards/blob/main/docs/user_manual.md)
- [CodeQL Coding Standards — Supported Rules](https://github.com/github/codeql-coding-standards/blob/main/rules.csv)
- [CodeQL CLI documentation](https://docs.github.com/en/code-security/codeql-cli)
- [CodeQL Action](https://github.com/github/codeql-action)
- [SARIF Viewer VS Code Extension](https://marketplace.visualstudio.com/items?itemName=MS-SarifVSCode.sarif-viewer)
