#include "../utilities/template.h"
#include "../../content/data-structure/LiChaoTreePtr.h"

int main() {
	mt19937 rng(3);
	rep(it,0,500) {
		int L = -(int)(rng() % 50), R = (int)(rng() % 50);
		LiChao* root = new LiChao();
		vector<array<ll, 4>> lines; // a, b, u, v
		rep(q,0,100) {
			if (rng() % 2) {
				ll a = (ll)(rng() % 2000001) - 1000000;
				ll b = (ll)(rng() % 2000000001) - 1000000000;
				int u = L, v = R;
				if (rng() % 2) {
					u = L + (int)(rng() % (R - L + 1));
					v = L + (int)(rng() % (R - L + 1));
					if (u > v) swap(u, v);
				}
				root->update(L, R, u, v, LiLine(a, b));
				lines.push_back({a, b, u, v});
			} else {
				int x = L + (int)(rng() % (R - L + 1));
				ll best = -INF;
				for (auto& [a, b, u, v] : lines)
					if (u <= x && x <= v) best = max(best, a * x + b);
				assert(root->query(L, R, x) == best);
			}
		}
	}
	// minimum via negation, large domain
	LiChao* root = new LiChao();
	int L = -1000000000, R = 1000000000;
	vector<pair<ll, ll>> ls;
	rep(i,0,2000) {
		ll a = (ll)(rng() % 2000001) - 1000000;
		ll b = (ll)(rng() % 2000000001) - 1000000000;
		root->update(L, R, L, R, LiLine(-a, -b)), ls.push_back({a, b});
		int x = (int)(rng() % 2000000001) - 1000000000;
		ll mn = LLONG_MAX;
		for (auto [a2, b2] : ls) mn = min(mn, a2 * x + b2);
		assert(-root->query(L, R, x) == mn);
	}
	cout << "Tests passed!" << endl;
}
