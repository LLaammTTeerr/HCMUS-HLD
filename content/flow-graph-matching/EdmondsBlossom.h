/**
 * Usage: maximum matching on general graph.
 * Time: $O(V^3)$ 
*/

#pragma once

struct Blossom {
    int n;
    vector<vector<int>> g;
    vector<int> match, p, base, q;
    vector<char> used, inBlossom;
    Blossom(int n) : n(n), g(n), match(n, -1), p(n), base(n), q(n), used(n), inBlossom(n) {}
    void addEdge(int u, int v) { g[u].push_back(v); g[v].push_back(u); }
    int lca(int a, int b) {
        vector<char> mark(n, 0);
        while (true) { a = base[a]; mark[a] = 1; if (match[a] == -1) break; a = p[match[a]]; }
        while (true) { b = base[b]; if (mark[b]) return b; b = p[match[b]]; }
    }
    void markPath(int v, int b, int children) {
        for (; base[v] != b; v = p[match[v]]) {
            inBlossom[base[v]] = inBlossom[base[match[v]]] = 1;
            p[v] = children; children = match[v];
        }
    }
    int findPath(int root) {
        fill(used.begin(), used.end(), 0); fill(p.begin(), p.end(), -1);
        for (int i = 0; i < n; i++) base[i] = i;
        used[root] = 1; int qh = 0, qt = 0; q[qt++] = root;
        while (qh < qt) {
            int v = q[qh++];
            for (int to : g[v]) {
                if (base[v] == base[to] || match[v] == to) continue;
                if (to == root || (match[to] != -1 && p[match[to]] != -1)) {   // exist cycle with odd vertices -> have blossom
                    int curbase = lca(v, to);
                    fill(inBlossom.begin(), inBlossom.end(), 0);
                    markPath(v, curbase, to); markPath(to, curbase, v);
                    for (int i = 0; i < n; i++) if (inBlossom[base[i]]) {
                        base[i] = curbase;
                        if (!used[i]) { used[i] = 1; q[qt++] = i; }
                    }
                } else if (p[to] == -1) {
                    p[to] = v;
                    if (match[to] == -1) return to; // augment path
                    to = match[to]; used[to] = 1; q[qt++] = to;
                }
            }
        }
        return -1;
    }
    int solve() {
        for (int i = 0; i < n; i++) if (match[i] == -1) // greedy init
            for (int to : g[i]) if (match[to] == -1) { match[i] = to; match[to] = i; break; }
        for (int i = 0; i < n; i++) if (match[i] == -1) {
            int v = findPath(i);
            while (v != -1) { int pv = p[v], ppv = match[pv]; match[v] = pv; match[pv] = v; v = ppv; }
        }
        int res = 0;
        for (int i = 0; i < n; i++) if (match[i] > i) res++;
        return res;
    }
};