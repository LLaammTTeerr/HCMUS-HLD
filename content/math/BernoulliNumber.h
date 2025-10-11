#pragma once

inline ll C2(ll n) { return (n & 1) ? (n + 1) / 2 % MOD * (n % MOD) % MOD : n / 2 % MOD * ((n + 1) % MOD) % MOD; }

inline ll nCk(int n, int k) {
    return (k > n) ? 0 : frac[n] * finv[k] % MOD * finv[n - k] % MOD;
}

ll powermod(ll a, int exponent) {
    ll res(1);
    while(exponent > 0) {
        if(exponent & 1) res = res * a % MOD;
        exponent >>= 1;
        a = a * a % MOD;
    }
    return res;
}

ll tmp[MAXN];
ll bernoulli(int n) {
    for (int i = 0; i <= n; ++i) {
        tmp[i] = inv[i + 1];
        for (int j = i; j > 0; --j) tmp[j - 1] = 1LL * j * (tmp[j - 1] - tmp[j] + MOD) % MOD;
    }
    return tmp[0];
}

ll calc(int n) {
    ll res(0), invn = powermod(n, MOD - 2);
    n = powermod(n, expo + 1);
    for (int k = 0; k <= expo; ++k) {
        res = (res + n * nCk(expo + 1, k) % MOD * B[k] % MOD) % MOD;
        n = n * invn % MOD;
    }
    return res * powermod(expo + 1, MOD - 2) % MOD;
}

void init(void) {
    frac[0] = finv[0] = 1;
    for (int i = 1; i <= 21; ++i) {
        frac[i] = frac[i - 1] * i % MOD;
        finv[i] = powermod(frac[i], MOD - 2);
        inv[i] = powermod(i, MOD - 2);
    }
    for (int i = 0; i <= 20; ++i) B[i] = bernoulli(i);
}