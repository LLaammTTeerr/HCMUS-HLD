/**
 * Author: HCMUS-HLD
 * Description: DSU keeping parity to the root. add(a,b) says
 * a and b have different colours; ok(v) tells whether v's
 * component is still bipartite. par(v) = colour of v relative
 * to its root. Nodes 0..n-1.
 * Time: O(\alpha(N)) amortized.
 */
#pragma once

struct BipDSU {
	vi p, d, rk, bip;
	BipDSU(int n) : p(n), d(n), rk(n), bip(n, 1) {
		iota(all(p), 0);
	}
	int find(int v) { // also sets d[v] = parity to root
		if (p[v] == v) return v;
		int r = find(p[v]);
		d[v] ^= d[p[v]]; return p[v] = r;
	}
	void add(int a, int b) {
		int x = find(a), y = find(b), w = d[a] ^ d[b] ^ 1;
		if (x == y) { if (w) bip[x] = 0; return; }
		if (rk[x] < rk[y]) swap(x, y);
		p[y] = x, d[y] = w, bip[x] &= bip[y];
		rk[x] += rk[x] == rk[y];
	}
	bool ok(int v) { return bip[find(v)]; }
	int par(int v) { find(v); return d[v]; }
};
