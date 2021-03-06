#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
using namespace std;

using ll = long long;
string s;
short n, len;
ll m;
vector<vector<ll>> *dp1, *dp2;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	cin >>s >>n >>m;
	len = s.length();
	int pos = len;
	dp1 = new vector<vector<ll>>(2, vector<ll>(1e3));
	dp2 = new vector<vector<ll>>(2, vector<ll>(1e3));
	for(bool bg : {0, 1})
		for(short rem = 0; rem < n; rem++)
			(*dp2)[bg][rem] = bg && rem == 0;
	for(--pos; pos >= 0; pos--)
	{
		for(bool bg : {0, 1})
			for(short rem = 0; rem < n; rem++)
				(*dp1)[bg][rem] = ((*dp2)[bg][rem] +
								   (*dp2)[1][(rem * 10 + s[pos] - '0') % n]) % m;
		swap(dp1, dp2);
	}

	cout <<(*dp2)[0][0] <<endl;
}
