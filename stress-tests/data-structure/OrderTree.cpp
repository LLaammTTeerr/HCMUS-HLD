#include "../utilities/template.h"
#include "../../content/data-structure/OrderTree.h"

int main() {
	example();
	mt19937 rng(6);
	rep(it,0,50) {
		Tree<int> t; set<int> ref;
		rep(q,0,2000) {
			int x = (int)(rng() % 200) - 100, op = rng() % 4;
			if (op == 0) t.insert(x), ref.insert(x);
			else if (op == 1) t.erase(x), ref.erase(x);
			else if (op == 2) {
				int k = (int)distance(ref.begin(), ref.lower_bound(x));
				assert((int)t.order_of_key(x) == k);
			} else if (sz(ref)) {
				int k = rng() % sz(ref);
				assert(*t.find_by_order(k) == *next(ref.begin(), k));
			}
			assert(sz(t) == sz(ref));
		}
		assert(t.find_by_order(sz(ref)) == t.end());
	}
	cout << "Tests passed!" << endl;
}
