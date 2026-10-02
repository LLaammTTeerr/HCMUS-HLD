#include "../utilities/template.h"
#include "../../content/math/CRT.h"

int main() {
	mt19937_64 rng(13);
	rep(m, 1, 40) rep(n, 1, 40) rep(a, 0, m) rep(b, 0, n) {
		ll l = m / __gcd(m, n) * n, want = -1;
		rep(x, 0, l) if (x % m == a && x % n == b) { want = x; break; }
		assert(crt(a, m, b, n) == want);
	}
	rep(m, 1, 60) rep(n, 1, 60) { // euclid on its own
		ll x, y, g = euclid(m, n, x, y);
		assert(g == __gcd(m, n) && m * x + n * y == g);
	}
	rep(it, 0, 100000) { // big moduli, lcm up to about 4e18
		ll g = (ll)(rng() % 1000) + 1;
		ll m = g * (ll)(rng() % 60000000 + 1);
		ll n = g * (ll)(rng() % 60000000 + 1);
		ll l = m / __gcd(m, n) * n;
		ll x = (ll)(rng() % (unsigned long long)l);
		ll r = crt(x % m, m, x % n, n);
		assert(r == x);
		if (__gcd(m, n) > 1) // b shifted by 1 is unsolvable
			assert(crt(x % m, m, (x + 1) % n, n) == -1);
	}
	cout << "Tests passed!" << endl;
}
