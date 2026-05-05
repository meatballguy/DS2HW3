# DS2HW3 — Hash Table Implementation

**Students:** 11327146 莊立聖 · 11327155 黃宇謙

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
**** Hash Table Operations  ******
* 0. QUIT                        *
* 1. Load data & Quadratic Probe *
* 2. Double Hashing              *
* 3. Search                      *
* 4. Statistics                  *
**********************************
Input a choice(0, 1, 2, 3, 4):
```

## File Structure

```
DS2HW3_11327146_11327155.cpp   # Main source file
input<N>.txt / input<N>.bin    # Input data files (not committed)
```

## Recent Commits

<!-- COMMITS_START -->
<!-- COMMITS_END -->
