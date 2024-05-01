#pragma once
#include "templates/top.cpp"

struct edge {
	ll from;
	ll to;
	ll id;
	ll revid;
};

struct weighted_edge :public edge {
	weighted_edge(ll _from, ll _to, ll _id, ll _revid, ll _weight) :edge({ _from, _to, _id, _revid }), weight(_weight) {};
	ll weight;
};

template<typename Edge>
class graph_base {
public:
	graph_base() : adjacency_list(), adjacency_list_reverse() {};
	graph_base(ll size) :adjacency_list(size), adjacency_list_reverse(size) {};

	const vector<Edge>& operator[](const ll& i)const { return adjacency_list[i]; };
	const vector<Edge>& adj_list(const ll& i)const { return adjacency_list[i]; };
	const vector<Edge>& adj_list_rev(const ll& i)const { return adjacency_list_reverse[i]; };

	const ll size(void)const { return static_cast<ll>(adjacency_list.size()); };

	const ll indeg(const ll& i)const { return static_cast<ll>(adjacency_list_reverse[i].size()); };
	const ll outdeg(const ll& i)const { return static_cast<ll>(adjacency_list[i].size()); };

protected:
	vector<vector<Edge>> adjacency_list, adjacency_list_reverse;

};

class directed_grqph :public graph_base<edge> {
public:
	using graph_base<edge>::graph_base;

	void addedge(const ll& from, const ll& to) {
		edge e(from, to, static_cast<ll>(adjacency_list[from].size()), static_cast<ll>(adjacency_list_reverse[to].size()));
		adjacency_list[from].push_back(e);
		adjacency_list_reverse[to].push_back(e);
	};

protected:

};

class undirected_graph :public directed_grqph {
public:
	using directed_grqph::directed_grqph;

	void addedge(const ll& from, const ll& to) {
		directed_grqph::addedge(from, to);
		directed_grqph::addedge(to, from);
	};

	const ll indeg(const ll& i) = delete;
	const ll outdeg(const ll& i) = delete;
	const ll deg(const ll& i)const { return directed_grqph::outdeg(i); };

protected:

};

class tree :public undirected_graph {
public:
	tree() :undirected_graph() {};
	tree(const vector<pair<ll, ll>>& es) :undirected_graph(static_cast<ll>(es.size()) + 1) {
		for (const pair<ll, ll>& p : es)undirected_graph::addedge(p.first, p.second);
	};
	tree(const vector<ll>& par, const ll& root) :undirected_graph(static_cast<ll>(par.size())) {
		REP(i, par.size())if (i != root)undirected_graph::addedge(i, par[i]);
	};

	void addedge(const ll& from, const ll& to) = delete;

protected:
	
};

class weighted_directed_graph :public graph_base<weighted_edge> {
public:
	using graph_base<weighted_edge>::graph_base;

	void addedge(const ll& from, const ll& to, const ll& weight) {
		weighted_edge e(from, to, static_cast<ll>(adjacency_list[from].size()), static_cast<ll>(adjacency_list_reverse[to].size()), weight);
		adjacency_list[from].push_back(e);
		adjacency_list_reverse[to].push_back(e);
	};

protected:

};

class weighted_undirected_graph :public weighted_directed_graph {
public:
	using weighted_directed_graph::weighted_directed_graph;

	void addedge(const ll& from, const ll& to, const ll& weight) {
		weighted_directed_graph::addedge(from, to, weight);
		weighted_directed_graph::addedge(to, from, weight);
	}

	const ll indeg(const ll& i) = delete;
	const ll outdeg(const ll& i) = delete;
	const ll deg(const ll& i)const { return weighted_directed_graph::outdeg(i); };

protected:

};