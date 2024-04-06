#pragma once
#include "templates/top.cpp"

class bitvector {
public:
	bitvector(vector<bool> b) :zc(0), rankarray(b.size() + 1, 0ll), selectarray(b.size(), 0ll) {
		for (ull i = 0; i < b.size(); i++) {
			rankarray[i + 1] = rankarray[i] + b[i];
			zc += !b[i];
		}
		ull p = 0, q = zc;
		for (ull i = 0; i < b.size(); i++) {
			if (!b[i]) {
				selectarray[p] = i;
				p++;
			}
			else {
				selectarray[q] = i;
				q++;
			}
		}
	}

	ull rank(bool b, ull p) {//get number of b in array[0, p)
		if (b)return rankarray[p];
		else return p - rankarray[p];
	}

	ull select(bool b, ull c) {//get position that is c-th b(first == 0-th)
		if (b) {
			c += zc;
			if (selectarray.size() <= c)return selectarray.size();
		}
		else if (zc <= c)return selectarray.size();
		return selectarray[c];
	}

private:
	ull zc;
	vector<ull> rankarray, selectarray;
};

constexpr ull w = 64; 

class wavelet_matrix {
public:
	wavelet_matrix(vector<ull> a) :sz(a.size()) {
		data.reserve(w);
		zc.reserve(w);
		vector<pair<bool, ull>> ta(sz);
		for (ull i = 0; i < sz; i++)ta[i].second = a[i];

		for (ll i = w - 1; 0 <= i; i--) {
			ull tzc = 0;
			vector<bool> t(sz);
			for (ull j = 0; j < sz; j++) {
				t[j] = ta[j].first = bit(ta[j].second, i);
				tzc += !t[j];
			}
			data.push_back(bitvector(t));
			zc.push_back(tzc);
			stable_sort(ALL(ta), [](pair<bool, ull> a, pair<bool, ull> b)->bool {return !a.first && b.first; });
		}
		reverse(ALL(data));
		reverse(ALL(zc));
		
		ull c = 1, p = 0;
		for (ull i = 1; i < sz; i++) {
			if (ta[i - 1].second != ta[i].second) {
				beginpos[ta[i - 1].second] = { p,c };
				p = i;
				c = 1;
			}
			else c++;
		}
		beginpos[ta.back().second] = { p,c };
	}

	ull rank(ull a, ull p) {	//get number of a in array[0, p)
		if (!beginpos.contains(a))return 0;
		for (ll i = w - 1; 0 <= i; i--) {
			if (bit(a, i)) {
				p = zc[i] + data[i].rank(true, p);
			}
			else {
				p = data[i].rank(false, p);
			}
		}
		return p - beginpos[a].first;
	}

	ull select(ull a, ull c) {	//get position that is c-th a(first == 0-th)
		ll p;
		{
			auto it = beginpos.find(a);
			if (it == beginpos.end() || it->second.second <= c)return sz;
			p = it->second.first + c;
		}
		for (ull i = 0; i < w; i++) {
			if (bit(a, i)) {
				p = data[i].select(true, p - zc[i]);
			}
			else {
				p = data[i].select(false, p);
			}
		}
		return p;
	}

	ull quantile(ull l, ull rp, ull c) {	//get number that is c-th small
		ull ans = 0;
		for (ll i = w - 1; 0 <= i; i--) {
			ull inzc = data[i].rank(false, rp) - data[i].rank(false, l);
			bool isone = (inzc <= c);
			if (isone) {
				ans |= (1ull) << i;
				l = zc[i] + data[i].rank(true, l);
				rp = zc[i] + data[i].rank(true, rp);
				c -= inzc;
			}
			else {
				l = data[i].rank(false, l);
				rp = data[i].rank(false, rp);
			}
		}
		return ans;
	}

private:
	ull sz;
	vector<bitvector> data;
	vector<ull> zc;
	map<ull, pair<ull, ull>> beginpos;	//beginpos[elem] = {pos, num}
};