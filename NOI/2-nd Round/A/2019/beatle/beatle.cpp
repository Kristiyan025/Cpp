#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
using namespace std;

const int m = 1e5 + 1;
int n;
struct plank
{ int l, r, y; };
vector<plank> segs;
vector<int> s, lz;

#define segTree 1, 0, m
inline void push(int v, int le, int ri)
{
	if(lz[v])
	{
		lz[le] = lz[ri] = s[v] = lz[v];
		lz[v] = 0;
	}
}

int ql, qr, qval;
void update(int v, int l, int r)
{
	if(qr <= l || r <= ql) return;
	if(ql <= l && r <= qr)
	{
		lz[v] = qval;
		return;
	}
	int mid = l + (r - l >> 1),
	    le = v + 1,
	    ri = v + (mid - l << 1);
	push(v, le, ri);
	update(le, l, mid);
	update(ri, mid, r);
}

int query(int v, int l, int r)
{
	if(r - l == 1)
	{
		return lz[v] > 0 ? (s[v] = lz[v]) : s[v];
	}
	int mid = l + (r - l >> 1),
	    le = v + 1,
	    ri = v + (mid - l << 1);
	push(v, le, ri);
	if(ql < mid)
		return query(le, l, mid);
	else
		return query(ri, mid, r);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	cin >>n;
	segs.resize(n);
	for(auto& [l, r, y] : segs)
	{
		cin >>l >>y >>r;
		r += l;
	}
	s.resize(m << 1, 0);
	lz.resize(m << 1, 0);
	sort(segs.begin(), segs.end(), [](const plank& p1, const plank& p2){return p1.y < p2.y || (p1.y == p2.y && p1.l < p2.l);});
	int i = 0, j = 1;
	while(i < n)
	{
		while(j < n && segs[j].y == segs[i].y) j++;
		for(int k = i; k < j; k++)
		{
			ql = segs[k].l - 1;
			qval = query(segTree);
			ql = segs[k].r;
			qval = min(qval, query(segTree)) + 1;
			ql = segs[k].l;
			qr = segs[k].r;
			update(segTree);
		}
		i = j;
	}
	int t;
	cin >>t;
	while(t--)
	{
		cin >>ql;
		cout <<query(segTree) <<" ";
	}
	cout <<"\n";
}
