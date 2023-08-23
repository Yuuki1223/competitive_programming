#pragma once
#include "templates/top.cpp"
#include "templates/static_modll.cpp"

using modll = modll_base<998244353>;

vector<modll> conv(vector<modll> a, vector<modll> b) {
	static_assert(modll::MOD == 998244353);		//998244353 == 2^23 * 119 + 1
	if (a.empty() || b.empty())return {};
	modll c(15311432);	// == 3^119, 3ÇÕ998244353ÇÃå¥énç™
	assert(a.size() + b.size() - 1 <= 1ll << 23);

	ll n = 1, k = 0;
	while (!(ll(a.size() + b.size()) - 1 <= n)) { n *= 2;	k++; }
	REP(i, 23 - k) c = c.pow(2);

	const static function<void(vector<modll>&, modll)> dft =
		[](vector<modll>& ar, modll t) {
		if (ar.size() == 1)return;
		ll m = ar.size() / 2;
		vector<modll> a(m), b(m);
		REP(i, m) {
			a[i] = ar[i * 2];
			b[i] = ar[i * 2 + 1];
		}
		dft(a, t.pow(2));
		dft(b, t.pow(2));
		modll tt = 1;
		REP(i, m * 2) {
			ar[i] = a[i < m ? i : i - m] + tt * b[i < m ? i : i - m];
			tt *= t;
		}
		return;
	};

	ll as = a.size(), bs = b.size();

	while ((ll)a.size() < n)a.push_back(0);
	while ((ll)b.size() < n)b.push_back(0);

	dft(a, c);
	dft(b, c);

	vector<modll> ans(n);
	REP(i, n)ans[i] = a[i] * b[i];
	c = c.inv();
	dft(ans, c);

	modll nn(modll(n).inv());

	REP(i, n)ans[i] *= nn;

	while (as + bs - 1 < (ll)ans.size())ans.pop_back();

	return ans;
}