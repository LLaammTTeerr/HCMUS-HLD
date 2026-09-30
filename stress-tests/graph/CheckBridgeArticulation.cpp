#include "../utilities/template.h"
#include "../../content/graph/CheckBridgeArticulation.h"

// The header leaves the bridge / cut actions as empty bodies. This is
// a copy of its tarjan with the bodies filled in; the test also runs
// the header's tarjan and checks both compute identical num[]/low[].
namespace filled {
int num[N], low[N]; bool isBr[N], isCut[N];
void tarjan(int u, int p_id) {
	low[u] = num[u] = ++num[0];
	int numChild = 0;
	for (auto [v, id] : adj[u]) {
		if (!num[v]) {
			tarjan(v, id);
			low[u] = min(low[u], low[v]);
			++numChild;
			if (low[v] > num[u]) isBr[id] = 1; // (u, v) is a bridge
			if (p_id != -1 && low[v] >= num[u]) isCut[u] = 1; // u is cut
		} else if (id != p_id) low[u] = min(low[u], num[v]);
	}
	if (p_id == -1 && numChild >= 2) isCut[u] = 1; // root u is cut
}
}

mt19937 rng(12);
int rnd(int a, int b) { return a + (int)(rng() % (b - a + 1)); }

int comps(int n, vector<pii>& E, int skipE, int skipV) {
	vi d(n + 1); iota(all(d), 0);
	function<int(int)> f = [&](int x) { return d[x] == x ? x : d[x] = f(d[x]); };
	int c = n - (skipV > 0);
	rep(i, 0, sz(E)) if (i != skipE) {
		auto [a, b] = E[i];
		if (a == skipV || b == skipV) continue;
		a = f(a), b = f(b);
		if (a != b) d[a] = b, c--;
	}
	return c;
}

int main() {
	rep(it, 0, 20000) {
		int n = rnd(1, 9), m = rnd(0, 14);
		vector<pii> E;
		rep(i, 0, m) { // multi-edges allowed, no self-loops
			int a = rnd(1, n), b = rnd(1, n);
			if (a != b) E.push_back({a, b});
		}
		m = sz(E);
		rep(i, 0, n + 1) {
			adj[i].clear(); num[i] = low[i] = 0;
			filled::num[i] = filled::low[i] = 0; filled::isCut[i] = 0;
		}
		rep(i, 0, m) {
			filled::isBr[i] = 0;
			adj[E[i].first].push_back({E[i].second, i});
			adj[E[i].second].push_back({E[i].first, i});
		}
		rep(u, 1, n + 1) if (!num[u]) tarjan(u, -1);
		rep(u, 1, n + 1) if (!filled::num[u]) filled::tarjan(u, -1);
		rep(u, 0, n + 1)
			assert(num[u] == filled::num[u] && low[u] == filled::low[u]);
		int base = comps(n, E, -1, 0);
		rep(i, 0, m) assert(filled::isBr[i] == (comps(n, E, i, 0) > base));
		rep(v, 1, n + 1) // cut vertex iff removing it adds components
			assert(filled::isCut[v] == (comps(n, E, -1, v) > base));
	}
	cout << "Tests passed!" << endl;
}
