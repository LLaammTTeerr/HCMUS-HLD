#pragma once

const int G = 3; // primitive root for MOD 998244353

ll mod_pow(ll a, ll e, ll M = MOD) // calc a^e % M in O(log)

void ntt(vector<ll>& a, bool invert) {
    int n = sz(a);
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        int wlen = mod_pow(G, (MOD - 1) / len);
        if (invert) wlen = mod_pow(wlen, MOD - 2);
        for (int i = 0; i < n; i += len) {
            int w = 1;
            for (int j = 0; j < len / 2; j++) {
                ll u = a[i + j];
                ll v = a[i + j + len / 2] * w % MOD;
                if((a[i + j] = u + v) >= MOD) a[i + j] -= MOD;
                if((a[i + j + len / 2] = u - v) < 0) a[i + j + len / 2] += MOD;
                w = 1LL * w * wlen % MOD;
            }
        }
    }
    if (invert) {
        int n_inv = mod_pow(n, MOD - 2);
        for (ll &x : a) x = 1LL * x * n_inv % MOD;
    }
}

vector<ll> convolution(const vector<ll>& a, const vector<ll>& b) {
    if(!sz(a) || !sz(b)) return {};
    vector<ll> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1, need = sz(a) + sz(b) - 1;
    while(n < need) n <<= 1;
    fa.resize(n), fb.resize(n);
    ntt(fa, false), ntt(fb, false);
    for (int i = 0; i < n; i++) fa[i] = 1LL * fa[i] * fb[i] % MOD;
    ntt(fa, true), fa.resize(need);
    return fa;
}