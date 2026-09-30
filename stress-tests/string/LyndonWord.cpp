#include "../utilities/template.h"
#include "../../content/string/LyndonWord.h"

bool isLyndon(const string& w) {
	rep(i,1,sz(w)) if (!(w < w.substr(i) + w.substr(0, i))) return false;
	return true;
}

int main() {
	mt19937 rng(22);
	auto* old = cout.rdbuf();
	rep(it,0,3000) {
		int n = 1 + rng() % 25, K = 1 + rng() % 3;
		string s;
		rep(i,0,n) s += char('a' + rng() % K);
		stringstream out;
		cout.rdbuf(out.rdbuf());
		lyndon(s);
		cout.rdbuf(old);
		vector<string> f; string w, cat;
		while (out >> w) f.push_back(w), cat += w;
		// the factorization into non-increasing Lyndon words is unique
		assert(cat == s);
		rep(i,0,sz(f)) {
			assert(isLyndon(f[i]));
			if (i) assert(f[i - 1] >= f[i]);
		}
	}
	cout << "Tests passed!" << endl;
}
