#include "../utilities/template.h"
#include "../../content/math/PolySeries.h"

ll md(ll x) { return (x % MOD + MOD) % MOD; }

int main() {
	mt19937 rng(22);
	rep(it, 0, 300) {
		int n = int(rng() % 40) + 1, la = int(rng() % 45) + 1;
		poly a(la);
		for (ll& x : a) x = rng() % MOD;
		if (it % 5 == 0) for (ll& x : a) x = rng() % 3; // small
		// inv: a * b = 1 mod x^n
		poly a1 = a;
		if (!a1[0]) a1[0] = 1;
		poly b = inv(a1, n);
		assert(sz(b) == n);
		poly p = convolution(a1, b);
		rep(i, 0, n) assert(p[i] == (i == 0));
		// log: n * l_n = sum k a_k * ... ; check l' * a = a' brute
		poly a2 = a1;
		a2[0] = 1;
		poly l = log(a2, n);
		assert(sz(l) == n && l[0] == 0);
		rep(m, 0, n - 1) { // coefficient m of l' * a2 == (m+1) a2[m+1]
			ll s = 0;
			rep(k, 0, m + 1) if (m - k < sz(a2))
				s = md(s + l[k + 1] * (k + 1) % MOD * a2[m - k]);
			assert(s == (m + 1 < sz(a2) ? a2[m + 1] * (m + 1) % MOD : 0));
		}
		// exp brute: n e_n = sum_{k=1}^{n} k a_k e_{n-k}
		poly a3 = a;
		a3[0] = 0;
		poly e = exp(a3, n), eb(n);
		eb[0] = 1;
		rep(m, 1, n) {
			ll s = 0;
			rep(k, 1, m + 1) if (k < sz(a3))
				s = md(s + k * a3[k] % MOD * eb[m - k]);
			eb[m] = s * mod_pow(m, MOD - 2) % MOD;
		}
		assert(e == eb);
		// exp(log(a)) = a
		poly back = exp(l, n);
		rep(i, 0, n) assert(back[i] == (i < sz(a2) ? a2[i] : 0));
	}
	poly big(1 << 18); // speed
	for (ll& x : big) x = rng() % MOD;
	big[0] = 0;
	assert(sz(exp(big, 1 << 18)) == 1 << 18);
	cout << "Tests passed!" << endl;
}
