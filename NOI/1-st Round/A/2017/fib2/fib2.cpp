#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
using namespace std;

using ll = long long;
using num = short;
using vec = vector<num>;
using mtx = vector<vec>;
const int maxP = 16;
const int maxPP = maxP * maxP + 1;
num p, mod, n;
string s, f1, f2;
char id[100];
mtx rec{{1, 1}, {1, 0}};
vec baseCase;

vec operator *(const mtx& a, const vec& b)
{
	vec res(a.size(), 0);
	for(int i = 0; i < a.size(); i++)
		for(int k = 0; k < a.size(); k++)
			res[i] = (res[i] + a[i][k] * b[k] % mod) % mod;
	return res;
}

mtx operator *(const mtx& a, const mtx& b)
{
	mtx res(a.size(), vec(a.size(), 0));
	for(int i = 0; i < a.size(); i++)
		for(int j = 0; j < a.size(); j++)
			for(int k = 0; k < a.size(); k++)
				res[i][j] = (res[i][j] + a[i][k] * b[k][j] % mod) % mod;
	return res;
}

void halve()
{
	for(int i = n - 1; i > 0; i--)
	{
		if(id[i] & 1) id[i - 1] += 10;
		id[i] >>= 1;
	}
	id[0] >>= 1;
	if(id[n - 1] == 0) n--;
}

mtx binpow(mtx a)
{
	mtx res(a.size(), vec(a.size(), 0));
	for(int i = 0; i < a.size(); i++)
		res[i][i] = 1;
	while(n)
	{
		if(id[0] & 1) res = a * res;
		a = a * a;
		halve();
	}
	return res;
}

inline int digit(char c)
{ return '0' <= c && c <= '9' ? c - '0' : c - 'A' + 10; }
inline char rev(int c)
{ return c < 10 ? c + '0' : c + 'A' - 10; }

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	cin >>p >>s >>f1 >>f2;
	mod = p * p;
	n = s.length();
	for(int i = 0; i < n; i++)
		id[i] = s[n - i - 1] - '0';
	baseCase =
	{
		digit(f2.back()) + p * digit((int)f2.length() - 2 >= 0 ? f2[f2.length() - 2] : '0'),
		digit(f1.back()) + p * digit((int)f1.length() - 2 >= 0 ? f1[f1.length() - 2] : '0')
	};
	baseCase = {baseCase[1], (baseCase[0] + mod - baseCase[1]) % mod};
	baseCase = {baseCase[1], (baseCase[0] + mod - baseCase[1]) % mod}; //baseCase = {f(0), f(-1)}
	int fn = (binpow(rec) * baseCase)[0];
	fn /= p;
	cout <<rev(fn) <<endl;
}
