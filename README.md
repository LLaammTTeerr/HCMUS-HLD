# HCMUS-HLD-V3.11Pro-258B Team Reference Document

[![CI](https://github.com/LLaammTTeerr/HCMUS-HLD/actions/workflows/ci.yml/badge.svg)](https://github.com/LLaammTTeerr/HCMUS-HLD/actions/workflows/ci.yml)
[![Latest release](https://img.shields.io/github/v/release/LLaammTTeerr/HCMUS-HLD)](https://github.com/LLaammTTeerr/HCMUS-HLD/releases/latest)

ICPC team reference document (TRD) of team HCMUS-HLD-V3.11Pro-258B,
VNUHCM University of Science. Copy-pasteable C++ for ICPC-style contests,
built on the [KACTL](https://github.com/kth-competitive-programming/kactl) template.

**[Download the latest PDF](https://github.com/LLaammTTeerr/HCMUS-HLD/releases/latest/download/hcmus.pdf)**
(built and released automatically from `main`).

## ICPC World Finals rules

The document follows the WF TRD rules, and CI checks the ones it can:

- At most **25 pages** (A4, single-sided). CI fails the build above 25.
- Page number in the upper right; university and team name in the upper left of every page.
  Both come from `\university` / `\team` in `content/hcmus.tex`, so a rename touches one place.
- No cover page, because it would count towards the 25 pages.

## Contents

| Chapter | Highlights |
|---|---|
| Contest | template, `.bashrc`, `hash.sh`, troubleshooting checklist |
| Mathematics | formulas, NTT/FFT mod, CRT, discrete log, modular square root, FWHT, Berlekamp–Massey, Gauss, Simplex, Miller–Rabin, Pollard rho |
| Dynamic Programming | Knuth, slope trick, Aliens trick |
| Combinatorial | formulas, partition numbers |
| Flow & Matching | modelling notes, Dinic, min-cost flow, Hopcroft–Karp, Hungarian, blossom, Stoer–Wagner, Gomory–Hu |
| Data structures | ZKW segment tree, Li Chao, convex hull trick, splay tree, order tree, hash map, generic hash |
| Graph | 2-SAT, Tarjan SCC, centroid, block-cut tree, bridges/articulation, max clique, Euler tour |
| String | KMP, Z-function, Manacher, Aho–Corasick, hashing, suffix arrays, Lyndon |
| Geometry | KACTL 2D/3D geometry |
| Various | BigNum, y-combinator, fast I/O, fast mod, memory pool |
| Techniques | checklist of algorithm names to scan when stuck |

Files in `content/` that are not printed are commented out in their chapter's `chapter.tex`.
Run `make showexcluded` to list them.

## Building and testing

Requirements: `pdflatex` (TeX Live), `python3`, `g++` (C++17) and `cpp`.

```sh
make hcmus           # build hcmus.pdf (make fast: one LaTeX pass)
make test-compiles   # every printed header compiles right after template.cpp
make test            # stress tests in stress-tests/ (~1 min)
```

The PDF is not committed (`hcmus.pdf` is gitignored).

## Adding or changing an algorithm

1. Put the code in `content/<chapter>/Name.h`. It must compile right after
   `content/contest/template.cpp` with nothing else: declare every global, constant and
   typedef it uses, or `#include` another header from the same directory.
2. Start the file with a header comment. Allowed fields: `Author`, `Date`, `Description`,
   `Source`, `Time`, `Memory`, `License`, `Status`, `Usage`, `Details`.
   `Author` and `Description` are required, and any other field breaks the build.
   ```cpp
   /**
    * Author: HCMUS-HLD
    * Description: What it does, conventions (0/1-indexed, [l, r)), limits.
    * Usage: ZKW st(n); st.update(i, v); st.query(l, r);
    * Time: O(\log N)
    */
   #pragma once
   ```
   `Description` is LaTeX: wrap math in `$...$`, and write `_`, `%`, `#`, `&` as `\_`, `\%`, `\#`, `\&`.
   `Usage` is code and is escaped automatically. `Time` may use `O(...)` directly.
3. Add `\kactlimport{Name.h}` to that chapter's `chapter.tex`.
4. Add a brute-force test `stress-tests/<chapter>/Name.cpp`, like the existing ones.
   It starts with `#include "../utilities/template.h"` and `#include "../../content/<chapter>/Name.h"`,
   uses `assert`, and should run in under 2 s at `-O2`.
5. Check with `make test-compiles && make test && make hcmus`, and keep an eye on the page count.

Style: terse, tabs for indentation (printed as 2 spaces), lines up to about 63 characters.
Each code block in the PDF shows a 6-character hash of its code, ignoring whitespace and comments.
After typing a block at the contest, run `sh hash.sh < file.cpp` to check it matches.

## CI and releases

`.github/workflows/ci.yml` runs on every push:

- **test**: `make test-compiles` and `make test`.
- **pdf**: builds the PDF, checks `hash.sh` works and the page count is at most 25, and attaches the PDF to the run as the `hcmus-pdf` artifact.
- **release**: runs on `main` only, after both pass. It creates a GitHub Release with `hcmus.pdf` attached.
  The version is the latest `v*` tag plus a patch bump.
  Write `#minor` or `#major` in the commit message to bump those instead.

If a push to `main` doesn't produce a release, start one by hand:
Actions → CI → Run workflow → `main`.

## License

As usual for competitive programming, the licensing situation is a bit unclear.
Many source files are marked with a license (we try to use
[CC0](https://creativecommons.org/share-your-work/public-domain/cc0/)); sources and authors are noted in each file.
Everything in `stress-tests` is implicitly CC0, except reference implementations taken from elsewhere.
Based on [KACTL](https://github.com/kth-competitive-programming/kactl).
