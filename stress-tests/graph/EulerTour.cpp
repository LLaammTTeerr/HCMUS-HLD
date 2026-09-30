#include "../utilities/template.h"
#include "../../content/graph/EulerTour.h"

mt19937 rng(14);
int rnd(int a, int b) { return a + (int)(rng() % (b - a + 1)); }

int main() {
	int solvable = 0;
	rep(it, 0, 30000) {
		bool dir = it % 2;
		int n = rnd(1, 6), m = rnd(0, 9);
		vector<pii> E;
		rep(i, 0, m) E.push_back({rnd(0, n - 1), rnd(0, n - 1)});
		rep(i, 0, n) adj[i].clear();
		rep(i, 0, m) {
			used_edge[i] = 0;
			auto [a, b] = E[i];
			adj[a].push_back(Edge(b, i));
			if (!dir) adj[b].push_back(Edge(a, i));
		}
		// brute existence: degree condition + edges connected
		vi out(n), in(n);
		for (auto [a, b] : E) out[a]++, in[b]++;
		int start = m ? E[0].first : 0, bad = 0, plus = 0, odd = 0;
		rep(v, 0, n) {
			if (dir) {
				int d = out[v] - in[v];
				if (d == 1) plus++, start = v;
				else if (d != 0 && d != -1) bad = 1;
				else if (d == -1) odd++;
			} else if ((out[v] + in[v]) % 2) odd++, start = odd == 1 ? v : start;
		}
		if (dir) bad |= plus > 1 || odd > 1 || plus != odd;
		else bad |= odd > 2;
		vi d(n); iota(all(d), 0);
		function<int(int)> f = [&](int x) { return d[x] == x ? x : d[x] = f(d[x]); };
		for (auto [a, b] : E) d[f(a)] = f(b);
		for (auto [a, b] : E) if (f(a) != f(E[0].first)) bad = 1;
		auto walk = euler_walk(start);
		vi w(all(walk));
		// NOTE: size == m + 1 alone does not prove validity (e.g. directed
		// 1->0, 1->0 gives "1 1 0"); the degree condition must hold too.
		if (bad) continue;
		assert(sz(w) == m + 1);
		multiset<pii> left;
		for (auto [a, b] : E) {
			left.insert({a, b});
			if (!dir && a != b) left.insert({b, a});
		}
		rep(i, 0, m) {
			pii e = {w[i], w[i + 1]};
			auto itr = left.find(e); assert(itr != left.end());
			left.erase(itr);
			if (!dir && e.first != e.second)
				left.erase(left.find({e.second, e.first}));
		}
		solvable += !bad;
	}
	assert(solvable > 5000);
	cout << "Tests passed!" << endl;
}
