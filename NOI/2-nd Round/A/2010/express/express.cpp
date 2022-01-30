#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
using namespace std;

using ll = long long;
const char maxD = 15;
string s;
char d[maxD], o[maxD - 1];
ll dp[maxD][maxD];

inline ll calc(ll a, char op, ll b)
{
	switch(op)
	{
		case '+': return a + b;
		case '-': return a - b;
		default:  return a * b;
	}
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >>s;
    char n = s.length();
	for(int i = 0; i < n; i++)
		if(i & 1)
			o[i >> 1] = s[i];
		else
			d[i >> 1] = s[i] - '0';
	n >>= 1;
	for(char i = 0; i <= n; i++) dp[i][i] = d[i];
	for(char len = 1, l, r, k; len <= n; len++)
	{
		for(l = 0, r = l + len; r <= n; l++, r++)
		{
			ll& val = dp[l][r];
			val = LLONG_MAX;
			cout <<"for: " <<int(l) <<" " <<int(r) <<endl;
			for(k = l; k < r; k++)
				(cout <<int(k) <<": " <<dp[l][k] <<" " <<o[k] <<" " <<dp[k + 1][r] <<" = " <<calc(dp[l][k], o[k], dp[k + 1][r]) <<endl),
				val = min(val, calc(dp[l][k], o[k], dp[k + 1][r]));
		}
	}
	//for(char len = 0, l, r; len <= n; len++)
	//{
	//	for(l = 0, r = l + len; r <= n; l++, r++)
	//	{
	//		cout <<dp[l][r] <<" ";
	//	} cout <<endl;
	//}
	cout <<dp[0][n] <<endl;
}
//9*9*9*9*9*9*9*9*9*9*9*9*9*9*9
