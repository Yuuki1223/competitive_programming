#pragma once
#include "templates/top.cpp"

template<typename T>
class sparse_table {
public:

	sparse_table(vector<T> ar, function<T(T, T)> _bop) :k(0), bop(_bop) {
		assert(!ar.empty());
		k = countr_zero(bit_floor<ull>(ar.size())) + 1ll;
		dat.resize(k);
		dat[0] = ar;
		REP(i, k - 1) {
			ll w = ar.size() - (1ull << (i + 1)) + 1;
			dat[i + 1].resize(w);
			REP(j, w) {
				dat[i + 1][j] = bop(dat[i][j], dat[i][j + (1ull << i)]);
			}
		}
	}

	T getr(ll l, ll rp) {
		ll w = rp - l;
		if (w <= 0)return T();
		else {
			ll b = countr_zero(bit_floor<ull>(w));
			return bop(dat[b][l], dat[b][rp - (1ull << b)]);
		}
	}

private:
	ll k;
	vector<vector<T>> dat;
	function<T(T, T)> bop;
};