#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
using namespace std;

using num = unsigned short;
using ll = long long;
using ui = unsigned int;
using pnn = pair<num, num>;
using seg = pair<pnn, pnn>;
const ui maxI = 500;
const ui maxX = maxI + 1;
const ui maxB = 2 * maxI + 1;
#define X first
#define Y second
num n;
#define sh(x) (num)(x + maxI)
struct pnn_hash {
    inline size_t operator()(const pnn& s) const {
        return s.X * maxX + s.Y;
    }
};
struct seg_hash {
    inline size_t operator()(const seg& s) const {
        return ((s.X.X * maxX + s.X.Y) * maxX + s.Y.X) * maxX + s.Y.Y;
    }
};
unordered_set<seg, seg_hash> segs;

void read()
{
	cin >>n;
	short ax, ay, bx, by;
	seg s;
	for(int i = 0; i < n; i++)
	{
		cin >>ax >>ay >>bx >>by;
		s = {{sh(ax), sh(ay)}, {sh(bx), sh(by)}};
		if(s.X.X > s.Y.X || (s.X.X == s.Y.X && s.X.Y > s.Y.Y)) swap(s.X, s.Y);
		segs.insert(s);
	}
	n = segs.size();
}

inline bool in(ll x, int xa, int xb)
{
	return min(xa, xb) <= x && x <= max(xa, xb);
}

bitset<maxB> pts[maxB];
inline void add(const seg& s)
{
	short dx = (short)s.Y.X - s.X.X;
	short dy = (short)s.Y.Y - s.X.Y;
	short d = __gcd(abs(dx), abs(dy));
	dx /= d;
	dy /= d;
	for(int x = s.X.X, y = s.X.Y; x <= s.Y.X && in(y, s.X.Y, s.Y.Y); x += dx, y += dy)
		pts[x][y] = 1;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	read();
	for(seg s : segs)
		add(s);
	ll res = 0;
	for(int i = 0; i < maxB; i++)
		res += pts[i].count();
	cout <<res <<endl;
}
