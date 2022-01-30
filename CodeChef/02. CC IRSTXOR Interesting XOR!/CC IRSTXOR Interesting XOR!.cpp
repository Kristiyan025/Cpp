#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	int t, a, b, c, d;
	bool w;
	cin >>t;
	while(t--)
	{
		a = b = w = 0;
		cin >>c;
		d = c;
		d |= d >> 1;
		d |= d >> 2;
		d |= d >> 4;
		d |= d >> 8;
		d |= d >> 16;
		d = __builtin_ctz(++d) - 1;
		for(; d >= 0; d--)
		{
			if(c & 1 << d)
			{
				if(w)
					a |= 1 << d;
				else
					b |= 1 << d;
				w = 1;
			}
			else
				a |= 1 << d,
				b |= 1 << d;
		}
		cout <<1LL * a * b <<"\n";
	}
}
