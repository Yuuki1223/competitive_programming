#pragma once
#include "templates/top.cpp"

template<typename T>
class trie_tree {
public:

	trie_tree() :dat(1, { T(),-1,{},0,0 }), u({ T(), -1, map<T, ll>{}, 0, 0 }) {}

	ll insert(vector<T> ar) {
		get<3>(dat[0])++;
		ll p = 0;
		for (const T& v : ar) {
			if (get<2>(dat[p]).contains(v)) {
				p = get<2>(dat[p])[v];
			}
			else {
				get<2>(dat[p])[v] = dat.size();
				dat.push_back(u);
				get<0>(dat.back()) = v;
				get<1>(dat.back()) = p;
				p = dat.size() - 1;
			}
			get<3>(dat[p])++;
		}
		get<4>(dat[p])++;
		return p;
	}

	ll count(vector<T> ar)const {
		ll p = dive(ar);
		return p != -1 ? get<4>(dat[p]) : 0;
	}

	ll prefix(vector<T> ar)const {
		ll p = dive(ar);
		return p != -1 ? get<3>(dat[p]) : 0;
	}

	void erase(vector<T> ar) {
		if (count(ar)) {
			ll p = dive(ar);
			get<4>(dat[p])--;
			while (p != 0) {
				get<3>(dat[p])--;
				p = get<1>(dat[p]);
			}
			get<3>(dat[0])--;
		}
		return;
	}

	ll dive(vector<T> ar)const {
		ll p = 0;
		for (const T& v : ar) {
			if (get<2>(dat[p]).contains(v)) {
				p = get<2>(dat[p]).at(v);
			}
			else {
				return -1;
			}
		}
		return p;
	}

	ll size(void)const { return get<3>(dat[0]); }

	const vector<tuple<T, ll, map<T, ll>, ll, ll>>& getdat(void) { return dat; }

private:

	vector<tuple<T, ll, map<T, ll>, ll, ll>> dat;	//dat[i] == { data, par, [ch] == chid, shares_count, end_count }
	const tuple<T, ll, map<T, ll>, ll, ll> u;
};

class trie_tree_string {
public:

	trie_tree_string() {};

	ll insert(string s) {
		return tr.insert(stove(s));	
	}

	ll count(string s)const {
		return tr.count(stove(s));
	}

	ll prefix(string s)const {
		return tr.prefix(stove(s));
	}

	void erase(string s) {
		tr.erase(stove(s));
	}

	ll dive(string s)const {
		return tr.dive(stove(s));
	}

	const vector<tuple<char, ll, map<char, ll>, ll, ll>>& getdat(void) { return tr.get(); }
	
	ll size(void)const { return tr.size(); }

private:

	static vector<char> stove(string s) {
		return vector<char>(s.begin(), s.end());
	}

	trie_tree<char> tr;
};