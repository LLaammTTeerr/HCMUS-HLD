#pragma once

struct Point {
    int x, y, xy, id;
} p[MAXN];

struct Edge {
    int u, v; ll w;
    Edge(int _u = 0, int _v = 0, ll _w = 0) : u(_u), v(_v), w(_w) {}
};

int nArr;

typedef pair<ll, int> pli;
namespace ManhattanSpanningTree {
    vector<int> idx;
    pli fen[MAXN];
    int nTree;
    
    void modify(int i, pli x) {
        for (; i > 0; i -= i & -i) fen[i] = min(fen[i], x);
    }
    
    pli get(int i) {
        pli res = {2e9+7, -1};
        for (; i <= nTree; i += i & -i) res = min(res, fen[i]);
        return res;
    }
    
    void buildSpan(vector<Edge> &edges) {
        sort(p + 1, p + nArr + 1, [](const Point &a, const Point &b) { return ii(a.x, a.y) < ii(b.x, b.y); });
        idx.clear();
        for (int i = 1; i <= nArr; ++i) {
            p[i].xy = p[i].y - p[i].x;
            idx.push_back(p[i].xy);
        }
        sort(idx.begin(), idx.end());
        idx.erase(unique(idx.begin(), idx.end()), idx.end());
        nTree = idx.size();
        for (int i = 1; i <= nTree; ++i) fen[i] = {2e9+7, -1};
        for (int i = 1; i <= nArr; ++i) p[i].xy = upper_bound(idx.begin(), idx.end(), p[i].xy) - idx.begin();
        for (int i = nArr; i > 0; --i) {
            ii v = get(p[i].xy);
            if(v.se != -1) edges.push_back(Edge(p[i].id, p[v.se].id, abs(p[i].x - p[v.se].x) + abs(p[i].y - p[v.se].y)));
            modify(p[i].xy, ii(p[i].x + p[i].y, i));
        }
    }
    
    void buildEdge(vector<Edge> &edges) {
        edges.clear();
        for (int loop = 0; loop < 4; ++loop) {
            buildSpan(edges);
            for (int i = 1; i <= nArr; ++i) swap(p[i].x, p[i].y);
            buildSpan(edges);
            for (int i = 1; i <= nArr; ++i) {
                swap(p[i].x, p[i].y);
                if(loop & 1) { p[i].y = -p[i].y; } 
                else p[i].x = -p[i].x;
            }
        }
    }
}