#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
using namespace std;

using ll = long long;
const int mod = 1e9 + 7;
const int maxN = 5e5 + 1;
int n, k;
vector<int> a;
int dp[maxN][2];
ll res = 1;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	cin >>n >>k;
	a.resize(n);
	for(int i = 0; i < n; i++)
		cin >>a[i];
	dp[0][0] = 0;
	dp[0][1] = 1;
	for(int i = 1; i < n; i++)
	{
		dp[i][0] = (ll)(k - 1) * dp[i - 1][1] % mod;
		dp[i][1] = ((ll)(k - 2) * dp[i - 1][1] % mod + dp[i - 1][0]) % mod;
	}
	int i = 0, j = n - 1;
	while(i < n && a[i] == 0) i++;
	if(i == n)
	{
		cout <<(n == 1 ? k : ((ll)k * dp[n - 2][0] % mod + (ll)k * (k - 1) % mod * (ll)dp[n - 2][1] % mod) % mod) <<endl;
		return 0;
	}
	if(i)
	{
		res = res * (((ll)(k - 1) * dp[i - 1][1] % mod + dp[i - 1][0]) % mod) % mod;
	}
	while(j >= i && a[j] == 0) j--;
	if(j < n - 1)
	{
		res = res * (((ll)(k - 1) * dp[n - j - 1 - 1][1] % mod + dp[n - j - 1 - 1][0]) % mod) % mod;
	}
	int st, col;
	for(i++; i <= j; i++)
	{
		if(a[i - 1] != 0 && a[i] == 0)
		{
			st = i;
			col = a[i - 1];
		}
		else if(a[i - 1] == 0 && a[i] != 0)
		{
			res = res * dp[i - st][col != a[i]] % mod;
		}
	}
	cout <<res <<endl;
}
