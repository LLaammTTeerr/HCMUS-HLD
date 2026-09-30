#include "../utilities/template.h"
#include "../../content/dp/Knuth.h"

int main() {
	mt19937 rng(12);
	rep(it,0,2000) {
		int n = 1 + rng() % 30;
		vector<ll> w(n), pre(n + 1);
		rep(i,0,n) w[i] = rng() % (it % 2 ? 10 : 1000000000);
		rep(i,0,n) pre[i + 1] = pre[i] + w[i];
		auto C = [&](int i, int j) { return pre[j + 1] - pre[i]; };
		vector<ll> base(n, 0);
		// brute O(n^3): optimal merging of adjacent piles
		vector<vector<ll>> dp(n, vector<ll>(n));
		for (int i = n - 1; i >= 0; --i) rep(j,i+1,n) {
			dp[i][j] = LLONG_MAX;
			rep(k,i,j) dp[i][j] = min(dp[i][j], dp[i][k] + dp[k+1][j]);
			dp[i][j] += C(i, j);
		}
		assert(knuth(n, base, C) == dp[0][n - 1]);
	}
	cout << "Tests passed!" << endl;
}
