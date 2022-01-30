#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
using namespace std;

int n;
vector<int> a, seg, id, rw[2];
map<int, vector<int>> pools;
vector<vector<int>> pls;
bool cur = 0, opp = 1;

#define segTree 1, 0, n
void build(int v, int l, int r)
{
	if(r - l == 1)
	{
		seg[v] = a[l];
		return;
	}
	int mid = l + (r - l >> 1),
	    le = v + 1,
	    ri = v + (mid - l << 1);
	build(le, l, mid);
	build(ri, mid, r);
	seg[v] = max(seg[le], seg[ri]);
}

int ql, qr, x;
int sub(int v, int l, int r)
{
	if(r - l == 1) return a[l] > x ? l : -1;
	int mid = l + (r - l >> 1),
	    le = v + 1,
	    ri = v + (mid - l << 1);
	return seg[le] > x ? sub(le, l, mid) : sub(ri, mid, r);
}
int query(int v, int l, int r)
{
	if(qr <= l || r <= ql) return -1;
	int mid = l + (r - l >> 1),
	    le = v + 1,
	    ri = v + (mid - l << 1);
	if(ql <= l && r <= qr)
		return sub(v, l, r);
	return ~(le = query(le, l, mid)) ? le : query(ri, mid, r);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	cin >>n;
	a.resize(n);
	seg.resize(n << 1);
	id.resize(n);
	rw[0].resize(n);
	rw[1].resize(n);
	for(int i = 0; i < n; i++)
	{
		cin >>a[i];
		pools[a[i]].emplace_back(i);
	}
	pls.reserve(pools.size());
	for(auto& [_, pl] : pools)
	{
		pls.push_back({});
		pls.back() = move(pl);
	}
	build(segTree);
	qr = n;
	id[n - 1] = -1;
	for(int i = 0; i < n - 1; i++)
	{
		ql = i + 1; x = a[i];
		id[i] = query(segTree);
	}
	rw[0] = move(a);
	bool ok;
	int iter = 0;
	while(iter < 12)
	{
		for(int i = 0; i < n; i++)
			rw[opp][i] = id[i] == -1 ? rw[cur][i] : rw[cur][i] + rw[cur][id[i]] >> 1;
		ok = 0;
		for(int i = 0; i < n; i++)
			if(rw[0][i] != rw[1][i])
			{ ok = 1; break; }
		ok = 1;
		if(!ok) break;
		for(auto& pl : pls)
		{
			for(int i : pl)
				if(rw[opp][i] != rw[opp][pl[0]])
				{ ok = 0; break; }
			if(!ok) break;
		}
		if(!ok) break;
		for(int i = 1; i < pls.size(); i++)
			if(rw[opp][pls[i][0]] <= rw[opp][pls[i - 1][0]])
			{ ok = 0; break; }
		if(!ok) break;
		swap(cur, opp);
		iter++;
	}
	for(int i : rw[cur])
		cout <<i <<"\n";
}
