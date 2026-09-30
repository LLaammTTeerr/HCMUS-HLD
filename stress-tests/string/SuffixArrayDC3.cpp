#include "../utilities/template.h"
#include "../../content/string/SuffixArrayDC3.h"

int main() {
	mt19937 rng(20);
	rep(it,0,3000) {
		int n = rng() % 40, K = 1 + rng() % 3;
		string s;
		rep(i,0,n) s += char(rng() % 5 ? 'a' + rng() % K : 200);
		SuffixArray S(s);
		vi ord(n);
		iota(all(ord), 0);
		sort(all(ord), [&](int a, int b) {
			return lexicographical_compare(s.begin() + a, s.end(),
				s.begin() + b, s.end(), [](char x, char y) {
					return (unsigned char)x < (unsigned char)y; });
		});
		rep(i,1,n+1) {
			assert(S.sa[i] == ord[i - 1] + 1 && S.pos[S.sa[i]] == i);
			if (i < n) {
				int k = 0, a = ord[i - 1], b = ord[i];
				while (a + k < n && b + k < n && s[a + k] == s[b + k]) k++;
				assert(S.lcp[i] == k);
			}
		}
	}
	// long string sanity
	string big(100000, 'a');
	SuffixArray S(big);
	rep(i,1,100001) assert(S.sa[i] == 100001 - i);
	cout << "Tests passed!" << endl;
}
