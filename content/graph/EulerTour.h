#pragma once
struct Edge {
    int target, id;

    Edge(int _target, int _id): target(_target), id(_id) {}
};

vector<Edge> adj[N];
bool used_edge[M];

list<int> euler_walk(int u) {
    list<int> ans;
    ans.push_back(u);

    while (!adj[u].empty()) {
        int v = adj[u].back().target;
        int eid = adj[u].back().id;

        adj[u].pop_back();
        if (used_edge[eid]) continue;

        used_edge[eid] = true;

        u = v;
        ans.push_back(u);
    }

    for (auto it = ++ans.begin(); it != ans.end(); ++it) {
        auto t = euler_walk(*it);
        t.pop_back();
        ans.splice(it, t);
    }

    return ans;
}