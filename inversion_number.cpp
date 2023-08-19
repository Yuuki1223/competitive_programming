#pragma once
#include "templates/top.cpp"
#include "templates/fentrees.cpp"

template<typename T>
ll invnum(vector<T> v) {
	ll k = 0, ans = 0;
	map<T, ll> mp;
	REP(i, v.size())mp[v[i]];
	ITR(it, mp)it->second = k++;
	fentrees::fenwicktree<ll> tr(k);
	for (ll i = v.size() - 1; 0 <= i; i--) {
		ans += tr.getr(mp[v[i]]);
		tr.updateadd(mp[v[i]], 1);
	}
	return ans;
}