#include "../utilities/template.h"
#include "../../content/math/FWHT.h"

int main() {
	mt19937 rng(9);
	rep(it,0,500) {
		int n = 1 << (rng() % 9);
		vector<ll> a(n), b(n), c(n);
		for (auto& x : a) x = rng() % MOD;
		for (auto& x : b) x = rng() % MOD;
		rep(i,0,n) rep(j,0,n) c[i ^ j] = (c[i ^ j] + a[i] * b[j]) % MOD;
		vector<ll> fa(a), fb(b);
		FWHT(fa), FWHT(fb);
		rep(i,0,n) fa[i] = fa[i] * fb[i] % MOD;
		FWHT(fa, true);
		assert(fa == c);
		vector<ll> id(a);
		FWHT(id), FWHT(id, true);
		assert(id == a);
	}
	cout << "Tests passed!" << endl;
}
