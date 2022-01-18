#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
using namespace std;

using ll = long long;
using vec = vector<int>;
using mtx = vector<vec>;
int n;
ll m;
vec p, res;
vector<bool> used;
mtx cycles;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	cin >>n >>m;
	p.resize(n);
	res.resize(n);
	used.assign(n, 0);
	for(int i = 0; i < n; i++)
	{
		cin >>p[i];
		p[i]--;
	}
	for(int i = 0; i < n; i++)
		if(!used[i])
	{
		cycles.push_back({});
		while(!used[i])
		{
			used[i] = 1;
			cycles.back().emplace_back(i);
			i = p[i];
		}
	}
	int m_c;
	for(vec& c : cycles)
	{
		m_c = m % c.size();
		for(int i = 0; i < c.size(); i++)
			res[c[(i + m_c) % c.size()]] = c[i] + 1;
	}
	for(int i : res)
		cout <<i <<" ";
	cout <<"\n";
}
