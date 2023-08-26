#pragma once
#include "templates/top.cpp"

//requests _MOD is prime
template<ll _MOD>
class modll_base {
public:
	ll var;
	constexpr static const ll MOD = _MOD;

	modll_base() :var(0) {};
	modll_base(const ll& x) { var = parup(x, MOD); };

	modll_base pow(ll x)const { x = parup(x, MOD - 1); modll_base y(1), t(*this); while (0 < x) { if (x & 1) { y *= t; }t *= t; x >>= 1; }return y; } // 0^0 := 1
	modll_base inv(void)const { if (!var) { cout << "Modll division by zero."; exit(-1); }return pow(MOD - 2); }

	modll_base	operator+(const modll_base& x)const { modll_base y; y.var = (var + x.var < MOD ? var + x.var : var + x.var - MOD); return y; }
	modll_base	operator-(const modll_base& x)const { modll_base y; y.var = (0 <= var - x.var ? var - x.var : var - x.var + MOD); return y; }
	modll_base	operator*(const modll_base& x)const { modll_base y; y.var = (var * x.var) % MOD; return y; }
	modll_base	operator/(const modll_base& x)const { modll_base y(*this * x.inv()); return y; }
	modll_base& operator+=(const modll_base& x) { *this = *this + x; return *this; }
	modll_base& operator-=(const modll_base& x) { *this = *this - x; return *this; }
	modll_base& operator*=(const modll_base& x) { *this = *this * x; return *this; }
	modll_base& operator/=(const modll_base& x) { *this = *this / x; return *this; }
	modll_base	operator++() { var++; if (var == MOD)var = 0; return *this; }
	modll_base	operator--() { var--; if (var == -1)var += MOD; return *this; }
	modll_base	operator++(int) { modll_base y(*this); ++(*this); return y; }
	modll_base	operator--(int) { modll_base y(*this); --(*this); return y; }
	auto	operator<=>(const modll_base& x) const = default;
};

template<ll _MOD>
modll_base<_MOD> fact(const ll& x) { static vector<modll_base<_MOD>>ve(1, 1); if ((ll)ve.size() <= x) { ll i = ve.size(); ve.resize(x + 1); while (i <= x) { ve[i] = modll_base<_MOD>(i) * ve[i - 1]; ++i; } }return ve[x]; }
template<ll _MOD>
modll_base<_MOD> factr(const ll& x) { static vector<modll_base<_MOD>>ve(1, 1); if ((ll)ve.size() <= x) { ll i = ve.size(); ve.resize(x + 1); while (i <= x) { ve[i] = modll_base<_MOD>(i).inv() * ve[i - 1]; ++i; } }return ve[x]; }
template<ll _MOD>
modll_base<_MOD> perm(const ll& n, const ll& r) { if (n < r) { cout << "Wrong functioin parameter " << n << ',' << r << '.'; exit(-1); }return fact<_MOD>(n) * factr<_MOD>(n - r); }
template<ll _MOD>
modll_base<_MOD> comb(const ll& n, const ll& r) { return perm<_MOD>(n, r) * factr<_MOD>(r); }
template<ll _MOD>
modll_base<_MOD> comb_hev(const modll_base<_MOD>& n, const ull& r) { modll_base<_MOD> t = 1; REP(i, r)t *= n - modll_base<_MOD>(i); t *= factr<_MOD>(r); return t; }
template<ll _MOD>
modll_base<_MOD> repcomb(const ll& n, const ll& r) { return comb<_MOD>(n + r - 1, r); }
template<ll _MOD>
ostream& operator<<(ostream& stream, const modll_base<_MOD>& x) { stream << x.var; return stream; }
template<ll _MOD>
istream& operator>>(istream& stream, modll_base<_MOD>& x) { ll t; stream >> t; x.var = parup(t, modll_base<_MOD>::MOD); return stream; }