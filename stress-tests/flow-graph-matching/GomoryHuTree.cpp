#include "../utilities/template.h"
#include "../../content/flow-graph-matching/GomoryHuTree.h"

mt19937 rng(7);
int rnd(int a, int b) { return a + (int)(rng() % (b - a + 1)); }

int main() {
	rep(it, 0, 5000) {
		int n = rnd(1, 7), m = rnd(0, 12);
		vector<Edge> ed;
		rep(i, 0, m) {
			int u = rnd(0, n - 1), v = rnd(0, n - 1);
			if (u != v) ed.push_back({u, v, rnd(0, 10)});
		}
		auto tree = gomoryHu(n, ed);
		assert(sz(tree) == n - 1);
		vector<vector<pair<int, ll>>> T(n);
		for (auto [a, b, w] : tree)
			T[a].push_back({(int)b, w}), T[b].push_back({(int)a, w});
		rep(s, 0, n) {
			// min edge on tree path from s to every vertex
			vector<ll> mn(n, -1); mn[s] = LLONG_MAX;
			vi st = {s};
			while (sz(st)) {
				int u = st.back(); st.pop_back();
				for (auto [v, w] : T[u]) if (mn[v] == -1)
					mn[v] = min(mn[u], w), st.push_back(v);
			}
			rep(t, s + 1, n) {
				ll best = LLONG_MAX;
				rep(mk, 0, 1 << n) if ((mk >> s & 1) && !(mk >> t & 1)) {
					ll c = 0;
					for (auto [u, v, w] : ed)
						if ((mk >> u & 1) != (mk >> v & 1)) c += w;
					best = min(best, c);
				}
				assert(mn[t] == best);
			}
		}
	}
	cout << "Tests passed!" << endl;
}
