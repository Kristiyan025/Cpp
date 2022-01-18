#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
using namespace std;

using ull = unsigned long long;
const int mod = 1e9 + 7;
const int maxA = 71;
const int d = 19;
const int maxM = 1 << d;
const short pr[d] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67 };
int n, a;
int fr[maxA], mask[maxA], pos[maxA];
int *dp1, *dp2;

void solve()
{
	dp1 = new int[maxM];
	dp2 = new int[maxM];
	for(int i = 1; i < maxA; i++)
		if(pos[i] & 1)
			pos[i] = pos[i] + mod >> 1;
		else
			pos[i] >>= 1;
	for(short i = 2, k, cnt; i < maxA; i++)
	{
		k = i;
		for(short j = 0; j < d; j++)
		{
			cnt = 0;
			while(k % pr[j] == 0) k /= pr[j], cnt++;
			if(cnt & 1) mask[i] |= 1 << j;
		}
	}
	dp2[0] = 1;
	for(int at = 1; at < maxA; at++)
	{
		if(fr[at])
		{
			for(int msk = 0; msk < maxM; msk++)
			{
				dp1[msk] = (ull)(dp2[msk] + dp2[msk ^ mask[at]]) * pos[at] % mod;
			}
			swap(dp1, dp2);
		}
	}
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	cin >>n;
	fill_n(pos, maxA, 1);
	for(int i = 0; i < n; i++)
	{
		cin >>a;
		fr[a]++;
		pos[a] = ((ull)pos[a] << 1) % mod;
	}
	solve();
	cout <<(dp2[0] + mod - 1) % mod <<endl;
}
