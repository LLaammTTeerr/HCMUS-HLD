/**
 * Author: HCMUS-HLD
 * Description: Global min cut of an undirected graph given as a
 * weighted adjacency matrix. Returns \{cut weight, vertices of one
 * side\}. For $n = 1$ returns \{INF, \{\}\}.
 * Time: $O(V^3)$
 */
#pragma once

pair<ll, vi> stoerWagner(vector<vector<ll>> w) {
	int n = sz(w);
	vector<vi> grp(n); // original vertices merged into i
	rep(i, 0, n) grp[i] = {i};
	vi id(n); iota(all(id), 0); // alive vertices
	ll best = LLONG_MAX; vi bestSet;
	while (sz(id) > 1) {
		int k = sz(id), prev = -1, last = -1;
		vector<ll> d(k); vector<char> in(k);
		rep(step, 0, k) {
			int sel = -1;
			rep(i, 0, k) if (!in[i] && (sel < 0 || d[i] > d[sel]))
				sel = i;
			in[sel] = 1; prev = last; last = sel;
			rep(i, 0, k) if (!in[i]) d[i] += w[id[sel]][id[i]];
		}
		if (d[last] < best)
			best = d[last], bestSet = grp[id[last]];
		int a = id[prev], b = id[last]; // merge b into a
		rep(i, 0, k) {
			w[a][id[i]] += w[b][id[i]];
			w[id[i]][a] = w[a][id[i]];
		}
		grp[a].insert(grp[a].end(), all(grp[b]));
		id.erase(id.begin() + last);
	}
	return {best, bestSet};
}
