#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
const char sz = 64;
bitset<sz> s, t;
short z, off, maxZ;
ll dp[sz][2][2][2][61];

ll rec(short pos = 0, bool bl = 1, bool bu = 1, bool bg = 0, short zc = 0)
{
	if(zc > z) return 0;;
	if(pos == maxZ) return zc == z;
	ll& res = dp[pos][bl][bu][bg][zc];
	if(~res) return res;
	res = 0;
	char lw = bl ? s[pos] : 0;
	char up = bu ? char(t[pos]) + 1 : 2;
	for(char i = lw; i < up; i++)
		res += rec(pos + 1, bl && i == lw, bu && i == up - 1, bg || i > 0, zc + (i == 0 && bg));
	return res;
}

inline ull msb(ull x)
{
	x |= x >> 1;
	x |= x >> 2;
	x |= x >> 4;
	x |= x >> 8;
	x |= x >> 16;
	x |= x >> 32;
	return ++x;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	ull _s, _t, __s = 0, __t = 0;
	cin >>_s >>_t >>z;
	maxZ = max(__builtin_ctzll(msb(_s)), __builtin_ctzll(msb(_t)));
	for(int i = 0; i < sz; i++)
		__s |= ull((_s >> i) & 1) << (sz - i - 1),
		__t |= ull((_t >> i) & 1) << (sz - i - 1);
	off = min(__builtin_ctzll(__s), __builtin_ctzll(__t));
	s = __s >> off;
	t = __t >> off;
	memset(dp, -1, sizeof(dp));
	cout <<rec() <<endl;
}
