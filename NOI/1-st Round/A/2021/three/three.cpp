#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
using namespace std;

using ull = unsigned long long;
const int maxN = 1e5 + 1;
int n;
vector<int> tr[maxN];
ull dp1[maxN], dp2[maxN], dp3[maxN];

inline ull sq(ull a)
{ return a * a; }

inline ull cb(ull a)
{ return a * a * a; }

void dfs(int v, int p = -1)
{
	dp1[v] = 1;
	if(tr[v].size() == 1 && tr[v][0] == p) return;
	/*  dp1  */
	for(int nxt : tr[v])
		if(nxt != p)
	{
		dfs(nxt, v);
		dp1[v] += dp1[nxt]; // 1
	}
	/*  dp2  */
	for(int nxt : tr[v])
		if(nxt != p)
	{
		dp2[v] += dp1[nxt] * (dp1[v] - dp1[nxt] - 1);
	}
	dp2[v] >>= 1; // 1 - 1
	for(int nxt : tr[v])
		if(nxt != p)
	{
		dp2[v] += dp2[nxt]; // 2
	}
	dp2[v] += dp1[v] - (tr[v].size() - (p != -1)) - 1; // 1 - v
	/*  dp3  */
	for(int nxt : tr[v])
		if(nxt != p)
	{
		dp3[v] += dp1[nxt];
	}
	dp3[v] = cb(dp3[v]);
	for(int nxt : tr[v])
		if(nxt != p)
	{
		dp3[v] -= cb(dp1[nxt]);
	}
	ull sum2 = 0;
	for(int nxt : tr[v])
		if(nxt != p)
	{
		sum2 += sq(dp1[nxt]) * (dp1[v] - dp1[nxt] - 1);
	}
	dp3[v] -= 3 * sum2;
	dp3[v] /= 6; // 1 - 1 - 1
	for(int nxt : tr[v])
		if(nxt != p)
	{
		dp3[v] += dp3[nxt]; // 3
	}
	for(int nxt : tr[v])
		if(nxt != p)
	{
		dp3[v] += dp2[nxt] * (dp1[v] - dp1[nxt] - 1); // 2 - 1
	}
	ull sz = sum2 = 0;
	for(int nxt : tr[v])
		if(nxt != p)
	{
		for(int des : tr[nxt])
			if(des != v)
		{
			dp3[v] += dp2[des]; // 2 - v
			sz += dp1[des];
		}
	}
	for(int nxt : tr[v])
		if(nxt != p)
	{
		for(int des : tr[nxt])
			if(des != v)
		{
			sum2 += dp1[des] * (sz - dp1[des]);
		}
	}
	dp3[v] += sum2 >> 1; // 1 - v - 1
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
	dfs(1);
	cout <<dp3[1] <<"\n";
}
