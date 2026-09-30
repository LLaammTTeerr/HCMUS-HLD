#include "../utilities/template.h"
#include <unistd.h>

#include "../../content/various/FastInput.h"

// gc() keeps static state, so the whole input is one file read once:
// many ints with assorted whitespace, spanning several buffer refills.
int main() {
	char pattern[] = "/tmp/fastinputXXXXXX";
	string dir = mkdtemp(pattern), file = dir + "/stdin.txt";
	mt19937 rng(7);
	vi want;
	string s;
	const char* ws[] = {" ", "\n", "\t", "  ", "\r\n", " \n "};
	rep(i,0,300000) {
		int x;
		switch (rng() % 4) {
			case 0: x = (int)(rng() % 10); break;
			case 1: x = -(int)(rng() % 1000); break;
			// readInt computes (prefix + 48) * 10: safe for
			// |x| <= 2147483119 (larger |x| is signed overflow)
			case 2: x = (2147483119 - (int)(rng() % 3)) *
				(rng() % 2 ? 1 : -1); break;
			default: x = (int)(rng() % 2000000001) - 1000000000;
		}
		want.push_back(x);
		s += to_string(x);
		s += ws[rng() % 6];
	}
	assert(sz(s) > 3 * (1 << 16));
	{ ofstream fout(file); fout << s; }
	FILE* ret = freopen(file.c_str(), "r", stdin);
	assert(ret == stdin);
	for (int x : want) assert(readInt() == x);
	rep(i,0,5) assert(gc() == 0); // EOF
	unlink(file.c_str());
	rmdir(dir.c_str());
	cout << "Tests passed!" << endl;
}
