#include "../utilities/template.h"
#include "../../content/math/LinearSieve.h"

int main() {
	linearSieve();
	rep(n,1,30000) {
		int m = n, mu = 1, d = 1, ph = n, e0 = 0, first = 1;
		for (int p = 2; (ll)p * p <= m; ++p) if (m % p == 0) {
			int e = 0;
			while (m % p == 0) m /= p, e++;
			if (first) e0 = e, first = 0;
			mu = e > 1 ? 0 : -mu; d *= e + 1; ph = ph / p * (p - 1);
		}
		if (m > 1) { if (first) e0 = 1; mu = -mu; d *= 2; ph = ph / m * (m - 1); }
		assert(u[n] == mu && numd[n] == d && phi[n] == ph);
		assert(isComp[n] == (n > 1 && !(d == 2)));
		if (n > 1) assert(cnt[n] == e0);
	}
	// primes list up to MAXN matches a plain sieve
	vector<bool> comp(MAXN);
	int c = 0;
	rep(i,2,MAXN) if (!comp[i]) { assert(primes[c++] == i); for (ll j = (ll)i * i; j < MAXN; j += i) comp[j] = 1; }
	assert(c == sz(primes));
	cout << "Tests passed!" << endl;
}
