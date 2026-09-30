/**
 * Author: HCMUS-HLD
 * Description: Polynomial hash as a value type. HV = hash of a
 * sequence plus its length; a + b is the hash of the concatenation
 * (associative, identity HV()), so HV works in segment trees for
 * dynamic strings. H h(s): h.get(l, r) = hash of s[l, r), comparable
 * across different strings. Call initHash() once. Elements must be
 * in $[0, MD)$; lengths $< $ MAXL.
 * Usage: initHash(); H a(s), b(t);
 * a.get(0, 3) + b.get(2, 4) == a.get(5, 9)
 * Time: O(N) build, O(NMOD) per get / +
 */
#pragma once

const int NMOD = 2, BASE = 131, MAXL = 1e6 + 5;
const ll MD[] = {(ll)1e9 + 2277, (ll)1e9 + 5277};
array<ll, NMOD> pw[MAXL];
void initHash() {
	rep(j,0,NMOD) pw[0][j] = 1;
	rep(i,1,MAXL) rep(j,0,NMOD) pw[i][j] = pw[i-1][j] * BASE % MD[j];
}

struct HV {
	array<ll, NMOD> v{}; int len = 0;
	HV() {}
	HV(ll c) : len(1) { rep(j,0,NMOD) v[j] = c; }
	HV operator+(const HV& b) const { // concatenation
		HV r; r.len = len + b.len;
		rep(j,0,NMOD) r.v[j] = (v[j] * pw[b.len][j] + b.v[j]) % MD[j];
		return r;
	}
	bool operator==(const HV& b) const {
		return len == b.len && v == b.v;
	}
};

struct H {
	vector<HV> h;
	H(const string& s) : h(sz(s) + 1) {
		rep(i,0,sz(s)) h[i+1] = h[i] + HV((unsigned char)s[i]);
	}
	HV get(int l, int r) { // [l, r)
		HV res; res.len = r - l;
		rep(j,0,NMOD) res.v[j] = ((h[r].v[j] - h[l].v[j] *
			pw[r-l][j]) % MD[j] + MD[j]) % MD[j];
		return res;
	}
};
