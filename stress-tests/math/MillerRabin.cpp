#include "../utilities/template.h"
#include "../../content/math/MillerRabin.h"

int main() {
	const int N = 2000000;
	vector<bool> comp(N + 1);
	comp[0] = comp[1] = 1;
	for (int i = 2; (ll)i * i <= N; ++i) if (!comp[i])
		for (int j = i * i; j <= N; j += i) comp[j] = 1;
	rep(n,0,N+1) assert(isPrime(n) == !comp[n]);
	// strong pseudoprimes / Carmichael numbers
	for (ull n : {2047ULL, 3215031751ULL, 4759123141ULL, 1122004669633ULL,
			2152302898747ULL, 3474749660383ULL, 341550071728321ULL,
			3825123056546413051ULL, 561ULL,
			41041ULL, 9080191ULL, 25326001ULL})
		if (n > 1) assert(!isPrime(n));
	// known primes near powers of two
	for (ull p : {4294967291ULL, 4294967311ULL, 1000000007ULL, 998244353ULL,
			9223372036854775783ULL, 18446744073709551557ULL, 2305843009213693951ULL})
		assert(isPrime(p));
	// products of two large primes
	assert(!isPrime(4294967291ULL * 4294967279ULL));
	assert(!isPrime(1000000007ULL * 998244353ULL));
	// random 64-bit odd n vs trial division by small primes (only composites detectable)
	mt19937_64 rng(12);
	rep(it,0,200000) {
		ull n = rng() | 1;
		bool small = false;
		for (ull p = 3; p < 1000; p += 2) if (n % p == 0) { small = true; break; }
		if (small) assert(!isPrime(n));
	}
	cout << "Tests passed!" << endl;
}
