#pragma once
#include "templates/top.cpp"
#include "templates/utilitys.cpp"

class rolling_hash {
public:
	constexpr static ll n = 2;

	rolling_hash(string _s) :s(_s) {	//requests s.element in ['a', 'z']
		REP(i, n) {
			if (bs[i].empty())bs[i].push_back(1);
			if (brs[i].empty())brs[i].push_back(1);
			while (bs[i].size() < s.size())bs[i].push_back(bs[i].back() * b[i] % r[i]);
			while (brs[i].size() < s.size())brs[i].push_back(brs[i].back() * br[i] % r[i]);

			ss[i].resize(s.size() + 1);
			ss[i][0] = 0;
			REP(j, s.size()) {
				ss[i][j + 1] = (ss[i][j] + bs[i][j] * (ll(s[j]) - 'a' + 1) % r[i]) % r[i];
			}
		}
	};

	array<ll, n> hash(ll l, ll rp) {
		array<ll, n> h{};
		REP(i, n) {
			h[i] = parup(ss[i][rp] - ss[i][l], r[i]) * brs[i][l] % r[i];
		}
		return h;
	}

	string get(void) { return s; }

	static void random_init(void) {
		REP(i, n) {
			b[i] = kyopro_utility::random::integer<ll>(30, r[i] - 1);
			tie(ignore, br[i], ignore) = kyopro_utility::extgcd(b[i], r[i]);
			br[i] = parup(br[i], r[i]);
		}
	}

private:
	string s;
	array<vector<ll>, n> ss;

	constexpr static array<ll, n> r = { 2147483629,2147483587 };

	static array<ll, n> b, br;
	static array<vector<ll>, n> bs, brs;
};
array<ll, rolling_hash::n> rolling_hash::b = { 32,333 }, rolling_hash::br = { 1811939312,361138381 };
array<vector<ll>, rolling_hash::n> rolling_hash::bs, rolling_hash::brs;