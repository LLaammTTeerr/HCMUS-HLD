/**
 * Author: HCMUS-HLD
 * Description: Prime factorization of $1 \le n < 2^{63}$ (sorted, with
 * multiplicity) using Pollard rho with Brent's cycle detection
 * and batched gcds. factorize(1) = \{\}.
 * Time: O(n^{1/4} \log^2 n)
 * Status: Library Checker factorize
 */
#pragma once

#include "MillerRabin.h"

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

void pollard(ll n, vector<ll> &ans) {
	if (n == 1) return;
	if (isPrime(n)) { ans.push_back(n); return; }
	while (1) {
		ll c = 1 + rng() % (n - 1);
		auto f = [&](ll y) {
			ull r = mulmod(y, y, n) + c;
			return ll(r >= (ull)n ? r - n : r);
		};
		ll y = 2, g = 1;
		int B = 100, len = 1;
		while (1) {
			ll z = y, zs = -1;
			rep(i,0,len) z = f(z);
			int lft = len;
			while (g == 1 && lft > 1) {
				zs = z;
				ll p = 1;
				for (int i = 0; i < B && i < lft; ++i) {
					p = mulmod(p, abs(z - y), n);
					z = f(z);
				}
				g = __gcd(p, n);
				lft -= B;
			}
			if (g == 1) { y = z; len <<= 1; continue; }
			if (g == n) {
				g = 1, z = zs;
				while (g == 1) g = __gcd(abs(z - y), n), z = f(z);
			}
			if (g == n) break;
			pollard(g, ans), pollard(n / g, ans);
			return;
		}
	}
}

vector<ll> factorize(ll n) {
	vector<ll> ans;
	for (ll p : {2, 3, 5, 7, 11, 13, 17, 19})
		while (n % p == 0) n /= p, ans.push_back(p);
	pollard(n, ans);
	sort(all(ans));
	return ans;
}
