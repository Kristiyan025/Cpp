#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
using namespace std;

using ull = unsigned long long;
typedef double dbl;
const dbl PI = acos(-1);
const dbl EPS = 1e-9;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	int R, d, n, nh;
	cin >>R >>d >>n;
	nh = n + 1 >> 1;
	R <<= 1;
	ull res = (n & 1) == 0 && R <= d ? nh : 0;
	int l = 1, r = nh, mid;
	while(r - l > 1)
	{
		mid = l + (r - l >> 1);
		if(sin(PI / n * mid) * R <= d + EPS)
			l = mid;
		else
			r = mid;
	}
	res += ull(l) * n;
	cout <<res <<endl;
}
