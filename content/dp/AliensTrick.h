#pragma once

II choose(II A, II B) {
    if(A.fs == B.fs) return (A.sc > B.sc) ? A : B;
    return (A.fs > B.fs) ? A : B; 
}

II calc(int x) {
    vector<II> dp(n + 1, mp(-INF, -INF));
    
    dp[0] = {0, 0};
    forlr(i, 1, n) {
        dp[i] = dp[i - 1];
        if(i >= m) dp[i] = choose(dp[i], {dp[i - m].fs + (p[i] - p[i - m]) - x, dp[i - m].sc + 1}); 
    } 
    return dp[n];
}

void solve() {
    int ans = 1e14;
    int lo = 0, hi = 1e14;
 
    while(lo <= hi) {
        int mid = (lo + hi) >> 1;
 
        II v = calc(mid);
 
        if(v.sc < k) hi = mid - 1;
        else lo = mid + 1, ans = v.fs + k * mid;
    }
}