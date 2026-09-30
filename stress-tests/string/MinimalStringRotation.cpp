#include "../utilities/template.h"
#include "../../content/string/MinimalStringRotation.h"

int main() {
	mt19937 rng(21);
	rep(it,0,5000) {
		int n = 1 + rng() % 20, K = 1 + rng() % 3;
		string s;
		rep(i,0,n) s += char('a' + rng() % K);
		int best = 0;
		rep(i,1,n) if (s.substr(i) + s.substr(0, i) <
			s.substr(best) + s.substr(0, best)) best = i;
		assert(minmove(s) == best);
	}
	cout << "Tests passed!" << endl;
}
