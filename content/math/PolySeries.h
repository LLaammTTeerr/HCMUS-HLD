/**
 * Author: HCMUS-HLD
 * Description: Power series mod 998244353, first n terms.
 * Coefficients in $[0, MOD)$. inv needs $a_0 \ne 0$, log needs
 * $a_0 = 1$, exp needs $a_0 = 0$. Power: $a^k = \exp(k \log a)$
 * when $a_0 = 1$.
 * Time: O(N \log N)
 */
#pragma once

#include "NTTMOD.h"

typedef vector<ll> poly;
poly inv(const poly& a, int n) {
	poly b{mod_pow(a[0], MOD - 2)};
	for (int k = 1; k < n; k *= 2) { // b = b(2 - ab)
		poly c(a.begin(), a.begin() + min(sz(a), 2 * k));
		c = convolution(b, c), c.resize(2 * k);
		for (ll& x : c) x = (MOD - x) % MOD;
		c[0] = (c[0] + 2) % MOD;
		b = convolution(b, c), b.resize(2 * k);
	}
	b.resize(n);
	return b;
}
poly log(const poly& a, int n) { // integral of a'/a
	poly d(max(sz(a) - 1, 1));
	rep(i, 1, sz(a)) d[i - 1] = a[i] * i % MOD;
	d = convolution(d, inv(a, n)), d.resize(n);
	for (int i = n - 1; i > 0; i--)
		d[i] = d[i - 1] * mod_pow(i, MOD - 2) % MOD;
	if (n) d[0] = 0;
	return d;
}
poly exp(const poly& a, int n) {
	poly b{1};
	for (int k = 1; k < n; k *= 2) { // b = b(1 - log b + a)
		poly c = log(b, 2 * k);
		rep(i, 0, 2 * k)
			c[i] = ((i < sz(a) ? a[i] : 0) - c[i] + MOD) % MOD;
		c[0] = (c[0] + 1) % MOD;
		b = convolution(b, c), b.resize(2 * k);
	}
	b.resize(n);
	return b;
}
