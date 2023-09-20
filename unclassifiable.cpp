#pragma once
#include "templates/top.cpp"
#include "templates/segtrees.cpp"

#if true

int main() {
	//cout << fixed << setprecision(25);
	//ios_base::sync_with_stdio(false);	//<iosteam>,<stdio.h>同時不可
	//cin.tie(nullptr);					//cin,cout,flushなし同時利用不可
	
	/* 変数, 計算量limit
	int = +-2^31 = 2.1*10^9
	long long int = +-2^63 = 9.2*10^18

	INF					O(1)
	10^10^8				O(logn)
	1000000000 = 10^8	O(n)
	10000000 = 10^7		O(nlogn)
	10000 = 10^4		O(n^2)
	10000 = 10^4		O(n^2logn)
	500					O(n^3)
	100					O(n^4)
	48					O(n2^(n/2))
	30					O(2^n)
	25					O(n2^n)
	18					O(3^n)
	16					O(n3^n)
	12					O(n!)
	11					O(n!n)
	*/

	//permutation_full_search
	{
		using T = ll;
		vector<T> a;

		ranges::sort(a);
		do {

		} while (ranges::next_permutation(a).found);
	}

	//TSP(巡回セールスマン問題),O(n^2*n^k)
	{
		constexpr ll n = 18;
		vector<vector<ll>> dis(n, vector<ll>(n)), dp(1 << n, vector<ll>(n, Llmax / 3));
			//dp[1<<k][k], [st][i] == {st}に到達済みで現在iにいる最短距離

		//dp初期値

		REP(st, 1 << n) {
			REP(i, n) {
				if (bit(st, i)) {
					ull sst = st ^ (1ll << i);
					REP(j, n) {
						if (bit(sst, j)) {
							chmin(dp[st][i], dp[sst][j] + dis[i][j]);
						}
					}
				}
			}
		}
	}

	//全方位木DP(rerooting)
	{
		using DPTYPE = ll;
		const DPTYPE dpunit = 0;
		const function<DPTYPE(DPTYPE, DPTYPE)> bop = [](DPTYPE a, DPTYPE b)->DPTYPE {return 0; };
		const function<DPTYPE(DPTYPE)> addroot = [](DPTYPE r)->DPTYPE {return 0; };
		constexpr ll startroot = 0;

		ll n;
		cin >> n;
		vector<vector<tuple<ll, ll, DPTYPE>>> e(n);		//e[i][j] == 頂点iから出るj番目の辺の{行き先, 行き先でのid, {dpデータ}}
		REP(i, n - 1) {
			ll u, v;
			cin >> u >> v;
			u--; v--;
			e[u].push_back({ v,e[v].size(),DPTYPE() });
			e[v].push_back({ u,e[u].size() - 1,DPTYPE() });
		}

		vector<ll> par(n, -1);
		{
			const function<void(ll)> dfspar =
				[&](ll v)->void {
				REP(j, e[v].size()) {
					if (get<0>(e[v][j]) != par[v]) {
						par[get<0>(e[v][j])] = v;
						dfspar(get<0>(e[v][j]));
					}
				}
				return;
			};
			dfspar(startroot);
		}

		vector<DPTYPE> ans(n);
		vector<vector<DPTYPE>> foldf(n), foldb(n);

		{
			const function<DPTYPE(ll, ll)> dfs =
				[&](ll v, ll id)->DPTYPE {
				DPTYPE tans = dpunit;
				REP(j, e[v].size())if (get<0>(e[v][j]) != par[v]) {
					tans = bop(tans, dfs(get<0>(e[v][j]), j));
				}
				if (v != startroot)get<2>(e[par[v]][id]) = addroot(tans);
				return addroot(tans);
			};
			ans[startroot] = dfs(startroot, -1);
			foldf[startroot].resize(e[startroot].size() + 1, dpunit);
			foldb[startroot].resize(e[startroot].size() + 1, dpunit);
			REP(i, e[startroot].size())foldf[startroot][i + 1] = bop(foldf[startroot][i], get<2>(e[startroot][i]));
			for (ll i = e[startroot].size() - 1; 0 <= i; i--)foldb[startroot][i] = bop(foldb[startroot][i + 1], get<2>(e[startroot][i]));
		}

		{
			queue<ll> qu;
			REP(j, e[startroot].size())qu.push(get<0>(e[startroot][j]));
			while (!qu.empty()) {
				ll v = qu.front();
				qu.pop();
				DPTYPE tans = dpunit;
				REP(j, e[v].size()) {
					DPTYPE ttans;
					if (get<0>(e[v][j]) == par[v]) {
						DPTYPE tttans = dpunit;
						tttans = bop(tttans, foldf[get<0>(e[v][j])][get<1>(e[v][j])]);
						tttans = bop(tttans, foldb[get<0>(e[v][j])][get<1>(e[v][j]) + 1]);
						get<2>(e[v][j]) = ttans = addroot(tttans);
					}
					else {
						ttans = get<2>(e[v][j]);
						qu.push(get<0>(e[v][j]));
					}
					tans = bop(tans, ttans);
				}
				ans[v] = addroot(tans);
				foldf[v].resize(e[v].size() + 1, dpunit);
				foldb[v].resize(e[v].size() + 1, dpunit);
				REP(i, e[v].size())foldf[v][i + 1] = bop(foldf[v][i], get<2>(e[v][i]));
				for (ll i = e[v].size() - 1; 0 <= i; i--)foldb[v][i] = bop(foldb[v][i + 1], get<2>(e[v][i]));
			}
		}
	}

	//Mo's Algorithm
	{
		using T_in = ll;
		using t_out = ll;
		struct vector_and_range : public vector<T_in> {

			vector_and_range(ll size) : vector<T_in>(size), l(-1), rp(-1) {

			}

			void construct(ll cl, ll crp) {
				l = cl;
				rp = crp;
				for (ll i = l; i < rp; i++) {

				}
			}

			void popleft(void) {

				l++;
			}

			void pushleft(void) {
				l--;

			}

			void pushright(void) {

				rp++;
			}

			t_out ans(void) {
				return t_out();
			}

			ll l, rp;
		};

		ll n, q;
		cin >> n >> q;
		vector<ll> l(q), r(q);
		vector_and_range a(n);
		REP(i, n)cin >> a[i];
		REP(i, q)cin >> l[i] >> r[i];

		vector<t_out> ans(q);

		ll k = 0;
		while (k * k < q)k++;
		ll w = divup(n, k);

		vector<vector<tuple<ll, ll, ll>>> qsp(k);
		REP(i, q) {
			qsp[l[i] / w].push_back({ l[i],r[i] ,i });
		}
		REP(i, k) {
			REP(j, qsp[i].size())swap(get<0>(qsp[i][j]), get<1>(qsp[i][j]));
			sort(ALL(qsp[i]));
			REP(j, qsp[i].size())swap(get<0>(qsp[i][j]), get<1>(qsp[i][j]));
		}

		REP(i, k) {
			REP(j, qsp[i].size()) {
				if (!j) {
					a.construct(get<0>(qsp[i][j]), get<1>(qsp[i][j]));
				}
				else {
					while (a.l < get<0>(qsp[i][j])) {
						a.popleft();
					}
					while (get<0>(qsp[i][j]) < a.l) {
						a.pushleft();
					}
					while (a.rp < get<1>(qsp[i][j])) {
						a.pushright();
					}
				}
				ans[get<2>(qsp[i][j])] = a.ans();
			}
		}
	}

	//Heavy_Light_Decomposition
	{
		constexpr ll n = 500000;
		vector<vector<ll>> e(n);

		vector<ll> dep(n, -1), pardat;		//pardat[k] == v <=> posrdat[k][0] -> v
		vector<vector<ll>> posrdat;
		vector<pair<ll, ll>> posdat(n);		//posdat[v] == (a, b) <=> v == posrdat[a][b]
		{
			constexpr ll root = 0;
			vector<ll> par(n, -2), chsize(n, 0);
			queue<ll> qu;
			par[root] = -1;
			qu.push(root);
			{
				const function<void(ll)> makepar =
					[&](ll v) {
					REP(j, e[v].size()) {
						if (par[e[v][j]] == -2) {
							par[e[v][j]] = v;
							makepar(e[v][j]);
							chsize[v] += chsize[e[v][j]];
						}
					}
					chsize[v]++;
				};
				makepar(root);
			}
			while (!qu.empty()) {
				ll v = qu.front(), d = (v == root ? 0 : dep[par[v]] + 1);
				qu.pop();
				posrdat.push_back({ v });
				posdat[v] = { posrdat.size() - 1, posrdat.back().size() - 1 };
				dep[v] = d;
				pardat.push_back(par[v]);

				while (2 <= chsize[v]) {
					ll m = 0, nv = -1;
					REP(j, e[v].size())if (e[v][j] != par[v])chmax(m, chsize[e[v][j]]);
					REP(j, e[v].size())if (e[v][j] != par[v]) {
						if (m == chsize[e[v][j]]) {
							nv = e[v][j];
							m++;
							posrdat.back().push_back(e[v][j]);
							posdat[e[v][j]] = { posrdat.size() - 1, posrdat.back().size() - 1 };
							dep[e[v][j]] = d;
						}
						else {
							qu.push(e[v][j]);
						}
					}
					v = nv;
				}
			}
		}
	}

	return 0;
}

#endif