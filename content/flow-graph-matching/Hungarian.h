/**
 * Author: HCMUS-HLD
 * Description: Min cost perfect matching on an $n \times n$ cost
 * matrix, 1-indexed. Negative costs OK. Rectangular: pad with 0
 * rows/cols. Max cost: negate. Missing edges default to 1e18.
 * matchX[i] = column of row i. hungarian() returns the total cost.
 * Time: $O(N^3)$
 */

#pragma once

struct Hungarian {
	vector<vector<ll>> c; // matrix cost
	vector<ll> fx, fy, dist;
	vi matchX, matchY; // potentials | corresponding node
	vi trace, arg; // prev left vertex | argmin of dist
	queue<int> qu; // used for bfs

	int numNode; // assume that |L| = |R| = n
	int start;   // current root of the tree
	int finish;  // leaf node of augmenting path

	Hungarian(int _n) {
		numNode = _n;
		c.assign(numNode + 1, vector<ll>(numNode + 1, 1e18));
		fx = fy = dist = vector<ll>(numNode + 1);
		matchX = matchY = trace = arg = vi(numNode + 1);
	}

	inline void addEdge(int u, int v, ll _cost) { c[u][v] = min(c[u][v], _cost); }
	inline ll cost(int u, int v) const { return c[u][v] - fx[u] - fy[v]; }

	void initBFS(int root) {
		start = root;
		qu = queue<int>(); qu.push(start);
		for (int i = 1; i <= numNode; ++i) {
			trace[i] = 0, arg[i] = start;
			dist[i] = cost(start, i);
		}
	}

	int findPath(void) {
		while(sz(qu)) {
			int u(qu.front()); qu.pop();
			for (int v = 1; v <= numNode; ++v) {
				if(trace[v]) continue;
				ll w = cost(u, v);
				if(w == 0) {
					trace[v] = u;
					if(!matchY[v]) return v;
					qu.push(matchY[v]);
				}
				if(dist[v] > w) dist[v] = w, arg[v] = u;
			}
		}
		return 0;
	}

	void enlarge(void) {
		for (int y = finish, next; y != 0; y = next) {
			int x = trace[y]; next = matchX[x];
			matchX[x] = y, matchY[y] = x;
		}
	}

	void update(void) {
		ll delta = LLONG_MAX;
		for (int i = 1; i <= numNode; ++i) if(!trace[i]) delta = min(delta, dist[i]);
		fx[start] += delta;
		for (int i = 1; i <= numNode; ++i) {
			if(trace[i]) {
				fx[matchY[i]] += delta, fy[i] -= delta;
			} else {
				dist[i] -= delta;
				if(dist[i] == 0) {
					trace[i] = arg[i];
					if(matchY[i] == 0) { finish = i; } 
					else qu.push(matchY[i]);
				}
			}
		}
	}

	ll hungarian(void) {
		for (int i = 1; i <= numNode; ++i)
			fx[i] = *min_element(c[i].begin() + 1, c[i].end());
		for (int i = 1; i <= numNode; ++i) {
			initBFS(i);
			do {
				finish = findPath();
				if(!finish) update();
			} while(!finish);
			enlarge();
		}
		ll ans = 0;
		for (int i = 1; i <= numNode; ++i) ans += c[i][matchX[i]];
		return ans;
	}
};