/**
 * Author: HCMUS-HLD
 * Description: Splits an even graph (undirected: all degrees even;
 * directed: in = out) into edge-disjoint simple cycles. g[u] holds
 * {v, edge id}, ids in [0, m); undirected: add to g[a] and g[b].
 * Cycle {vs, es}: es[i] goes vs[i] -> vs[(i+1) % k], so it also
 * orients edges with in = out. Self-loop = 1-cycle. Not even: still
 * returns edge-disjoint simple cycles; uncovered edges form a forest
 * (undirected) or a DAG (directed), not necessarily minimum.
 * Time: O(N + M)
 */
#pragma once

vector<pair<vi, vi>> cycleDecomp(vector<vector<pii>> g, int m) {
	int n = sz(g), p;
	vi pos(n, -1), used(m), vs, es;
	vector<pair<vi, vi>> res;
	rep(s, 0, n) {
		vs = {s}, es = {}, pos[s] = 0;
		while (sz(vs)) {
			int u = vs.back();
			while (sz(g[u]) && used[g[u].back().second]) g[u].pop_back();
			if (g[u].empty()) { // even: only when vs = {s}
				pos[u] = -1, vs.pop_back();
				if (sz(es)) es.pop_back(); // drop the edge into u
				continue;
			}
			auto [v, e] = g[u].back();
			used[e] = 1, es.push_back(e);
			if ((p = pos[v]) < 0) pos[v] = sz(vs), vs.push_back(v);
			else { // close the cycle at v
				res.push_back({vi(p + all(vs)), vi(p + all(es))});
				rep(i, p + 1, sz(vs)) pos[vs[i]] = -1;
				vs.resize(p + 1), es.resize(p);
			}
		}
	}
	return res;
}
