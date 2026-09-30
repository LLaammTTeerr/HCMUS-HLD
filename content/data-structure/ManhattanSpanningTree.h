/**
 * Author: HCMUS-HLD
 * Description: Manhattan MST candidate edges. using
 * namespace ManhattanSpanningTree; fill p[1..nArr] (x, y, id),
 * call buildEdge(edges), then run Kruskal on the <= 4N
 * returned edges.
 * Time: O(N \log N)
 */
#pragma once

namespace ManhattanSpanningTree {
	const int MAXN = 200005;
	struct MPoint { ll x, y; int xy, id; } p[MAXN];
	struct Edge {
		int u, v; ll w;
		Edge(int a = 0, int b = 0, ll c = 0) : u(a), v(b), w(c) {}
	};
	int nArr;
	typedef pair<ll, int> pli;
	vector<ll> idx;
	pli fen[MAXN];
	int nTree;
	
	void modify(int i, pli x) {
		for (; i > 0; i -= i & -i) fen[i] = min(fen[i], x);
	}
	
	pli get(int i) {
		pli res = {LLONG_MAX, -1};
		for (; i <= nTree; i += i & -i) res = min(res, fen[i]);
		return res;
	}
	
	void buildSpan(vector<Edge> &edges) {
		sort(p + 1, p + nArr + 1, [](auto &a, auto &b) {
			return pair(a.x, a.y) < pair(b.x, b.y); });
		idx.clear();
		rep(i,1,nArr+1) idx.push_back(p[i].y - p[i].x);
		sort(all(idx));
		idx.erase(unique(all(idx)), idx.end());
		nTree = sz(idx);
		for (int i = 1; i <= nTree; ++i) fen[i] = {LLONG_MAX, -1};
		for (int i = 1; i <= nArr; ++i) p[i].xy = int(
			upper_bound(all(idx), p[i].y - p[i].x) - idx.begin());
		for (int i = nArr; i > 0; --i) {
			pli v = get(p[i].xy);
			if(v.second != -1) { MPoint &q = p[v.second];
				edges.push_back(Edge(p[i].id, q.id,
					abs(p[i].x - q.x) + abs(p[i].y - q.y))); }
			modify(p[i].xy, pli(p[i].x + p[i].y, i));
		}
	}
	
	void buildEdge(vector<Edge> &edges) {
		edges.clear();
		for (int loop = 0; loop < 4; ++loop) {
			buildSpan(edges);
			for (int i = 1; i <= nArr; ++i) swap(p[i].x, p[i].y);
			buildSpan(edges);
			for (int i = 1; i <= nArr; ++i) {
				swap(p[i].x, p[i].y);
				if(loop & 1) p[i].y = -p[i].y;
				else p[i].x = -p[i].x;
			}
		}
	}
}
