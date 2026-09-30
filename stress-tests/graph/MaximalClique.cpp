#include "../utilities/template.h"
#include "../../content/graph/MaximalClique.h"

mt19937 rng(13);
int rnd(int a, int b) { return a + (int)(rng() % (b - a + 1)); }

int main() {
	rep(it, 0, 20000) {
		int n = rnd(1, 14), p = rnd(1, 9);
		rep(i, 1, n + 1) rep(j, 1, n + 1) g[i][j] = 0;
		vi adjm(n);
		rep(i, 1, n + 1) rep(j, i + 1, n + 1) if (rnd(0, 9) < p) {
			g[i][j] = g[j][i] = 1;
			adjm[i - 1] |= 1 << (j - 1), adjm[j - 1] |= 1 << (i - 1);
		}
		int best = 0;
		rep(mk, 0, 1 << n) {
			bool ok = 1;
			rep(i, 0, n) if ((mk >> i & 1) && (mk & ~adjm[i] & ~(1 << i)))
				{ ok = 0; break; }
			if (ok) best = max(best, __builtin_popcount(mk));
		}
		assert(max_clique(n) == best);
	}
	// larger: n = 62 complete graph and empty graph
	int n = 62;
	rep(i, 1, n + 1) rep(j, 1, n + 1) g[i][j] = i != j;
	assert(max_clique(n) == 62);
	rep(i, 1, n + 1) rep(j, 1, n + 1) g[i][j] = 0;
	assert(max_clique(n) == 1);
	cout << "Tests passed!" << endl;
}
