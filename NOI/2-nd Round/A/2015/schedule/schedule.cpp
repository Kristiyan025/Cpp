#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
using namespace std;

const int maxN = 1e5 + 1;
int n, m;
vector<int> t[maxN], tr[maxN];
int in[maxN];
vector<int> lvl[2];
char ti[maxN];
int lev[maxN];
int cnt = 0, cur = 0;
vector<int> top_sort;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ifstream cin("C:\\Users\\PMGZam1\\Downloads\\schedule\\tests\\schedule.02.in");
	cin >>n >>m;
	lvl[0].reserve(n);
	lvl[1].reserve(n);
	top_sort.reserve(n);
	int a, b;
	for(int i = 1; i < n; i++)
	{
		cin >>a >>b;
		t[a].emplace_back(b);
		tr[b].emplace_back(a);
		in[b]++;
	}
	for(int i = 1; i <= n; i++)
		if(!in[i])
			lvl[0].emplace_back(i),
			ti[i] = 2,
			cnt++,
			top_sort.emplace_back(i);
	cout <<"0 -> "; for(int i : lvl[cur]) cout <<i <<" "; cout <<endl;
	bool ok;
	int ans = 0;
	while(cnt < n)
	{
		for(int i : lvl[cur])
			for(int j : t[i])
				if(ti[j] == 0)
		{
			ok = 1;
			for(int k : tr[j])
				if(ti[k] != 2)
			{
				ok = 0;
				break;
			}
			if(ok)
				lvl[cur ^ 1].emplace_back(j),
				ti[j] = 1,
				cnt++;
		}
		lvl[cur].clear();
		ans++;
		cur ^= 1;
		for(int i : lvl[cur])
			ti[i] = 2,
			lev[i] = ans,
			top_sort.emplace_back(i);
		cout <<ans <<" -> "; for(int i : lvl[cur]) cout <<i <<" "; cout <<endl;
	}
	ans = 0;
	memset(ti, 0, (n + 1) * sizeof(ti[0]));
	cout <<"top_sort: "; for(int i : top_sort) cout <<i <<" "; cout <<endl;
	for(int i = 0, ii = 0; i < n;)
	{
		cnt = 0;
		while(i < n && cnt < m)
		{
			ok = 1;
			for(int j : tr[top_sort[i]])
				if(ti[j] != 2)
			{
				ok = 0;
				break;
			}
			if(!ok) break;
			ti[top_sort[i]] = 1;
			cnt++; i++;
		}
		for(int j = ii; j < i; j++)
			ti[top_sort[j]] = 2;
		if(i == ii) break;
		cout <<ans <<" --> ";
		for(int j = ii; j < i; j++)
			cout <<top_sort[j] <<" "; cout <<endl;
		ii = i;
		ans++;
	}
	cout <<ans <<endl;
}
