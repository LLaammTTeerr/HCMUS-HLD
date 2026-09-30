/**
 * Author: HCMUS-HLD
 * Description: Recursive lambdas without std::function.
 * Usage: auto fib = y_combinator([&](auto self, int n) -> ll {
 *   return n < 2 ? n : self(n-1) + self(n-2); });
 */
#pragma once

template<class Fun> struct y_combinator_result {
	Fun fun_;
	template<class T>
	explicit y_combinator_result(T&& fun) : fun_(forward<T>(fun)) {}
	template<class... Args> decltype(auto) operator()(Args&&... args) const {
		return fun_(ref(*this), forward<Args>(args)...);
	}
};
template<class Fun> decltype(auto) y_combinator(Fun&& fun) {
	return y_combinator_result<decay_t<Fun>>(forward<Fun>(fun));
}
