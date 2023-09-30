#pragma once
#include "templates/top.cpp"

namespace segtrees {
	template<typename segT>
	class segtree {
	public:
		segtree(ll _size, segT startdata, segT _dunit, function<segT(segT, segT)> _bop) :size(_size), dunit(_dunit), bop(_bop), size2p(1) {
			while (size2p < size)size2p *= 2;
			data.resize(size2p * 2 - 1, dunit);
			for (ll i = size2p - 2; 0 <= i; i--)data[i] = bop(data[i * 2 + 1], data[i * 2 + 2]);
		}

		segtree(vector<segT> startarray, segT _dunit, function<segT(segT, segT)> _bop) :size(startarray.size()), dunit(_dunit), bop(_bop), size2p(1) {
			while (size2p < size)size2p *= 2;
			data.resize(size2p * 2 - 1, dunit);
			REP(i, size)data[i + size2p - 1] = startarray[i];
			for (ll i = size2p - 2; 0 <= i; i--)data[i] = bop(data[i * 2 + 1], data[i * 2 + 2]);
		}

		void update(ll pos, segT _data) {
			pos += size2p - 1;
			data[pos] = _data;
			while (pos != 0) {			//根でない
				pos = (pos - 1) / 2;	//親へ移動
				data[pos] = bop(data[pos * 2 + 1], data[pos * 2 + 2]);
			}
			return;
		}

		segT getr(ll l, ll rp) {
			l += size2p - 1;
			rp += size2p - 1;
			segT ltot = dunit, rtot = dunit;
			while (l < rp) {
				if (!(l & 1)) {
					ltot = bop(ltot, data[l]);
					l++;
				}
				if (!(rp & 1)) {
					rp--;
					rtot = bop(data[rp], rtot);
				}
				l = (l - 1) / 2;
				rp = (rp - 1) / 2;
			}
			return bop(ltot, rtot);
		}

		segT operator[](ll pos) {
			return data[pos + size2p - 1];
		}

		ll lowerbound(ll x, function<bool(segT)> g) {	//requests gは"範囲が広がる => true->falseにはならない", g(tr[x, p]) が true を返す最小のpの値を返す、なければsize
			bse = g;
			ll res = lowerbound_sub(x, dunit, 0, 0, size2p).first;
			return res != -1 ? res : size;
		}

	private:

		pair<ll, segT> lowerbound_sub(ll x, segT ltot, ll k, ll kl, ll krp) {
			if (krp <= x)return { -1,dunit };
			else if (kl < x) {
				pair<ll, segT> p = lowerbound_sub(x, ltot, k * 2 + 1, kl, (kl + krp) / 2);
				if (p.first != -1)return p;
				ltot = p.second;
				p = lowerbound_sub(x, ltot, k * 2 + 2, (kl + krp) / 2, krp);
				return p;
			}
			else {
				if (bse(bop(ltot, data[k]))) {
					if (kl + 1 == krp) return { k - size2p + 1,bop(ltot,data[k]) };
					pair<ll, segT> p = lowerbound_sub(x, ltot, k * 2 + 1, kl, (kl + krp) / 2);
					if (p.first != -1)return p;
					ltot = p.second;
					p = lowerbound_sub(x, ltot, k * 2 + 2, (kl + krp) / 2, krp);
					return p;
				}
				else {
					ltot = bop(ltot, data[k]);
					return { -1,ltot };
				}
			}
		};

	protected:
		ll size, size2p;
		segT dunit;
		function<segT(segT, segT)> bop;
		vector<segT> data;
		function<bool(segT)> bse;

		//assert<ll>(0 <= size < (十分小さい値));
		//assert<segT>(bop(bop(a, b), c) == bop(a, bop(b, c)));
		//assert<segT>(bop(e, a) == bop(a, e) == a);
	};

	template<typename segT, typename segF>
	class segtree_dual {
	public:
		segtree_dual(ll _size, segT startdata, segF _funit, function<segT(segF, segT)> _fbact, function<segF(segF, segF)> _fop) :size(_size), funit(_funit), fbact(_fbact), fop(_fop), size2p(1) {
			while (size2p < size)size2p *= 2;
			data.resize(size2p, startdata);
			func.resize(size2p * 2 - 1, funit);
		}

		segtree_dual(vector<segT> startarray, segF _funit, function<segT(segF, segT)> _fbact, function<segF(segF, segF)> _fop) :size(startarray.size()), funit(_funit), fbact(_fbact), fop(_fop), size2p(1) {
			while (size2p < size)size2p *= 2;
			data.resize(size2p);
			REP(i, startarray.size())data[i] = startarray[i];
			func.resize(size2p * 2 - 1, funit);
		}

		segT operator[](ll pos) {
			segT dat = fbact(func[pos + size2p - 1], data[pos]);
			pos += size2p - 1;
			while (pos != 0) {
				pos = (pos - 1) / 2;
				dat = fbact(func[pos], dat);
			}
			return dat;
		}

		vector<segT> eval(void) {
			REP(i, size2p - 1) {
				func[i * 2 + 1] = fop(func[i], func[i * 2 + 1]);
				func[i * 2 + 2] = fop(func[i], func[i * 2 + 2]);
				func[i] = funit;
			}
			REP(i, size2p) {
				data[i] = fbact(func[i + size2p - 1], data[i]);
				func[i + size2p - 1] = funit;
			}
			auto tdata = data;
			tdata.resize(size);
			return tdata;
		}

