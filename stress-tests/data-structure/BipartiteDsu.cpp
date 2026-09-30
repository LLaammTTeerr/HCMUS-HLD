#include "../utilities/template.h"
#include "../../content/data-structure/BipartiteDsu.h"

int main() {
	mt19937 rng(11);
	rep(it,0,1000) {
		int n = 1 + rng() % 12;
		BipDSU d(n);
		vector<vi> g(n);
		rep(q,0,20) {
			int a = rng() % n, b = rng() % n;
			d.add(a, b), g[a].push_back(b), g[b].push_back(a);
			// brute: BFS 2-colouring per component
			vi col(n, -1), comp(n, -1), okc(n, 1);
			rep(s,0,n) if (col[s] < 0) {
				queue<int> qu; qu.push(s), col[s] = 0;
				while (sz(qu)) {
					int u = qu.front(); qu.pop(); comp[u] = s;
					for (int v : g[u]) {
						if (col[v] < 0) col[v] = col[u] ^ 1, qu.push(v);
						else if (col[v] == col[u]) okc[s] = 0;
					}
				}
			}
			rep(u,0,n) {
				assert(d.ok(u) == (bool)okc[comp[u]]);
				assert((d.find(u) == d.find(comp[u])));
			}
			rep(u,0,n) rep(v,0,n) if (comp[u] == comp[v] && okc[comp[u]])
				assert((d.par(u) ^ d.par(v)) == (col[u] ^ col[v]));
		}
	}
	cout << "Tests passed!" << endl;
}
