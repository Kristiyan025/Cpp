#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;
#define X first
#define Y second
#define all(x) x.begin(), x.end()
int n, m, r;
vector<int> a, b;
vector<pii> as, bs, ida, idb;
int p, q, cnt;

bool possible()
{
	as.resize(n);
	bs.resize(m);
	for(int i = 0; i < n; i++)
		as[i] = { a[i], i };
	for(int i = 0; i < m; i++)
		bs[i] = { b[i], i };
	sort(all(as));
	sort(all(bs));
	ida.resize(n + m);
	auto it = set_intersection(all(as), all(bs), ida.begin(), [](const pii& p1, const pii& p2){return p1.X < p2.X;});
	ida.resize(it - ida.begin());
	r = ida.size();
	p = q = 0;
	idb.clear(); idb.reserve(r);
	while(q < r)
	{
		while(bs[p].X < ida[q].X) p++;
		idb.push_back({bs[p].Y, q++});
	}
	for(int i = 0; i < r; i++)
		ida[i] = {ida[i].Y, i};
	sort(all(ida));
	sort(all(idb));
	for(int i = 0; i < r; i++)
		if(ida[i].Y != idb[i].Y)
			return false;
	return true;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	for(int t = 0; t < 5; t++)
	{
		cin >>n;
		a.resize(n);
		for(int i = 0; i < n; i++)
			cin >>a[i];
		cin >>m;
		b.resize(m);
		for(int i = 0; i < m; i++)
			cin >>b[i];
		cout <<possible();
	}
	cout <<endl;
}
