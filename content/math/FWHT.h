/**
 * Author: HCMUS-HLD
 * Description: Xor-convolution modulo prime MOD: $c_k = \sum_{i \oplus j = k}
 * a_i b_j$. sz(a) must be a power of 2. For AND use (u+v, v) / (u-v, v);
 * for OR use (u, u+v) / (u, v-u), without the final 1/n scaling.
 * Usage: FWHT(a), FWHT(b); a[i] = a[i]*b[i] mod MOD; FWHT(a, true);
 * Time: O(N \log N)
 * Status: Library Checker bitwise\_xor\_convolution
 */
#pragma once

const ll MOD = 998244353;
ll pw(ll b, ll e) {
	ll r = 1;
	for (b %= MOD; e; e >>= 1, b = b * b % MOD)
		if (e & 1) r = r * b % MOD;
	return r;
}
void FWHT(vector<ll>& a, bool inv = false) {
	int n = sz(a);
	for (int k = 1; k < n; k <<= 1)
		for (int i = 0; i < n; i += 2 * k) rep(j,i,i+k) {
			ll u = a[j], v = a[j + k];
			a[j] = (u + v) % MOD, a[j + k] = (u - v + MOD) % MOD;
		}
	if (inv) {
		ll ni = pw(n, MOD - 2);
		for (ll& x : a) x = x * ni % MOD;
	}
}
