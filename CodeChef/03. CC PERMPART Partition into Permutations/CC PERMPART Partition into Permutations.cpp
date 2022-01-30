#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
using namespace std;

int n, nn, ans;
int v[2000001];
priority_queue<int> pq;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	int t, a;
	cin >>t;
	while(t--)
	{
		cin >>n;
		nn = n << 1;
		ans = 0;
		memset(v + 1, 0, nn * sizeof v[0]);
		for(int i = 0; i < n; i++)
		{
			cin >>a;
			if(a > nn) ans++;
			else v[a]++;
		}
		pq = {};
		for(int i = nn; i; i--)
		{
			if(pq.size() && pq.top() > v[i])
			{
				ans += pq.top() - v[i];
				pq.pop();
				pq.push(v[i]);
			}
			pq.push(v[i]);
		}
		cout <<ans <<"\n";
	}
}
