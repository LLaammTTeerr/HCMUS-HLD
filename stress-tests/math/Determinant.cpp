#include "../utilities/template.h"
#include "../../content/math/Determinant.h"

ll bruteDet(const vector<vector<ll>>& a, ll m) { // permutation sum
	int n = sz(a);
	vi p(n);
	iota(all(p), 0);
	ll r = 0;
	do {
		ll t = 1;
		rep(i, 0, n) t = t * (a[i][p[i]] % m) % m;
		int inv = 0;
		rep(i, 0, n) rep(j, i + 1, n) inv += p[i] > p[j];
		r = (r + (inv % 2 ? -t : t)) % m;
	} while (next_permutation(all(p)));
	return (r + m) % m;
}

int main() {
	mt19937 rng(23);
	rep(it, 0, 20000) {
		int n = int(rng() % 6) + 1;
		ll m = it % 3 == 0 ? 1000000007 : (ll)(rng() % 100) + 1;
		if (it % 7 == 0) m = 1LL << 30; // composite, large
		vector<vector<ll>> a(n, vector<ll>(n));
		for (auto& v : a) for (ll& x : v)
			x = it % 4 ? (ll)(rng() % 2000000001) - 1000000000 : rng() % 3;
		ll want = bruteDet(a, m);
		assert(det(a, m) == want);
	}
	rep(it, 0, 2000) { // Kirchhoff: count spanning trees by brute
		int n = int(rng() % 5) + 2;
		vector<pii> es;
		rep(i, 0, n) rep(j, i + 1, n) if (rng() % 3) es.push_back({i, j});
		if (rng() % 2 && sz(es)) es.push_back(es[rng() % sz(es)]); // multi-edge
		ll cnt = 0;
		rep(mk, 0, 1 << sz(es)) if (__builtin_popcount(mk) == n - 1) {
			vi par(n);
			iota(all(par), 0);
			function<int(int)> f = [&](int x) { return par[x] == x ? x : par[x] = f(par[x]); };
			int comps = n;
			rep(i, 0, sz(es)) if (mk >> i & 1) {
				int u = f(es[i].first), v = f(es[i].second);
				if (u != v) par[u] = v, comps--;
			}
			cnt += comps == 1;
		}
		vector<vector<ll>> L(n - 1, vector<ll>(n - 1));
		for (auto [u, v] : es) for (auto [x, y] : {pii{u, v}, pii{v, u}})
			if (x < n - 1) {
				L[x][x]++;
				if (y < n - 1) L[x][y]--;
			}
		assert(det(L, 1000000007) == cnt);
	}
	cout << "Tests passed!" << endl;
}
