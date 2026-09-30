/**
 * Author: HCMUS-HLD
 * Description: Gomory-Hu tree of an undirected graph with nodes
 * $0..n-1$ and edges \{u, v, w\}. Returns $n-1$ tree edges
 * \{i, par, w\}; min cut(u, v) = min weight on the tree path u-v.
 * Time: $n-1$ max flow calls, $O(V^3E)$.
 */
#pragma once

#include "DinicFlow.h"

typedef array<ll, 3> Edge;
vector<Edge> gomoryHu(int n, const vector<Edge>& ed) {
	vi par(n, 0); vector<Edge> tree;
	rep(i, 1, n) {
		DinicFlow D(n);
		for (auto [u, v, w] : ed) D.addEdge(u, v, w, w);
		tree.push_back({i, par[i], D.maxFlow(i, par[i])});
		rep(j, i + 1, n)
			if (D.leftOfMinCut(j) && par[j] == par[i]) par[j] = i;
	}
	return tree;
}
