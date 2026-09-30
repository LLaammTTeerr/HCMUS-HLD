#include "../utilities/template.h"
#include "../../content/data-structure/ZKWSegTree.h"

int main() {
	mt19937 rng(1);
	auto rnd = [&]() { return (ll)(rng() % 2000000001) - 1000000000; };
	rep(it,0,3000) {
		int n = rng() % 40;
		vector<ll> a(n);
		for (ll& x : a) x = rnd();
		ZKW st = it % 2 ? ZKW(a) : ZKW(n);
		if (it % 2 == 0) rep(i,0,n) st.update(i, a[i]);
		rep(q,0,100) {
			if (!n) break;
			if (rng() % 2) {
				int p = rng() % n;
				a[p] = rnd(); st.update(p, a[p]);
			} else {
				int l = rng() % (n + 1), r = rng() % (n + 1);
				if (l > r) swap(l, r);
				ll s = 0;
				rep(i,l,r) s += a[i];
				assert(st.query(l, r) == s);
			}
		}
	}
	ZKW e(0); assert(e.query(0, 0) == 0);
	ZKW d(5, 3); assert(d.query(0, 5) == 15 && d.query(1, 3) == 6);
	cout << "Tests passed!" << endl;
}
