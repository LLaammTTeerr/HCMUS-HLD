// ways of writing n as a sum of positive integers O(N \sqrt(N))
#pragma once
ll partitionNumber(int n) {
    if (n < 0) return 0;
    vector<ll> dp(n + 1, 0);
    dp[0] = 1; // base

    for (int i = 1; i <= n; ++i) {
        for (int k = 1; ; ++k) {
            int pent1 = k * (3 * k - 1) / 2; // g(k)
            if (pent1 > i) break;
            ll sign = (k % 2 == 1) ? 1 : -1;
            dp[i] += sign * dp[i - pent1];

            int pent2 = k * (3 * k + 1) / 2; // g(-k)
            if (pent2 > i) continue;
            dp[i] += sign * dp[i - pent2];
        }
    }
    return dp[n];
}