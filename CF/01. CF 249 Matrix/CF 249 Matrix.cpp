#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
using namespace std;

int n, m, dn, dm;
inline int g(int n)
{ return n ^ (n >> 1);}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	cin >>n >>m;
	dn = 1 << n;
	dm = 1 << m;
	for(int i = 0; i < dn; i++)
	{
		for(int j = 0; j < dm; j++)
			cout <<(g(i)<< m | g(j)) <<" ";
		cout <<"\n";
	}
}
