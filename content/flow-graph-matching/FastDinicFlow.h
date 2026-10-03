/**
 * Author: HCMUS-HLD (after KACTL)
 * Description: Faster Dinic max flow with capacity scaling. Nodes in
 * $[0, n]$ (0- or 1-indexed). addEdge(u, v, c, rc) adds u->v cap c
 * and v->u cap rc (rc = c for undirected). maxFlow does NOT reset
 * flow: a second call continues in the residual graph. After
 * maxFlow(s, t), leftOfMinCut(v) = v is on the s side of a min cut.
 * Flow on an edge e = adj[u][i]: e.flow().
 * Time: $O(VE\log U)$, $O(E\sqrt V)$ unit caps / bipartite.
 */
#pragma once

struct FastDinicFlow {
	struct E {
		int to, rev; ll c, oc;
		ll flow() { return max(oc - c, 0LL); }
	};
	vi lvl, ptr, q;
	vector<vector<E>> adj;
	FastDinicFlow(int n)
		: lvl(n + 1), ptr(n + 1), q(n + 1), adj(n + 1) {}
	void addEdge(int u, int v, ll c, ll rc = 0) {
		adj[u].push_back({v, sz(adj[v]), c, c});
		adj[v].push_back({u, sz(adj[u]) - 1, rc, rc});
	}
	ll dfs(int v, int t, ll f) {
		if (v == t || !f) return f;
		for (int &i = ptr[v]; i < sz(adj[v]); i++) {
			E &e = adj[v][i];
			if (lvl[e.to] == lvl[v] + 1)
				if (ll p = dfs(e.to, t, min(f, e.c))) {
					e.c -= p, adj[e.to][e.rev].c += p;
					return p;
				}
		}
		return 0;
	}
	ll maxFlow(int s, int t) {
		ll flow = 0; q[0] = s;
		rep(L, 0, 31) do {
			lvl = ptr = vi(sz(q));
			int qi = 0, qe = lvl[s] = 1;
			while (qi < qe && !lvl[t]) {
				int v = q[qi++];
				for (E e : adj[v])
					if (!lvl[e.to] && e.c >> (30 - L))
						q[qe++] = e.to, lvl[e.to] = lvl[v] + 1;
			}
			while (ll p = dfs(s, t, LLONG_MAX)) flow += p;
		} while (lvl[t]);
		return flow;
	}
	bool leftOfMinCut(int v) { return lvl[v] != 0; }
};
