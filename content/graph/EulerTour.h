/**
 * Author: HCMUS-HLD
 * Description: Euler walk (Hierholzer). Undirected: add edge id to
 * both endpoints; directed: only to adj[from]. Start at an odd
 * vertex (directed: out - in = 1) if any. No existence check: the
 * walk is valid iff its size is m + 1. Recursion depth up to m.
 * Time: $O(V + E)$
 */
#pragma once
const int N = 5e5 + 5, M = 5e5 + 5; // vertices, edges
struct Edge {
	int target, id;

	Edge(int _target, int _id): target(_target), id(_id) {}
};

vector<Edge> adj[N];
bool used_edge[M];

list<int> euler_walk(int u) {
	list<int> ans;
	ans.push_back(u);

	while (!adj[u].empty()) {
		int v = adj[u].back().target;
		int eid = adj[u].back().id;

		adj[u].pop_back();
		if (used_edge[eid]) continue;

		used_edge[eid] = true;

		u = v;
		ans.push_back(u);
	}

	for (auto it = ans.begin(); it != ans.end(); ++it)
		if (!adj[*it].empty()) {
			auto t = euler_walk(*it);
			t.pop_back();
			ans.splice(it, t);
		}

	return ans;
}