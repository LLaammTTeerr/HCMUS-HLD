#include "../utilities/template.h"
#include "../../content/flow-graph-matching/Hungarian.h"

mt19937 rng(4);
ll rnd(ll a, ll b) { return a + (ll)(rng() % (b - a + 1)); }

int main() {
	rep(it, 0, 20000) {
		int n = (int)rnd(1, 7);
		bool sparse = it % 3 == 0;
		ll lim = it % 2 ? (ll)1e9 : 10;
		vector<vector<ll>> c(n + 1, vector<ll>(n + 1, (ll)1e18));
		vi perm(n); iota(all(perm), 1); shuffle(all(perm), rng);
		Hungarian H(n);
		rep(i, 1, n + 1) rep(j, 1, n + 1) {
			if (sparse && perm[i - 1] != j && rng() % 2) continue;
			c[i][j] = rnd(-lim, lim);
			H.addEdge(i, j, c[i][j]);
		}
		vi p(n); iota(all(p), 1);
		ll best = LLONG_MAX;
		do {
			ll s = 0; bool ok = 1;
			rep(i, 0, n) {
				if (c[i + 1][p[i]] >= (ll)1e18) { ok = 0; break; }
				s += c[i + 1][p[i]];
			}
			if (ok) best = min(best, s);
		} while (next_permutation(all(p)));
		ll got = H.hungarian();
		assert(got == best);
		vi seen(n + 1); ll s = 0;
		rep(i, 1, n + 1) {
			int j = H.matchX[i];
			assert(j >= 1 && j <= n && !seen[j]); seen[j] = 1;
			s += c[i][j];
		}
		assert(s == best);
	}
	cout << "Tests passed!" << endl;
}
