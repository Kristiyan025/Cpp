#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
using namespace std;

const int maxN = 61;
int n, m;
string a, b;
bool dp[maxN][3];
bool pos[maxN][2];

void ex(char i = 0, char carry = 0)
{
	if(i == n)
	{
		dp[n][carry] = 1;
		return;
	}
	if(a[i] == '?' && b[i] == '?')
	{
		dp[i][2] = 1;
		pos[i + 1][0] = 1;
		pos[i + 1][1] = 1;
	}
	else if(a[i] == '?')
	{
		dp[i][2] = 1;
		if(carry)
		{
			pos[i + 1][1] = 1;
			if(b[i] == '0') pos[i + 1][0] = 1;
		}
		else
		{
			pos[i + 1][0] = 1;
			if(b[i] == '1') pos[i + 1][1] = 1;
		}
	}
	else if(b[i] == '?')
	{
		dp[i][2] = 1;
		if(carry)
		{
			pos[i + 1][1] = 1;
			if(a[i] == '0') pos[i + 1][0] = 1;
		}
		else
		{
			pos[i + 1][0] = 1;
			if(a[i] == '1') pos[i + 1][1] = 1;
		}
	}
	else
	{
		carry = a[i] - '0' + b[i] - '0' + carry;
		dp[i][carry & 1] = 1;
		pos[i + 1][carry >> 1] = 1;
	}
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	cin >>a >>b;
	n = a.size();
	m = b.size();
	reverse(a.begin(), a.end());
	reverse(b.begin(), b.end());
	if(n < m) swap(a, b), swap(n, m);
	b += string(n - m, '0');
	pos[0][0] = 1;
	for(int i = 0; i <= n; i++)
	{
		if(pos[i][0]) ex(i, 0);
		if(pos[i][1]) ex(i, 1);
	}
	for(int i = n; i >= 0; i--)
	{
		if(dp[i][0] + dp[i][1] + dp[i][2] > 1) cout <<'?';
		else if(dp[i][0] && i != n) cout <<'0';
		else if(dp[i][1]) cout <<'1';
		else if(dp[i][2]) cout <<'?';
	}
	cout <<endl;
}
