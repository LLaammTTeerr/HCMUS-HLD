#include "../utilities/template.h"
#include "../../content/graph/TwoSat.h"

mt19937 rng(8);
int rnd(int a, int b) { return a + (int)(rng() % (b - a + 1)); }

int main() {
	rep(it, 0, 30000) {
		int n = rnd(1, 8), m = rnd(0, 12);
		vector<array<int, 4>> cl;
		TWO_SAT S(n);
		rep(i, 0, m) {
			array<int, 4> c = {rnd(1, n), rnd(0, 1), rnd(1, n), rnd(0, 1)};
			cl.push_back(c); S.add_disjunction(c[0], c[1], c[2], c[3]);
		}
		auto sat = [&](auto val) { // val(x) = truth of variable x
			for (auto [a, na, b, nb] : cl)
				if (!((val(a) ^ na) || (val(b) ^ nb))) return false;
			return true;
		};
		bool any = false;
		rep(mk, 0, 1 << n) if (sat([&](int x) { return (mk >> (x - 1)) & 1; }))
			any = true;
		vector<bool>* res = S.find_solution();
		assert((res != nullptr) == any);
		if (res) {
			assert(sat([&](int x) { return (bool)(*res)[x]; }));
			delete res;
		}
	}
	cout << "Tests passed!" << endl;
}
