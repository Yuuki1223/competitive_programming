#pragma once
#include "templates/top.cpp"
#include "templates/static_modll.cpp"

using modll = modll_base<998244353>;

vector<modll> conv(vector<modll> a, vector<modll> b) {
	static_assert(modll::MOD == 998244353);		//998244353 == 2^23 * 119 + 1
	if (a.empty() || b.empty())return {};
	modll c(15311432);	// == 3^119, 3ÇÕ998244353ÇÃå¥énç™
	assert(a.size() + b.size() - 1 <= 1ll << 23);

	ll k = (ll)countr_zero(bit_ceil(a.size() + b.size() - 1ull)), n = 1ll << k, as = a.size(), bs = b.size();
	REP(i, 23 - k) c = c.pow(2);

	auto dft_fast = [](vector<modll>& ar, modll w)->void {
		const ll k = countr_zero(ar.size()), n = ar.size();

		for (ll d = 1ll << (k - 1); 1 <= d; d >>= 1) {
			for (ll b = 0; b < n; b += d * 2) {
				modll wt = 1;
				REP(dd, d) {
					modll s = ar[b + dd], t = ar[d + b + dd];
					ar[b + dd] = s + t;
					ar[d + b + dd] = wt * (s - t);
					wt *= w;
				}
			}
			w *= w;
		}

		REP(i, n) {
			ll j = 0;
			REP(t, k)j |= ll(bit(i, t)) << (k - 1 - t);
			if (i < j)swap(ar[i], ar[j]);
		}

		return;
	};

	a.resize(n);
	b.resize(n);

	dft_fast(a, c);
	dft_fast(b, c);

	vector<modll> ans(n);
	REP(i, n)ans[i] = a[i] * b[i];
	c = c.inv();
	dft_fast(ans, c);

	modll nn(modll(n).inv());

	REP(i, n)ans[i] *= nn;

	ans.resize(as + bs - 1);

	return ans;
}