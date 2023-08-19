#pragma once
#include "templates/top.cpp"

namespace mat {
	template<typename T>
	bool matcheck(const vector<vector<T>>& a) {
		if (!a.size() || !a[0].size())return false;
		REP(i, a.size() - 1) if (a[i].size() != a[i + 1].size())return false;
		return true;
	}

	template<typename T>
	vector<vector<T>> matsum(const vector<vector<T>>& a, const vector<vector<T>>& b) {
		if (!matcheck(a) || !matcheck(b) || a.size() != b.size() || a[0].size() != b[0].size()) {
			cout << "\nmatsum failed.";
			exit(-1);
		}
		vector<vector<T>> c(a);
		REP(i, b.size())REP(j, b[i].size())c[i][j] += b[i][j];
		return c;
	}

	template<typename T>
	vector<vector<T>> matscale(const vector<vector<T>> a, const T k) {
		if (!matcheck(a)) {
			cout << "\nmatscale failed.";
			exit(-1);
		}
		vector<vector<T>> c(a);
		REP(i, a.size())REP(j, a[i].size())c[i][j] *= k;
		return c;
	}

	template<typename T>
	vector<vector<T>> matproduct(const vector<vector<T>>& a, const vector<vector<T>>& b) {
		if (!matcheck(a) || !matcheck(b) || a[0].size() != b.size()) {
			cout << "\nmatproduct failed.";
			exit(-1);
		}
		vector<vector<T>> c(a.size(), vector<T>(b[0].size(), T(0)));
		REP(i, a.size()) {
			REP(j, b[0].size()) {
				REP(k, b.size()) {
					c[i][j] += a[i][k] * b[k][j];
				}
			}
		}
		return c;
	}

	template<typename T>
	T matdet(vector<vector<T>> a) {
		if (!matcheck(a) || a.size() != a[0].size()) {
			cout << "\nmatinfo failed.";
			exit(-1);
		}
		T det(1);
		const ll n = a.size();
		REP(i, n) {
			ll k;
			for (k = i; k < n; k++)if (a[k][i] != T(0))break;
			if (k != n) {
				if (k != i) {
					swap(a[i], a[k]);
					det *= T(-1);
				}
				det *= a[i][i];
				T t;
				{
					t = a[i][i];
					REPn(k, n)a[i][k] /= t;
					a[i][i] = T(1);
				}
				REPn(k, n) if (k != i) {
					t = a[k][i] / a[i][i];
					REP(l, n) {
						a[k][l] -= t * a[i][l];
					}
					a[k][i] = T(0);
				}
			}
			else return T(0);
		}
		return det;
	}
}