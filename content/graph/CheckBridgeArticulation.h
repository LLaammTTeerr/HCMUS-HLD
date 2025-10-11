#pragma once

void tarjan(int u, int p_id) {
    low[u] = num[u] = ++num[0];
    int numChild = 0;
    for (auto [v, id] : adj[u])
        if(!num[v]) {
            tarjan(v, id);
            low[u] = min(low[u], low[v]);
            ++numChild;
            if(low[v] >= num[u]) {} // (u, v) la cau
            if(p_id != -1 && low[v] >= num[u]) {} // u la khop
        } else if(id != p_id) low[u] = min(low[u], num[v]);
    }
    if(p == -1 && sz >= 2) {} // u la khop
}