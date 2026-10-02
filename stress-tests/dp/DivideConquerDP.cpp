#include "../utilities/template.h"
#include "../../content/dp/DivideConquerDP.h"

int main() {
	mt19937 rng(33);
	const ll INF = (ll)1e18;
	rep(it, 0, 3000) {
		int n = int(rng() % 40) + 1, K = int(rng() % n) + 1;
		vector<ll> a(n), pre(n + 1);
		rep(i, 0, n) a[i] = rng() % 1000, pre[i + 1] = pre[i] + a[i];
		// split into exactly K blocks, cost of block (k, i] = sum^2
		auto C = [&](int k, int i) { ll s = pre[i] - pre[k]; return s * s; };
		vector<vector<ll>> dp(K + 1, vector<ll>(n + 1, INF));
		dp[0][0] = 0;
		rep(j, 1, K + 1) rep(i, 1, n + 1) rep(k, 0, i)
			if (dp[j - 1][k] < INF)
				dp[j][i] = min(dp[j][i], dp[j - 1][k] + C(k, i));
		vector<ll> prv(n + 1, INF), cur;
		prv[0] = 0;
		rep(j, 1, K + 1) {
			cur.assign(n + 1, INF);
			dnc(1, n, 0, n - 1, prv, cur, C);
			swap(prv, cur);
			rep(i, 0, n + 1) if (dp[j][i] < INF) assert(prv[i] == dp[j][i]);
		}
		assert(prv[n] == dp[K][n]);
	}
	cout << "Tests passed!" << endl;
}
