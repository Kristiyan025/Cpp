#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
#define X first
#define Y second
int n;
string s;
vector<pii> poly;

const int dx[] = {+1,  0, -1,  0};
const int dy[] = { 0, +1,  0, -1};
int d = 0;
pii turn(char c, int num, const pii& p)
{
	d = (d + (c == '+' ? +1 : -1)) & 3;
	return {p.X + dx[d] * num, p.Y + dy[d] * num};
}

ll area()
{
	ll res = 0;
	for(int i = 1; i < n; i++)
		res += (ll)poly[i].X * poly[i - 1].Y - (ll)poly[i].Y * poly[i - 1].X;
	return abs(res >> 1);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	cin >>s;
	stringstream ss(s);
	char c;
	int num;
	if(s[0] == '+' || s[0] == '-') ss >>c;
	ss >>num;
	poly.push_back({num, 0});
	while(ss >>c >>num)
		poly.push_back(turn(c, num, poly.back()));
	n = poly.size();
	cout <<area() <<endl;
}
