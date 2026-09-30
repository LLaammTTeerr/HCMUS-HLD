#include "../utilities/template.h"
#include "../../content/string/SuffixArray.h"

int main() {
	mt19937 rng(19);
	using namespace SuffixArray;
	rep(it,0,2000) {
		int n = 1 + rng() % 40, K = 1 + rng() % 3;
		str.clear();
		rep(i,0,n) str += char('a' + rng() % K);
		strLen = n;
		buildSA();
		vi ord(n);
		iota(all(ord), 0);
		sort(all(ord), [&](int a, int b) {
			return str.substr(a) < str.substr(b); });
		rep(i,0,n) assert(sa[i] == ord[i] && pos[sa[i]] == i);
		rep(i,0,n-1) {
			int k = 0;
			while (ord[i] + k < n && ord[i+1] + k < n &&
				str[ord[i] + k] == str[ord[i+1] + k]) k++;
			assert(lcp[i] == k);
		}
	}
	cout << "Tests passed!" << endl;
}
