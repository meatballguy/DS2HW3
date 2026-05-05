# DS2HW3 — Hash Table Implementation

## Description

This project implements a **Hash Table** in C++ that stores student records (`StudentData`).  
Two collision-resolution strategies are supported:

| Method | Description |
|---|---|
| **Quadratic Probing** | `pos = (hash + i²) % tableSize` |
| **Double Hashing** | `pos = (hash1 + i × hash2) % tableSize` |

The program reads student data from a binary (`.bin`) or text (`.txt`) input file and provides an interactive menu for building and querying the hash table.

## Build

```bash
g++ -std=c++23 -o DS2HW3 DS2HW3_11327146_11327155.cpp
```

## Usage

```
* Data Structures and Algorithms *
************ Hash Table **********
* 0. QUIT                        *
* 1. Quadratic probing           *
* 2. Double hashing              *
**********************************
Input a choice(0, 1, 2):
```

### Menu Options

| Option | Description |
|---|---|
| **0. QUIT** | Exit the program |
| **1. Quadratic probing** | Load data from `input<N>.bin` (or convert from `input<N>.txt`), build the hash table using quadratic probing, write results to `quadratic<N>.txt`, and print average probe counts for successful and unsuccessful searches |
| **2. Double hashing** | Build a second hash table from the already-loaded data using double hashing, write results to `double<N>.txt`, and print the average probe count for successful searches |

> **Note:** Option 2 requires option 1 to be run first (to load data). Statistics are printed automatically after each build — there is no separate search or statistics menu item.

## File Structure

```
DS2HW3_11327146_11327155.cpp   # Main source file
input<N>.txt / input<N>.bin    # Input data files (not committed)
```

## Recent Commits

<!-- COMMITS_START -->
- `92e5f67` Merge pull request #7 from meatballguy/kitakaaki (HUANG YU CHIEN, 2026-05-05)
- `23c4c66` 5/5 20:49 update (kitakaaki, 2026-05-05)
- `28c33ae` docs: update README with recent commits [skip ci] (github-actions[bot], 2026-05-05)
- `8e75e47` Merge pull request #6 from meatballguy/master (HUANG YU CHIEN, 2026-05-05)
- `121fa26` almost complete but no test quadratic (meatballpasta, 2026-05-05)
- `ed962c8` docs: update README with recent commits [skip ci] (github-actions[bot], 2026-05-05)
- `b24f641` Refactor README update workflow for recent commits (HUANG YU CHIEN, 2026-05-05)
- `92b047d` Update README to remove student names (HUANG YU CHIEN, 2026-05-05)
- `3ab4c09` Merge pull request #5 from meatballguy/copilot/modify-readme-new-commit (HUANG YU CHIEN, 2026-05-05)
- `f831bac` Add GitHub Actions workflow to auto-update README with recent commits (copilot-swe-agent[bot], 2026-05-05)
- `a15545c` Delete .github/workflows directory (HUANG YU CHIEN, 2026-05-05)
- `23e9c5a` Merge pull request #4 from meatballguy/kitakaaki (HUANG YU CHIEN, 2026-05-05)
- `cbb643d` 5/5 12:18 update (kitakaaki, 2026-05-05)
- `0790727` Merge pull request #3 from meatballguy/master (HUANG YU CHIEN, 2026-05-05)
- `f8556bf` Merge branch 'main' into master (HUANG YU CHIEN, 2026-05-05)
- `985610e` Update C++ standard from C++17 to C++23 (HUANG YU CHIEN, 2026-05-04)
- `eebe5f8` semi completed mission zero, need to rework AI trace (meatballpasta, 2026-05-04)
- `33eaa7d` docs: update recent commits in README [skip ci] (github-actions[bot], 2026-05-03)
- `6f1582e` Merge pull request #2 from meatballguy/kitakaaki (HUANG YU CHIEN, 2026-05-03)
- `af76ff8` 5/3 22:20 update (kitakaaki, 2026-05-03)- `1f47601` Add README.md and GitHub Actions workflow to auto-update commits section (copilot-swe-agent[bot], 2026-05-03)- `9fddffa` initial commit (meatballpasta, 2026-05-02)<!-- COMMITS_END -->
