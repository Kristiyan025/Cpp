#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
using namespace std;

int n, k, x, l, r;
int a[100000];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >>t;
	while(t--)
	{
		cin >>n >>k >>x;
		if(x > k)
		{
			cout <<"-1\n";
			continue;
		}
		for(int i = 0; i < x; i++)
			a[i] = i;
		for(int i = x; i < k; i++)
			a[i] = x - 1;
		for(l = 0, r = k; r < n; l++, r++)
			a[r] = a[l];
		for(int i = 0; i < n; i++)
			cout <<a[i] <<" ";
		cout <<"\n";
	}
}
