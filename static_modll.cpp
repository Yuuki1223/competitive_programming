#pragma once
#include "templates/top.cpp"

class modll {
public:
	ll var;
	constexpr static const ll MOD = 998244353; //998244353,1000000007,(1000000009)

	modll() :var(0) {};
	modll(const ll& x) { var = parup(x, MOD); };

	modll pow(ll x)const { x = parup(x, MOD - 1); modll y(1), t(*this); while (0 < x) { if (x & 1) { y *= t; }t *= t; x >>= 1; }return y; } // 0^0 := 1
	modll inv(void)const { if (!var) { cout << "Modll division by zero."; exit(-1); }return pow(MOD - 2); }

	modll	operator+(const modll& x)const { modll y; y.var = (var + x.var < MOD ? var + x.var : var + x.var - MOD); return y; }
	modll	operator-(const modll& x)const { modll y; y.var = (0 <= var - x.var ? var - x.var : var - x.var + MOD); return y; }
	modll	operator*(const modll& x)const { modll y; y.var = (var * x.var) % MOD; return y; }
	modll	operator/(const modll& x)const { modll y(*this * x.inv()); return y; }
	modll& operator+=(const modll& x) { *this = *this + x; return *this; }
	modll& operator-=(const modll& x) { *this = *this - x; return *this; }
	modll& operator*=(const modll& x) { *this = *this * x; return *this; }
	modll& operator/=(const modll& x) { *this = *this / x; return *this; }
	modll	operator++() { var++; if (var == MOD)var = 0; return *this; }
	modll	operator--() { var--; if (var == -1)var += MOD; return *this; }
	modll	operator++(int) { modll y(*this); ++(*this); return y; }
	modll	operator--(int) { modll y(*this); --(*this); return y; }
	auto	operator<=>(const modll& x) const = default;
};
modll fact(const ll& x) { static vector<modll> ve(1, 1); if ((ll)ve.size() <= x) { ll i = ve.size(); ve.resize(x + 1); while (i <= x) { ve[i] = modll(i) * ve[i - 1]; ++i; } }return ve[x]; }
modll factr(const ll& x) { static vector<modll> ve(1, 1); if ((ll)ve.size() <= x) { ll i = ve.size(); ve.resize(x + 1); while (i <= x) { ve[i] = modll(i).inv() * ve[i - 1]; ++i; } }return ve[x]; }
modll perm(const ll& n, const ll& r) { if (n < r) { cout << "Wrong functioin parameter " << n << ',' << r << '.'; exit(-1); } return fact(n) * factr(n - r); }
modll comb(const ll& n, const ll& r) { return perm(n, r) * factr(r); }
modll comb_hev(const modll& n, const ull& r) { modll t = 1; REP(i, r)t *= n - modll(i); t *= factr(r); return t; }
modll repcomb(const ll& n, const ll& r) { return comb(n + r - 1, r); }
ostream& operator<<(ostream& stream, const modll& x) { stream << x.var; return stream; };
istream& operator>>(istream& stream, modll& x) { ll t; stream >> t; x.var = parup(t, modll::MOD); return stream; };