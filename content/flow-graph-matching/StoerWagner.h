/**
 * Usage: global min cut (all source all sink)
 *  
 *  Input adjacent matrix w (weighted). Output total weight and vertices list of a part.
 *
 * Time: $O(V^3)$ 
*/

pair<ll, vector<int>> stoerWagner(vector<vector<ll>> w) {
    int n = w.size();
    vector<vector<int>> grp(n); // Original vertices have merged to vertex i
    for (int i = 0; i < n; i++) grp[i] = {i};
    vector<int> id(n); iota(id.begin(), id.end(), 0); // alive vertex
    ll best = INF; vector<int> bestSet;
    while ((int)id.size() > 1) {
        int k = id.size();
        vector<ll> d(k, 0); vector<char> in(k, 0);
        int prev = -1, last = -1;
        for (int step = 0; step < k; step++) {
            int sel = -1;
            for (int i = 0; i < k; i++) if (!in[i] && (sel < 0 || d[i] > d[sel])) sel = i;
            in[sel] = 1; prev = last; last = sel;
            for (int i = 0; i < k; i++) if (!in[i]) d[i] += w[id[sel]][id[i]];
        }
        if (d[last] < best) { best = d[last]; bestSet = grp[id[last]]; }
        int a = id[prev], b = id[last]; // merge b to a
        for (int i = 0; i < k; i++) { w[a][id[i]] += w[b][id[i]]; w[id[i]][a] = w[a][id[i]]; }
        grp[a].insert(grp[a].end(), grp[b].begin(), grp[b].end());
        id.erase(id.begin() + last);
    }
    return {best, bestSet};
}