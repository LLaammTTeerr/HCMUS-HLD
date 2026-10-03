#include "../utilities/template.h"
#include "../../content/graph/DominatorTree.h"

int main() {
	mt19937 rng(3);
	rep(it, 0, 20000) {
		int n = int(rng() % 9) + 1, m = int(rng() % 25), s = int(rng() % n);
		vector<vi> g(n);
		rep(i, 0, m) g[rng() % n].push_back(int(rng() % n));
		auto reach = [&](int ban) { // reachable from s avoiding ban
			vector<bool> v(n);
			if (s == ban) return v;
			vi st{s};
			v[s] = 1;
			while (sz(st)) {
				int u = st.back();
				st.pop_back();
				for (int w : g[u])
					if (w != ban && !v[w]) v[w] = 1, st.push_back(w);
			}
			return v;
		};
		auto r0 = reach(-1);
		vector<vector<bool>> D(n, vector<bool>(n)); // d dominates v
		rep(d, 0, n) {
			auto r = reach(d);
			rep(v, 0, n) D[d][v] = r0[v] && (v == d || !r[v]);
		}
		vi idom = dominators(g, s);
		rep(v, 0, n) {
			if (!r0[v]) { assert(idom[v] == -1); continue; }
			if (v == s) { assert(idom[v] == s); continue; }
			int d = idom[v];
			assert(0 <= d && d != v && D[d][v]);
			rep(e, 0, n) if (e != v && D[e][v]) assert(D[e][d]);
		}
	}
	int n = 200000; // long path: deep recursion
	vector<vi> g(n);
	rep(i, 0, n - 1) g[i].push_back(i + 1);
	vi idom = dominators(g, 0);
	rep(i, 1, n) assert(idom[i] == i - 1);
	cout << "Tests passed!" << endl;
}
