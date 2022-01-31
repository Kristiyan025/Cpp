#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
using namespace std;

using ll = long long;
const int mod = 998244353;
int n, m, A, b, c;

int binpowmod(int a, int b)
{
	static int res; res = 1;
	while(b)
	{
		if(b & 1) res = ll(res) * a % mod;
		a = ll(a) * a % mod;
		b >>= 1;
	}
	return res;
}

int gcd(int a, int b, int& a1, int& b1)
{
	if(!b)
	{
		a1 = 1;
		b1 = 0;
		return a;
	}
	int d = gcd(b, a % b, a1, b1);
	tie(a1, b1) = make_tuple(b1, a1 - a / b * b1);
	return d;
}

int inverse(int a, int m = mod)
{
	static int a1, b1;
	assert(gcd(a, m, a1, b1) == 1);
	return ((a1 % m) + m) % m;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	cin >>n >>m >>A >>b;
	ll res = (binpowmod(A, b) + 1) % mod;
	for(int i = 1; i < m ; i++)
	{
		cin >>c;
		res = res * (binpowmod(A, c - b) + 1) % mod;
		b = c;
	}
	res = res * binpowmod(A, n - b) % mod;
	res = res * inverse(binpowmod(2, m)) % mod;
	cout <<res <<endl;
}
