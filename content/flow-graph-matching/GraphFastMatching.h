/**
 * Author: HCMUS-HLD
 * Description: Hopcroft-Karp bipartite matching. Left 1..m, right
 * 1..n. After solve(): cntMatching, matx[u] = right partner or 0.
 * Time: $O(E\sqrt V)$
 */
#pragma once

struct HopcroftKarp {
	vector<vector<int>> adj;
	vector<int> dist, matx, maty;
	int mNode, nNode, cntMatching;

	HopcroftKarp(int _m, int _n) {
		mNode = _m, nNode = _n;
		adj = vector<vector<int>>(mNode + 1, vector<int>());
		dist = matx = vector<int>(mNode + 1);
		maty = vector<int>(nNode + 1);
	}

	inline void addEdge(int u, int v) { adj[u].push_back(v); }

	bool bfs(void) {
		queue<int> qu;
		for (int i = 1; i <= mNode; ++i) {
			dist[i] = 1e9+7;
			if(!matx[i]) { dist[i] = 0; qu.push(i); }
		}
		dist[0] = 1e9+7;
		while(sz(qu)) {
			int u(qu.front()); qu.pop();
			if(dist[u] >= dist[0]) continue;
			for (int v : adj[u]) {
				if(dist[maty[v]] < 1e9+7) continue;
				dist[maty[v]] = dist[u] + 1;
				qu.push(maty[v]);
			}
		}
		return (dist[0] < 1e9+7);
	}

	bool dfs(int u) {
		if(!u) return true;
		for (int v : adj[u]) {
			if(dist[maty[v]] == dist[u] + 1 && dfs(maty[v])) {
				matx[u] = v, maty[v] = u; return true;
			}
		}
		dist[u] = 1e9+7;
		return false;
	}

	void solve(void) {
		cntMatching = 0;
		while(bfs()) for (int i = 1; i <= mNode; ++i) if(!matx[i]) cntMatching += dfs(i);
	}

	// Konig, after solve(): (coverL, coverR) = minimum vertex cover;
	// the complement is the largest independent set.
	pair<vector<int>, vector<int>> minVertexCover() {
		vector<int> visL(mNode + 1), visR(nNode + 1);
		function<void(int)> go = [&](int u) {
			visL[u] = 1;
			for (int v : adj[u]) if(!visR[v]) {
				visR[v] = 1;
				if(maty[v] && !visL[maty[v]]) go(maty[v]);
			}
		};
		for (int u = 1; u <= mNode; ++u) if(!matx[u]) go(u);
		for (int u = 1; u <= mNode; ++u) visL[u] = !visL[u];
		return {visL, visR};
	}

	void show(void) {
		cout << cntMatching << '\n';
		for (int i = 1; i <= mNode; ++i) if(matx[i]) cout << i << ' ' << matx[i] << '\n';
	}
};