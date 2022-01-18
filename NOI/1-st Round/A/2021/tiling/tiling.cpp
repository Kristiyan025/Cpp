#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
using namespace std;

using ll = long long;
using arr = vector<int>;
using mtx = vector<arr>;
const int mod = 1e9 + 7;
int t;
ll n;
mtx rec;
arr baseCase;

arr operator *(const mtx& a, const arr& b)
{
	arr res(a.size(), 0);
	for(int i = 0; i < a.size(); i++)
		for(int k = 0; k < b.size(); k++)
			res[i] = (res[i] + (ll)a[i][k] * b[k] % mod) % mod;
	return res;
}

mtx operator *(const mtx& a, const mtx& b)
{
	mtx res(a.size(), arr(b[0].size(), 0));
	for(int i = 0; i < a.size(); i++)
		for(int j = 0; j < b[0].size(); j++)
			for(int k = 0; k < b.size(); k++)
				res[i][j] = (res[i][j] + (ll)a[i][k] * b[k][j] % mod) % mod;
	return res;
}

int binpow(int a, ll b)
{
	int res = 1;
	while(b)
	{
		if(b & 1) res = (ll)a * res % mod;
		a = (ll)a * a % mod;
		b >>= 1;
	}
	return res;
}

mtx operator ^(mtx& a, ll b)
{
	mtx res(a.size(), arr(a.size(), 0));
	for(int i = 0; i < a.size(); i++)
		res[i][i] = 1;
	while(b)
	{
		if(b & 1) res = a * res;
		a = a * a;
		b >>= 1;
	}
	return res;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	cin >>n >>t;
	switch(t)
	{
	case 1:
		rec =
		{
			{1, 1},
			{1, 0}
		};
		baseCase = {1, 0};
		cout <<((rec ^ n) * baseCase)[0] <<"\n";
		return 0;
	case 2:
		if(n % 3)
			cout <<"0\n";
		else
			cout <<binpow(2, n / 3) <<"\n";
		return 0;
	case 3:
		rec =
		{
			{1, 1, 2},
			{1, 0, 0},
			{0, 1, 1}
		};
		baseCase = {2, 1, 1};
		if(n < 3)
			cout <<baseCase[2 - n] <<"\n";
		else
			cout <<((rec ^ (n - 2)) * baseCase)[0] <<"\n";
	}
}
