#include "../utilities/template.h"
#include "../../content/math/PollardRho.h"

int main() {
	assert(factorize(1).empty());
	rep(n,1,200000) {
		vector<ll> f = factorize(n), g;
		ll m = n;
		for (ll p = 2; p * p <= m; ++p) while (m % p == 0) g.push_back(p), m /= p;
		if (m > 1) g.push_back(m);
		assert(f == g);
	}
	mt19937_64 rng(13);
	auto check = [&](ll n) {
		vector<ll> f = factorize(n);
		assert(is_sorted(all(f)));
		__int128 prod = 1;
		for (ll p : f) assert(isPrime(p)), prod *= p;
		assert(prod == n);
	};
	rep(it,0,2000) check((ll)(rng() >> 1) | 1);
	rep(it,0,300) check((ll)(rng() >> 1));
	// hard cases: semiprimes with ~31-bit factors, prime powers, max values
	check(4294967291LL * 2147483647LL);
	check(3037000493LL * 3037000453LL);
	check(9223372036854775783LL);
	check(LLONG_MAX);
	check(1LL << 62);
	check(998244353LL * 998244353LL);
	check(2147483647LL * 2147483647LL);
	cout << "Tests passed!" << endl;
}
