#include "../utilities/template.h"
#include "../../content/string/Manacher.h"

bool pal(const string& s, int l, int r) { // 0-indexed [l, r]
	for (; l < r; l++, r--) if (s[l] != s[r]) return false;
	return true;
}

int main() {
	mt19937 rng(16);
	rep(it,0,3000) {
		int n = 1 + rng() % 30, K = 1 + rng() % 3;
		string s;
		rep(i,0,n) s += char('a' + rng() % K);
		Manacher M(s);
		rep(i,1,n+1) { // s[i-k..i+k] 1-indexed = s[i-1-k..i-1+k]
			int k = 0;
			while (i - 1 - (k + 1) >= 0 && i - 1 + k + 1 < n &&
				pal(s, i - 2 - k, i + k)) k++;
			assert(M.pod[i] == k);
		}
		rep(i,1,n) { // s[i-k+1..i+k] 1-indexed = s[i-k..i+k-1]
			int k = 0;
			while (i - (k + 1) >= 0 && i + k < n &&
				pal(s, i - k - 1, i + k)) k++;
			assert(M.pev[i] == k);
		}
	}
	cout << "Tests passed!" << endl;
}
