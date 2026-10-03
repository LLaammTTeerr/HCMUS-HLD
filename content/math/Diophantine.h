/**
 * Author: HCMUS-HLD
 * Description: Solves $ax + by = c$ ($a, b \ne 0$). On success sets
 * $g = \gcd(|a|, |b|)$ and the solution with smallest $x \ge 0$. All
 * solutions: $(x + k\frac{b}{g},\ y - k\frac{a}{g})$, $k \in \mathbb{Z}$.
 * countSol counts solutions with $x \in [lx, rx]$, $y \in [ly, ry]$.
 * Time: O(\log \min(|a|, |b|))
 */
#pragma once

#include "CRT.h"

bool dioph(ll a, ll b, ll c, ll &x, ll &y, ll &g) {
	g = euclid(abs(a), abs(b), x, y);
	if (c % g) return false;
	ll m = abs(b / g);
	if (a < 0) x = -x;
	x = (ll)((__int128)x * (c / g) % m);
	if (x < 0) x += m;
	y = (ll)(((__int128)c - (__int128)a * x) / b);
	return true;
}

ll fdiv(ll a, ll b) { return a / b - ((a ^ b) < 0 && a % b); }
// k range with lo <= v + k*d <= hi
pair<ll, ll> kRange(ll v, ll d, ll lo, ll hi) {
	if (d < 0) return kRange(-v, -d, -hi, -lo);
	return {-fdiv(v - lo, d), fdiv(hi - v, d)};
}

ll countSol(ll a, ll b, ll c, ll lx, ll rx, ll ly, ll ry) {
	ll x, y, g;
	if (!dioph(a, b, c, x, y, g)) return 0;
	auto [l1, r1] = kRange(x, b / g, lx, rx);
	auto [l2, r2] = kRange(y, -a / g, ly, ry);
	return max(0LL, min(r1, r2) - max(l1, l2) + 1);
}
