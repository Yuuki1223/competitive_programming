#pragma once
#include "templates/top.cpp"

namespace fentrees {
	template<typename T>
	class fenwicktree {
	public:
		fenwicktree(ll _size) :size(_size), dunit(T(0)) {
			data.resize(size, dunit);
		}

		bool updateadd(ll pos, T add) {
			if (pos < 0 || size <= pos)return false;
			for (pos++; pos <= size; pos += (pos & -pos)) {
				data[pos - 1] = data[pos - 1] + add;
			}
			return true;
		}

		T getr(ll pos) {
			if (pos <= 0)return dunit;
			pos = min(pos, size);
			T sum = dunit;
			for (; 0 < pos; pos -= (pos & -pos)) {
				sum = sum + data[pos - 1];
			}
			return sum;
		}

	private:
		ll size;
		T dunit;
		vector<T> data;
	};

	template<typename T>
	class fenwicktree_2d {
	public:
		fenwicktree_2d(ll _sizeh, ll _sizew) :sizeh(_sizeh), sizew(_sizew), dunit(T(0)) {
			data.resize(sizeh, vector<T>(sizew, dunit));
		}

		bool updateadd(ll posx, ll posy, T add) {
			if (posx < 0 || sizeh <= posx || posy < 0 || sizew <= posy)return false;
			for (ll tx = posx + 1; tx <= sizeh; tx += (tx & -tx)) {
				for (ll ty = posy + 1; ty <= sizew; ty += (ty & -ty)) {
					data[tx - 1][ty - 1] = data[tx - 1][ty - 1] + add;
				}
			}
			return true;
		}

		T getr(ll posx, ll posy) {
			if (posx <= 0 || posy <= 0)return dunit;
			posx = min(posx, sizeh);
			posy = min(posy, sizew);
			T sum = dunit;
			for (ll tx = posx; 0 < tx; tx -= (tx & -tx)) {
				for (ll ty = posy; 0 < ty; ty -= (ty & -ty)) {
					sum += data[tx - 1][ty - 1];
				}
			}
			return sum;
		}

	private:
		ll sizeh, sizew;
		T dunit;
		vector<vector<T>> data;
	};

	template<typename T>
	class fenwicktree_dynamic {
	public:
		fenwicktree_dynamic(ll _size) :size(_size), dunit(T(0)) {}

		bool updateadd(ll pos, T add) {
			if (pos < 0 || size <= pos)return false;
			for (pos++; pos <= size; pos += (pos & -pos)) {
				data[pos - 1] = data[pos - 1] + add;
			}
			return true;
		}

		T getr(ll pos) {
			if (pos <= 0)return dunit;
			pos = min(pos, size);
			T sum = dunit;
			for (; 0 < pos; pos -= (pos & -pos)) {
				sum = sum + data[pos - 1];
			}
			return sum;
		}

	private:
		ll size;
		T dunit;
		unordered_map<ll, T> data;
	};

	template<typename T>
	class fenwicktree_2d_dynamic {
	public:
		fenwicktree_2d_dynamic(ll _sizeh, ll _sizew) :sizeh(_sizeh), sizew(_sizew), dunit(T(0)) {}

		bool updateadd(ll posx, ll posy, T add) {
			if (posx < 0 || sizeh <= posx || posy < 0 || sizew <= posy)return false;
			for (ll tx = posx + 1; tx <= sizeh; tx += (tx & -tx)) {
				auto& datar = data[tx];
				for (ll ty = posy + 1; ty <= sizew; ty += (ty & -ty)) {
					datar[ty] += add;
				}
			}
			return true;
		}

		T getr(ll posx, ll posy) {
			if (posx <= 0 || posy <= 0)return dunit;
			posx = min(posx, sizeh);
			posy = min(posy, sizew);
			T sum = dunit;
			for (ll tx = posx; 0 < tx; tx -= (tx & -tx)) {
				auto& datar = data[tx];
				for (ll ty = posy; 0 < ty; ty -= (ty & -ty)) {
					sum += datar[ty];
				}
			}
			return sum;
		}

	private:
		ll sizeh, sizew;
		T dunit;
		unordered_map<ll, unordered_map<ll, T>> data;
	};
}