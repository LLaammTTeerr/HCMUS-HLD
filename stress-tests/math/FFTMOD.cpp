#include "../utilities/template.h"
#include "../../content/math/FFTMOD.h"

const ll M = 1000000007;
vector<ll> naive(const vector<ll>& a, const vector<ll>& b) {
	if (a.empty() || b.empty()) return {};
	vector<ll> r(sz(a) + sz(b) - 1);
	rep(i,0,sz(a)) rep(j,0,sz(b)) r[i + j] = (r[i + j] + a[i] * b[j]) % M;
	return r;
}

int main() {
	mt19937 rng(7);
	assert(convMod<M>({}, {1, 2}).empty());
	rep(it,0,1500) {
		int n = (int)(rng() % 60), m = (int)(rng() % 60);
		vector<ll> a(n), b(m);
		for (auto& x : a) x = it % 3 ? rng() % M : M - 1;
		for (auto& x : b) x = it % 3 ? rng() % M : M - 1;
		assert(convMod<M>(a, b) == naive(a, b));
	}
	// large: check a few coefficients of a max-value product
	int n = 1 << 17;
	vector<ll> a(n, M - 1), b(n, M - 1);
	vector<ll> r = convMod<M>(a, b);
	ll sq = (M - 1) * (M - 1) % M;
	for (int k : {0, 1, 1000, n - 1, n, 2 * n - 2})
		assert(r[k] == sq * (min(k, 2 * n - 2 - k) + 1) % M);
	cout << "Tests passed!" << endl;
}
