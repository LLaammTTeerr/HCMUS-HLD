/**
 * Author: HCMUS-HLD
 * Description: Monotone convex hull trick for MAXIMUM. Lines
 * y = kx + m must be added with non-decreasing k (equal k is
 * fine); query at any x. For minimum, add (-k, -m) in
 * non-increasing k and negate the answer. Faster than
 * DynamicHull when slopes come sorted.
 * Time: O(1) amortized add, O(\log N) query.
 */
#pragma once

struct MonoHull {
	struct L { ll k, m, p; }; // p: first x where L is best
	vector<L> h;

	void add(ll k, ll m) {
		assert(h.empty() || h.back().k <= k);
		if (sz(h) && h.back().k == k) {
			if (h.back().m >= m) return;
			h.pop_back();
		}
		ll p = LLONG_MIN;
		while (sz(h)) { // ceil((m' - m) / (k - k')), k > k'
			ll a = h.back().m - m, b = k - h.back().k;
			p = a / b + (a % b > 0);
			if (p > h.back().p) break;
			h.pop_back(), p = LLONG_MIN;
		}
		h.push_back({k, m, p});
	}

	ll query(ll x) {
		assert(sz(h));
		auto l = *--partition_point(all(h),
			[&](const L& l) { return l.p <= x; });
		return l.k * x + l.m;
	}
};
