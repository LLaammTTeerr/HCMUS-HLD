#include "../utilities/template.h"
#include "../../content/flow-graph-matching/StoerWagner.h"

mt19937 rng(6);
int rnd(int a, int b) { return a + (int)(rng() % (b - a + 1)); }

int main() {
	rep(it, 0, 20000) {
		int n = rnd(2, 8);
		vector<vector<ll>> w(n, vector<ll>(n));
		rep(i, 0, n) rep(j, i + 1, n) if (rng() % 2)
			w[i][j] = w[j][i] = it % 4 ? rnd(0, 10) : rnd(0, 1 << 30);
		auto cut = [&](int mk) {
			ll c = 0;
			rep(i, 0, n) rep(j, 0, n) if ((mk >> i & 1) && !(mk >> j & 1))
				c += w[i][j];
			return c;
		};
		ll best = LLONG_MAX;
		rep(mk, 1, (1 << n) - 1) best = min(best, cut(mk));
		auto [val, side] = stoerWagner(w);
		assert(val == best);
		int mk = 0;
		for (int v : side) { assert(v >= 0 && v < n && !(mk >> v & 1)); mk |= 1 << v; }
		assert(mk != 0 && mk != (1 << n) - 1);
		assert(cut(mk) == best);
	}
	auto [v1, s1] = stoerWagner({{0}});
	assert(v1 == LLONG_MAX && s1.empty());
	cout << "Tests passed!" << endl;
}
