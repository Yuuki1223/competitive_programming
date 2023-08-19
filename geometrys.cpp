#pragma once
#include "templates/top.cpp"

namespace two_dimention {
	//todo
}

vector<pair<ll, ll>> convex_hull(vector<pair<ll, ll>> xy) {
	vector<pair<ll, ll>> rexy;
	ll s;
	deque<pair<ll, ll>> dans = { xy[1],xy[0] }, uans = { xy[1],xy[0] };

	sort(ALL(xy));

	for (ll i = 2; i < ll(xy.size()); i++) {
		while (2 <= dans.size() && 0 > (s = (((dans[0].first - dans[1].first) * (xy[i].second - dans[0].second)) - ((dans[0].second - dans[1].second) * (xy[i].first - dans[0].first)))))
			dans.pop_front();
		dans.push_front(xy[i]);
	}

	for (ll i = 2; i < ll(xy.size()); i++) {
		while (2 <= uans.size() && 0 < (s = (((uans[0].first - uans[1].first) * (xy[i].second - uans[0].second)) - ((uans[0].second - uans[1].second) * (xy[i].first - uans[0].first)))))
			uans.pop_front();
		uans.push_front(xy[i]);
	}
	while (!dans.empty()) {
		rexy.push_back(dans.back());
		dans.pop_back();
	}
	uans.pop_back();
	uans.pop_front();
	while (!uans.empty()) {
		rexy.push_back(uans.front());
		uans.pop_front();
	}
	return rexy;
}