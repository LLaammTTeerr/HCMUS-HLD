#include "../utilities/template.h"
#include "../../content/graph/OnlineBridgeCounting.h"

mt19937 rng(11);
int rnd(int a, int b) { return a + (int)(rng() % (b - a + 1)); }

int comps(int n, vector<pii>& E, int skip) {
	vi d(n); iota(all(d), 0);
	function<int(int)> f = [&](int x) { return d[x] == x ? x : d[x] = f(d[x]); };
	int c = n;
	rep(i, 0, sz(E)) if (i != skip) {
		int a = f(E[i].first), b = f(E[i].second);
		if (a != b) d[a] = b, c--;
	}
	return c;
}

int main() {
	rep(it, 0, 5000) {
		int n = rnd(1, 10), m = rnd(0, 20);
		init(n);
		vector<pii> E;
		rep(i, 0, m) {
			int a = rnd(0, n - 1), b = rnd(0, n - 1); // loops/multi-edges OK
			E.push_back({a, b}); add_edge(a, b);
			int base = comps(n, E, -1), br = 0;
			rep(j, 0, sz(E)) br += comps(n, E, j) > base;
			assert(bridges == br);
		}
	}
	cout << "Tests passed!" << endl;
}
