#include "../utilities/template.h"
#include "../../content/string/ZFunction.h"

int main() {
	mt19937 rng(12);
	assert(Z("").empty());
	rep(it, 0, 100000) {
		int n = int(rng() % 20) + 1, c = int(rng() % 3) + 1;
		string s(n, 'a');
		for (char& ch : s) ch = char('a' + rng() % c);
		vi z = Z(s);
		assert(sz(z) == n);
		rep(i, 0, n) {
			int k = 0;
			while (i + k < n && s[k] == s[i + k]) k++;
			assert(z[i] == k);
		}
	}
	cout << "Tests passed!" << endl;
}
