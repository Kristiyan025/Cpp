#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
#define X first
#define Y second
const int maxN = 5e5;
int n, logN;
vector<pii> a;
vector<vector<int>> mini, maxi;
unordered_map<int, int> pow2;

inline bool cmp(const pii& p1, const pii& p2)
{
	return p1.Y < p2.Y || (p1.Y == p2.Y && p1.X < p2.X);
}

inline int gp2(int a)
{
	a |= a >> 1;
	a |= a >> 2;
	a |= a >> 4;
	a |= a >> 8;
	a |= a >> 16;
	a++;
	return a >> 1;
}

int tmp, tmp2;
inline int getMin(int l, int r)
{
	tmp = gp2(r - l);
	tmp2 = pow2[tmp];
	return min(mini[l][tmp2], mini[r - tmp][tmp2]);
}
inline int getMax(int l, int r)
{
	tmp = gp2(r - l);
	tmp2 = pow2[tmp];
	return max(maxi[l][tmp2], maxi[r - tmp][tmp2]);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    for(int i = 0, p = 1; p < maxN; i++, p <<= 1)
		pow2[p] = i;

	cin >>n;
	logN = ceil(log2(n)) + 1;
	a.resize(n);
	for(int i = 0; i < n; i++)
	{
		cin >>a[i].Y;
		a[i].X = i;
	}
	sort(a.begin(), a.end(), &cmp);
	mini = vector<vector<int>>(n, vector<int>(logN));
	maxi = vector<vector<int>>(n, vector<int>(logN));
	for(int i = 0; i < n; i++)
		mini[i][0] = maxi[i][0] = a[i].X;
	for(int l = 1, len = 1; l < logN; l++, len <<= 1)
		for(int i = 0; i + len < n; i++)
	{
		mini[i][l] = min(mini[i][l - 1], mini[i + len][l - 1]);
		maxi[i][l] = max(maxi[i][l - 1], maxi[i + len][l - 1]);
	}
	ll res = 0;
	for(int i = 0; i + 1 < n; i++)
		res = max(res, max((ll)(a[i].X - getMin(i + 1, n)) * a[i].Y,
				           (ll)(getMax(i + 1, n) - a[i].X) * a[i].Y));
	cout <<res <<endl;
}
