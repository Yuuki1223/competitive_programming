#pragma once
#include "templates/top.cpp"

namespace kyopro_utility {
	template<typename T>
	class multiset {
	public:
		ll size() {
			return datsize;
		}
		void insert(T x) {
			dat[x]++;
			datsize++;
		}
		void insert(T x, ll count) {
			dat[x] += count;
			datsize += count;
		}
		bool erase(T x) {
			auto it = dat.find(x);
			if (it == dat.end())return false;
			if (it->second == 1)dat.erase(it);
			else it->second--;
			datsize--;
			return true;
		}
		bool erase(T x, ll count) {
			auto it = dat.find(x);
			if (it == dat.end())return false;
			datsize -= min(it->second, count);
			count = it->second -= count;
			if (count <= 0)dat.erase(it);
			return 0 <= count;
		}
		ll count(T x) {
			auto it = dat.find(x);
			if (it == dat.end())return 0;
			else return it->second;
		}
		void clear() {
			dat.clear();
			datsize = 0;
		}
		map<T, ll> dat;
		ll datsize = 0;
	};

	class random {
	public:
		template<integral T>
		static T integer(T lower, T upper) {	//O(1)
			return uniform_int_distribution<T>(lower, upper)(rnd);
		}

		template<floating_point T>
		static T real_number(T lower, T upper) {	//O(1)
			return uniform_real_distribution<T>(lower, upper)(rnd);
		}

		template<typename T>
		static vector<T> unique_vector(ll size, T lower, T upper) {	//expected O(n(logn)^2), è’ìÀÇ™è≠Ç»Ç¢Ç»ÇÁO(nlogn)
			if (is_integral<T>() && upper - lower + T(1) < T(size)) {
				return vector<T>();
			}
			vector<T> arr(size);
			set<T> s;
			REP(i, size) {
				T a;
				do {
					a = integer<T>(lower, upper);
				} while (s.contains(a));
				s.insert(a);
				arr[i] = a;
			}
			return arr;
		}

		static vector<vector<ll>> tree(ll size) {	//O(n)
			vector<ll> par(size), shu(size);
			vector<vector<ll>> e(size);
			REP(i, size) shu[i] = i;
			shuffle(ALL(shu), rnd);
			REP1(i, size - 1)par[i] = integer(0ll, i - 1);
			REP1(i, size - 1) {
				ll j = par[i];
				e[shu[i]].push_back(shu[j]);
				e[shu[j]].push_back(shu[i]);
			}
			return e;
		}

		static vector<vector<ll>> nondirectedgraph(ll vsize, ll esize, bool connected, bool allowloop, bool allowmultiedge) {
			vector<vector<ll>> e(vsize);
			set<pair<ll, ll>> es;
			if (connected) {
				if (!(vsize - 1 <= esize))return vector<vector<ll>>();
				esize -= vsize - 1;
				e = tree(vsize);
				REP(i, vsize)REP(j, e[i].size()) es.insert({ i,e[i][j] });
			}
			while (esize) {
				ll u = integer(0ll, vsize - 1), v = integer(0ll, vsize - 1);
				tie(u, v) = pair{ min(u,v),max(u,v) };
				if ((allowloop || u != v) && (allowmultiedge || !es.count({ u,v }))) {
					e[u].push_back(v);
					e[v].push_back(u);
					esize--;
					es.insert({ u,v });
				}
			}
			return e;
		}

		static vector<vector<ll>> directedgraph(ll vsize, ll esize, bool isdag, bool allowloop, bool allowmultiedge) {
			vector<vector<ll>> e(vsize);
			set<pair<ll, ll>> es;
			vector<ll> shu(vsize);
			REP(i, vsize)shu[i] = i;
			shuffle(ALL(shu), rnd);
			while (esize) {
				ll u = integer(0ll, vsize - 1), v = integer(0ll, vsize - 1);
				if (isdag)tie(u, v) = pair{ min(u,v),max(u,v) };
				if ((allowloop || u != v) && (allowmultiedge || !es.count({ u,v }))) {
					if (isdag)e[shu[u]].push_back(shu[v]);
					else e[u].push_back(v);
					esize--;
					es.insert({ u,v });
				}
			}
			return e;
		}

		static bool probability(double p) { return (p <= 0 ? false : (1 <= p ? true : (real_number<double>(0.0, 1.0) < p))); }

		static mt19937_64& getengine(void) { return rnd; }

		static void initengine(ull seed) { rnd = mt19937_64(seed); }

	private:
		static mt19937_64 rnd;
	};
	mt19937_64 random::rnd(random_device().operator()());

	tuple<ll, ll, ll> extgcd(ll a, ll b) {
		//ax+by=gcd(a,b) Ç∆Ç»ÇÈ {gcd(a,b),x,y}ÇÃëgÇãÅÇﬂÇÈ
		if (b == 0)return { a,1,0 };
		ll g, x, y;
		tie(g, x, y) = extgcd(b, a % b);
		return { g,y,x - a / b * y };
	}

	template<integral T>
	T binsearch(T ye, T no, function<bool(T)> poss) {
		while (1 < abs(no - ye)) {
			if (poss((no + ye) / 2))ye = (no + ye) / 2;
			else no = (no + ye) / 2;
		}
		return ye;
	}

	template<floating_point T>
	T binsearch(T ye, T no, function<bool(T)> poss, ll loopcount = 60) {
		if (8 < sizeof(T))loopcount = 120;
		T m = (ye + no) / 2;
		for (ll i = 0; m != ye && m != no && i < loopcount; i++, m = (ye + no) / 2) {
			if (poss((no + ye) / 2))ye = (no + ye) / 2;
			else no = (no + ye) / 2;
		}
		return ye;
	}

	template<bool strict, typename T>
	vector<ll> longest_increase_sequence_dp(const vector<T>& ar) {	//dp[i] == ar[i]Ç™dpÇ≈ë}ì¸Ç≥ÇÍÇÈà íu
		vector<ll> dp(ar.size());
		vector<T> dp_lis;
		REP(i, ar.size()) {
			typename vector<T>::iterator it;
			if constexpr (strict) it = ranges::lower_bound(dp_lis, ar[i]);
			else it = ranges::upper_bound(dp_lis, ar[i]);
			dp[i] = it - dp_lis.begin();
			if (it == dp_lis.end())dp_lis.push_back(ar[i]);
			else *it = ar[i];
		}
		return dp;
	}

	template<typename T>
	vector<T> longest_common_sequence(const vector<T>& a, const vector<T>& b) {
		vector<vector<ll>> dp(a.size() + 1, vector<ll>(b.size() + 1, 0));
		REP(i, a.size())REP(j, b.size()) {
			if (a[i] == b[j])dp[i + 1][j + 1] = dp[i][j] + 1;
			else dp[i + 1][j + 1] = max(dp[i][j + 1], dp[i + 1][j]);
		}
		ll p = a.size(), q = b.size();
		vector<T> ans;
		while (p != 0 && q != 0) {
			if (dp[p][q] == dp[p - 1][q])p--;
			else if (dp[p][q] == dp[p][q - 1])q--;
			else {
				p--;
				q--;
				ans.push_back(a[p]);
			}
		}
		reverse(ALL(ans));
		return ans;
	}
}