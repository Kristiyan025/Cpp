#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
using namespace std;

const short maxX = 100;
const short p = 203;
unordered_set<short> slps;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	int n;
	cin >>n;
	int ax, ay, bx, by, dx, dy, d;
	for(int i = 0; i < n; i++)
	{
		cin >>ax >>ay >>bx >>by;
		dx = bx - ax;
		dy = by - ay;
		if(dx < 0)
			dx = -dx,
			dy = -dy;
		if(dx == 0 && dy < 0) dy = -dy;
		d = __gcd(abs(dx), abs(dy));
		if(d)
			dx /= d,
			dy /= d;
		slps.insert(dx * p + dy + maxX);
	}
	cout <<slps.size() <<endl;
}
