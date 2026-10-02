/**
 * Author: HCMUS-HLD
 * Description: Determinant of a square matrix modulo any m
 * (not necessarily prime), by Euclid-style row elimination.
 * Destroys a. Needs $m^2 < 2^{63}$. Spanning tree count:
 * see Kirchhoff in Combinatorial.
 * Time: O(N^3 \log m)
 */
#pragma once

ll det(vector<vector<ll>>& a, ll m) {
	int n = sz(a);
	ll r = 1;
	for (auto& v : a) for (ll& x : v) x %= m;
	rep(i, 0, n) {
		rep(j, i + 1, n) while (a[j][i]) { // gcd(a[i][i], a[j][i])
			ll t = a[i][i] / a[j][i];
			rep(k, i, n) a[i][k] = (a[i][k] - t * a[j][k]) % m;
			swap(a[i], a[j]), r = -r;
		}
		r = r * a[i][i] % m;
		if (!r) return 0;
	}
	return (r + m) % m;
}
