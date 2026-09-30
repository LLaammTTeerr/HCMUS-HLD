/**
 * Author: HCMUS-HLD
 * Description: Min cost max flow with SPFA. Nodes in $[0, n]$.
 * Negative costs allowed, negative cycles are not.
 * getFlow(s, t) resets flow and returns \{flow, cost\}.
 * Time: $O(F \cdot VE)$, F = number of augmenting paths.
 */
#pragma once

struct MaxFlowMinCost {
	struct Edge { int from, to; ll capa, flow, cost; };
	vector<vi> adj; vector<Edge> E;
	vector<ll> dist; vi tr;
	const ll INF = LLONG_MAX / 4;

	MaxFlowMinCost(int n) : adj(n + 1), dist(n + 1), tr(n + 1) {}

	void addEdge(int u, int v, ll ca, ll co) {
		adj[u].push_back(sz(E)); E.push_back({u, v, ca, 0, co});
		adj[v].push_back(sz(E)); E.push_back({v, u, 0, 0, -co});
	}

	bool spfa(int s, int t) {
		fill(all(dist), INF);
		vector<bool> inq(sz(dist));
		queue<int> qu; dist[s] = 0; qu.push(s);
		while (sz(qu)) {
			int u = qu.front(); qu.pop(); inq[u] = 0;
			for (int id : adj[u]) {
				Edge &e = E[id];
				if (e.flow < e.capa && dist[e.to] > dist[u] + e.cost) {
					dist[e.to] = dist[u] + e.cost; tr[e.to] = id;
					if (!inq[e.to]) inq[e.to] = 1, qu.push(e.to);
				}
			}
		}
		return dist[t] < INF;
	}

	pair<ll, ll> getFlow(int s, int t) {
		for (auto &e : E) e.flow = 0;
		ll fl = 0, cost = 0;
		while (spfa(s, t)) {
			ll d = INF;
			for (int u = t; u != s; u = E[tr[u]].from)
				d = min(d, E[tr[u]].capa - E[tr[u]].flow);
			for (int u = t; u != s; u = E[tr[u]].from)
				E[tr[u]].flow += d, E[tr[u] ^ 1].flow -= d;
			fl += d, cost += d * dist[t];
		}
		return {fl, cost};
	}
};
