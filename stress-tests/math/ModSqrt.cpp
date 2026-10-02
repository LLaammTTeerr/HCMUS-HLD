#include "../utilities/template.h"
#include "../../content/math/ModSqrt.h"

bool prime(ll p) {
	if (p < 2) return 0;
	for (ll d = 2; d * d <= p; d++) if (p % d == 0) return 0;
	return 1;
}

int main() {
	rep(p, 2, 1200) if (prime(p)) {
		vector<bool> sq(p);
		rep(x, 0, p) sq[(ll)x * x % p] = 1;
		rep(a, -p, 2 * p) {
			ll r = modSqrt(a, p), a0 = ((a % p) + p) % p;
			if (!sq[a0]) assert(r == -1);
			else assert(0 <= r && r < p && r * r % p == a0);
		}
	}
	mt19937_64 rng(15);
	// 998244353 = 119 * 2^23 + 1 exercises the full loop
	for (ll p : {998244353LL, 1000000007LL, 1000000009LL,
			 2013265921LL, 469762049LL})
		rep(it, 0, 20000) {
			ll x = (ll)(rng() % (unsigned long long)p);
			ll a = x * x % p, r = modSqrt(a, p);
			assert(r * r % p == a);
			ll y = (ll)(rng() % (unsigned long long)p);
			ll ry = modSqrt(y, p);
			assert(ry == -1 || ry * ry % p == y);
		}
	cout << "Tests passed!" << endl;
}
