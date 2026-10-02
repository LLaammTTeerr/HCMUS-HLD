/**
 * Author: HCMUS-HLD
 * Description: One layer of
 * $cur[i] = \min_{k < i} prv[k] + C(k, i)$ for i in $[l, r]$,
 * when the best k is non-decreasing in i (e.g. C satisfies the
 * quadrangle inequality). C(k, i) usually costs the block
 * $(k, i]$. Use INF like 1e18 in prv, not LLONG\_MAX.
 * Usage: prv = \{0, INF, ..., INF\} (size n + 1); per layer:
 * cur.assign(n + 1, INF); dnc(1, n, 0, n - 1, prv, cur, C);
 * swap(prv, cur);
 * Time: O(N \log N) calls to C per layer
 */
#pragma once

template<class F>
void dnc(int l, int r, int lo, int hi, const vector<ll>& prv,
		vector<ll>& cur, const F& C) {
	if (l > r) return;
	int m = (l + r) / 2, best = lo;
	cur[m] = LLONG_MAX;
	rep(k, lo, min(m - 1, hi) + 1) {
		ll v = prv[k] + C(k, m);
		if (v < cur[m]) cur[m] = v, best = k;
	}
	dnc(l, m - 1, lo, best, prv, cur, C);
	dnc(m + 1, r, best, hi, prv, cur, C);
}
