/** 
 * Usage: For n <= 2^32 and n <= 2^64, there exists in template
 *  n $<$ $2,047$ (~ 2^11):
 *  a $=$ $[2]$
 *  
 *  n $<$ $9,081,191$ (~ 2^23):
 *  a $=$ $[31, 73]$
 * 
 *  n $<$ $1,122,004,669,633$:
 *  a $=$ $[2, 13, 23, 1662803]$
 * 
 *  n $<$ $2,152,302,898,747$:
 *  a $=$ $[2, 3, 5, 7, 11]$
 * 
 *  n $<$ $3,474,749,660,383$:
 *  a $=$ $[2, 3, 5, 7, 11, 13]$
 * 
 *  n $<$ $318,665,857,834,031,151,167,461$:
 *  a $=$ $[2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37]$
 * 
 *  n $<$ $3,317,044,064,679,887,385,961,981$:
 *  a $=$ $[2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41]$
 * 
 * Time: $O(A \times \log(N))$, A is size of array a for testing
*/

#pragma once

inline puli factor(ull n) {
    int s = __builtin_ctzll(n);
    return make_pair(n >> s, s);
}

ull mulmod(ull a, ull b, ull MOD) { return (__uint128_t) a * b % MOD; }
ull powermod(ull a, ull expo, ull MOD); // calc a^expo % MOD in O(log)

bool check_miller(ull s, ull d, ull n, ull a) {
    if(a % n == 0) return true;
    ull p = powermod(a, d, n);
    if(p == 1) return true;
    for (; s > 0; --s) {
        if(p == n - 1) return true;
        p = mulmod(p, p, n);
        if(p == 1) return false;
    }
    return false;
}

bool isPrime(ull n) {
    if(n == 2 || n == 3 || n == 5 || n == 7) return true;
    if(n % 2 == 0 || n % 3 == 0 || n % 5 == 0 || n % 7 == 0) return false;
    if(n < 121) return (n > 1);
    ull d; int s;
    tie(d, s) = factor(n - 1);
    if(n < (1LL << 32)) {
        for (ull a : {2, 7, 61}) if(!check_miller(s, d, n, a)) return false;
    } else {
        for (ull a : {2, 325, 9375, 28178, 450775, 9780504, 1795265022}) if(!check_miller(s, d, n, a)) return false;
    }
    return true;
}