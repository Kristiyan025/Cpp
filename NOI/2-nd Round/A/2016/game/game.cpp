#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
using namespace std;

using ss = pair<short, short>;
#define X first
#define Y second
const short maxN = 1e4;
short n, m, q;
short cx[maxN], cy[maxN], cr[maxN];
bool even = 0;
vector<ss> rad[10];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	cin >>n >>m >>q;
	for(short i = 0; i < n; i++)
		cin >>cx[i] >>cy[i] >>cr[i];
	short px, py;
	unordered_map<short, short> r;
	for(int i = 0; i < m; i++)
	{
		cin >>px >>py;
		r.clear();
		for(int j = 0; j < n; j++)
			r[(short)ceil(hypot(px - cx[j], py - cy[j]) + cr[j])]++;
		rad[i].reserve(r.size() + 1);
		for(auto p : r) rad[i].emplace_back(p);
		sort(rad[i].begin(), rad[i].end());
		rad[i].emplace_back(SHRT_MAX, 0);
		for(int j = 1; j < rad[i].size(); j++)
			rad[i][j].Y += rad[i][j - 1].Y;
	}
	short s;
	int pr, res = 0;
	vector<ss>::iterator it;
	while(q--)
	{
		cin >>s;
		if(even) s <<= 1;
		pr = 0;
		for(int i = 0; i < m; i++)
		{
			it = lower_bound(rad[i].begin(), rad[i].end(), s, [](const ss& p, short h){return p.X < h;});
			if(it == rad[i].begin() && it->X != s) continue;
			if(it->X != s) it--;
			pr += it->Y;
		}
		even = pr & 1 ^ 1;
		res += pr;
	}
	cout <<res <<endl;
}
