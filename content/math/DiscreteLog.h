/**
 * Author: HCMUS-HLD
 * Description: Smallest $x \ge 0$ with $a^x \equiv b \pmod m$, or
 * -1. Any $m \ge 1$ (gcd(a, m) may be $> 1$). Baby-step
 * giant-step; products need $m^2 < 2^{63}$. Order of a
 * when gcd(a, m) = 1: 1 + modLog(a, $a^{-1}$, m).
 * Time: O(\sqrt m)
 */
#pragma once

ll modLog(ll a, ll b, ll m) {
	a %= m, b %= m;
	ll k = 1 % m, add = 0, g;
	while ((g = __gcd(a, m)) > 1) {
		if (b == k) return add;
		if (b % g) return -1;
		b /= g, m /= g, add++;
		k = k * (a / g) % m;
	}
	ll n = (ll)sqrt((double)m) + 1, an = 1;
	rep(i, 0, n) an = an * a % m;
	unordered_map<ll, ll> vals;
	for (ll q = 0, cur = b; q <= n; q++)
		vals[cur] = q, cur = cur * a % m;
	for (ll p = 1, cur = k; p <= n; p++) {
		cur = cur * an % m;
		if (vals.count(cur)) return n * p - vals[cur] + add;
	}
	return -1;
}
