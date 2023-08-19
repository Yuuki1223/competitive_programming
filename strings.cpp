#pragma once
#include "templates/top.cpp"
#include "templates/utilitys.cpp"

string longest_common_sequence(const string& s, const string& t) {
	vector<char> ans = kyopro_utility::longest_common_sequence(
		vector<char>(ALL(s)),
		vector<char>(ALL(t))
	);
	return string(ALL(ans));
}

pair<vector<ll>, vector<ll>> suffix_array_and_longest_common_prefix(string s) {
	vector<ll> suffarr(s.size() + 1), lcp(s.size(), -1);
	s += ';';
	constexpr ll b = 1ll << 32;
	const ll m = s.size();
	ll k = 1;
	while (1ll << (k - 1) < m)k++;
	vector<ll> tans(m);
	REP(t, k) {
		if (!t) {
			map<char, ll> mp;
			ll tt = 0;
			REP(i, m)mp[s[i]];
			ITR(it, mp)it->second = tt++;
			REP(i, m)tans[i] = mp[s[i]];
		}
		else {
			vector<pair<ll, ll>> ttans(m);
			REP(i, m)
				ttans[i] = { tans[i] * b + tans[(i + (1ull << (t - 1))) % m],i };
			sort(ALL(ttans));
			REP(i, m)
				tans[ttans[i].second] = (i && ttans[i - 1].first == ttans[i].first ? tans[ttans[i - 1].second] : i);
		}
	}
	REP(i, m)suffarr[tans[i]] = i;

	ll h = 0;
	REP(i, m - 1) {
		ll j = suffarr[tans[i] - 1];
		if (h)h--;
		while (i + h < (ll)s.size() && j + h < (ll)s.size() && s[i + h] == s[j + h])h++;
		lcp[tans[j]] = h;
	}
	return { suffarr,lcp };
}