#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
using namespace std;

using num = short;
using pnn = pair<num, num>;
using ll = long long;
const num maxDx = 200;
const int mod = 1e9 + 7;
const ll pr = 39209;
num n;
int ans = 0;
vector<pnn> pts;
unordered_map<ll, int> slopes;
#define X first
#define Y second

num d, dx, dy, a, b, c;
inline ll hashSlope(const pnn& p1, const pnn& p2)
{
	dx = p2.X - p1.X;
	dy = p2.Y - p1.Y;
	a = +dy;
	b = -dx;
	c = p1.Y * p2.X - p1.X * p2.Y;
	if(a < 0)
		a = -a, //[0, 198]
		b = -b, //[-198, 198]
		c = -c; //[-19602, 19602]
	if(a == 0 && b < 0)
		b = -b,
		c = -c;
	d = __gcd(__gcd((num)abs(a), (num)abs(b)), (num)abs(c));
	if(d)
		a /= d,
		b /= d,
		c /= d;
	return (a * pr + b + maxDx) * pr + c + (pr >> 1);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	cin >>n;
	pts.resize(n);
	for(int i = 0; i < n; i++)
		cin >>pts[i].X >>pts[i].Y;
	for(int i = 0; i < n; i++)
		for(int j = i + 1; j < n; j++)
			slopes[hashSlope(pts[i], pts[j])]++;
	for(auto [_, fr] : slopes)
		ans = max(ans, (1 + (int)sqrt(1 + (fr << 3))) >> 1);
	cout <<ans <<endl;
}
