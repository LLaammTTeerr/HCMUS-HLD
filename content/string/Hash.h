/**
 * Author: HCMUS-HLD
 * Description: Polynomial hash with NMOD moduli. H h(s);
 * h.get(l, r) is the hash of s[l, r) (0-indexed).
 * Hashes of equal-length substrings are comparable with ==.
 * Time: O(N) build, O(NMOD) per query.
 */
#pragma once

const int NMOD = 2, BASE = 131;
const ll MD[] = {(ll)1e9 + 2277, (ll)1e9 + 5277};
typedef array<ll, NMOD> HV;

struct H {
	vector<HV> h, pw;
	H(const string& s) : h(sz(s) + 1), pw(sz(s) + 1) {
		rep(j,0,NMOD) h[0][j] = 0, pw[0][j] = 1;
		rep(i,0,sz(s)) rep(j,0,NMOD) {
			h[i+1][j] = (h[i][j] * BASE + (unsigned char)s[i])
				% MD[j];
			pw[i+1][j] = pw[i][j] * BASE % MD[j];
		}
	}
	HV get(int l, int r) {
		HV res;
		rep(j,0,NMOD) res[j] = ((h[r][j] - h[l][j] * pw[r-l][j])
			% MD[j] + MD[j]) % MD[j];
		return res;
	}
};
