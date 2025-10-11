/**
 * Time: $O(N \sqrt(N))$ 
*/
#pragma once

struct GraphMatching {
    vector<vector<int>> adj;
    vector<int> dist, matx, maty;
    int mNode, nNode, cntMatching;

    GraphMatching(int _m, int _n) {
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

    void show(void) {
        cout << cntMatching << '\n';
        for (int i = 1; i <= mNode; ++i) if(matx[i]) cout << i << ' ' << matx[i] << '\n';
    }
};