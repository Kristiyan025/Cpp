#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
using namespace std;

using ll = long long;
const int mod = 1e9 + 7;
const short maxN = 100;
string s;
short n;
int dp[maxN][maxN];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >>s;
    n = s.length();
    for(int i = 0; i < n; i++) dp[i][1] = 1;
	for(short l = 2; l <= n; l++)
	{
		for(short i = 0; i <= n - l; i++)
		{
			dp[i][l] = (dp[i][l - 1] + dp[i + 1][l - 1] + ll(mod) - dp[i + 1][l - 2]) % mod;
			if(s[i] == s[i + l - 1]) dp[i][l] = (dp[i][l] + dp[i + 1][l - 2] + 1) % mod;
		}
	}
	cout <<dp[0][n] <<endl;
}
