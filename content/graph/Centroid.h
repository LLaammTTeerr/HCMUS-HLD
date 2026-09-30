/**
 * Author: HCMUS-HLD
 * Description: Find centroid of the current component of size n.
 * Needs child[v] = subtree sizes computed from the component root
 * (skipping del[] nodes), adj[] and del[] (removed centroids).
 * Time: $O(n)$
 */
#pragma once

int centroid(int u, int parent, int n) {
	for (int v : adj[u])
		if (v != parent && child[v] > n/2 && !del[v])
			return centroid(v, u, n);
	return u;
}