/**
 * Author: HCMUS-HLD
 * Description: Bridges and articulation points, vertices 1..n
 * (num[0] is the timer). Globals: adj[u] = \{v, edge id\}, num[],
 * low[] zeroed; call tarjan(u, -1) for each unvisited u.
 * Multi-edges OK (compares edge ids).
 * Time: $O(V + E)$
 */
#pragma once

const int N = 2e5 + 5;
vector<pii> adj[N]; // {v, edge id}
int num[N], low[N];

void tarjan(int u, int p_id) {
	low[u] = num[u] = ++num[0];
	int numChild = 0;
	for (auto [v, id] : adj[u]) {
		if (!num[v]) {
			tarjan(v, id);
			low[u] = min(low[u], low[v]);
			++numChild;
			if (low[v] > num[u]) {} // (u, v) is a bridge
			if (p_id != -1 && low[v] >= num[u]) {} // u is cut
		} else if (id != p_id) low[u] = min(low[u], num[v]);
	}
	if (p_id == -1 && numChild >= 2) {} // root u is cut
}
