/**
 * Author: HCMUS-HLD
 * Description: Bernoulli numbers $B_0..B_K$ with $B_1 = +\frac12$
 * (the $B^+$ convention; negate B[1] for $B^-$), and
 * powerSum $= \sum_{i=1}^{n} i^k = \frac{1}{k+1} \sum_{j=0}^{k}
 * \binom{k+1}{j} B_j n^{k+1-j}$. Z is a modular type
 * (MInt<P> from ModInt.h) with prime $P > K + 1$.
 * Usage: auto B = bernoulli<Z>(K); Z s = powerSum(n, k, B); // k<=K
 * Time: O(K^2) for bernoulli, O(k \log P) for powerSum
 */
#pragma once

template<class Z> vector<Z> bernoulli(int K) {
	vector<Z> B(K + 1), f(K + 2, 1), fi(K + 2);
	rep(i,1,K+2) f[i] = f[i-1] * Z(i);
	fi[K+1] = Z(1) / f[K+1];
	for (int i = K + 1; i; i--) fi[i-1] = fi[i] * Z(i);
	B[0] = 1;
	rep(m,1,K+1) {
		Z s = 0;
		rep(j,0,m) s += f[m+1] * fi[j] * fi[m+1-j] * B[j];
		B[m] = Z(0) - s / Z(m + 1);
	}
	if (K) B[1] = Z(0) - B[1];
	return B;
}

template<class Z> Z powerSum(ll n, int k, const vector<Z>& B) {
	vector<Z> pw(k + 2, 1);
	rep(i,1,k+2) pw[i] = pw[i-1] * Z(n);
	Z res = 0, c = 1; // c = C(k+1, j)
	rep(j,0,k+1) {
		res += c * B[j] * pw[k+1-j];
		c = c * Z(k + 1 - j) / Z(j + 1);
	}
	return res / Z(k + 1);
}
