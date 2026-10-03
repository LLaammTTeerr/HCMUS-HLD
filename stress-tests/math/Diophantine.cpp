#include "../utilities/template.h"
#include "../../content/math/Diophantine.h"

int main() {
	mt19937_64 rng(1);
	rep(a, -12, 13) rep(b, -12, 13) rep(c, -30, 31) {
		if (!a || !b) continue;
		ll x, y, g;
		bool ok = dioph(a, b, c, x, y, g);
		assert(g == __gcd(abs(a), abs(b)) && ok == (c % g == 0));
		if (!ok) continue;
		assert(a * x + b * y == c && 0 <= x && x < abs(b / g));
		rep(lx, -6, 4) rep(ly, -6, 4) { // boxes 6 x 5
			ll rx = lx + 5, ry = ly + 4, cnt = 0;
			rep(X, lx, rx + 1) rep(Y, ly, ry + 1) cnt += a * X + b * Y == c;
			assert(countSol(a, b, c, lx, rx, ly, ry) == cnt);
		}
	}
	auto R = [&](ll lim) { return (ll)(rng() % (2 * lim + 1)) - lim; };
	rep(it, 0, 200000) { // big values, half of them with a big gcd
		ll a = R(ll(1e18)), b = R(ll(1e18)), c = R(ll(1e18));
		if (it & 1) {
			ll k = (ll)(rng() % 1000000) + 1;
			a = R(ll(1e12)) * k, b = R(ll(1e12)) * k, c = R(ll(1e12)) * k;
		}
		if (!a || !b) continue;
		ll x, y, g;
		if (!dioph(a, b, c, x, y, g)) { assert(c % g); continue; }
		assert((__int128)a * x + (__int128)b * y == c);
		assert(0 <= x && x < abs(b / g));
	}
	cout << "Tests passed!" << endl;
}
