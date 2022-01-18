#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
using namespace std;

using ll = long long;
using pic = pair<int, char>;
using pii = pair<int, int>;
#define X first
#define Y second
#define all(x) x.begin(), x.end()
int n, m;
vector<pic> seg;
vector<pii> arr, pt;
vector<int> maxi;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	cin >>n >>m;
	int a;
	for(int i = 0; i < n; i++)
	{
		cin >>a;
		seg.push_back({a, 1});
		cin >>a;
		seg.push_back({a - m, 0});
		if(seg[seg.size() - 2].X > seg.back().X)
			seg.pop_back(),
			seg.pop_back();
	}
	n = seg.size();
	if(n == 0)
	{
		cout <<"\n";
		return 0;
	}
	sort(all(seg));
	arr.reserve(n);
	pt.reserve(n);
	int s = 0;
	for(auto [x, b] : seg)
	{
		if(b) s++;
		if(arr.empty())
			arr.push_back({x, s});
		else if(arr.back().X == x)
		{
			if(b) arr.back().Y++;
		}
		else
			arr.push_back({x, s});
		if(!b) s--;
	}
	n = arr.size();
	maxi.resize(n);
	maxi[0] = arr[0].Y;
	for(int i = 1; i < n; i++)
		maxi[i] = max(arr[i].Y, maxi[i - 1]);
	int res = maxi[n - 1], it;
	for(int i = 1; i < n; i++)
	{
		it = lower_bound(arr.begin(), arr.begin() + i, arr[i].X - m, [](const pii& p, const int g){return p.X < g;}) - arr.begin();
		if(arr[it].X == arr[i].X - m)
			res = max(res, arr[i].Y + maxi[it]);
		else if(it > 0)
			res = max(res, arr[i].Y + maxi[it - 1]);
	}
	cout <<res <<endl;
}
