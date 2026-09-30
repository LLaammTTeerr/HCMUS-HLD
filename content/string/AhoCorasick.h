/**
 * Author: HCMUS-HLD
 * Description: Aho-Corasick over alphabet [A, A+K).
 * insert() all patterns, then build(); count(s) = total
 * number of pattern occurrences in s. After build, cnt[v] =
 * patterns that are suffixes of node v, nxt is the full
 * automaton, link the suffix link.
 * Time: O(K \cdot \sum |P|) build, O(|s|) count.
 */
#pragma once

namespace AhoCorasick {
	const int K = 26; const char A = 'a';
	struct Node { int nxt[K] = {}, link = 0; ll cnt = 0; };
	vector<Node> T(1);
	int insert(const string &s) {
		int v = 0;
		for (char ch : s) {
			int c = ch - A;
			if (!T[v].nxt[c])
				T[v].nxt[c] = sz(T), T.emplace_back();
			v = T[v].nxt[c];
		}
		T[v].cnt++; return v;
	}
	void build() {
		queue<int> q; q.push(0);
		while (sz(q)) {
			int v = q.front(), u = T[v].link; q.pop();
			if (v) T[v].cnt += T[u].cnt;
			rep(c,0,K) {
				int &w = T[v].nxt[c];
				if (w) T[w].link = v ? T[u].nxt[c] : 0, q.push(w);
				else w = T[u].nxt[c];
			}
		}
	}
	ll count(const string &s) {
		int v = 0; ll r = 0;
		for (char ch : s) v = T[v].nxt[ch - A], r += T[v].cnt;
		return r;
	}
}
