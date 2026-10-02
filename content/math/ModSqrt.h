/**
 * Author: HCMUS-HLD
 * Description: Tonelli-Shanks. Returns x with $x^2 \equiv a
 * \pmod p$ (the other root is p - x), or -1 if none. p must be
 * prime, $p^2 < 2^{63}$.
 * Time: O(\log^2 p)
 */
#pragma once

ll modSqrt(ll a, ll p) {
	auto pw = [&](ll b, ll e) {
		ll r = 1;
		for (b %= p; e; e /= 2, b = b * b % p)
			if (e & 1) r = r * b % p;
		return r;
	};
	a %= p; if (a < 0) a += p;
	if (a == 0 || p == 2) return a;
	if (pw(a, (p - 1) / 2) != 1) return -1;
	if (p % 4 == 3) return pw(a, (p + 1) / 4);
	ll s = p - 1, z = 2;
	int r = 0, m;
	while (s % 2 == 0) r++, s /= 2;
	while (pw(z, (p - 1) / 2) != p - 1) z++; // non-residue
	ll x = pw(a, (s + 1) / 2), b = pw(a, s), g = pw(z, s);
	for (;; r = m) {
		ll t = b;
		for (m = 0; m < r && t != 1; m++) t = t * t % p;
		if (m == 0) return x;
		ll gs = pw(g, 1LL << (r - m - 1));
		g = gs * gs % p, x = x * gs % p, b = b * g % p;
	}
}
