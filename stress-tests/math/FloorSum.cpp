#include "../utilities/template.h"
#include "../../content/math/FloorSum.h"

ll fl(ll p, ll q) { return p / q - (p % q && (p < 0) != (q < 0)); }

typedef unsigned long long ull;
ull acl(ull n, ull m, ull a, ull b) { // AtCoder Library, a, b in [0, m)
	ull ans = 0;
	while (true) {
		if (a >= m) ans += n * (n - 1) / 2 * (a / m), a %= m;
		if (b >= m) ans += n * (b / m), b %= m;
		ull y = a * n + b;
		if (y < m) return ans;
		n = y / m, b = y % m, swap(m, a);
	}
}

int main() {
	mt19937_64 rng(2);
	rep(n, 0, 15) rep(m, 1, 12) rep(a, -25, 26) rep(b, -25, 26) {
		ll s = 0;
		rep(i, 0, n) s += fl((ll)a * i + b, m);
		assert(floorSum(n, m, a, b) == s);
	}
	rep(it, 0, 1000) { // n up to 1e5, any sign
		ll n = (ll)(rng() % 100000), m = (ll)(rng() % 2000000000) + 1;
		ll a = (ll)(rng() % 2000000001) - 1000000000;
		ll b = (ll)(rng() % 2000000001) - 1000000000;
		if (it % 3 == 0) a = (ll)(rng() % 20000000001LL) - 10000000000LL;
		__int128 s = 0;
		rep(i, 0, n) s += fl(a * i + b, m);
		assert(floorSum(n, m, a, b) == (ll)s);
	}
	rep(it, 0, 100000) { // n, m up to 2e9
		ll n = (ll)(rng() % 2000000000) + 1, m = (ll)(rng() % 2000000000) + 1;
		ll a = (ll)(rng() % (ull)m), b = (ll)(rng() % (ull)m);
		assert(floorSum(n, m, a, b) == (ll)acl(n, m, a, b));
	}
	cout << "Tests passed!" << endl;
}
