/**
 * Author: HCMUS-HLD
 * Description: Dinic max flow. Nodes in $[0, n]$ (0- or 1-indexed).
 * addEdge(u, v, c1, c2) adds u->v cap c1 and v->u cap c2 (c2 = c1
 * for undirected). maxFlow resets flow first; reset = false
 * continues in the residual graph. Edge 2k is the k-th addEdge,
 * 2k+1 its reverse; its flow is flow[2k]. After maxFlow(s, t),
 * dist[v] >= 0 iff v is on the s side of a min cut; minCutSide(s)
 * returns the cut edges (u, v).
 * Time: $O(V^2E)$, $O(E\sqrt V)$ unit caps / bipartite.
 */
#pragma once

struct DinicFlow {
	vector<ll> flow, capa;
	vector<int> point, next, head, work, dist;
	int numNode, numEdge;
	DinicFlow(int _n = 0) {
		numNode = _n, numEdge = 0;
		dist = work = vector<int>(_n + 7, 0);
		head = vector<int>(_n + 7, -1);
	}
	void addEdge(int u, int v, ll c1, ll c2 = 0) {
		point.push_back(v), capa.push_back(c1), flow.push_back(0);
		next.push_back(head[u]), head[u] = numEdge++;
		point.push_back(u), capa.push_back(c2), flow.push_back(0);
		next.push_back(head[v]), head[v] = numEdge++;
	}
	bool bfs(int s, int t) {
		queue<int> qu;
		for (int i = 0; i <= numNode; ++i) dist[i] = -1;
		dist[s] = 0; qu.push(s);
		while (!qu.empty()) {
			int u(qu.front()); qu.pop();
			for (int i = head[u]; i >= 0; i = next[i])
				if (flow[i] < capa[i] && dist[point[i]] < 0) {
					dist[point[i]] = dist[u] + 1;
					qu.push(point[i]);
				}
		}
		return (dist[t] >= 0);
	}
	ll dfs(int s, int t, ll fl) {
		if(s == t) return fl;
		for (int &i = work[s]; i >= 0; i = next[i])
			if(flow[i] < capa[i] && dist[point[i]] == dist[s] + 1) {
				ll d = dfs(point[i], t, min(fl, capa[i] - flow[i]));
				if (!d) continue;
				flow[i] += d, flow[i ^ 1] -= d;
				return d;
			}
		return 0;
	}
	ll maxFlow(int s, int t, bool reset = true) {
		if (reset) for (int i = 0; i < int(flow.size()); ++i) flow[i] = 0;
		ll totFlow = 0;
		while (bfs(s, t)) {
			for (int i = 0; i <= numNode; ++i) work[i] = head[i];
			while (true) {
				ll d = dfs(s, t, 1e18);
				if (!d) break;
				totFlow += d;
			}
		}
		return totFlow;
	}
	vector<pii> minCutSide(int s) {
		vector<int> vis(numNode + 7, 0);
		vector<pii> edges;
		queue<int> qu;
		qu.push(s); vis[s] = 1;
		while (!qu.empty()) {
			int u = qu.front(); qu.pop();
			for (int id = head[u]; id >= 0; id = next[id])
				if (flow[id] < capa[id] && !vis[point[id]]) {
					vis[point[id]] = 1;
					qu.push(point[id]);
				}
		}
		for (int i = 0; i < numEdge; ++i)
			if(capa[i] > 0 && vis[point[i ^ 1]] && !vis[point[i]])
				edges.push_back(pii(point[i ^ 1], point[i]));
		return edges; // vis for nodes, edges for edges
	}
} Df;
