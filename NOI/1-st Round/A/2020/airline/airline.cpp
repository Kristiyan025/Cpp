#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
using namespace std;

const int maxN = 1e5 + 1;
int n;
vector<int> tr[maxN];
int depth[maxN];
int par[maxN];

void dfs1(int v = 1, int p = 1)
{
	depth[v] = depth[p] + 1;
	for(int nxt : tr[v])
		if(nxt != p)
			dfs1(nxt, v);
}

void dfs2(int v, int p)
{
	depth[v] = depth[p] + 1;
	par[v] = p;
	for(int nxt : tr[v])
		if(nxt != p)
			dfs2(nxt, v);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	cin >>n;
	int a, b;
	for(int i = 1; i < n; i++)
	{
		cin >>a >>b;
		tr[a].emplace_back(b);
		tr[b].emplace_back(a);
	}
	dfs1();
	int d1 = 1, d2 = 1;
	for(int i = 2; i <= n; i++)
		if(depth[i] > depth[d1])
			d1 = i;
	dfs2(d1, d1);
	for(int i = 2; i <= n; i++)
		if(depth[i] > depth[d2])
			d2 = i;
	vector<int> d; // diameter
	while(par[d2] != d2)
	{
		d.emplace_back(d2);
		d2 = par[d2];
	}
	d.emplace_back(d2);
	if(d.size() & 1)
		d = { d[d.size() >> 1] };
	else
		d = { d[d.size() - 1 >> 1], d[d.size() >> 1] };
	sort(d.begin(), d.end());
	cout <<d.size() <<"\n";
	for(int i : d)
		cout <<i <<" ";
	cout <<"\n";
}
