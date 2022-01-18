#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
using namespace std;

using ull = unsigned long long;
using vi = vector<int>;
using lookup = unordered_map<ull, int>;
const int mod = 1e9 + 7;
const int p1 = 2e6 + 3;
const int p2 = 2e6 + 29;
char w;
short k;
int n, m, r;
vi a, b;
vi p_pow1, p_pow2;
vi ha1, hb1, ha2, hb2;
lookup subA, subB;

void calcHash(const vi& v, vi& h1, vi& h2)
{
	h1.resize(v.size() + 1);
	h2.resize(v.size() + 1);
	h1[0] = h2[0] = 0;
	for(int i = 1; i <= v.size(); i++)
		h1[i] = (h1[i - 1] + (ull)p_pow1[i - 1] * v[i - 1]) % mod,
		h2[i] = (h2[i - 1] + (ull)p_pow2[i - 1] * v[i - 1]) % mod;
}

inline int subs(const vi& h, const vi& p_pow, int i, int j) // [i..j)
{ return ((ull)((h[j] + mod - h[i]) % mod) * p_pow[r - i]) % mod; }
inline ull sub(const vi& h1, const vi& h2, int i, int j)
{ return (ull)subs(h1, p_pow1, i, j) * mod + subs(h2, p_pow2, i, j); }

void findSubs(const vi& v, vi& h1, vi& h2, lookup& his)
{
	const auto cond = w == '1' ? [](int a, int b){return a > b;} : [](int a, int b){return a == b;};
	int pr = v[0], cnt = 1;
	for(int i = 1; i < v.size(); i++)
	{
		if(cond(v[i], pr)) cnt++;
		else
		{
			cnt = 1;
		}
		if(cnt >= k)
			his[sub(h1, h2, i - k + 1, i + 1)]++;
		pr = v[i];
	}
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	cin >>w >>k;
	cin >>n;
	a.resize(n);
	for(int& i : a) cin >>i;
	cin >>m;
	b.resize(m);
	for(int& i : b) cin >>i;
	r = max(n, m);
	p_pow1.resize(r + 1);
	p_pow2.resize(r + 1);
	p_pow1[0] = p_pow2[0] = 1;
	for(int i = 1; i <= r; i++)
		p_pow1[i] = (ull)p1 * p_pow1[i - 1] % mod,
		p_pow2[i] = (ull)p2 * p_pow2[i - 1] % mod;
	calcHash(a, ha1, ha2);
	calcHash(b, hb1, hb2);
	findSubs(a, ha1, ha2, subA);
	findSubs(b, hb1, hb2, subB);
	ull res = 0;
	for(auto [h, f] : subA)
		res += (ull)f * subB[h];
	cout <<res <<endl;
}
