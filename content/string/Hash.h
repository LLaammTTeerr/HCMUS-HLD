#pragma once

const int MOD[] = {(int) 1e9 + 2277, (int) 1e9 + 5277, (int) 1e9 + 8277, (int) 1e9 + 9277};
const int BASE = 256;

struct Hash {
    ll value[NMOD];

    Hash(char c = 0) {
        for (int i = 0; i < NMOD; ++i) value[i] = c;
    }

    Hash operator + (const Hash &x) const {
        Hash res;
        for (int j = 0; j < NMOD; ++j) {
            res.value[j] = value[j] + x.value[j];
            if(res.value[j] >= MOD[j]) res.value[j] -= MOD[j];
        }
        return res;
    }

    Hash operator - (const Hash &x) const {
        Hash res;
        for (int j = 0; j < NMOD; ++j) {
            res.value[j] = value[j] - x.value[j];
            if(res.value[j] < 0) res.value[j] += MOD[j];
        }
        return res;
    }

    Hash operator * (int k) const {
        Hash res;
        for (int j = 0; j < NMOD; ++j) res.value[j] = value[j] * pw[j][k] % MOD[j];
        return res;
    }

    bool operator == (const Hash &x) const {
        for (int j = 0; j < NMOD; ++j) if(value[j] != x.value[j]) return false;
        return true;
    }

};

Hash getHash(int l, int r) { return (hashVal[r] - hashVal[l - 1]) * (n - r); }

void prepare() {
    for (int j = 0; j < NMOD; ++j) {
        pw[j][0] = 1;
        for (int i = 1; i <= n; ++i) pw[j][i] = pw[j][i - 1] * BASE % MOD[j];
    }
}