#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
using namespace std;

using ull = unsigned long long;
const int maxN = 1e4 + 1;
const short INF = 2e4;
const int mod = 1e9 + 7;
const int p = 29;
int n;
string s;
short dp[maxN];
int p_pow[maxN];
int hs[maxN], hr[maxN];

void prehash()
{
	p_pow[0] = 1;
	for(int i = 1; i <= n; i++)
		p_pow[i] = (ull)p * p_pow[i - 1] % mod,
		hs[i] = (hs[i - 1] + (ull)p_pow[i - 1] * (s[i - 1] - 'a' + 1)) % mod,
		hr[i] = (hr[i - 1] + (ull)p_pow[i - 1] * (s[n - i] - 'a' + 1)) % mod;
}

inline int subS(short i, short j){ return (hs[j] + mod - hs[i]) % mod * (ull)p_pow[n - i] % mod; }//[i, j)
inline int subR(short i, short j){ return (hr[n - i - 1] + mod - hr[n - j - 1]) % mod * (ull)p_pow[j + 1] % mod; } //(i, j]
inline bool palin(short i, short j)
{
	if(i == j) return 1;
	short mid = i + j >> 1;
	return subS(i, mid + ((j - i) & 1)) == subR(mid, j);
}

void iter()
{
	fill_n(dp, n + 1, INF);
	for(short i = 0; i < n; i++)
	{
		if(palin(0, i))
			dp[i] = 0;
		else for(short j = 0; j < i; j++)
			if(palin(j + 1, i))
				dp[i] = min(dp[i], short(dp[j] + 1));
	}
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	cin >>s;
	n = s.length();
	prehash();
	iter();
	cout <<dp[n - 1] <<endl;
}
