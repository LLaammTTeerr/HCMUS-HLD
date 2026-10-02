#include "../utilities/template.h"
#include "../../content/string/SuffixAutomaton.h"

int main() {
	mt19937 rng(21);
	rep(it, 0, 3000) {
		int n = int(rng() % 25), c = int(rng() % 3) + 1;
		string s(n, 'a');
		for (char& ch : s) ch = char('a' + rng() % c);
		SAM sa;
		for (char ch : s) sa.extend(ch - 'a');
		assert(sz(sa.t) <= max(1, 2 * n));
		map<string, ll> cnt; // substring -> occurrences
		rep(i, 0, n) rep(j, i + 1, n + 1) cnt[s.substr(i, j - i)]++;
		ll distinct = 0;
		rep(v, 1, sz(sa.t)) distinct += sa.t[v].len - sa.t[sa.t[v].link].len;
		assert(distinct == sz(cnt));
		vector<ll> occ = sa.occ();
		rep(q, 0, 40) { // walk random strings: accepted iff substring
			int len = int(rng() % (n + 2));
			string w(len, 'a');
			for (char& ch : w) ch = char('a' + rng() % (c + 1));
			if (q % 2 && n) { // force a real substring
				int i = int(rng() % n);
				w = s.substr(i, rng() % (n - i) + 1);
			}
			int v = 0;
			for (char ch : w) if (v >= 0) v = sa.t[v].nx[ch - 'a'] ? sa.t[v].nx[ch - 'a'] : -1;
			bool sub = w.empty() || cnt.count(w);
			assert((v >= 0) == sub);
			if (sub && !w.empty()) {
				assert(occ[v] == cnt[w]);
				assert(sa.t[sa.t[v].link].len < sz(w) && sz(w) <= sa.t[v].len);
			}
		}
	}
	SAM big; // speed
	rep(i, 0, 1000000) big.extend(int(rng() % 26));
	assert(sz(big.t) <= 2000000);
	cout << "Tests passed!" << endl;
}
