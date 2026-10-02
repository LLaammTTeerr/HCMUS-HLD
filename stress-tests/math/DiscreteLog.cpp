#include "../utilities/template.h"
#include "../../content/math/DiscreteLog.h"

ll brute(ll a, ll b, ll m) {
	ll e = 1 % m;
	rep(x, 0, 3 * m + 5) {
		if (e == b % m) return x;
		e = e * a % m;
	}
	return -1;
}

int main() {
	rep(m, 1, 130) rep(a, 0, m) rep(b, 0, m)
		assert(modLog(a, b, m) == brute(a, b, m));
	mt19937_64 rng(14);
	rep(it, 0, 300) { // big m: check a^x = b, and x minimal for small x
		ll m = (ll)(rng() % 1000000000) + 1;
		ll a = (ll)(rng() % (unsigned long long)m);
		ll x0 = (ll)(rng() % 1000000), b = 1 % m, e = a;
		for (ll k = x0; k; k /= 2, e = e * e % m)
			if (k & 1) b = b * e % m;
		ll x = modLog(a, b, m);
		assert(0 <= x && x <= x0);
		ll c = 1 % m;
		e = a;
		for (ll k = x; k; k /= 2, e = e * e % m)
			if (k & 1) c = c * e % m;
		assert(c == b);
	}
	cout << "Tests passed!" << endl;
}
