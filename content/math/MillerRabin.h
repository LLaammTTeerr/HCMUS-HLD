/** 
 * Usage: 
 *  n $<$ $2,047$: 
 *  a $=$ $[2]$
 *  
 *  n $<$ $1,373,653$: 
 *  a $=$ $[2, 3]$
 *  
 *  n $<$ $9,081,191$:
 *  a $=$ $[31, 73]$
 * 
 *  n $<$ $25,326,001$:
 *  a = $[2, 3, 5]$
 * 
 *  n $<$ $3,215,031,751$:
 *  a $=$ $[2, 3, 5, 7]$
 * 
 *  n $<$ $4,759,123,141$:
 *  a $=$ $[2, 7, 61]$
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
 *  n $<$ $341,550,071,728,321$:
 *  a $=$ $[2, 3, 5, 7, 11, 13, 17]$
 * 
 *  n $<$ $3,825,123,056,546,413,051$:
 *  a $=$ $[2, 3, 5, 7, 11, 13, 17, 19, 23]$
 * 
 *  n $<=$ $2^64$:
 *  a $=$ $[2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37]$
 * 
 *  n $<$ $318,665,857,834,031,151,167,461$:
 *  a $=$ $[2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37]$
 * 
 *  n $<$ $3,317,044,064,679,887,385,961,981$:
 *  a $=$ $[2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41]$
*/

inline pli factor(ll n) {
    int s = __builtin_ctz(n);
    return make_pair(n / (1LL << s), s);
}

ll mulmod(ll a, ll expo, ll MOD) {
    ll res = 0;
    while(expo > 0) {
        if(expo & 1) if((res += a) >= MOD) res -= MOD;
        if((a += a) >= MOD) a -= MOD;
        expo >>= 1;
    }
    return res;
}

ll powermod(ll a, ll expo, ll MOD) {
    ll res = 1;
    while(expo > 0) {
        if(expo & 1) res = mulmod(res, a, MOD);
        a = mulmod(a, a, MOD);
        expo >>= 1;
    }

    return res;
}

bool test_a(ll s, ll d, ll n, ll a) {
    if(n == a) return true;
    ll p = powermod(a, d, n);
    if(p == 1) return true;
    for (; s > 0; --s) {
        if(p == n - 1) return true;
        p = mulmod(p, p, n);
    }
    return false;
}

bool miller(ll n) {
    if(n < 2) return false;
    if((n & 1) == 0) return (n == 2);
    ll d; int s;
    tie(d, s) = factor(n - 1);
    vector<int> test_prime = {2, 3, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    for (int i = 0; i < sz(test_prime); ++i) if(!test_a(s, d, n, test_prime[i])) return false;
    return true;
}