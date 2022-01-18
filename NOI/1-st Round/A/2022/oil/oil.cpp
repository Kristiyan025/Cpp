#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
using namespace std;

using ll = long long;
int n, s;
vector<ll> a;
priority_queue<ll> pq;
ll res = 0;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	cin >>n >>s;
	a.resize(n);
	for(ll i = 0, j = 0; i < n; i++, j += s)
	{
		cin >>a[i];
		a[i] -= j;
	}
	for(int i = n - 1; i >= 0; i--)
	{
		if(pq.size() && pq.top() > a[i])
		{
			res += pq.top() - a[i];
			pq.pop();
			pq.push(a[i]);
		}
		pq.push(a[i]);
	}
	cout <<res <<endl;
}
