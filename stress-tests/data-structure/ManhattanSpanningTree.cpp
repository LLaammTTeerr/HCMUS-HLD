#include "../utilities/template.h"
#include "../../content/data-structure/ManhattanSpanningTree.h"

vi uf;
int find(int x) { return uf[x] < 0 ? x : uf[x] = find(uf[x]); }

int main() {
	mt19937 rng(10);
	rep(it,0,400) {
		int n = 1 + rng() % 60;
		ll C = it % 2 ? 10 : 1000000000;
		vector<ll> X(n), Y(n);
		rep(i,0,n) X[i] = (ll)(rng() % (2 * C + 1)) - C,
			Y[i] = (ll)(rng() % (2 * C + 1)) - C;
		using namespace ManhattanSpanningTree;
		nArr = n;
		rep(i,0,n) p[i + 1] = {X[i], Y[i], 0, i};
		vector<Edge> edges;
		buildEdge(edges);
		sort(all(edges), [](auto& a, auto& b) { return a.w < b.w; });
		uf.assign(n, -1);
		ll got = 0; int cnt = 0;
		for (auto& e : edges) {
			int a = find(e.u), b = find(e.v);
			assert(e.w == abs(X[e.u] - X[e.v]) + abs(Y[e.u] - Y[e.v]));
			if (a != b) uf[a] = b, got += e.w, cnt++;
		}
		assert(cnt == n - 1);
		// Prim O(n^2)
		vector<ll> d(n, LLONG_MAX); vector<bool> in(n);
		d[0] = 0; ll exp = 0;
		rep(k,0,n) {
			int u = -1;
			rep(i,0,n) if (!in[i] && (u < 0 || d[i] < d[u])) u = i;
			in[u] = 1, exp += d[u];
			rep(i,0,n) d[i] = min(d[i], abs(X[u] - X[i]) + abs(Y[u] - Y[i]));
		}
		assert(got == exp);
	}
	cout << "Tests passed!" << endl;
}
