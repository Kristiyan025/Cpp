#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
using namespace std;

using ii = pair<int, int>;
#define X first
#define Y second
const int maxN = 2e6;
int n;
ii v[maxN];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	cin >>n;
	for(int i = 0; i < n; i++) cin >>v[i].X >>v[i].Y;
	int mnYL = INT_MAX, mnYR = mnYL, mxYL = INT_MIN, mxYR;
	int l = 0, r = n - 1, ll, rr;
	int ans = v[r].X - v[l].X;
	bool b;
	while(r - l)
	{
		ll = l;
		rr = r;
		while(v[ll].X == v[l].X)
			mnYL = min(mnYL, v[ll].Y),
			mxYL = max(mxYL, v[ll].Y), ll++;
		while(v[rr].X == v[r].X)
			mnYR = min(mnYR, v[rr].Y),
			mxYR = max(mxYR, v[rr].Y), rr--;
		b = 1;
		if(v[ll])
		if(b) break;
	}
}
