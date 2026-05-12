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
- `5bac7c3` Merge pull request #11 from meatballguy/kitakaaki (HUANG YU CHIEN, 2026-05-12)
- `a31058d` 5/12 12:17 update (remove test file) (kitakaaki, 2026-05-12)
- `352fe2e` 5/12 12:13 update (final version) (kitakaaki, 2026-05-12)
- `1c70972` 11:15 (kitakaaki, 2026-05-12)
- `0cf0e10` 5/12 11:02 update (kitakaaki, 2026-05-12)
- `f679fcb` docs: update README with recent commits [skip ci] (github-actions[bot], 2026-05-06)
- `9e8c202` Merge pull request #10 from meatballguy/kitakaaki (HUANG YU CHIEN, 2026-05-06)
- `9dcfe26` 5/6 14:23 update(pass dc test) (kitakaaki, 2026-05-06)
- `2acd389` docs: update README with recent commits [skip ci] (github-actions[bot], 2026-05-06)
- `f170b61` Merge pull request #9 from meatballguy/kitakaaki (HUANG YU CHIEN, 2026-05-06)
- `1bef7be` 5/6 13:51 update(all terminal output correct) (kitakaaki, 2026-05-06)
- `aafeeee` 5/6 13:30 update(all output file correct) (kitakaaki, 2026-05-06)
- `c6e638d` 5/6 13:09 update (kitakaaki, 2026-05-06)
- `43c98e3` docs: update README with recent commits [skip ci] (github-actions[bot], 2026-05-05)
- `f546bd4` Merge pull request #8 from meatballguy/copilot/update-readme-with-new-features (HUANG YU CHIEN, 2026-05-05)
- `d5965d2` docs: update README to reflect current menu and features (copilot-swe-agent[bot], 2026-05-05)
- `ec4d180` docs: update README with recent commits [skip ci] (github-actions[bot], 2026-05-05)
- `92e5f67` Merge pull request #7 from meatballguy/kitakaaki (HUANG YU CHIEN, 2026-05-05)
- `23c4c66` 5/5 20:49 update (kitakaaki, 2026-05-05)
- `28c33ae` docs: update README with recent commits [skip ci] (github-actions[bot], 2026-05-05)- `3ab4c09` Merge pull request #5 from meatballguy/copilot/modify-readme-new-commit (HUANG YU CHIEN, 2026-05-05)- `23e9c5a` Merge pull request #4 from meatballguy/kitakaaki (HUANG YU CHIEN, 2026-05-05)- `eebe5f8` semi completed mission zero, need to rework AI trace (meatballpasta, 2026-05-04)- `af76ff8` 5/3 22:20 update (kitakaaki, 2026-05-03)- `1f47601` Add README.md and GitHub Actions workflow to auto-update commits section (copilot-swe-agent[bot], 2026-05-03)- `9fddffa` initial commit (meatballpasta, 2026-05-02)<!-- COMMITS_END -->
