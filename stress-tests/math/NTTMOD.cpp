#include "../utilities/template.h"
#include "../../content/math/NTTMOD.h"

vector<ll> naive(const vector<ll>& a, const vector<ll>& b) {
	if (a.empty() || b.empty()) return {};
	vector<ll> r(sz(a) + sz(b) - 1);
	rep(i,0,sz(a)) rep(j,0,sz(b))
		r[i + j] = (r[i + j] + (a[i] % MOD + MOD) % MOD * ((b[j] % MOD + MOD) % MOD)) % MOD;
	return r;
}

int main() {
	mt19937_64 rng(8);
	assert(convolution({}, {1}).empty());
	assert((convolution({1, 2}, {3, 4}) == vector<ll>{3, 10, 8}));
	rep(it,0,1500) {
		int n = (int)(rng() % 70), m = (int)(rng() % 70);
		vector<ll> a(n), b(m);
		// any ll input is reduced mod MOD (negatives included)
		for (auto& x : a) x = (ll)rng() / (it % 2 ? 1 : 1000000);
		for (auto& x : b) x = (ll)rng() / (it % 2 ? 1 : 1000000);
		assert(convolution(a, b) == naive(a, b));
	}
	int n = 1 << 18;
	vector<ll> a(n, MOD - 1), b(n, MOD - 1);
	vector<ll> r = convolution(a, b);
	for (int k : {0, 5, n - 1, n, 2 * n - 2})
		assert(r[k] == (ll)(min(k, 2 * n - 2 - k) + 1) % MOD);
	cout << "Tests passed!" << endl;
}
