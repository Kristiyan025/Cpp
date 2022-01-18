#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
using namespace std;

const short maxW = 201;
short n, w1, w2;
vector<char> a;
bool dp[maxW][maxW][maxW];

void dyn_prog()
{
	dp[0][0][0] = 1;
	for(short i = 1; i <= n; i++)
	{
		for(short j = 0; j <= w1; j++)
		{
			for(short k = 0; k <= w2; k++)
			{
				dp[i][j][k] = dp[i - 1][j][k];
				if(j - a[i] >= 0)
					dp[i][j][k] = dp[i][j][k] || dp[i - 1][j - a[i]][k];
				if(k - a[i] >= 0)
					dp[i][j][k] = dp[i][j][k] || dp[i - 1][j][k - a[i]];
			}
		}
	}
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	cin >>n >>w1 >>w2;
	a.resize(n + 1);
	short num;
	for(int i = 1; i <= n; i++)
	{
		cin >>num;
		a[i] = num;
	}
	dyn_prog();
	for(int s = w1 + w2; s >= 0; s--)
	{
		for(int j = w1, k = s - j; j >= 0 && k <= w2; j--, k++)
		{
			if(dp[n][j][k])
			{
				cout <<s <<endl;
				return 0;
			}
		}
	}
}
