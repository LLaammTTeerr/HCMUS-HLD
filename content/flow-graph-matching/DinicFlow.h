/**
 * Time: $O(V^2 * E)$ for general case
 *  $O(E * \sqrt(E))$ for unit network
*/ 
#pragma once

struct DinicFlow {
    vector<int> flow, capa;
    vector<int> point, next, head, work, dist;
    int numNode, numEdge;

    DinicFlow(int _n = 0) {
        numNode = _n, numEdge = 0;
        dist = work = vector<int>(_n + 7, 0);
        head = vector<int>(_n + 7, -1);
    }

    void addEdge(int u, int v, int c1, int c2 = 0) {
        point.push_back(v), capa.push_back(c1), flow.push_back(0);
        next.push_back(head[u]), head[u] = numEdge++;
        point.push_back(u), capa.push_back(c2), flow.push_back(0);
        next.push_back(head[v]), head[v] = numEdge++;
    }

    bool bfs(int s, int t) {
        queue<int> qu;
        for (int i = 1; i <= numNode; ++i) dist[i] = -1;
        dist[s] = 0; qu.push(s);
        while(!qu.empty()) {
            int u(qu.front()); qu.pop();
            for (int i = head[u]; i >= 0; i = next[i])
                if(flow[i] < capa[i] && dist[point[i]] < 0) {
                    dist[point[i]] = dist[u] + 1;
                    qu.push(point[i]);
                }
        }
        return (dist[t] >= 0);
    }

    int dfs(int s, int t, int fl) {
        if(s == t) return fl;
        for (int &i = work[s]; i >= 0; i = next[i])
            if(flow[i] < capa[i] && dist[point[i]] == dist[s] + 1) {
                int d = dfs(point[i], t, min(fl, capa[i] - flow[i]));
                if(!d) continue;
                flow[i] += d, flow[i ^ 1] -= d;
                return d;
            }
        return 0;
    }

    int maxFlow(int s, int t) {
        for (int i = 0; i < int(flow.size()); ++i) flow[i] = 0;
        int totFlow(0);
        while(bfs(s, t)) {
            for (int i = 1; i <= numNode; ++i) work[i] = head[i];
            while(true) {
                int d = dfs(s, t, 1e9+7); totFlow += d;
                if(!d) break;
            }
        }
        return totFlow;
    }
};