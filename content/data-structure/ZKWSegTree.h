/**
 * Author: HCMUS-HLD
 * Description: Bottom-up (zkw) segment tree, 0-indexed. Point
 * assign, query over $[l, r)$. f may be any associative function
 * (need not be commutative); unit is its identity.
 * Usage: ZKW st(n); st.update(i, v); st.query(l, r + 1);
 * ZKW st(a) builds from a vector in $O(n)$.
 * Time: O(\log N)
 */
#pragma once

struct ZKW {
	typedef ll T;
	static constexpr T unit = 0;
	T f(T a, T b) { return a + b; } // (any associative fn)
	vector<T> s; int n;
	ZKW(int n = 0, T def = unit) : s(2 * n, def), n(n) {
		for (int i = n; --i > 0;) s[i] = f(s[2 * i], s[2 * i + 1]);
	}
	ZKW(const vector<T>& a) : ZKW(sz(a)) {
		copy(all(a), s.begin() + n);
		for (int i = n; --i > 0;) s[i] = f(s[2 * i], s[2 * i + 1]);
	}
	void update(int p, T v) {
		for (s[p += n] = v; p /= 2;) s[p] = f(s[2 * p], s[2 * p + 1]);
	}
	T query(int l, int r) { // [l, r)
		T ra = unit, rb = unit;
		for (l += n, r += n; l < r; l /= 2, r /= 2) {
			if (l & 1) ra = f(ra, s[l++]);
			if (r & 1) rb = f(s[--r], rb);
		}
		return f(ra, rb);
	}
};
