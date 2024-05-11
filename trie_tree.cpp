#pragma once
#include "templates/top.cpp"

template<typename T>
class trie_tree {
public:

	struct node {
		T data;
		ll par;
		map<T, ll> childs;
		ll shares_count, end_count;
	};

	trie_tree() : dat(1, u) {}

	ll insert(const vector<T>& ar) {
		dat[0].shares_count++;
		ll p = 0;
		for (const T& v : ar) {
			if (dat[p].childs.contains(v)) {
				p = dat[p].childs[v];
			}
			else {
				dat[p].childs[v] = dat.size();
				dat.push_back(u);
				dat.back().data = v;
				dat.back().par = p;
				p = dat.size() - 1;
			}
			dat[p].shares_count++;
		}
		dat[p].end_count++;
		return p;
	}

	

	ll count(const vector<T>& ar)const {
		ll p = dive(ar);
		return p != -1 ? dat[p].end_count : 0;
	}

	ll prefix(const vector<T>& ar)const {
		ll p = dive(ar);
		return p != -1 ? dat[p].shares_count : 0;
	}

	void erase(const vector<T>& ar) {
		if (count(ar)) {
			ll p = dive(ar);
			dat[p].end_count--;
			while (p != 0) {
				dat[p].shares_count--;
				p = dat[p].par;
			}
			dat[p].shares_count--;
		}
		return;
	}

	ll dive(const vector<T>& ar)const {
		ll p = 0;
		for (const T& v : ar) {
			if (dat[p].childs.contains(v)) {
				p = dat[p].childs.at(v);
			}
			else {
				return -1;
			}
		}
		return p;
	}

	ll size(void)const { return dat[0].shares_count; }

	void clear(void) { dat.assign(1, u); }

	const vector<node>& getdat(void) { return dat; }

private:

	vector<node> dat;
	static const node u;
};
template<typename T>
typename const trie_tree<T>::node trie_tree<T>::u{ T(), -1, map<T, ll>{}, 0, 0 };

class trie_tree_string {
public:
	trie_tree_string() = default;

	ll insert(const string& s) {
		return tr.insert(stove(s));	
	}

	ll count(const string& s)const {
		return tr.count(stove(s));
	}

	ll prefix(const string& s)const {
		return tr.prefix(stove(s));
	}

	void erase(const string& s) {
		tr.erase(stove(s));
	}

	ll dive(const string& s)const {
		return tr.dive(stove(s));
	}

	const vector<trie_tree<char>::node>& getdat(void) { return tr.getdat(); }
	
	ll size(void)const { return tr.size(); }

	void clear(void) { tr.clear(); }

private:

	static vector<char> stove(const string& s) {
		return vector<char>(s.begin(), s.end());
	}

	trie_tree<char> tr;
};