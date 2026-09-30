/**
 * Author: HCMUS-HLD
 * Description: Convolution modulo MOD = 998244353 (= 119 * 2^{23} + 1,
 * primitive root 3). Inputs may be any ll; they are reduced mod MOD.
 * For other NTT primes $c \cdot 2^k + 1$ change MOD and G.
 * Usage: convolution({1, 2}, {3, 4}) // {3, 10, 8}
 * Time: O(N \log N)
 * Status: Library Checker convolution\_mod
 */
#pragma once

const ll MOD = 998244353, G = 3;
ll mod_pow(ll a, ll e) {
	ll r = 1;
	for (a %= MOD; e; e >>= 1, a = a * a % MOD)
		if (e & 1) r = r * a % MOD;
	return r;
}

void ntt(vector<ll>& a, bool invert) {
	int n = sz(a);
	for (int i = 1, j = 0; i < n; i++) {
		int bit = n >> 1;
		for (; j & bit; bit >>= 1) j ^= bit;
		j ^= bit;
		if (i < j) swap(a[i], a[j]);
	}
	for (int len = 2; len <= n; len <<= 1) {
		ll wlen = mod_pow(G, (MOD - 1) / len);
		if (invert) wlen = mod_pow(wlen, MOD - 2);
		for (int i = 0; i < n; i += len) {
			ll w = 1;
			rep(j,0,len/2) {
				ll u = a[i+j], v = a[i+j+len/2] * w % MOD;
				a[i+j] = u + v < MOD ? u + v : u + v - MOD;
				a[i+j+len/2] = u - v >= 0 ? u - v : u - v + MOD;
				w = w * wlen % MOD;
			}
		}
	}
	if (invert) {
		ll n_inv = mod_pow(n, MOD - 2);
		for (ll &x : a) x = x * n_inv % MOD;
	}
}

vector<ll> convolution(const vector<ll>& a, const vector<ll>& b) {
	if (!sz(a) || !sz(b)) return {};
	vector<ll> fa(all(a)), fb(all(b));
	for (ll &x : fa) x = (x % MOD + MOD) % MOD;
	for (ll &x : fb) x = (x % MOD + MOD) % MOD;
	int n = 1, need = sz(a) + sz(b) - 1;
	while (n < need) n <<= 1;
	fa.resize(n), fb.resize(n);
	ntt(fa, false), ntt(fb, false);
	rep(i,0,n) fa[i] = fa[i] * fb[i] % MOD;
	ntt(fa, true), fa.resize(need);
	return fa;
}
