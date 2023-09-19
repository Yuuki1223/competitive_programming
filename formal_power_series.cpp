#pragma once
#include "templates/top.cpp"
#include "templates/static_modll.cpp"
#include "templates/convolution.cpp"

using modll = modll_base<998244353>;

class fps : public vector<modll> {
public:

	fps(void) :vector<modll>() {};
	fps(ll sz) :vector<modll>(sz) {};
	fps(modll x) :vector<modll>(1, x) {};
	fps(vector<modll> ar) :vector<modll>(ar) {};

	fps inv(void)const {
		assert(!(*this).empty() && (*this)[0] != modll(0));
		ll k = countr_zero(bit_ceil((*this).size()));
		fps r((*this)[0].inv());
		REP1(i, k) {
			r = r * (fps(modll(2)) - r * (*this));
			r.resize(1ull << i);
		}
		r.resize((*this).size());
		return r;
	};

	fps differential(void)const {
		if ((*this).empty())return fps();
		fps r((*this).size() - 1);
		REP(i, (*this).size() - 1)r[i] = (*this)[i + 1] * modll(i + 1);
		return r;
	};
	
	fps integral(void) {
		fps r((*this).size() + 1);
		REP(i, (*this).size())r[i + 1] = (*this)[i] * modll(i + 1).inv();
		return r;
	};

	fps log(void)const {
		assert(!(*this).empty() && (*this)[0] == modll(1));
		fps r = ((*this).differential() / (*this)).integral();
		r.resize((*this).size());
		return r;
	};

	fps shrink(void) {
		if (maxsize < ll((*this).size()))(*this).resize(maxsize);
		return (*this);
	};

	fps operator+(const fps& x)const {
		ll s = min(maxsize, max<ll>((*this).size(), x.size()));
		fps r(s);
		REP(i, min<ll>(maxsize, (*this).size()))r[i] += (*this)[i];
		REP(i, min<ll>(maxsize, x.size()))r[i] += x[i];
		return r;
	};

	fps operator-(const fps& x)const {
		ll s = min(maxsize, max<ll>((*this).size(), x.size()));
		fps r(s);
		REP(i, min<ll>(maxsize, (*this).size()))r[i] += (*this)[i];
		REP(i, min<ll>(maxsize, x.size()))r[i] -= x[i];
		return r;
	};

	fps operator*(const fps& x)const {
		fps r(conv((*this), x));
		r.shrink();
		return r;
	};

	fps operator/(const fps& x)const {
		return (*this).operator*(x.inv());
	};

	fps& operator+=(const fps& x) { (*this) = (*this) + x; return (*this); };
	fps& operator-=(const fps& x) { (*this) = (*this) - x; return (*this); };
	fps& operator*=(const fps& x) { (*this) = (*this) * x; return (*this); };
	fps& operator/=(const fps& x) { (*this) = (*this) / x; return (*this); };
	auto operator<=>(const fps& x) const = default;

	static ll maxsize;
private:

};
ll fps::maxsize = 1 << 22;