#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
using namespace std;

using ld = long double;
const char maxN = 10;
int c, s, cc;
ld avg, res;
short a[maxN];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout <<fixed <<setprecision(5);
	int test = 0;
	while(cin >>c >>s)
	{
		cc = c << 1;
		avg = res = 0.0;
		for(int i = 0; i < s; i++)
		{
			cin >>a[i];
			avg += a[i];
		}
		avg /= c;
		for(int i = s; i < cc; i++) a[i] = 0;
		sort(a, a + cc);
		cout <<"Set #" <<++test <<"\n";
		for(int i = 0; i < c; i++)
		{
			cout <<" " <<i <<":";
			if(a[i]) cout <<" " <<a[i];
			if(a[cc - i - 1]) cout <<" " <<a[cc - i - 1];
			res += fabs(a[i] + a[cc - i - 1] - avg);
			cout <<"\n";
		}
		cout <<"IMBALANCE = " <<res <<"\n" <<"\n";
	}
}
