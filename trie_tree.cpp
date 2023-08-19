#pragma once
#include "templates/top.cpp"

class trie_tree {
public:

	trie_tree() :dat(1, u) {};

	ll insert(const string& s) {
		ll p = 0;
		REP(i, s.size()) {
			get<2>(dat[p])++;
			if (get<1>(dat[p])[ll(s[i]) - 'a'] == -1) {
				get<1>(dat[p])[ll(s[i]) - 'a'] = dat.size();
				dat.push_back(u);
				get<0>(dat.back()) = p;
				p = dat.size() - 1;
			}
			else {
				p = get<1>(dat[p])[ll(s[i]) - 'a'];
			}
		}
		get<2>(dat[p])++;
		return p;
	}

	const vector<tuple<ll, array<ll, 26>, ll>>& get_data() { return dat; }

private:
	vector<tuple<ll, array<ll, 26>, ll>> dat;	//{親id, [char - 'A']{charの子ids}, 子の数(終端文字含む)}

	static constexpr tuple<ll, array<ll, 26>, ll> u = { -1,{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},0 };
};