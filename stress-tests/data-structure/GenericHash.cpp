#include "../utilities/template.h"
#include "../../content/data-structure/GenericHash.h"
#include "../../content/data-structure/HashMap.h"

struct Q { int x, y; }; // no padding: hashed as raw bytes
struct Pd { int a; ll b; string s; }; // padded: hash via tie

int main() {
	GHash H;
	mt19937 rng(8);
	// padding bytes must not matter
	typedef pair<int, ll> PL;
	alignas(PL) unsigned char b1[sizeof(PL)], b2[sizeof(PL)];
	memset(b1, 0x00, sizeof b1), memset(b2, 0xAB, sizeof b2);
	PL* p1 = new (b1) PL(3, 7);
	PL* p2 = new (b2) PL(3, 7);
	assert(H(*p1) == H(*p2));
	// floats: -0 == 0
	assert(H(0.0) == H(-0.0) && H(1.5) != H(2.5));
	assert(H(vector<double>{-0.0}) == H(vector<double>{0.0}));
	// nested containers, strings, tuples, sets, maps, bool vectors
	vector<vi> vv = {{1, 2}, {3}}, vv2 = {{1, 2}, {3}};
	assert(H(vv) == H(vv2) && H(vector<vi>{{1}, {2, 3}}) != H(vv));
	assert(H(string("abc")) == H(string("abc")));
	assert(H(string("ab")) != H(string("abc")));
	typedef tuple<int, string, double> T3;
	assert(H(T3(1, "x", 2.0)) == H(T3(1, "x", 2.0)));
	assert(H(set<int>{1, 2, 3}) == H(set<int>{3, 2, 1}));
	assert(H(vector<bool>{1, 0, 1}) != H(vector<bool>{1, 1, 0}));
	assert(H(array<int, 3>{1, 2, 3}) != H(array<int, 3>{3, 2, 1}));
	assert(H(map<int, string>{{1, "a"}}) != H(map<int, string>{{1, "b"}}));
	assert(H(Q{1, 2}) == H(Q{1, 2}) && H(Q{1, 2}) != H(Q{2, 1}));
	Pd a{1, 2, "x"}, b{1, 2, "x"}, c{1, 3, "x"};
	assert(H(tie(a.a, a.b, a.s)) == H(tie(b.a, b.b, b.s)));
	assert(H(tie(a.a, a.b, a.s)) != H(tie(c.a, c.b, c.s)));
	// raw bytes
	int arr[3] = {1, 2, 3}, arr2[3] = {1, 2, 3};
	assert(hashBytes(arr, sizeof arr) == hashBytes(arr2, sizeof arr2));
	assert(hashBytes(arr, 8) != hashBytes(arr, 12));
	assert(hashBytes("", 0) == hashBytes("x", 0));
	// as a hash map key vs std::map
	unordered_map<vi, int, GHash> um;
	__gnu_pbds::gp_hash_table<vi, int, GHash> gp;
	map<vi, int> ref;
	rep(i,0,100000) {
		vi k(rng() % 4);
		for (int& x : k) x = rng() % 5;
		int v = (int)rng();
		um[k] = v, gp[k] = v, ref[k] = v;
	}
	assert(sz(um) == sz(ref));
	for (auto& [k, v] : ref) assert(um[k] == v && gp[k] == v);
	// no 64-bit collisions among many distinct keys
	unordered_set<ull> hs;
	rep(i,0,300000) hs.insert(H(vi{i, i * 7}));
	assert(sz(hs) == 300000);
	cout << "Tests passed!" << endl;
}
