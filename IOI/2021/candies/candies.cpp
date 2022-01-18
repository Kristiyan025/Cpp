#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
using namespace std;

const int maxN = 2e5;
int n;
vector<int> c, lz, mn, id;

#define segTree 1, 0, n
#define le(x) (x << 1)
#define ri(x) (x << 1 | 1)

void build(int v, int l, int r)
{
	if(r - l == 1)
	{
		id[v] = l;
		return;
	}
	int mid = l + (r - l >> 1);
	build(le(v), l, mid);
	build(ri(v), mid, r);
}

void push(int v)
{
	if(lz[v])
	{
		push(le(v));
		push(ri(v));
		if(~id[le(v)]) lz[le(v)] = lz[v];
		else lz[le(v)] = min(max(0, lz[le(v)] + lz[v]), c[id[le(v)]]);
		if(~id[ri(v)]) lz[ri(v)] = lz[v];
		else lz[ri(v)] = min(max(0, lz[ri(v)] + lz[v]), c[id[ri(v)]]);
		lz[v] = 0;
	}
}

int ql, qr, qv;
void update(int v, int l, int r)
{
	if(qr <= l || r <= ql) return;
	if(r - l == 1)
	{
		lz[v] = min(max(0, lz[v] + qv), c[l]);
		return;
	}
	push(v);
	if(ql <= l && r <= qr)
	{
		lz[v] = qv;
		return;
	}
	int mid = l + (r - l >> 1);
	update(le(v), l, mid);
	update(ri(v), mid, r);
}

void query(int v, int l, int r)
{
	if(r - l == 1)
	{
		c[l] = lz[v];
		return;
	}
	push(v);
	int mid = l + (r - l >> 1);
	query(le(v), l, mid);
	query(ri(v), mid, r);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	cin >>n;
	c.resize(n);
	lz.resize(n << 2, 0);
	id.resize(n << 2, -1);
	//mn.resize(n << 2);
	for(int& i : c) cin >>i;
	build(segTree);
	int q;
	cin >>q;
	while(q--)
	{
		cin >>ql >>qr >>qv;
		qr++;
		update(segTree);
	}
	query(segTree);
	for(int i : c)
		cout <<i <<" ";
	cout <<endl;
}
/*
3
10 15 13
2
0 2 20
0 1 -11
*/
