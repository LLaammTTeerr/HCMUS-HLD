#include "../utilities/template.h"
#include "../../content/data-structure/BitsetTree.h"

int main() {
	mt19937 rng(9);
	const int U = 1 << 18;
	rep(it,0,6) {
		bst.init();
		set<int> ref;
		int span = it < 3 ? 300 : U; // dense and sparse
		rep(q,0,100000) {
			int x = (int)(rng() % span), op = rng() % 3;
			if (op == 0) {
				bst.update(x);
				if (!ref.erase(x)) ref.insert(x);
			} else if (op == 1) {
				auto i = ref.lower_bound(x);
				assert(bst.walk_forward(x) == (i == ref.end() ? -1 : *i));
			} else {
				auto i = ref.lower_bound(x);
				assert(bst.walk_backward(x) ==
					(i == ref.begin() ? -1 : *prev(i)));
			}
		}
		assert(bst.walk_forward(U - 1) ==
			(ref.count(U - 1) ? U - 1 : -1));
	}
	cout << "Tests passed!" << endl;
}
