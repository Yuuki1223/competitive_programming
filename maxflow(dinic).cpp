#pragma once
#include "templates/top.cpp"

class dinic_maxflow {
private:
	const ll vsize;							//���_��
	struct edge {
		ll to, cap, rev;						//to:�s����, cap:�e��, rev:g[to][rev]�����g�̋t��
		bool nr = false;								//nr:*this�����ӂ��t�ӂ�
	};
	vector<ll> level, iter;					//level[vsize],[i]:�T���n�_����i�܂ł̋���
	vector<vector<edge>> g, e;					//e:�ӂ̋t�ӊ܂ޗאڃ��X�g,g:�ő嗬�v�Z�p

	[[noreturn]] void dinic_err(const string msg) {
		cout << NL << NL << msg << endl;
		exit(0);
	};

	void bfs(ll s) {							//�t���[���c���Ă�ӂ�����s����̋�����level��
		REP(i, vsize) level[i] = Llmax / 3;
		queue<ll> que;
		level[s] = 0;
		que.push(s);
		while (!que.empty()) {
			ll v = que.front();
			que.pop();
			REP(i, g[v].size()) {
				const edge& ed = g[v][i];
				if (0 < ed.cap && level[ed.to] == Llmax / 3) {
					level[ed.to] = level[v] + 1;
					que.push(ed.to);
				}
			}
		}
	};

	ll dfs(ll v, ll t, ll f) {
		if (v == t)return f;
		for (ll& i = iter[v]; i < g[v].size(); i++) {
			edge& ed = g[v][i];
			if (0 < ed.cap && level[v] < level[ed.to]) {
				ll d = dfs(ed.to, t, min(f, ed.cap));
				if (0 < d) {
					ed.cap -= d;
					g[ed.to][ed.rev].cap += d;
					return d;
				}
			}
		}
		return 0;
	};

public:
	dinic_maxflow(ll size) :vsize(size), e(size), level(size), iter(size) {};

	dinic_maxflow(const vector<vector<pair<ll, ll>>>& ag) :vsize(ag.size()), e(ag.size()), level(ag.size()), iter(ag.size()) {
		REP(i, vsize)REP(j, ag[i].size()) {
			e[i].push_back({ ag[i][j].first, ag[i][j].second, (ll)e[ag[i][j].first].size(), true });
			e[ag[i][j].first].push_back({ i, 0ll, (ll)e[i].size() - 1, false });
		}
	};

	dinic_maxflow(const ll size, const vector<vector<pair<ll, ll>>>& ag) :vsize(size), e(size), level(size), iter(size) {
		if (size < ag.size())dinic_err("fail to create new dinic class(too small vertex size).");
		REP(i, ag.size())REP(j, ag[i].size()) {
			e[i].push_back({ ag[i][j].first, ag[i][j].second, (ll)e[ag[i][j].first].size(), true });
			e[ag[i][j].first].push_back({ i, 0, (ll)e[i].size() - 1, false });
		}
	};

	void add_edge(ll from, ll to, ll cap) {
		if (from < 0 || vsize <= from || to < 0 || vsize <= to || cap < 0)dinic_err("fail to add dinic graph(invalid argument).");
		e[from].push_back({ to, cap, (ll)e[to].size(), true });
		e[to].push_back({ from, 0, (ll)e[from].size() - 1, false });
	};

	ll max_flow(ll s, ll t) {
		ll flow = 0;
		g = e;
		while (true) {
			bfs(s);
			if (level[t] == Llmax / 3)return flow;		//t�ɓ��B�s�\
			REP(i, vsize) iter[i] = 0;
			ll f;
			while (0 < (f = dfs(s, t, Llmax))) { flow += f; }
		}
	};

	vector<vector<pair<ll, ll>>> max_flow_result(void) {
		//g��e��˂����킹�� vector<vcetor<pair<ll,ll>>> [vsize][?],[i][j] == i����(�o�Ă���j�ڂ̒��_�ւ�).first��.second��������Ă���
		vector<vector<pair<ll, ll>>> d(vsize);
		REP(i, vsize) {
			REP(j, g[i].size()) {
				if (!g[i][j].nr)continue;
				d[i].push_back(make_pair(g[i][j].to, e[i][j].cap - g[i][j].cap));
			}
		}
		return d;
	};
};