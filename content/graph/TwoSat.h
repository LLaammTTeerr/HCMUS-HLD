/**
 * Usage: 
 *  add_disjunction(u, nu, v, nv) to represent the or and the negate of variable
 */

#pragma once

class TWO_SAT {
private:
	int n;
	vector <vector <int>> forward_edge, back_edge;
	vector <bool> used;
	vector <int> order, comp;

	void dfs_first(int u) {
		used[u] = true;
		for (auto v : forward_edge[u])
			if (not used[v]) dfs_first(v);
		order.push_back(u);
	}

	void dfs_second(int u, int turn) {
		comp[u] = turn;
		for (auto v : back_edge[u])
			if (comp[v] == -1) dfs_second(v, turn);
	}
public:
	TWO_SAT(int n = 0): n(n) {
		used.assign(2 * n + 7, false);
		comp.assign(2 * n + 7, -1);
		forward_edge.resize(2 * n + 7);
		back_edge.resize(2 * n + 7);
	}

	void add_disjunction(int a, bool na, int b, bool nb) {
		a = (a << 1) ^ na;
		b = (b << 1) ^ nb;
		int neg_a = a ^ 1;
		int neg_b = b ^ 1;
		forward_edge[neg_a].push_back(b);
		forward_edge[neg_b].push_back(a);
		back_edge[a].push_back(neg_b);
		back_edge[b].push_back(neg_a);
	}

	vector <bool>* find_solution(void) {
		vector <bool> *assignment = new vector <bool> (2 * n + 7);

		for (int i = 2; i <= 2 * n + 1; i++)
			if (not used[i]) dfs_first(i);

		for (int i = 1, turn = 0; i <= 2 * n; i++) {
			int u = order[2 * n - i];
			if (comp[u] == -1) dfs_second(u, ++turn);
		}

		for (int i = 2; i <= 2 * n; i += 2) {
			if (comp[i] == comp[i + 1])
				return nullptr;
			(*assignment)[i / 2] = comp[i] > comp[i + 1];
		}

		return assignment;
	}
};