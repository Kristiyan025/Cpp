#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
using namespace std;

using ull = unsigned long long;
short n, m;
vector<ull> dp;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	cin >>n >>m;
	dp.resize(n + 1);
	dp[0] = 1;
	int bnd;
	for(short i = 1; i <= m; i++)
	{
		for(short j = n; j >= 1; j--)
		{
			for(short k = i; k <= j; k += i)
				dp[j] += dp[j - k];
		}

	}
	cout <<dp[n] <<endl;
}
