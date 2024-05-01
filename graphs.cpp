#pragma once
#include "templates/top.cpp"
#include "templates/graph_base.cpp"

vector<ll> shortest_path_unweighted(directed_grqph g, ll start) {
	vector<ll> dis(g.size(), Llmax / 3);
	queue<ll> q;
	dis[start] = 0;
	q.push(start);
	while (!q.empty()) {
		ll v = q.front();
		q.pop();
		REP(j, g[v].size())if (chmin(dis[g[v][j].to], dis[v] + 1))q.push(g[v][j].to);
	}
	return dis;
}

vector<ll> shortest_path_positive_weighted(weighted_directed_graph g, ll start) {
	vector<ll> dis(g.size(), Llmax / 3);
	priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> pq; // (累計コスト,到達頂点)
	dis[start] = 0;
	pq.push(make_pair(0, start));
	
	while (!pq.empty()) {
		ll v = pq.top().second, d = pq.top().first;
		pq.pop();
		if (dis[v] != d)continue;
		REP(j, g[v].size()) {
			if (chmin(dis[g[v][j].to], dis[v] + g[v][j].weight))pq.push(make_pair(dis[g[v][j].to], g[v][j].to));
		}
	}
	return dis;
}

vector<ll> topological_sort(vector<vector<ll>> e) {
	vector<ll> sortedid, ine(e.size(), 0);	//入次数
	queue<ll> ninq;							//入次数0の頂点
	sortedid.reserve(e.size());

	REP(i, e.size()) {
		REP(j, e[i].size()) {
			ine[e[i][j]]++;
		}
	}

	REP(i, e.size())if (ine[i] == 0) ninq.push(i);

	while (!ninq.empty()) {
		ll v = ninq.front();				//探索頂点
		ninq.pop();
		sortedid.push_back(v);
		REP(i, e[v].size()) {
			ine[e[v][i]]--;
			if (ine[e[v][i]] == 0) ninq.push(e[v][i]);
		}
	}
	sortedid.resize(e.size(), -1);
	return sortedid;
}

pair<ll, vector<ll>> strongly_connected_component(vector<vector<ll>> e) {
	const ll n = e.size();
	ll k = 0;					//強連結成分数
	vector<ll> scc(n, -1);		//scc[i] == 頂点iを含む強連結成分の番号 in [0,k) ,トポソ順
	vector<vector<ll>> einv(n);//逆向き辺
	REP(i, n)REP(j, e[i].size()) {
		einv[e[i][j]].push_back(i);
	}

	vector<ll> postorder;		//dfs帰りがけ順
	postorder.reserve(n);
	{
		vector<bool> vis(n, false);	//dfs到達済み?
		const function<void(ll)> dfs =
			[&](ll v) {
			if (vis[v])return;
			vis[v] = true;
			REP(j, e[v].size()) {
				dfs(e[v][j]);
			}
			postorder.push_back(v);
			return;
		};
		REP(i, n)dfs(i);
	}

	reverse(ALL(postorder));

	{
		vector<bool> vis(n, false);		//dfs到達済み?
		const function<bool(ll)> dfs =	//返り値 == 頂点を追加したか
			[&](ll v)->bool {
			if (vis[v])return false;
			vis[v] = true;
			scc[v] = k;
			REP(j, einv[v].size())dfs(einv[v][j]);
			return true;
		};
		REP(i, n)if (dfs(postorder[i]))k++;
	}
	return { k,scc };
}

class lowest_common_ancestor {
public:

	lowest_common_ancestor(vector<vector<ll>> e, ll lcaroot)
		:dep(vector<ll>(e.size(), -1)), doup(vector<vector<ll>>(e.size())) {
		const ll n = e.size();
		ll npow2, doupmax;
		function<void(ll, ll)> df =
			[&](ll d, ll v)->void {
			if (dep[v] != -1) return;
			dep[v] = d;
			d++;
			REP(j, e[v].size()) {
				df(d, e[v][j]);
			}
		};

		df(0, lcaroot);

		npow2 = 1;
		doupmax = 1;
		while (npow2 < n) { npow2 *= 2; doupmax++; }

		REP(i, n)doup[i].resize(doupmax, -2);

		function<void(ll, ll)> pa =
			[&](ll par, ll v)->void {
			if (doup[v][0] != -2)return;
			doup[v][0] = par;
			REP(j, e[v].size()) {
				pa(v, e[v][j]);
			}
		};

		pa(-1, lcaroot);

		REP(j, doupmax - 1) {
			REP(i, n) {
				if (doup[i][j] != -1) {
					doup[i][j + 1] = doup[doup[i][j]][j];
				}
				else { doup[i][j + 1] = -1; }
			}
		}
		
	}

	vector<ll> getdep() { return dep; }

	ll lca(ll u, ll v) {
		if (dep[v] < dep[u])swap(u, v);
		ll ddif = dep[v] - dep[u], doupd = doup[0].size();

		REP(k, doupd) {
			if (ddif >> k & 1) { v = doup[v][k]; }
		}

		if (v == u)return u;

		for (ll k = doupd - 1; 0 <= k; k--) {
			if (doup[v][k] == -1 || doup[u][k] == -1 || doup[v][k] == doup[u][k])continue;
			else {
				v = doup[v][k];
				u = doup[u][k];
			}
		}

		return doup[v][0];
	}

	bool operator==(const lowest_common_ancestor& other) const = default;

private:
	vector<ll> dep;
	vector<vector<ll>> doup;
};

pair<ll, vector<vector<pair<ll, ll>>>> minimum_spanning_tree(vector<vector<pair<ll, ll>>> e) {
	constexpr ll start = 0;
	ll cost = 0, see = 0;
	vector<bool> vis(e.size(), false);
	vector<vector<pair<ll, ll>>> ee(e.size());
	priority_queue<tuple<ll, ll, ll>, vector<tuple<ll, ll, ll>>, greater<tuple<ll, ll, ll>>> pq;
	
	vis[start] = true;
	REP(j, e[start].size())pq.push({ e[start][j].second,start,e[start][j].first });
	see++;

	while (see < ll(e.size())) {
		ll c = get<0>(pq.top()), u = get<1>(pq.top()), v = get<2>(pq.top());
		pq.pop();
		if (!vis[v]) {
			vis[v] = true;
			see++;
			cost += c;
			REP(j, e[v].size()) {
				if (!vis[e[v][j].first])pq.push({ e[v][j].second,v,e[v][j].first });
			}
			ee[u].push_back({ v,c });
			ee[v].push_back({ u,c });
		}
	}

	return { cost,ee };
}

vector<ll> parent_array(vector<vector<ll>> e, ll root) {
	vector<ll> par(e.size(), -2);
	par[root] = -1;
	auto dfs = [&](auto dfs, ll v)->void {
		REP(j, e[v].size()) {
			if (par[e[v][j]] == -2) {
				par[e[v][j]] = v;
				dfs(dfs, e[v][j]);
			}
		}
	};
	dfs(dfs, root);

	return par;
}

vector<pair<ll, ll>> euler_tour(vector<vector<ll>> e, ll root) {
	ll id = 0;
	vector<pair<ll, ll>> etid(e.size());
	auto par = parent_array(e, root);
	auto dfs = [&](auto dfs, ll v)->void {
		etid[v].first = id++;
		REP(j, e[v].size())if (e[v][j] != par[v])dfs(dfs, e[v][j]);
		etid[v].second = id++;
	};
	dfs(dfs, root);
	return etid;
}