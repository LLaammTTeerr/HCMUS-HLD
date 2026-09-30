#include "../utilities/template.h"
#include "../../content/string/AhoCorasick.h"

int main() {
	mt19937 rng(17);
	rep(it,0,1000) {
		AhoCorasick::T.assign(1, AhoCorasick::Node());
		int K = 1 + rng() % 3;
		vector<string> pats(1 + rng() % 8);
		for (auto& p : pats) {
			int l = 1 + rng() % 4;
			rep(i,0,l) p += char('a' + rng() % K);
			AhoCorasick::insert(p);
		}
		AhoCorasick::build();
		rep(q,0,20) {
			string s;
			rep(i,0,rng()%40) s += char('a' + rng() % K);
			ll exp = 0;
			for (auto& p : pats) rep(i,0,sz(s))
				exp += s.compare(i, sz(p), p) == 0 && i + sz(p) <= sz(s);
			assert(AhoCorasick::count(s) == exp);
		}
	}
	cout << "Tests passed!" << endl;
}
