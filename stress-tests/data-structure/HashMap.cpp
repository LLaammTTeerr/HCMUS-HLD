#include "../utilities/template.h"
#include "../../content/data-structure/HashMap.h"

int main() {
	mt19937_64 rng(7);
	unordered_map<ll, int> ref;
	rep(q,0,300000) {
		ll k = q % 3 ? (ll)(rng() % 1000) - 500 : (ll)rng();
		int op = rng() % 3;
		if (op == 0) { int v = (int)rng(); h[k] = v, ref[k] = v; }
		else if (op == 1) { h.erase(k), ref.erase(k); }
		else {
			auto it = h.find(k); auto jt = ref.find(k);
			assert((it == h.end()) == (jt == ref.end()));
			if (jt != ref.end()) assert(it->second == jt->second);
		}
	}
	assert(sz(h) == sz(ref));
	for (auto [k, v] : ref) assert(h[k] == v);
	cout << "Tests passed!" << endl;
}
