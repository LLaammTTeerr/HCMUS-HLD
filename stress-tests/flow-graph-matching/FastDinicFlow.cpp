#include "../utilities/template.h"
#include "../../content/flow-graph-matching/FastDinicFlow.h"

mt19937 rng(1);
int rnd(int a, int b) { return a + (int)(rng() % (b - a + 1)); }

// brute s-t min cut: min over S containing s, not t
ll bruteCut(int n, vector<array<ll, 4>>& ed, int s, int t) {
	ll best = LLONG_MAX;
	rep(m, 0, 1 << n) if ((m >> s & 1) && !(m >> t & 1)) {
		ll c = 0;
		for (auto [u, v, w, rw] : ed) {
			if ((m >> u & 1) && !(m >> v & 1)) c += w;
			if ((m >> v & 1) && !(m >> u & 1)) c += rw;
		}
		best = min(best, c);
	}
	return best;
}

void testMaxFlow() {
	rep(it, 0, 20000) {
		int n = rnd(2, 7), m = rnd(0, 12);
		int s = rnd(0, n - 1), t = rnd(0, n - 2); if (t >= s) t++;
		bool und = it % 3 == 0, one = it % 2; // 0- or 1-indexed
		vector<array<ll, 4>> ed;
		FastDinicFlow D(n + one);
		rep(i, 0, m) {
			int u = rnd(0, n - 1), v = rnd(0, n - 1);
			ll w = it % 5 == 0 ? rnd(0, 1 << 30) * 1000LL : rnd(0, 10);
			ll rw = und ? w : 0;
			ed.push_back({u, v, w, rw});
			D.addEdge(u + one, v + one, w, rw);
		}
		ll f = D.maxFlow(s + one, t + one);
		assert(f == bruteCut(n, ed, s, t));
		// cut side from leftOfMinCut has capacity == flow
		ll c = 0;
		for (auto [u, v, w, rw] : ed) {
			bool lu = D.leftOfMinCut(int(u) + one), lv = D.leftOfMinCut(int(v) + one);
			if (lu && !lv) c += w;
			if (lv && !lu) c += rw;
		}
		assert(D.leftOfMinCut(s + one) && !D.leftOfMinCut(t + one));
		assert(c == f);
		assert(D.maxFlow(s + one, t + one) == 0); // continues, no reset
	}
}

// Lower bounds [L, R] (chapter.tex procedure), vs brute enumeration
void testLowerBounds() {
	int feas = 0;
	rep(it, 0, 20000) {
		int n = rnd(2, 5), m = rnd(1, 5), S = 0, T = n - 1;
		vector<array<int, 4>> ed;
		while (sz(ed) < m) {
			int u = rnd(0, n - 1), v = rnd(0, n - 1);
			if (u == v || v == S || u == T) continue; // no edges into S / out of T
			int L = rnd(0, 2); ed.push_back({u, v, L, L + rnd(0, 2)});
		}
		ll bmin = LLONG_MAX, bmax = LLONG_MIN; vi f(m);
		function<void(int)> go = [&](int i) {
			if (i == m) {
				vector<ll> bal(n);
				rep(j, 0, m) bal[ed[j][0]] -= f[j], bal[ed[j][1]] += f[j];
				rep(v, 0, n) if (v != S && v != T && bal[v]) return;
				bmin = min(bmin, -bal[S]), bmax = max(bmax, -bal[S]);
				return;
			}
			for (f[i] = ed[i][2]; f[i] <= ed[i][3]; f[i]++) go(i + 1);
		};
		go(0);
		int Sp = n, Tp = n + 1; ll sumL = 0;
		FastDinicFlow D(n + 2);
		for (auto [u, v, L, R] : ed) {
			D.addEdge(u, v, R - L); D.addEdge(u, Tp, L); D.addEdge(Sp, v, L);
			sumL += L;
		}
		D.addEdge(T, S, (ll)1e15);
		bool ok = D.maxFlow(Sp, Tp) == sumL;
		assert(ok == (bmin != LLONG_MAX));
		if (!ok) continue;
		feas++;
		FastDinicFlow D2 = D;
		assert(D.maxFlow(S, T) == bmax); // max flow: continue, keep T->S
		auto& e = D2.adj[T].back(); // min flow: remove T->S
		ll fl = e.flow(); e.c = 0; D2.adj[S][e.rev].c = 0;
		assert(fl - D2.maxFlow(T, S) == bmin);
	}
	assert(feas > 1000);
}

int main() {
	testMaxFlow();
	testLowerBounds();
	cout << "Tests passed!" << endl;
}
