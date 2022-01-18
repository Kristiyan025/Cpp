#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
using namespace std;

using ll = long long;
const ll maxP = 5e4;
const ll maxS = ceil(maxP / (12 * sqrt(3)) * maxP) + 100;
ll P, P_2, P_3;
unordered_map<int, int> sq;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	for(int i = 1; i * i < maxS; i++)
		sq[i * i] = i;
    cin >>P;
    P_2 = P + 2 >> 1;
    P_3 = floor(P / 3.0) + 1;
    int a, b, c;
    ll S, R, r;
    int s;
    ll ans = 0;
    int up, lw;
    bool pos;
    for(a = 1; a < P_3; a++)
	{
		up = (P - a >> 1) + 1;
		lw = max((P - (a << 1) + 1 + (((P - (a << 1)) & 1) == 0)) >> 1, (ll)a);
		for(b = lw; b < up; b++)
			//if(b <= (c = P - a - b) && c < a + b)
		{
			c = P - a - b;
			S = P * (P - (a << 1)) * (P - (b << 1)) * (P - (c << 1));
			ans += pos = (S & 15) == 0 && sq.count(S >>= 4) && ((s = sq[S]) << 1) % P == 0 && (ll)a * b * c % (s << 2) == 0;
			//if(pos) cout <<a <<" " <<b <<" " <<c <<endl;
		}
	}

	cout <<ans <<endl;
}
