#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
using namespace std;

int n, ans = 0, e;
priority_queue<int> pq;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	cin >>n;
	for(int i = 0; i < n; i++)
	{
		cin >>e;
		if(pq.size() && pq.top() > e)
		{
			ans += pq.top() - e;
			pq.pop();
			pq.push(e);
		}
		pq.push(e);
	}
	cout <<ans <<"\n";
}
