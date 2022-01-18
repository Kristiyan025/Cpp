#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
using namespace std;

const int maxN = 2e4 + 1;
short k, mx = 1;
vector<short> g[maxN];
char vis[maxN];
vector<int> top;
short rev[maxN];

void dfs(short v)
{
	vis[v] = 1;
	for(short u : g[v])
		if(!vis[u])
			dfs(u);
	top.emplace_back(v);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	cin >>k;
	int sz;
	short pr, nx;
	for(short i = 0; i < k; i++)
	{
		cin >>sz;
		if(sz)
			(cin >>pr),
			mx = max(mx, pr);
		for(short j = 1; j < sz; j++)
		{
			cin >>nx;
			mx = max(mx, nx);
			g[pr].emplace_back(nx);
			pr = nx;
		}
	}
	for(short i = 1; i < mx; i++)
		if(!vis[i])
			dfs(i);
	for(short i = 0; i < top.size(); i++)
		rev[top[i]] = i;
	for(short i = 0; i < top.size(); i++)
	{
		for(short u : g[top[i]])
		{
			if(rev[u] > i)
			{
				cout <<0 <<endl;
				return 0;
			}
		}
	}
	cout <<1 <<endl;
}
