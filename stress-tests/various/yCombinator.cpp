#include "../utilities/template.h"

#include "../../content/various/yCombinator.h"

int main() {
	auto fib = y_combinator([&](auto self, int n) -> ll {
		return n < 2 ? n : self(n - 1) + self(n - 2);
	});
	assert(fib(0) == 0 && fib(1) == 1 && fib(30) == 832040);
	// const object, recursion over a tree
	vector<vi> g(1000);
	rep(i,1,1000) g[(i - 1) / 2].push_back(i);
	const auto cnt = y_combinator([&](auto self, int u) -> int {
		int s = 1;
		for (int v : g[u]) s += self(v);
		return s;
	});
	vi sub(1000, 1); // brute: children have larger indices
	for (int u = 999; u > 0; u--) sub[(u - 1) / 2] += sub[u];
	rep(u,0,1000) assert(cnt(u) == sub[u]);
	cout << "Tests passed!" << endl;
}
