#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
using namespace std;

using num = short;
using ss = pair<num, num>;
#define X first
#define Y second
const num maxNN = 12;
const num INF = 2e4;
num n, nn;
ss v[maxNN];
num d[maxNN][maxNN];
num dp[1 << maxNN][maxNN];

inline num dist(char i, char j)
{ return max(abs(v[i].X - v[j].X), abs(v[i].Y - v[j].Y)); }
#define forVBit(j, f, x, p) for(int p = x, f = p & -p, j = __builtin_ctz(f); p; p -= f, f = p & -p, j = __builtin_ctz(f))

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	cin >>n;
	nn = n << 1;
	int bnd = (((1 << n) - 1) << n) + 1;
	for(num i = 0; i < nn; i++)
		cin >>v[i].X >>v[i].Y;
	for(char i = 0; i < nn; i++)
		for(char j = 0; j < nn; j++)
			d[i][j] = dist(i, j);
	num res = INF, dd;
	for(char i = 0; i < nn; i++)
		dp[1 << i][i] = max(abs(v[i].X), abs(v[i].Y));
	if(n == 1)
		for(char i = 0; i < nn; i++)
			res = min(res, dp[1 << i][i]);
	else for(int msk = 3, cnt = 2; msk < bnd; msk++, cnt = __builtin_popcount(msk))
		if(1 < cnt && cnt <= n)
			forVBit(j, f, msk, tmp1)
	{
		num& val = dp[msk][j];
		val = INF;
		forVBit(k, g, msk, tmp2)
			if(j != k)
				val = min(val, num(dp[msk ^ f][k] + d[j][k]));
		if(cnt == n) res = min(res, val);
	}
	cout <<res <<endl;
}
