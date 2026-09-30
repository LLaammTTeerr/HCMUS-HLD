#include "../utilities/template.h"
#include "../../content/dp/AliensTrick.h"

// Choose exactly k pairwise non-adjacent elements with maximum sum
// (concave in k). Values may be negative.
int main() {
	mt19937 rng(14);
	rep(it,0,3000) {
		int n = 1 + rng() % 14;
		vector<ll> a(n);
		for (ll& x : a) x = (ll)(rng() % 2000001) - 1000000;
		int k = rng() % ((n + 1) / 2 + 1);
		// brute: dp[i][c][took last]
		const ll NEG = LLONG_MIN / 4;
		vector<vector<array<ll, 2>>> dp(n + 1,
			vector<array<ll, 2>>(n + 1, {NEG, NEG}));
		dp[0][0][0] = 0;
		rep(i,0,n) rep(c,0,n+1) rep(t,0,2) if (dp[i][c][t] > NEG) {
			dp[i+1][c][0] = max(dp[i+1][c][0], dp[i][c][t]);
			if (!t && c < n)
				dp[i+1][c+1][1] = max(dp[i+1][c+1][1], dp[i][c][t] + a[i]);
		}
		ll exp = max(dp[n][k][0], dp[n][k][1]);
		auto calc = [&](ll lam) {
			// max (value, count) with each chosen item costing lam
			pair<ll, ll> f0 = {0, 0}, f1 = {NEG, 0};
			rep(i,0,n) {
				pair<ll, ll> t1 = {f0.first + a[i] - lam, f0.second + 1};
				f0 = max(f0, f1), f1 = t1;
			}
			return max(f0, f1);
		};
		assert(aliens(k, calc) == exp);
	}
	cout << "Tests passed!" << endl;
}
