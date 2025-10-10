#pragma once

constexpr int max_log = 18;
 
struct Tree {
	int n, T;
	std::vector <int> heavy, head, st, en, lvl, sz, pv;
	mutable std::vector <int> visited;
	std::vector <std::vector <int>> g, up;
 
	Tree(int _n = 0) : n(_n) {
		heavy.assign(n, -1);
		head.assign(n, 0);
		st.assign(n, 0);
		en.assign(n, 0);
		lvl.assign(n, 0);
		sz.assign(n, 0);
		pv.assign(n, 0);
		g.assign(n, {});
		up.assign(max_log, {});
		visited.assign(n, 0);
	}
 
	void add_edge(int u, int v) {
		g[u].push_back(v);
		g[v].push_back(u);
	}
 
	int dfs(int u) {
		sz[u] = 1;
		heavy[u] = -1;
		int max_size = 0;
		for (int v : g[u]) if (v ^ pv[u]) {
			pv[v] = u;
			lvl[v] = lvl[u] + 1;
			dfs(v);
			if (max_size < sz[v]) {
				max_size = sz[v];
				heavy[u] = v;
			}
			sz[u] += sz[v];
		}
		return sz[u];
	}
 
	void decompose(int u, int h) {
		st[u] = T++;
		head[u] = h;
		if (heavy[u] != -1)
			decompose(heavy[u], h);
		for (int v : g[u]) if (v != pv[u] and v != heavy[u])
			decompose(v, v);
		en[u] = T;
	}
 
	void work(int x = 0) {
		T = 0;
		pv[x] = x;
		lvl[x] = 0;
		dfs(x);
		decompose(x, x);
		up[0] = pv;
		for (int j = 1; j < max_log; j += 1) {
			up[j].resize(n);
			for (int i = 0; i < n; i += 1)
				up[j][i] = up[j - 1][up[j - 1][i]];
		}
	}
 
	bool IS_ANCESTOR(int u, int v) const {
		return st[u] <= st[v] and en[u] >= en[v];
	}
 
	int LCA(int u, int v) const {
		if (IS_ANCESTOR(u, v))
			return u;
		if (IS_ANCESTOR(v, u))
			return v;
		for (int j = max_log - 1; j >= 0; j -= 1) {
			if (not IS_ANCESTOR(up[j][u], v))
				u = up[j][u];
		}
		return pv[u];
	}
  
	void apply_on_path(int x, int y, const std::function <void (int, int, bool)>& f) const {
		int z = LCA(x, y);
		{
			int v = x;
			while (v != z) {
				if (lvl[head[v]] <= lvl[z]) {
					f(st[z] + 1, st[v], true);
					break;
				}
				f(st[head[v]], st[v], true);
				v = pv[head[v]];
			}
		}
		f(st[z], st[z], false);
		int cnt_visited = 0;
		{
			int v = y;
			int cnt_visited = 0;
			while (v != z) {
				if (lvl[head[v]] <= lvl[z]) {
					f(st[z] + 1, st[v], false);
					break;
				}
				visited[cnt_visited++] = v;
				v = pv[head[v]];
			}
			for (int at = cnt_visited - 1; at >= 0; at--) {
				v = visited[at];
				f(st[head[v]], st[v], false);
			}
		}
	}
};