		void updater(ll l, ll rp, segF f) {
			updater_sub(l, rp, f, 0, 0, size2p);
		}
	private:
		ll size, size2p;
		segF funit;
		vector<segT> data;
		vector<segF> func;
		function<segT(segF, segT)> fbact;
		function<segF(segF, segF)> fop;

		void updater_sub(ll l, ll rp, segF f, ll k, ll kl, ll krp) {
			if (l <= kl && krp <= rp) func[k] = fop(f, func[k]);
			else if (l < krp && kl < rp) {
				func[k * 2 + 1] = fop(func[k], func[k * 2 + 1]);
				func[k * 2 + 2] = fop(func[k], func[k * 2 + 2]);
				func[k] = funit;
				updater_sub(l, rp, f, k * 2 + 1, kl, (kl + krp) / 2);
				updater_sub(l, rp, f, k * 2 + 2, (kl + krp) / 2, krp);
			}
			return;
		}
	};

	template<typename segT, typename segF>
	class segtree_lazy {
	public:
		segtree_lazy(ll _size, segT startdata, segT _dunit, function<segT(segT, segT)> _bop, segF _funit, function<segT(segF, segT)> _fbact, function<segF(segF, segF)> _fop)
			:size(_size), dunit(_dunit), bop(_bop), funit(_funit), fbact(_fbact), fop(_fop), size2p(1), hig(0) {
			while (size2p < size)size2p *= 2, hig++;
			data.resize(size2p * 2 - 1, dunit);
			lazy.resize(size2p * 2 - 1, funit);
			for (ll i = size2p - 2; 0 <= i; i--)data[i] = bop(data[i * 2 + 1], data[i * 2 + 2]);
		}

		segtree_lazy(vector<segT> startarray, segT _dunit, function<segT(segT, segT)> _bop, segF _funit, function<segT(segF, segT)> _fbact, function<segF(segF, segF)> _fop)
			:size(startarray.size()), dunit(_dunit), bop(_bop), funit(_funit), fbact(_fbact), fop(_fop), size2p(1), hig(0) {
			while (size2p < size)size2p *= 2, hig++;
			data.resize(size2p * 2 - 1, dunit);
			lazy.resize(size2p * 2 - 1, funit);
			REP(i, startarray.size())data[i + size2p - 1] = startarray[i];
			for (ll i = size2p - 2; 0 <= i; i--)data[i] = bop(data[i * 2 + 1], data[i * 2 + 2]);
		}

		segT operator[](ll pos) {
			for (ll p = hig, k = 0; k < size2p * 2 - 1; p--, k = k * 2 + (bit(pos, p) ? 2 : 1))
				eval(k);
			return data[pos + size2p - 1];
		}

		segT getr(ll l, ll rp) {
			return getr_sub(l, rp, 0, 0, size2p);
		}

		void update(ll pos, segT _data) {
			for (ll p = hig, k = 0; k < size2p * 2 - 1; p--, k = k * 2 + (bit(pos, p) ? 2 : 1))
				eval(k);
			pos += size2p - 1;
			data[pos] = _data;
			while (pos != 0) {			//根でない
				pos = (pos - 1) / 2;	//親へ移動
				eval(pos * 2 + 1);
				eval(pos * 2 + 2);
				data[pos] = bop(data[pos * 2 + 1], data[pos * 2 + 2]);
			}
		}

		void updater(ll l, ll rp, segF f) {
			updater_sub(l, rp, f, 0, 0, size2p);
		}

	private:
		ll size, size2p, hig;

		segT dunit;
		function<segT(segT, segT)> bop;
		vector<segT> data;

		segF funit;
		vector<segF> lazy;
		function<segT(segF, segT)> fbact;
		function<segF(segF, segF)> fop;

		void eval(ll k) {
			data[k] = fbact(lazy[k], data[k]);
			if (k < size2p - 1) {
				lazy[k * 2 + 1] = fop(lazy[k], lazy[k * 2 + 1]);
				lazy[k * 2 + 2] = fop(lazy[k], lazy[k * 2 + 2]);
			}
			lazy[k] = funit;
		}

		segT updater_sub(ll l, ll rp, segF f, ll k, ll kl, ll krp) {
			if (l <= kl && krp <= rp) {
				lazy[k] = fop(f, lazy[k]);
				eval(k);
			}
			else if (l < krp && kl < rp) {
				eval(k);
				data[k] = bop(updater_sub(l, rp, f, k * 2 + 1, kl, (kl + krp) / 2), updater_sub(l, rp, f, k * 2 + 2, (kl + krp) / 2, krp));
			}
			else {
				eval(k);
			}
			return data[k];
		}

		segT getr_sub(ll l, ll rp, ll k, ll kl, ll krp) {
			eval(k);
			if (l <= kl && krp <= rp) return data[k];
			else if (l < krp && kl < rp) {
				return bop(getr_sub(l, rp, k * 2 + 1, kl, (kl + krp) / 2), getr_sub(l, rp, k * 2 + 2, (kl + krp) / 2, krp));
			}
			else return dunit;
		}
	};

}