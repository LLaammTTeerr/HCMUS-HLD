/**
 * Author: Phan Binh Nguyen Lam
 * Date: 2024-11-07
 * License: CC0
 * Description: Operators for modular arithmetic.
 * Usage:
 *  using Z = Mint<MOD>;
 *  Z inverse = CInv<42, MOD>;
 */
#pragma once

using i64 = long long;

template<class T>
constexpr T power(T a, i64 b) {
	T res = 1;
	for (; b; b /= 2, a *= a) {
		if (b % 2) {
			res *= a;
		}
	}
	return res;
}

template<int P>
struct MInt {
	int x;
	constexpr MInt() : x{} {}
	constexpr MInt(i64 x) : x{norm(x % P)} {}
	
	constexpr int norm(int x) const {
		if (x < 0) {
			x += P;
		}
		if (x >= P) {
			x -= P;
		}
		return x;
	}
	constexpr int val() const {
		return x;
	}
	explicit constexpr operator int() const {
		return x;
	}
	constexpr MInt operator-() const {
		MInt res;
		res.x = norm(P - x);
		return res;
	}
	constexpr MInt inv() const {
		assert(x != 0);
		return power(*this, P - 2);
	}
	constexpr MInt &operator*=(MInt rhs) {
		x = 1LL * x * rhs.x % P;
		return *this;
	}
	constexpr MInt &operator+=(MInt rhs) {
		x = norm(x + rhs.x);
		return *this;
	}
	constexpr MInt &operator-=(MInt rhs) {
		x = norm(x - rhs.x);
		return *this;
	}
	constexpr MInt &operator/=(MInt rhs) {
		return *this *= rhs.inv();
	}
	friend constexpr MInt operator*(MInt lhs, MInt rhs) {
		MInt res = lhs;
		res *= rhs;
		return res;
	}
	friend constexpr MInt operator+(MInt lhs, MInt rhs) {
		MInt res = lhs;
		res += rhs;
		return res;
	}
	friend constexpr MInt operator-(MInt lhs, MInt rhs) {
		MInt res = lhs;
		res -= rhs;
		return res;
	}
	friend constexpr MInt operator/(MInt lhs, MInt rhs) {
		MInt res = lhs;
		res /= rhs;
		return res;
	}
	friend constexpr std::istream &operator>>(std::istream &is, MInt &a) {
		i64 v;
		is >> v;
		a = MInt(v);
		return is;
	}
	friend constexpr std::ostream &operator<<(std::ostream &os, const MInt &a) {
		return os << a.val();
	}
	friend constexpr bool operator==(MInt lhs, MInt rhs) {
		return lhs.val() == rhs.val();
	}
	friend constexpr bool operator!=(MInt lhs, MInt rhs) {
		return lhs.val() != rhs.val();
	}
};

template<int V, int P>
constexpr MInt<P> CInv = MInt<P>(V).inv();