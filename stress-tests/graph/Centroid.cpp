#include "../utilities/template.h"
#include "../../content/graph/Centroid.h"

mt19937 rng(9);
int rnd(int a, int b) { return a + (int)(rng() % (b - a + 1)); }

int calcSize(int u, int p) {
	child[u] = 1;
	for (int v : adj[u]) if (v != p && !del[v]) child[u] += calcSize(v, u);
	return child[u];
}
int compSize(int u, int p) { // brute size of component of u
	int s = 1;
	for (int v : adj[u]) if (v != p && !del[v]) s += compSize(v, u);
	return s;
}
int levels;
void decompose(int root) {
	int n = calcSize(root, 0);
	int c = centroid(root, 0, n);
	assert(!del[c]);
	del[c] = 1;
	for (int v : adj[c]) if (!del[v]) assert(compSize(v, c) <= n / 2);
	for (int v : adj[c]) if (!del[v]) decompose(v);
}

int main() {
	rep(it, 0, 20000) {
		int n = rnd(1, 60);
		rep(i, 1, n + 1) adj[i].clear(), del[i] = 0, child[i] = 0;
		rep(i, 2, n + 1) {
			int p = it % 4 ? rnd(1, i - 1) : i - 1; // also paths
			adj[i].push_back(p), adj[p].push_back(i);
		}
		decompose(rnd(1, n));
		rep(i, 1, n + 1) assert(del[i]);
	}
	cout << "Tests passed!" << endl;
}
