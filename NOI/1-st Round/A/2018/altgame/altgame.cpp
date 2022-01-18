#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
using namespace std;

using ll = long long;
short a, b, m, n;
string s;
int g[201];
/*
g[i] - Grundy value for game of size i
g[i] == g[i % (a + b)] // i.e. periodic function
with period a + b
*/

int mex(int x, int y = 3)
{
	return x && y ? 0 : (x == 1 || y == 1 ? 2 : 1);
}

void calc()
{
	for(int i = a; i <= a + b; i++)
		if(i < b)
			g[i] = mex(g[i - a]);
		else
			g[i] = mex(g[i - a], g[i - b]);
}

ll d;
ll divide()
{
	n = s.length();
	ll t = 0, i = 0;
	while(i < n)
	{
		while(i < n && t < d) t = t * 10 + s[i++] - '0';
		t %= d;
	}
	return t;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	cin >>a >>b >>m;
	if(a > b) swap(a, b);
	d = a + b;
	calc();
	while(m--)
	{
		cin >>s;
		cout <<(g[divide()] ? "1\n" : "2\n");
	}
}
