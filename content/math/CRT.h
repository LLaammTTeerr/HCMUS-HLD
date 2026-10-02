/**
 * Author: HCMUS-HLD
 * Description: euclid(a, b, x, y) returns $g = \gcd(a, b)$ and
 * sets $ax + by = g$. crt solves $x \equiv a \pmod m$,
 * $x \equiv b \pmod n$ for any moduli (not necessarily coprime):
 * returns x in $[0, \mathrm{lcm}(m, n))$, or -1 if no solution.
 * Needs $0 \le a < m$, $0 \le b < n$, lcm $< 2^{63}$. For many
 * equations fold: a = crt(a, m, b, n), m = lcm(m, n).
 * Time: O(\log \min(m, n))
 */
#pragma once

ll euclid(ll a, ll b, ll &x, ll &y) {
	if (!b) return x = 1, y = 0, a;
	ll d = euclid(b, a % b, y, x);
	return y -= a / b * x, d;
}

ll crt(ll a, ll m, ll b, ll n) {
	ll x, y, g = euclid(m, n, x, y), l = m / g * n;
	if ((b - a) % g) return -1;
	__int128 t = (__int128)((b - a) / g) * x % (n / g);
	return (ll)(((a + m * t) % l + l) % l);
}
