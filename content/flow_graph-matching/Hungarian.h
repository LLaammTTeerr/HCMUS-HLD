/**
 * Time: $O(N^3)$
*/

#pragma once

struct Hungarian {
    vector<vector<int>> c; // matrix cost
    vector<int> fx, fy, matchX, matchY; // potentials | corresponding node
    vector<int> trace, dist, arg; // last vertex on the left side | distance from the tree | the corresponding node
    queue<int> qu; // used for bfs

    int numNode; // assume that |L| = |R| = n
    int start;   // current root of the tree
    int finish;  // leaf node of augmenting path

    Hungarian(int _n) {
        numNode = _n;
        c = vector<vector<int>>(numNode + 1, vector<int>(numNode + 1, 1e9+7));
        fx = fy = matchX = matchY = trace = dist = arg = vector<int>(numNode + 1);
    }

    inline void addEdge(int u, int v, int _cost) { c[u][v] = min(c[u][v], _cost); }
    inline int cost(int u, int v) const { return c[u][v] - fx[u] - fy[v]; }

    void initBFS(int root) {
        start = root;
        qu = queue<int>(); qu.push(start);
        for (int i = 1; i <= numNode; ++i) {
            trace[i] = 0, arg[i] = start;
            dist[i] = cost(start, i);
        }
    }

    int findPath(void) {
        while(sz(qu)) {
            int u(qu.front()); qu.pop();
            for (int v = 1; v <= numNode; ++v) {
                if(trace[v]) continue;
                int w = cost(u, v);
                if(w == 0) {
                    trace[v] = u;
                    if(!matchY[v]) return v;
                    qu.push(matchY[v]);
                }
                if(dist[v] > w) dist[v] = w, arg[v] = u;
            }
        }
        return 0;
    }

    void enlarge(void) {
        for (int y = finish, next; y != 0; y = next) {
            int x = trace[y]; next = matchX[x];
            matchX[x] = y, matchY[y] = x;
        }
    }

    void update(void) {
        int delta = 1e9+7;
        for (int i = 1; i <= numNode; ++i) if(!trace[i]) delta = min(delta, dist[i]);
        fx[start] += delta;
        for (int i = 1; i <= numNode; ++i) {
            if(trace[i]) {
                fx[matchY[i]] += delta, fy[i] -= delta;
            } else {
                dist[i] -= delta;
                if(dist[i] == 0) {
                    trace[i] = arg[i];
                    if(matchY[i] == 0) { finish = i; } 
                    else qu.push(matchY[i]);
                }
            }
        }
    }

    void hungarian(void) {
        for (int i = 1; i <= numNode; ++i) {
            initBFS(i);
            do {
                finish = findPath();
                if(!finish) update();
            } while(!finish);
            enlarge();
        }
    }

    void show() {
        int ans = 0;
        for (int i = 1; i <= numNode; ++i) if(matchX[i]) ans += c[i][matchX[i]];
        cout << ans << '\n';
        for (int i = 1; i <= numNode; ++i) cout << i << ' ' << matchX[i] << '\n';
    }
};