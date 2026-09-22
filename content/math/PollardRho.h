#pragma once

ll gcd(ll x, ll y) {
    while(y > 0) { x %= y; swap(x, y); }
    return x;
}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll Random(ll l, ll r) {
    return uniform_int_distribution<ll>(l, r)(rng);
}

// check for MillerRabin template to get isPrime and mulmod functions
void pollard(ll n, vector<ll> &ans) { // Factorize n into prime numbers
    if(isPrime(n)) {
        ans.push_back(n);
        return;
    }
    ll c;
    while(1) {
        c = 1 + Random(0, n - 2);
        auto f = [&](ll y) {
            ll res = mulmod(y, y, n) + c;
            if(res >= n) res -= n;
            return res;
        };
        ll y = 2, g = 1;
        int B = 100, len = 1;
        while(1) {
            ll z = y, zs = -1;
            for (int i = 0; i < len; ++i) z = f(z);
            int lft = len;
            while(g == 1 && lft > 1) {
                zs = z;
                ll p = 1;
                for (int i = 0; i < B && i < lft; ++i) {
                    p = mulmod(p, abs(z - y), n);
                    z = f(z);
                }
                g = gcd(p, n);
                lft -= B;
            }
            if(g == 1) {
                y = z;
                len <<= 1;
                continue;
            }
            if(g == n) {
                g = 1;
                z = zs;
                while(g == 1) {
                    g = gcd(abs(z - y), n);
                    z = f(z);
                }
            }
            if(g == n) break;
            assert(g != -1);
            pollard(g, ans);
            pollard(n / g, ans);
            return;
        }
    }
}

// return list of all prime factors of n (can have duplicate)
vector<ll> factorize(ll n) {
    vector<ll> ans;
    for (ll p : {2, 3, 5, 7, 11, 13, 17, 19}) {
        while(n % p == 0) {
            n /= p;
            ans.push_back(p);
        }
    }

    if(x > 1) pollard(x, ans);
    sort(ans.begin(), ans.end()); // ans may not be sorted before this
    return ans;
}