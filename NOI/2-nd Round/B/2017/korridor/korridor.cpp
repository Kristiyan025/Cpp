#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
using namespace std;

using ull = unsigned long long;
using ii = pair<int, int>;
#define X first
#define Y second
struct iii{ int l, r, w; };
int w, h, n, nh, m;
vector<ii> pts;
vector<iii> segs;
vector<int> endpts, ys;
vector<int> seg, lz;
unordered_map<int, int> dic;
ull res = 0;

inline void push(int v, int le, int ri)
{
	if(lz[v])
	{
		lz[le] = max(lz[le], lz[v]);
		lz[ri] = max(lz[ri], lz[v]);
		seg[le] = max(seg[le], lz[v]);
		seg[ri] = max(seg[ri], lz[v]);
		lz[v] = 0;
	}
}

#define segTree 1, 0, m
int ql, qr, qv;
void update(int v, int l, int r)
{
	if(qr <= l || r <= ql) return;
	if(ql <= l && r <= qr)
	{
		seg[v] = max(seg[v], qv);
		lz[v] = max(lz[v], qv);
		return;
	}
	int mid = l + (r - l >> 1),
		le = v + 1,
		ri = v + (mid - l << 1);
	push(v, le, ri);
	update(le, l, mid);
	update(ri, mid, r);
	seg[v] = max(seg[le], seg[ri]);
}

void answer(int v, int l, int r)
{
	if(r - l == 1)
	{
		if(l + 1 < m)
			res += ull(endpts[l + 1] - endpts[l]) * (w - seg[v]);
		return;
	}
	int mid = l + (r - l >> 1),
		le = v + 1,
		ri = v + (mid - l << 1);
	push(v, le, ri);
	answer(le, l, mid);
	answer(ri, mid, r);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	cin >>w >>h >>n;
	pts.resize(n);
	for(int i = 0; i < n; i++)
	{
		cin >>pts[i].X >>pts[i].Y;
		if(i - 2 >= 0 && (pts[i].X == pts[i - 1].X && pts[i].X == pts[i - 2].X ||
						  pts[i].Y == pts[i - 1].Y && pts[i].Y == pts[i - 2].Y))
			swap(pts[i], pts[i - 1]),
			i--, n--, pts.pop_back();
	}
	assert((n & 1) == 0);
	nh = n >> 1;
	segs.resize(nh);
	ys.resize(n);
	for(ull i = 0, a, b, c, d; i < nh; i++)
	{
		a = pts[i << 1].X;
		b = pts[i << 1].Y;
		c = pts[i << 1 | 1].X;
		d = pts[i << 1 | 1].Y;
		assert(a == c);
		ys[i << 1] = b;
		ys[i << 1 | 1] = d;
		segs[i] = {min(b, d), max(b, d), a };
	}
	sort(ys.begin(), ys.end());
	endpts.reserve((n - 2 >> 1) + 2);
	ull pos = 0;
	for(auto i : ys)
		if(endpts.empty() || endpts.size() && endpts.back() != i)
			endpts.emplace_back(i), dic[i] = pos++;
	m = endpts.size();
	seg.resize(m << 1, 0);
	lz.resize(m << 1, 0);
	for(auto& [l, r, x] : segs)
	{
		ql = dic[l], qr = dic[r], qv = x;
		tie(ql, qr) = make_tuple(min(ql, qr), max(ql, qr));
		update(segTree);
	}
	answer(segTree);
	cout <<res <<endl;
}
