#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
const ll maxN = 1e5 + 1;
int n, m;
vector<int> g[maxN];
int tin[maxN], low[maxN];
bool vis[maxN];
int timer = 0;
unordered_set<ll> bridges;

inline ll hashE(int i, int j)
{ return min(i, j) * maxN + max(i, j); }
inline pii dehashE(ll h)
{ return {h / maxN, h % maxN}; }
void dfs(int v = 1, int p = -1)
{
	vis[v] = 1;
	tin[v] = low[v] = timer++;
	for(int to : g[v])
	{
		if(to == p) continue;
		if(vis[to])
			low[v] = min(low[v], low[to]);
		else
		{
			dfs(to, v);
			low[v] = min(low[v], low[to]);
			if(low[to] > tin[v])
				bridges.insert(hashE(v, to));
		}
	}
}

int bfs(int s)
{
	int sz = 1;
	queue<int> q;
	vis[s] = 1;
	q.push(s);
	while(q.size())
	{
		int v = q.front();
		q.pop();
		for(int to : g[v])
			if(!vis[to])
		{
			vis[to] = 1;
			sz++;
			q.push(to);
		}
	}
	return sz;
}

inline ll f(int x)
{ return (ll)x * (x - 1) >> 1; }

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	cin >>n >>m;
	int a, b;
	while(m--)
	{
		cin >>a >>b;
		g[a].emplace_back(b);
		g[b].emplace_back(a);
	}
	dfs();
	for(auto h : bridges)
	{
		auto [a, b] = dehashE(h);
		for(int i = 0; i < g[a].size(); i++)
			if(g[a][i] == b)
		{
			g[a][i] = g[a].back();
			g[a].pop_back();
			break;
		}
		for(int i = 0; i < g[b].size(); i++)
			if(g[b][i] == a)
		{
			g[b][i] = g[b].back();
			g[b].pop_back();
			break;
		}
	}
	memset(vis + 1, 0, n * sizeof(vis[0]));
	ll res = 0;
	for(int i = 1; i <= n; i++)
		if(!vis[i])
			res += f(bfs(i));
	cout <<res <<endl;
}
