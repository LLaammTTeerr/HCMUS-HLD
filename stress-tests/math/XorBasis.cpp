#include "../utilities/template.h"
#include "../../content/math/XorBasis.h"

int main() {
	mt19937 rng(10);
	rep(it,0,1500) {
		int bits = 1 + rng() % 12, cnt = rng() % 8;
		Node A, B;
		vi va, vb;
		rep(i,0,cnt) { int x = rng() % (1 << bits); A.insertVector(x); va.push_back(x); }
		rep(i,0,(int)(rng() % 6)) { int x = rng() % (1 << bits); B.insertVector(x); vb.push_back(x); }
		auto span = [&](const vi& v) {
			set<int> s = {0};
			for (int x : v) { set<int> t = s; for (int y : s) t.insert(y ^ x); s = t; }
			return vi(all(s));
		};
		vi sa = span(va);
		assert(A.szBasis == __builtin_ctz(sz(sa)));
		rep(x,0,1 << bits) assert(A.checkVector(x) == binary_search(all(sa), x));
		rep(k,0,sz(sa)) {
			assert(A.query(k + 1) == sa[k]);
			assert(A.getValPos(sa[k]) == k + 1);
		}
		assert(A.getMax() == sa.back());
		vi all_ = va; all_.insert(all_.end(), all(vb));
		vi sab = span(all_);
		Node M = A.mergeNode(B);
		rep(x,0,1 << bits) assert(M.checkVector(x) == binary_search(all(sab), x));
	}
	Node big;
	big.insertVector(INT_MAX); big.insertVector(1 << 30);
	assert(big.getMax() == INT_MAX && big.query(4) == INT_MAX);
	cout << "Tests passed!" << endl;
}
