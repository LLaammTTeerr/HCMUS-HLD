/**
 * Time: $O(N^3)$
*/

#pragma once

struct GraphMatching {
    vector<vector<int>> adj;
    vector<int> asi;
    vector<bool> dx;
    int mNode, nNode, cntMatching;

    GraphMatching(int _m, int _n) {
        mNode = _m, nNode = _n;
        adj = vector<vector<int>>(mNode + 1, vector<int>());
        asi = vector<int>(nNode + 1);
        dx = vector<bool>(mNode + 1);
    }

    inline void addEdge(int u, int v) { adj[u].push_back(v); }

    bool visit(int u) {
        if(dx[u]) return false;
        dx[u] = 1;
        for (int v : adj[u]) {
            if(!asi[v] || visit(asi[v])) {
                asi[v] = u; return true;
            }
        }
        return false;
    }

    void solve(void) {
        cntMatching = 0;
        for (int i = 1; i <= mNode; ++i) {
            for (int j = 1; j <= mNode; ++j) dx[j] = 0;
            cntMatching += visit(i);
        } 
    }

    void show(void) {
        cout << cntMatching << '\n';
        for (int i = 1; i <= nNode; ++i) if(asi[i] > 0) cout << asi[i] << ' ' << i << '\n';
    }
};