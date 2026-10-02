#include "../utilities/template.h"
#include "../../content/graph/TarjanSCC.h"

int main() {
	mt19937 rng(11);
	rep(it, 0, 20000) {
		int n = int(rng() % 9) + 1, m = int(rng() % 20);
		SCC s(n);
		vector<vector<bool>> r(n, vector<bool>(n));
		vector<pii> es;
		rep(i, 0, n) r[i][i] = 1;
		rep(i, 0, m) {
			int u = int(rng() % n), v = int(rng() % n);
			s.add(u, v), r[u][v] = 1, es.push_back({u, v});
		}
		rep(k, 0, n) rep(i, 0, n) rep(j, 0, n)
			if (r[i][k] && r[k][j]) r[i][j] = 1;
		s.run();
		set<int> ids;
		rep(u, 0, n) {
			assert(0 <= s.comp[u] && s.comp[u] < s.nc);
			ids.insert(s.comp[u]);
			rep(v, 0, n)
				assert((s.comp[u] == s.comp[v]) == (r[u][v] && r[v][u]));
		}
		assert(sz(ids) == s.nc);
		for (auto [u, v] : es) assert(s.comp[u] >= s.comp[v]);
	}
	SCC big(200000); // long cycle: deep recursion
	rep(i, 0, 200000) big.add(i, (i + 1) % 200000);
	big.run();
	assert(big.nc == 1);
	cout << "Tests passed!" << endl;
}
