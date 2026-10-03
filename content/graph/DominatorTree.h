/**
 * Author: HCMUS-HLD
 * Description: Dominator tree (Lengauer-Tarjan) of a directed graph,
 * nodes 0..n-1, from root s. d dominates v if every path s -> v
 * passes d. Returns idom: idom[s] = s, idom[v] = -1 if v is
 * unreachable, else the immediate dominator (tree parent) of v.
 * Recursive, depth up to n.
 * Time: O(M \log N)
 */
#pragma once

vi dominators(const vector<vi>& g, int s) {
	int n = sz(g), t = 0;
	vi id(n, -1), rv(n), par(n), sdom(n), dom(n), dsu(n), lab(n);
	vector<vi> rg(n), bkt(n);
	auto dfs = [&](auto& self, int u) -> void {
		id[u] = t, rv[t] = u, lab[t] = sdom[t] = dsu[t] = t, t++;
		for (int w : g[u]) {
			if (id[w] < 0) self(self, w), par[id[w]] = id[u];
			rg[id[w]].push_back(id[u]);
		}
	};
	dfs(dfs, s);
	// node with min sdom on the dsu path
	auto find = [&](auto& self, int u, int x) -> int {
		if (u == dsu[u]) return x ? -1 : u;
		int v = self(self, dsu[u], x + 1);
		if (v < 0) return u;
		if (sdom[lab[dsu[u]]] < sdom[lab[u]]) lab[u] = lab[dsu[u]];
		dsu[u] = v;
		return x ? v : lab[u];
	};
	for (int i = t - 1; i >= 0; i--) {
		for (int w : rg[i])
			sdom[i] = min(sdom[i], sdom[find(find, w, 0)]);
		if (i) bkt[sdom[i]].push_back(i);
		for (int w : bkt[i]) {
			int v = find(find, w, 0);
			dom[w] = sdom[v] == sdom[w] ? sdom[w] : v;
		}
		if (i) dsu[i] = par[i];
	}
	vi idom(n, -1);
	rep(i, 1, t) {
		if (dom[i] != sdom[i]) dom[i] = dom[dom[i]];
		idom[rv[i]] = rv[dom[i]];
	}
	idom[s] = s;
	return idom;
}
