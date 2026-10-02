/**
 * Author: HCMUS-HLD
 * Description: Tarjan's strongly connected components, nodes
 * 0..n-1. After run(), comp[u] = component id in $[0, nc)$, in
 * reverse topological order: for an edge $u \to v$,
 * comp[u] $\ge$ comp[v]. Recursive: depth up to n.
 * Usage: SCC s(n); s.add(u, v); s.run(); s.comp[u]
 * Time: O(N + M)
 */
#pragma once

struct SCC {
	int n, t = 0, nc = 0;
	vector<vi> g;
	vi low, num, comp, st;
	SCC(int n) : n(n), g(n), low(n), num(n, -1), comp(n, -1) {}
	void add(int u, int v) { g[u].push_back(v); }
	void dfs(int u) {
		low[u] = num[u] = t++, st.push_back(u);
		for (int v : g[u]) if (comp[v] < 0) {
			if (num[v] < 0) dfs(v);
			low[u] = min(low[u], low[v]);
		}
		if (low[u] == num[u]) {
			int v;
			do v = st.back(), st.pop_back(), comp[v] = nc;
			while (v != u);
			nc++;
		}
	}
	void run() { rep(u, 0, n) if (num[u] < 0) dfs(u); }
};
