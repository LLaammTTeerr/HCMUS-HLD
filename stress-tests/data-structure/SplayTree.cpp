#include "../utilities/template.h"
#include "../../content/data-structure/SplayTree.h"
using namespace SplayTree;

void inorder(int x, vi& out) {
	if (!x) return;
	inorder(node[x].L, out), out.push_back(x), inorder(node[x].R, out);
}
int size(int x) { return x ? node[x].sz : 0; }

int main() {
	mt19937 rng(5);
	rep(it,0,300) {
		int n = 1 + rng() % 300;
		rep(i,0,n+2) node[i] = TNode();
		nArr = n;
		int rt = buildSplay(1, nArr);
		vi ref(n);
		iota(all(ref), 1);
		rep(q,0,200) {
			// cut a random segment [l, r) and move it to position p
			int l = rng() % (n + 1), r = rng() % (n + 1);
			if (l > r) swap(l, r);
			int A, B, C, D;
			split(rt, A, B, l);
			split(B, C, D, r - l);
			assert(size(A) == l && size(C) == r - l);
			int rest = join(A, D);
			int p = rng() % (n - (r - l) + 1);
			int X, Y;
			split(rest, X, Y, p);
			rt = join(join(X, C), Y);
			vi mid(ref.begin() + l, ref.begin() + r), oth;
			rep(i,0,n) if (i < l || i >= r) oth.push_back(ref[i]);
			ref.clear();
			ref.insert(ref.end(), oth.begin(), oth.begin() + p);
			ref.insert(ref.end(), all(mid));
			ref.insert(ref.end(), oth.begin() + p, oth.end());
			vi got; inorder(rt, got);
			assert(got == ref && size(rt) == n);
			int c = 1 + rng() % n;
			assert(locate(rt, c) == ref[c - 1]);
		}
	}
	cout << "Tests passed!" << endl;
}
