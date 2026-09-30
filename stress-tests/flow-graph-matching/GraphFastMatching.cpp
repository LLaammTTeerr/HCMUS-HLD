#include "../utilities/template.h"
#include "../../content/flow-graph-matching/GraphFastMatching.h"

mt19937 rng(3);
int rnd(int a, int b) { return a + (int)(rng() % (b - a + 1)); }

int main() {
	rep(it, 0, 20000) {
		int L = rnd(1, 8), R = rnd(1, 8);
		vector<vi> adj(L + 1);
		HopcroftKarp H(L, R);
		rep(u, 1, L + 1) rep(v, 1, R + 1) if (rng() % 3 == 0)
			adj[u].push_back(v), H.addEdge(u, v);
		// brute: dp over right-side masks
		vi dp(1 << R, -1); dp[0] = 0; int best = 0;
		rep(u, 1, L + 1) {
			vi nd = dp;
			rep(mk, 0, 1 << R) if (dp[mk] >= 0) for (int v : adj[u])
				if (!(mk >> (v - 1) & 1))
					nd[mk | 1 << (v - 1)] = max(nd[mk | 1 << (v - 1)], dp[mk] + 1);
			dp = nd;
		}
		for (int x : dp) best = max(best, x);
		H.solve();
		assert(H.cntMatching == best);
		int cnt = 0; vi usedR(R + 1);
		rep(u, 1, L + 1) if (H.matx[u]) {
			int v = H.matx[u]; cnt++;
			assert(count(all(adj[u]), v) && !usedR[v] && H.maty[v] == u);
			usedR[v] = 1;
		}
		assert(cnt == best);
	}
	// larger smoke test
	int n = 20000; HopcroftKarp H(n, n);
	rep(u, 1, n + 1) rep(k, 0, 3) H.addEdge(u, rnd(1, n));
	H.solve(); assert(H.cntMatching > n / 2);
	cout << "Tests passed!" << endl;
}
