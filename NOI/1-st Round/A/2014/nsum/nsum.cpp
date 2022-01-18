#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
using namespace std;

using ll = long long;
const ll maxN = 1e12;
const ll maxP = 1414214;
ll n;
ll pre[maxP] = {0};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	cin >>n;
	int i;
	for(i = 1; i < maxP; i++)
		pre[i] = i + pre[i - 1];
	ll it = 0;
	ll ans = 0;
	for(int i = 0; i <= n; i++)
	{
		it = lower_bound(pre + i, pre + maxP, pre[i] + n) - pre;
		if(it == maxP) break;
		ans += pre[it] == pre[i] + n;
		//if(pre[it] == pre[i] + n) cout <<i <<" " <<it <<" " <<pre[i] <<" " <<pre[it] <<endl;
	}
	cout <<ans <<endl;
}
