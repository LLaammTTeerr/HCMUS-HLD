#pragma once

namespace RabinKarp {
    const int NMOD = 3;
    
    const int MOD[] = {(int) 1e9 + 2277, (int) 1e9 + 5277, (int) 1e9 + 8277, (int) 1e9 + 9277};
    const int BASE = 256;
    
    ll pw[NMOD][MAXN];
    
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
    
        Hash operator * (Hash h) const {
            Hash res;
            for (int j = 0; j < NMOD; ++j) res.value[j] = 1LL * value[j] * h.value[j] % MOD[j];
            return res;
        }
    
        bool operator == (const Hash &x) const {
            for (int j = 0; j < NMOD; ++j) if(value[j] != x.value[j]) return false;
            return true;
        }
    
    } hashVal[MAXN];
    
    void prepare() {
        for (int j = 0; j < NMOD; ++j) {
            pw[j][0] = 1;
            for (int i = 1; i < MAXN; ++i) pw[j][i] = pw[j][i - 1] * BASE % MOD[j];
        }
    }
    
    Hash dr = 1, dc = 1; // Highest power for row/col hashing
    
    // Checks if all values of pattern matches with the text
    bool check(vector<vector<char>> &txt, vector<vector<char>> &pat, int r, int c) {
        /*for (int i = 0; i < pat.size(); ++i) {
            for (int j = 0; j < pat[0].size(); ++j)
                if(pat[i][j] != txt[i + r][j + c]) return false;
        }*/
        return true;
    }
    
    // Finds the first hash of first n rows where n is no. of rows in pattern
    vector<Hash> findHash(vector<vector<char>> &mat, int row) {
        vector<Hash> hash;
        int col = mat[0].size();
        for (int i = 0; i < col; ++i) {
            Hash h(0);
            for (int j = 0; j < row; ++j) h = h * 1 + mat[j][i];
            hash.push_back(h);
        }
        return hash;
    }
    
    //rolling hash function for columns
    void colRollingHash(vector<vector<char>> &txt, vector<Hash> &t_hash, int row, int p_row) {
        for (int i = 0; i < sz(t_hash); ++i)
            t_hash[i] = (t_hash[i] - Hash(txt[row][i]) * dr) * 1 + Hash(txt[row + p_row][i]);
    }

    int solve(vector<vector<char>> &txt, vector<vector<char>> &pat) {
        int t_row = sz(txt), t_col = sz(txt[0]);
        int p_row = sz(pat), p_col = sz(pat[0]);
        dr = Hash(1) * (p_row - 1);
        dc = Hash(1) * (p_col - 1);
        vector<Hash> t_hash = findHash(txt, p_row); // column hash of p_row rows
        vector<Hash> p_hash = findHash(pat, p_row); // column hash of p_row rows
        Hash p_val = 0;  // hash of entire pattern matrix
        for (int i = 0; i < p_col; ++i) p_val = p_val * 1 + p_hash[i];
        int res = 0;
        for(int i = 0; i <= (t_row - p_row); ++i) {
            Hash t_val = 0;
            for(int i = 0; i < p_col; ++i) t_val = t_val * 1 + t_hash[i];
            for(int j = 0; j <= (t_col - p_col); ++j) {
                res += (p_val == t_val && check(txt, pat, i, j));
                // calculating t_val for next set of columns
                t_val = (t_val - t_hash[j] * dc) * 1 + t_hash[j + p_col];
            }
            // call this function for hashing form next row
            if(i < t_row - p_row) colRollingHash(txt, t_hash, i, p_row);
        }
        return res;
    }
}