#pragma once

class MaxFlowMinCost {
    public:
        struct Edge {
            int from, to, capa, flow, cost;
            Edge(int _u = 0, int _v = 0, int _ca = 0, int _co = 0) : from(_u), to(_v), capa(_ca), flow(0), cost(_co) {}
            inline int residual(void) const { return capa - flow; }
        };
 
        vector<vector<int>> adj;
        vector<Edge> E;
        vector<int> dist, tr;
        int n;
 
        MaxFlowMinCost(int _n = 0) {
            n = _n, E.clear();
            adj.assign(_n + 7, vector<int>());
            dist = vector<int>(_n + 7);
            tr = vector<int>(_n + 7);
        }
 
        void addEdge(int u, int v, int ca, int co) {
            adj[u].push_back(E.size());
            E.push_back(Edge(u, v, ca, co));
            adj[v].push_back(E.size());
            E.push_back(Edge(v, u, 0, -co));
        }
 
        bool FordBellman(int s, int t) {
            for (int i = 1; i <= n; ++i) dist[i] = 1e9+7, tr[i] = 1;
            queue<int> qu;
            vector<bool> inq = vector<bool>(n + 7, false);
            inq[s] = 1, dist[s] = 0; qu.push(s);
            while(!qu.empty()) {
                int u(qu.front()); qu.pop();
                inq[u] = 0;
                for (auto &it : adj[u]) {
                    if(E[it].residual() > 0) {
                        int v(E[it].to);
                        if(dist[v] > dist[u] + E[it].cost) {
                            dist[v] = dist[u] + E[it].cost; tr[v] = it;
                            if(!inq[v]) { inq[v] = 1; qu.push(v); }
                        }
                    }
                }
            }
            return (dist[t] < 1e9+7);
        }

        ii getFlow(int s, int t) {
            for (int i = 0; i < int(E.size()); ++i) E[i].flow = 0;
            int totFlow(0), totCost(0);
            while(FordBellman(s, t)) {
                int delta(1e9+7);
                for (int u = t; u != s; u = E[tr[u]].from)
                    delta = min(delta, E[tr[u]].residual());
                for (int u = t; u != s; u = E[tr[u]].from)
                    E[tr[u]].flow += delta, E[tr[u] ^ 1].flow -= delta;
                totFlow += delta, totCost += delta * dist[t];
            }
            return ii(totFlow, totCost);
        }
};