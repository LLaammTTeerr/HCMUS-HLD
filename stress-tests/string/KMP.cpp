#include "../utilities/template.h"
#include "../../content/string/KMP.h"

int main() {
	mt19937 rng(15);
	rep(it,0,3000) {
		int n = rng() % 30, K = 1 + rng() % 3;
		string s = " ";
		rep(i,0,n) s += char('a' + rng() % K);
		vi lps = kmp(s);
		assert(sz(lps) == n + 1);
		rep(i,1,n+1) {
			int b = 0;
			rep(len,1,i)
				if (s.substr(1, len) == s.substr(i - len + 1, len)) b = len;
			assert(lps[i] == b);
		}
		// pattern search
		string P, T;
		rep(i,0,1+rng()%3) P += char('a' + rng() % K);
		rep(i,0,rng()%30) T += char('a' + rng() % K);
		vi l = kmp(" " + P + "#" + T);
		int cnt = 0, exp = 0;
		rep(i,0,sz(T)) cnt += l[sz(P) + 2 + i] == sz(P);
		rep(i,0,sz(T)) exp += T.compare(i, sz(P), P) == 0 &&
			i + sz(P) <= sz(T);
		assert(cnt == exp);
	}
	cout << "Tests passed!" << endl;
}
