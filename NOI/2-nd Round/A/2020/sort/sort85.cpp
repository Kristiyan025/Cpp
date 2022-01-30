#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
using namespace std;

const int maxN = 1e5;
const int maxA = 1e4;
int n, ans;
short a[maxN];
int dp[maxN][2], mn[maxN][2];
bool cur = 0, opp = 1;
short mini, maxi;

inline short absol(short a) { return a > 0 ? a : -a; }
int solve()
{
	mini = *min_element(a, a + n);
	maxi = *max_element(a, a + n); maxi++;
	for(int i = 0; i < n; i++)
	{
		for(short j = mini; j < maxi; j++)
			dp[j][opp] = mn[j][cur] + absol(a[i] - j);
		mn[mini][opp] = dp[mini][opp];
		for(short j = mini + 1; j < maxi; j++)
			mn[j][opp] = min(mn[j - 1][opp], dp[j][opp]);
		swap(cur, opp);
	}
	ans = INT_MAX;
	for(short i = mini; i < maxi; i++) ans = min(ans, dp[i][cur]);
	return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	cin >>n;
	for(int i = 0; i < n; i++) cin >>a[i];
	cout <<solve() <<"\n";
}
