#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
using namespace std;

const int maxN = 1e5;
const short maxC = 10;
int n, b, c, d;
short a[maxN];
int dp[2][maxC];
int cur = 0, opp = 1;

int solve()
{
	char bnd;
	for(int i = 0; i < n; i++)
	{
		for(char j = b; j < c; j++)
		{
			int& val = dp[cur][j]; val = INT_MIN;
			bnd = min(j + d + 1, c);
			for(char k = max(j - d, 1); k < bnd; k++)
				val = max(val, dp[opp][k] + k * a[i]);
		}
		swap(cur, opp);
	}
	int res = INT_MIN;
	for(char k = b; k < c; k++)
		res = max(res, dp[opp][k]);
	return res;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	cin >>n >>b >>c >>d; c++;
	for(int i = 0; i < n; i++)
		cin >>a[i];
	cout <<solve() <<endl;
}
