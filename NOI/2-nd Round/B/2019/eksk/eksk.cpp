#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
using namespace std;

const int maxN = 2e5 + 1;
int n, a, b, ans = 0;
vector<int> t[maxN];
int par[maxN], d[maxN], h[maxN];
int res1[maxN], res2[maxN];

int dfs(int v, int p)
{
	par[v] = p;
	d[v] = d[p] + 1;
	for(int u : t[v])
		if(u != p)
			h[v] = max(h[v], dfs(u, v));
	return ++h[v];
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	cin >>n;
	for(int i = 1; i < n; i++)
	{
		cin >>a >>b;
		t[a].emplace_back(b);
		t[b].emplace_back(a);
	}
	cin >>a >>b;
	assert(1 <= a && a <= n);
	assert(1 <= b && b <= n);
	assert(a != b);
	dfs(a, a);
	par[a] = -1;
	vector<int> path;
	path.reserve(d[b]);
	int sub = b;
	while(sub != -1)
		path.emplace_back(sub),
		sub = par[sub];
	for(int v : t[a])
		if(v != path[path.size() - 2])
			res1[a] = max(res1[a], h[v]);
	res1[a]++;
	res2[b] = h[b];
	ans = max((int)path.size() >> 1, min(res1[a], res2[b]));
	for(int i = path.size() - 2; i > 0; i--)
	{
		for(int v : t[path[i]])
			if(v != path[i - 1] && v != path[i + 1])
				res1[path[i]] = max(res1[path[i]], h[v]);
		res1[path[i]] += d[path[i]];
		res1[path[i]] = max(res1[path[i]], res1[path[i + 1]]);
	}
	for(int i = 1; i < path.size() - 1; i++)
	{
		for(int v : t[path[i]])
			if(v != path[i - 1] && v != path[i + 1])
				res2[path[i]] = max(res2[path[i]], h[v]);
		res2[path[i]] += d[b] - d[path[i]] + 1;
		res2[path[i]] = max(res2[path[i]], res2[path[i - 1]]);
	}
	for(int i = 1; i < path.size(); i++)
		ans = max(ans, min(res1[path[i]], res2[path[i - 1]]));
	cout <<ans <<endl;
}
