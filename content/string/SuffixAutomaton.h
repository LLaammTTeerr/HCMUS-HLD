/**
 * Author: HCMUS-HLD
 * Description: Suffix automaton over 'a'..'z'; state 0 is the
 * root and nx = 0 means no edge. A walk from 0 spells exactly the
 * substrings of s. Distinct substrings: sum over v > 0 of
 * len[v] - len[link[v]]. occ()[v] = occurrences of the
 * substrings ending in v. At most 2|s| states.
 * Usage: SAM sa; for (char c : s) sa.extend(c - 'a');
 * Time: O(N \cdot 26) build
 */
#pragma once

struct SAM {
	struct St { int len, link; array<int, 26> nx{}; };
	vector<St> t{{0, -1}};
	vector<bool> clone{0};
	int last = 0;
	void extend(int c) {
		int cur = sz(t), p = last;
		t.push_back({t[last].len + 1, 0}), clone.push_back(0);
		for (; p != -1 && !t[p].nx[c]; p = t[p].link)
			t[p].nx[c] = cur;
		if (p != -1) {
			int q = t[p].nx[c];
			if (t[p].len + 1 == t[q].len) t[cur].link = q;
			else {
				int cl = sz(t);
				t.push_back({t[p].len + 1, t[q].link, t[q].nx});
				clone.push_back(1);
				for (; p != -1 && t[p].nx[c] == q; p = t[p].link)
					t[p].nx[c] = cl;
				t[q].link = t[cur].link = cl;
			}
		}
		last = cur;
	}
	vector<ll> occ() {
		int n = sz(t);
		vector<ll> c(n);
		vi o(n);
		iota(all(o), 0);
		sort(all(o), [&](int a, int b) { return t[a].len > t[b].len; });
		for (int v : o) if (v) {
			c[v] += !clone[v];
			c[t[v].link] += c[v];
		}
		return c;
	}
};
