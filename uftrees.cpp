#pragma once
#include "templates/top.cpp"

namespace uftrees {

	class uftree {
	public:
		uftree(const ll& n) :csize(n) {
			tree.resize(n);
			high.resize(n, 0);
			size.resize(n, 1);
			REP(i, n)tree[i] = i;
		};

		bool same(const ll& x, const ll& y) {
			return root(x) == root(y);
		};

		ll connectsize(const ll& x) {
			return size[root(x)];
		}

		ll connectelement(void)const {
			return csize;
		}

		bool unite(ll x, ll y) {	//åãçáÇµÇΩÇ©
			x = root(x);
			y = root(y);
			if (x == y)return false;
			if (high[x] < high[y]) {
				tree[x] = y;
				size[y] += size[x];
				size[x] = -1;
			}
			else {
				tree[y] = x;
				size[x] += size[y];
				size[y] = -1;
				if (high[x] == high[y]) {
					high[x]++;
				}
			}
			csize--;
			return true;
		};

		ll root(const ll& x) {
			if (tree[x] == x) {
				return x;
			}
			else {
				return tree[x] = root(tree[x]);
			}
		};

	private:
		vector<ll> tree, size, high;
		ll csize;
	};

	class uftree_potential {
	public:
		uftree_potential(const ll& n) :csize(n) {
			tree.resize(n);
			high.resize(n, 0);
			size.resize(n, 1);
			pot.resize(n, 0ll);
			REP(i, n)tree[i] = i;
		};

		bool same(const ll& x, const ll& y) {
			return root(x) == root(y);
		};

		ll connectsize(const ll& x) {
			return size[root(x)];
		}

		ll connectelement(void)const {
			return csize;
		}

		bool unite(ll x, ll y, ll d) {	//åãçáÇµÇΩÇ©
			root(x);
			root(y);
			d += pot[x];
			d -= pot[y];
			x = root(x);
			y = root(y);
			if (x == y)return false;
			if (high[x] < high[y]) {
				swap(x, y);
				d = -d;
			}
			tree[y] = x;
			size[x] += size[y];
			size[y] = -1;
			if (high[x] == high[y]) {
				high[x]++;
			}
			pot[y] = d;
			csize--;
			return true;
		};

		ll diff(ll x, ll y) {
			root(x);
			root(y);
			return pot[y] - pot[x];
		};

		ll root(const ll& x) {
			if (tree[x] == x) {
				return x;
			}
			else {
				ll r = root(tree[x]);
				pot[x] += pot[tree[x]];
				return tree[x] = r;
			}
		};

	private:
		vector<ll> tree, size, high, pot;
		ll csize;
	};

}