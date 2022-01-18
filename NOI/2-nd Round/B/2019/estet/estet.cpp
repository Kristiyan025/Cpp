#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
using namespace std;

const int INF = INT_MAX;
const int maxN = 1e5 + 1;
int n;
vector<int> v;
int d[maxN];
int ans[maxN];

void lis(int st, int en, int inc)
{
	fill_n(d, n + 1, INF);
	d[0] = -INF;
	int pos;
	for(int i = st; i != en; i += inc)
	{
		pos = lower_bound(d, d + n + 1, v[i]) - d;
		if(v[i] < d[pos])
			d[pos] = v[i];
		ans[i] += pos;
	}
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	cin >>n;
	v.resize(n);
	for(auto it = v.begin(); it != v.end(); it++)
		cin >>*it;
	fill_n(ans, n, -1);
	lis(0, n, +1);
	lis(n - 1, -1, -1);
	int mx = 0;
	for(int i = 0; i < n; i++)
		mx = max(mx, ans[i]);
	cout <<mx <<endl;
}
