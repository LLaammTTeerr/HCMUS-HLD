#include "../utilities/template.h"
#include "../../content/graph/BlockCutTree.h"

mt19937 rng(10);
int rnd(int a, int b) { return a + (int)(rng() % (b - a + 1)); }

int main() {
	rep(it, 0, 20000) {
		int n = rnd(1, 7);
		vector<vi> ids(n + 1, vi(n + 1, -1)); vector<pii> E;
		rep(i, 1, n + 1) rep(j, i + 1, n + 1) if ((int)(rng() % 10) < rnd(2, 7))
			ids[i][j] = ids[j][i] = sz(E), E.push_back({i, j});
		int m = sz(E);
		// brute: edges e ~ f iff they lie on a common simple cycle
		vector<int> dsu(m); iota(all(dsu), 0);
		function<int(int)> f = [&](int x) { return dsu[x] == x ? x : dsu[x] = f(dsu[x]); };
		vi path; vector<bool> on(n + 1);
		function<void(int, int)> dfs = [&](int s, int u) {
			for (int v = s; v <= n; v++) if (ids[u][v] >= 0) {
				if (v == s && sz(path) >= 3) { // cycle path + (u, s)
					int e0 = ids[u][s];
					rep(k, 0, sz(path) - 1) dsu[f(ids[path[k]][path[k + 1]])] = f(e0);
				} else if (v != s && !on[v]) {
					on[v] = 1; path.push_back(v); dfs(s, v);
					path.pop_back(); on[v] = 0;
				}
			}
		};
		rep(s, 1, n + 1) { path = {s}; on[s] = 1; dfs(s, s); on[s] = 0; }
		map<int, set<int>> cls;
		rep(e, 0, m) cls[f(e)].insert(E[e].first), cls[f(e)].insert(E[e].second);
		multiset<vi> want;
		for (auto& [k, s] : cls) want.insert(vi(all(s)));
		// run header
		rep(i, 0, n + 1) adj[i].clear(), num[i] = low[i] = lastComp[i] = 0;
		rep(i, 0, 2 * n + 2 + m) adjp[i].clear();
		st = stack<int>(); numNode = n; numBCC = 0;
		for (auto [a, b] : E) adj[a].push_back(b), adj[b].push_back(a);
		rep(u, 1, n + 1) if (!num[u]) { tarjan(u); st = stack<int>(); }
		// adjp is stored parent -> child: a block's top vertex u has the
		// block in adjp[u] and is not repeated in adjp[block].
		vector<vi> blk(numBCC + 1);
		rep(b, 1, numBCC + 1) blk[b] = adjp[n + b];
		rep(u, 1, n + 1) for (int x : adjp[u]) {
			assert(x > n && x <= n + numBCC);
			blk[x - n].push_back(u);
		}
		multiset<vi> got;
		rep(b, 1, numBCC + 1) {
			vi s = blk[b]; sort(all(s));
			assert(unique(all(s)) == s.end());
			got.insert(s);
		}
		assert(got == want);
	}
	cout << "Tests passed!" << endl;
}
