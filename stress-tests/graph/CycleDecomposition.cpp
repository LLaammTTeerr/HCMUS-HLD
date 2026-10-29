#include "../utilities/template.h"
#include "../../content/graph/CycleDecomposition.h"

mt19937 rng(14);
int rnd(int a, int b) { return a + (int)(rng() % (b - a + 1)); }

bool isEven(int n, const vector<pii>& E, bool dir) {
	vi in(n), out(n);
	for (auto [a, b] : E) out[a]++, in[b]++;
	rep(v, 0, n) if (dir ? in[v] != out[v] : (in[v] + out[v]) % 2) return 0;
	return 1;
}

// cycles simple, edge-disjoint and following real edges; even =>
// all edges covered; else leftover is a forest / DAG
void check(int n, const vector<pii>& E, bool dir) {
	int m = sz(E);
	vector<vector<pii>> g(n);
	rep(i, 0, m) {
		auto [a, b] = E[i];
		g[a].push_back({b, i});
		if (!dir) g[b].push_back({a, i});
	}
	for (auto& v : g) shuffle(all(v), rng);
	vi cnt(m);
	for (auto& [vs, es] : cycleDecomp(g, m)) {
		int k = sz(vs);
		assert(k >= 1 && sz(es) == k);
		assert(sz(set<int>(all(vs))) == k);
		rep(i, 0, k) {
			int a = vs[i], b = vs[(i + 1) % k], e = es[i];
			assert(0 <= e && e < m);
			cnt[e]++;
			auto [x, y] = E[e];
			if (dir) assert(x == a && y == b);
			else assert((x == a && y == b) || (x == b && y == a));
		}
	}
	vector<pii> left;
	rep(i, 0, m) {
		assert(cnt[i] <= 1);
		if (!cnt[i]) left.push_back(E[i]);
	}
	if (isEven(n, E, dir)) assert(left.empty());
	if (dir) {
		vi indeg(n), q; vector<vi> h(n);
		for (auto [a, b] : left) h[a].push_back(b), indeg[b]++;
		rep(v, 0, n) if (!indeg[v]) q.push_back(v);
		rep(i, 0, sz(q)) for (int w : h[q[i]]) if (!--indeg[w]) q.push_back(w);
		assert(sz(q) == n);
	} else {
		vi d(n); iota(all(d), 0);
		function<int(int)> f = [&](int x) { return d[x] == x ? x : d[x] = f(d[x]); };
		for (auto [a, b] : left) {
			assert(f(a) != f(b));
			d[f(a)] = f(b);
		}
	}
}

vector<pii> randomEven(int n, int m, bool dir) {
	vector<pii> E;
	if (dir) {
		while (sz(E) < m) { // union of closed walks => in = out
			int k = rnd(1, 5), s = rnd(0, n - 1), u = s;
			rep(j, 0, k - 1) {
				int v = rnd(0, n - 1);
				E.push_back({u, v}), u = v;
			}
			E.push_back({u, s});
		}
	} else {
		rep(i, 0, m) E.push_back({rnd(0, n - 1), rnd(0, n - 1)});
		vi deg(n), odd;
		for (auto [a, b] : E) deg[a]++, deg[b]++;
		rep(v, 0, n) if (deg[v] % 2) odd.push_back(v);
		shuffle(all(odd), rng);
		for (int i = 0; i < sz(odd); i += 2) E.push_back({odd[i], odd[i + 1]});
	}
	shuffle(all(E), rng);
	return E;
}

int main() {
	// every edge list on 3 nodes with <= 4 edges
	rep(dir, 0, 2) rep(m, 0, 5) {
		int tot = 1;
		rep(i, 0, m) tot *= 9;
		rep(code, 0, tot) {
			vector<pii> E;
			for (int i = 0, c = code; i < m; i++, c /= 9)
				E.push_back({c % 9 / 3, c % 3});
			check(3, E, dir);
		}
	}
	rep(it, 0, 100000) {
		bool dir = it % 2;
		int n = rnd(1, 8), m = rnd(0, 14);
		vector<pii> E;
		if (it % 3) E = randomEven(n, m, dir);
		else rep(i, 0, m) E.push_back({rnd(0, n - 1), rnd(0, n - 1)});
		check(n, E, dir);
	}
	assert(cycleDecomp({}, 0).empty());
	check(1, {{0, 0}, {0, 0}, {0, 0}}, 0);
	check(2, {{0, 1}, {1, 0}, {0, 1}}, 1);
	// long path / cycle: no recursion
	int n = 200000;
	vector<pii> P, C;
	rep(i, 0, n) P.push_back({i, i + 1}), C.push_back({i, (i + 1) % n});
	rep(dir, 0, 2) {
		check(n + 1, P, dir), check(n, C, dir);
		check(n / 10, randomEven(n / 10, n, dir), dir);
	}
	cout << "Tests passed!" << endl;
}
