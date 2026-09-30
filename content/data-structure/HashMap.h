/**
 * Author: Simon Lindholm (KACTL)
 * Description: Hash map ~3x faster than unordered\_map, with
 * an anti-hack hash. Use like unordered\_map (h[k], h.find).
 */
#pragma once
#include <bits/extc++.h>
// To use most bits rather than just the lowest ones :
struct chash { // large odd number for C
  const uint64_t C = ll(4e18 * acos(0)) | 71;
  ll operator()(ll x) const { return __builtin_bswap64(x*C); }
};
__gnu_pbds::gp_hash_table<ll,int,chash> h({},{},{},{},{1<<16});