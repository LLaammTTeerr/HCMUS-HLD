/**
 * Author: HCMUS-HLD
 * Description: Deterministic Miller-Rabin for all $n < 2^{64}$.
 * Bases $\{2,7,61\}$ suffice for $n < 2^{32}$, the 7 bases below for
 * $n < 2^{64}$. Other known sets: $n < 2047$: $\{2\}$;
 * $n < 9\,080\,191$: $\{31,73\}$;
 * $n < 3\,474\,749\,660\,383$: $\{2,3,5,7,11,13\}$;
 * $n < 3.3\cdot 10^{24}$: first 13 primes.
 * Time: O(A \log N), A = number of bases
 * Status: Library Checker primality\_test
 */
#pragma once

typedef unsigned long long ull;
ull mulmod(ull a, ull b, ull M) { return (__uint128_t)a * b % M; }
ull powermod(ull a, ull e, ull M) {
	ull r = 1;
	for (a %= M; e; e >>= 1, a = mulmod(a, a, M))
		if (e & 1) r = mulmod(r, a, M);
	return r;
}

bool check_miller(int s, ull d, ull n, ull a) {
	if (a % n == 0) return true;
	ull p = powermod(a, d, n);
	if (p == 1) return true;
	for (; s > 0; --s) {
		if (p == n - 1) return true;
		p = mulmod(p, p, n);
		if (p == 1) return false;
	}
	return false;
}

bool isPrime(ull n) {
	for (ull p : {2, 3, 5, 7}) if (n % p == 0) return n == p;
	if (n < 121) return n > 1;
	int s = __builtin_ctzll(n - 1);
	ull d = (n - 1) >> s;
	if (n < (1ULL << 32)) {
		for (ull a : {2, 7, 61})
			if (!check_miller(s, d, n, a)) return false;
	} else {
		for (ull a : {2, 325, 9375, 28178, 450775, 9780504,
				1795265022})
			if (!check_miller(s, d, n, a)) return false;
	}
	return true;
}
