#include "../utilities/template.h"
#include "../../content/flow-graph-matching/EdmondsBlossom.h"

mt19937 rng(5);
int rnd(int a, int b) { return a + (int)(rng() % (b - a + 1)); }

int main() {
	rep(it, 0, 20000) {
		int n = rnd(1, 12);
		vector<vector<bool>> g(n, vector<bool>(n));
		Blossom B(n);
		int p = rnd(1, 4);
		rep(i, 0, n) rep(j, i + 1, n) if ((int)(rng() % 8) < p)
			g[i][j] = g[j][i] = 1, B.addEdge(i, j);
		// brute: dp over masks, match lowest unmatched vertex
		vi dp(1 << n, 0);
		for (int mk = (1 << n) - 1; mk >= 0; mk--) {
			int i = 0; while (i < n && (mk >> i & 1)) i++;
			if (i == n) continue;
			int b = dp[mk | 1 << i];
			rep(j, i + 1, n) if (!(mk >> j & 1) && g[i][j])
				b = max(b, 1 + dp[mk | 1 << i | 1 << j]);
			dp[mk] = b;
		}
		int got = B.solve();
		assert(got == dp[0]);
		int cnt = 0;
		rep(v, 0, n) if (B.match[v] != -1) {
			int u = B.match[v];
			assert(g[u][v] && B.match[u] == v); cnt++;
		}
		assert(cnt == 2 * got);
	}
	cout << "Tests passed!" << endl;
}
