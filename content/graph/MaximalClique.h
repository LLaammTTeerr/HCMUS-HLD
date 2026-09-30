/**
 * Author: HCMUS-HLD
 * Description: Maximum clique size via Bron-Kerbosch, n <= 62.
 * g[i][j] is the 1-indexed adjacency matrix. For max independent
 * set, run on the complement graph.
 * Time: $O(3^{n/3})$
 */
#pragma once

int g[N][N];
int res;
ll edges[N];

void BronKerbosch(int n, ll R, ll P, ll X) { // O(3 ^ (n / 3))
	// each leaf is a maximal clique R
	if (P == 0ll && X == 0ll) { 
		int t = __builtin_popcountll(R);
		res = max(res, t);
		return;
	}

	int u = 0;
	while (!((1LL << u) & (P | X))) u++;
	for (int v = 0; v < n; v++) {
		if (((1LL << v) & P) && !((1LL << v) & edges[u])) {
			BronKerbosch(n, R | (1LL << v), P & edges[v], X & edges[v]);
			P -= (1LL << v);
			X |= (1LL << v);
		}
	}
}

int max_clique(int n) {
	res = 0;
	for (int i = 1; i <= n; i++) {
		edges[i - 1] = 0;
		for (int j = 1; j <= n; j++)  if (g[i][j]) edges[i - 1] |= (1ll << (j - 1));
	}
	BronKerbosch(n, 0, (1ll << n) - 1, 0);
	return res;
}