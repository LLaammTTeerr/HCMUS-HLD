/**
 * Author: HCMUS-HLD
 * Description: Inverse of a modulo m (m need not be prime) via
 * extended Euclid. Requires $\gcd(a, m) = 1$. Returns x in $[0, m)$.
 * Time: O(\log m)
 */
#pragma once

template<class T> T inverse_modulo(T a, T m) {
	T m0 = m, u = 0, v = 1;
	a %= m; if (a < 0) a += m;
	while (a > 0) {
		T t = m / a;
		m -= t * a; swap(a, m);
		u -= t * v; swap(u, v);
	}
	assert(m == 1);
	return u < 0 ? u + m0 : u;
}
