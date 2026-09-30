/**
 * Author: HCMUS-HLD
 * Description: Hash for any key: unordered\_map<K, V, GHash>,
 * also for HashMap.h. hashBytes(p, n) hashes n raw bytes; only
 * valid on objects without padding/pointers (GHash checks this).
 * Containers (vector, string, set, ...), pairs, tuples and arrays
 * are hashed element by element, recursively; floats treat
 * $-0 = 0$. Random seed per run (anti-hack). Struct without
 * padding: hashed directly; otherwise hash tie(x.a, x.b, ...)
 * (padded structs don't compile, instead of hashing garbage).
 * Usage: unordered_map<vector<int>, int, GHash> m;
 * Time: O(|key|)
 */
#pragma once

typedef unsigned long long ull;
const ull SEED = chrono::steady_clock::now()
	.time_since_epoch().count();
ull mix(ull x) { // splitmix64
	x += 0x9e3779b97f4a7c15;
	x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
	x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
	return x ^ (x >> 31);
}
ull hashBytes(const void* p, size_t n, ull h = SEED) {
	auto c = (const char*)p; ull w;
	for (size_t i = 0; i < n; i += 8, h = mix(h ^ w))
		w = 0, memcpy(&w, c + i, min<size_t>(8, n - i));
	return mix(h ^ n);
}

template<class T, class = void> struct isTup : false_type {};
template<class T> struct isTup<T,
	void_t<decltype(tuple_size<T>::value)>> : true_type {};
template<class T, class = void> struct flat : false_type {};
template<class T> struct flat<T, void_t<decltype(declval<T>()
	.data())>> : has_unique_object_representations<
	typename T::value_type> {};

struct GHash {
	template<class T> size_t operator()(const T& x) const {
		if constexpr (is_floating_point_v<T>) {
			T y = x == 0 ? 0 : x;
			return hashBytes(&y, sizeof y);
		} else if constexpr (has_unique_object_representations_v<T>)
			return hashBytes(&x, sizeof x);
		else if constexpr (flat<T>::value) // string, vector<int>
			return hashBytes(x.data(), sz(x) * sizeof(x[0]));
		else {
			ull h = SEED, n = 0;
			auto add = [&](const auto& e) {
				h = mix(h ^ (*this)(e)), n++; };
			if constexpr (isTup<T>::value)
				apply([&](const auto&... e) { (add(e), ...); }, x);
			else for (auto&& e : x) add(e);
			return mix(h ^ n);
		}
	}
};
