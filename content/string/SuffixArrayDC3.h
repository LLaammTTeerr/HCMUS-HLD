/**
 * Time O(N)
*/

#pragma once

#define MASK(i) (1LL<<(i))
#define BIT(x,i) (((x)>>(i))&1)
#define tget(i) BIT(t[(i) >> 3], (i) & 7)
#define tset(i, b) { if (b) t[(i) >> 3] |= MASK((i) & 7); else t[(i) >> 3] &= ~MASK((i) & 7); }
#define chr(i) (cs == sizeof(int) ? ((int *)s)[i] : ((unc *)s)[i])
#define isLMS(i) ((i) > 0 && tget(i) && !tget((i) - 1))

typedef unsigned char unc;
class SuffixArray {
    public:
        int *sa, *lcp, *pos, n;
        unc *s;

        void getBuckets(unc s[], vector<int> &bkt, int n, int k, int cs, int end) {
            for (int i = 0; i <= k; ++i) bkt[i] = 0;
            for (int i = 0; i < n; ++i) ++bkt[chr(i)];
            int sum = 0;
            for (int i = 0; i <= k; ++i) {
                sum += bkt[i];
                bkt[i] = (end) ? sum : sum - bkt[i];
            }
        }

        void inducesal(vector<unc> &t, int sa[], unc s[], vector<int> &bkt, int n, int k, int cs, int end) {
            getBuckets(s, bkt, n, k, cs, end);
            for (int i = 0; i < n; ++i) {
                int j = sa[i] - 1;
                if(j >= 0 && !tget(j)) sa[bkt[chr(j)]++] = j;
            }
        }

        void inducesas(vector<unc> &t, int sa[], unc s[], vector<int> &bkt, int n, int k, int cs, int end) {
            getBuckets(s, bkt, n, k, cs, end);
            for (int i = n - 1; i >= 0; --i) {
                int j = sa[i] - 1;
                if(j >= 0 && tget(j)) sa[--bkt[chr(j)]] = j;
            }
        }

        void buildSA(unc s[], int sa[], int n, int k, int cs) {
            vector<unc> t = vector<unc>(n / 8 + 1, 0);
            int j;
            tset(n - 2, 0); tset(n - 1, 1);
            for (int i = n - 3; i >= 0; --i) tset(i, (chr(i) < chr(i + 1)) || (chr(i) == chr(i + 1) && tget(i + 1)));
            vector<int> bkt = vector<int>(k + 1, 0);
            getBuckets(s, bkt, n, k, cs, true);
            for (int i = n - 1; i >= 0; --i) sa[i] = -1;
            for (int i = n - 1; i >= 0; --i) if(isLMS(i)) sa[--bkt[chr(i)]] = i;
            inducesal(t, sa, s, bkt, n, k, cs, false);
            inducesas(t, sa, s, bkt, n, k, cs, true);
            bkt.clear();
            int n1 = 0;
            for (int i = 0; i < n; ++i) if(isLMS(sa[i])) sa[n1++] = sa[i];
            for (int i = n1; i < n; ++i) sa[i] = -1;
            int name = 0, prev = -1;
            for (int i = 0; i < n1; ++i) {
                int pos = sa[i];
                bool diff = false;
                for (int d = 0; d < n; ++d) {
                    if(prev < 0 || chr(prev + d) != chr(pos + d) || tget(prev + d) != tget(pos + d)) {
                        diff = true;
                        break;
                    } else if(d > 0 && (isLMS(prev + d) || isLMS(pos + d))) break;
                }
                if(diff) ++name, prev = pos;
                sa[n1 + pos / 2] = name - 1;
            }
            j = n - 1;
            for (int i = n - 1; i >= n1; --i) if(sa[i] >= 0) sa[j--] = sa[i];
            int *sa1 = sa, *s1 = sa + n - n1;
            if(name < n1) buildSA((unc*)s1, sa1, n1, name - 1, sizeof(int));
            else for (int i = 0; i < n1; ++i) sa1[s1[i]] = i;
            bkt.assign(k + 1, 0);
            getBuckets(s, bkt, n, k, cs, true);
            j = 0;
            for (int i = 0; i < n; ++i) if(isLMS(i)) s1[j++] = i;
            for (int i = 0; i < n1; ++i) sa1[i] = s1[sa1[i]];
            for (int i = n1; i < n; ++i) sa[i] = -1;
            for (int i = n1 - 1; i >= 0; --i) j = sa[i], sa[i] = -1, sa[--bkt[chr(j)]] = j;
            inducesal(t, sa, s, bkt, n, k, cs, false);
            inducesas(t, sa, s, bkt, n, k, cs, true);
            bkt.clear(), t.clear();
        }

        void buildLCP(void) {
            for (int i = 1; i <= n; ++i) pos[sa[i]] = i;
            int k = 0;
            lcp[n] = 0;
            for (int i = 1; i <= n; ++i) if(pos[i] < n) {
                for (int j = sa[pos[i] + 1]; s[i + k - 1] == s[j + k - 1]; ) ++k;
                lcp[pos[i]] = k; k -= (k > 0);
            }
        }

        void show(void) {
            for (int i = 1; i <= n; ++i) cout << sa[i] << ' '; cout << '\n';
            for (int i = 1; i <= n; ++i) cout << pos[i] << ' '; cout << '\n';
            for (int i = 1; i <= n; ++i) cout << lcp[i] << ' '; cout << '\n';
        }

        SuffixArray() : n(0), sa(NULL), lcp(NULL), pos(NULL), s(NULL) {}
        
        SuffixArray(string ss) : n(sz(ss)) {
            sa = new int[n + 7];
            lcp = new int[n + 7];
            pos = new int[n + 7];
            s = (unc*) ss.c_str();
            buildSA(s, sa, n + 1, 256, sizeof(char));
            for (int i = 1; i <= n; ++i) ++sa[i];
            buildLCP();
        }
};