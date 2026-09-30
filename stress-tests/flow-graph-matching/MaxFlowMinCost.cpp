#include "../utilities/template.h"
#include "../../content/flow-graph-matching/MaxFlowMinCost.h"

mt19937 rng(2);
int rnd(int a, int b) { return a + (int)(rng() % (b - a + 1)); }

int main() {
	rep(it, 0, 20000) {
		int n = rnd(2, 5), m = rnd(0, 6), s = 0, t = n - 1;
		bool dag = it % 2; // DAG: negative costs allowed
		vector<array<int, 4>> ed; // u v cap cost
		while (sz(ed) < m) {
			int u = rnd(0, n - 1), v = rnd(0, n - 1);
			if (u == v || (dag && u > v)) continue;
			ed.push_back({u, v, rnd(0, 2), dag ? rnd(-5, 5) : rnd(0, 5)});
		}
		// brute: all integer flows, max value then min cost
		ll bf = -1, bc = 0; vi f(m);
		function<void(int)> go = [&](int i) {
			if (i == m) {
				vector<ll> bal(n); ll c = 0;
				rep(j, 0, m) {
					bal[ed[j][0]] -= f[j], bal[ed[j][1]] += f[j];
					c += (ll)f[j] * ed[j][3];
				}
				rep(v, 0, n) if (v != s && v != t && bal[v]) return;
				ll val = -bal[s];
				if (val > bf || (val == bf && c < bc)) bf = val, bc = c;
				return;
			}
			for (f[i] = 0; f[i] <= ed[i][2]; f[i]++) go(i + 1);
		};
		go(0);
		MaxFlowMinCost F(n);
		for (auto [u, v, ca, co] : ed) F.addEdge(u, v, ca, co);
		auto [fl, cost] = F.getFlow(s, t);
		assert(fl == bf && cost == bc);
		auto again = F.getFlow(s, t); // resets flow
		assert(again == make_pair(fl, cost));
	}
	cout << "Tests passed!" << endl;
}
