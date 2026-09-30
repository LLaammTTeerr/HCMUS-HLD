/**
 * Author: HCMUS-HLD
 * Description: Given $p[i] = f(i)$ for $i \in [0, n)$ with $\deg f < n$,
 * returns $f(x)$ for any integer x (negative or huge OK). Z is a
 * mod-$P$ int type (Z(ll) reducing negatives, + - * / +=), prime $P > n$.
 * Usage: lagrange<Z>(p, x)
 * Time: O(n \log P)
 */
#pragma once

template<class Z> Z lagrange(const vector<Z>& p, ll x) {
	int n = sz(p);
	vector<Z> pre(n + 1, 1), suf(n + 1, 1), fi(n, 1);
	rep(i,0,n) pre[i+1] = pre[i] * Z(x - i);
	for (int i = n; i--;) suf[i] = suf[i+1] * Z(x - i);
	rep(i,1,n) fi[i] = fi[i-1] * Z(i);
	Z ans = 0;
	rep(i,0,n) {
		Z t = p[i] * pre[i] * suf[i+1] / (fi[i] * fi[n-1-i]);
		ans += (n - 1 - i) % 2 ? Z(0) - t : t;
	}
	return ans;
}
