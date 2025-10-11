// Minimum +1/-1 operations to make A[i] increasing.
#pragma once
int slope_trick() {
    int n; cin >> n;
    multiset<int> slope_changing_points;
    long long answer = 0;
    for (int i = 1; i <= n; ++i) {
        int Ai; cin >> Ai;
        Ai -= i;
        slope_changing_points.insert(Ai);
        if (i == 1) continue;
        int opt = *slope_changing_points.rbegin();
        if (Ai < opt) {
            slope_changing_points.erase(--slope_changing_points.end());
            slope_changing_points.insert(Ai);
            answer += opt - Ai;
        }
    }
    cout << answer << endl;
    return 0;
}